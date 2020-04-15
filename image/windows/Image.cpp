#include "Image.h"

WindowsImage::WindowsImage() {  }

WindowsImage::WindowsImage(WindowsImage&& other)
{
    this->m_width = other.m_width;
    this->m_height = other.m_height;
    this->m_nPixels = other.m_nPixels;

    this->m_buff = std::move(other.m_buff);
}

WindowsImage::WindowsImage(const WindowsImage& other)
{
    this->m_width = other.m_width;
    this->m_height = other.m_height;
    this->m_nPixels = other.m_nPixels;

    const size_t bufferSize = this->m_nPixels * sizeof(Coloru8);
    this->m_buff = std::make_unique<Coloru8[]>(bufferSize);
    std::memcpy(this->m_buff.get(), other.m_buff.get(), bufferSize);
}

WindowsImage::WindowsImage(const char* filename)
{
    Microsoft::WRL::ComPtr<IWICBitmapSource>      decodedConvertedFrame;
    Microsoft::WRL::ComPtr<IWICBitmapDecoder>     bitmapDecoder;
    Microsoft::WRL::ComPtr<IWICImagingFactory>    factory;
    Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frameDecoder;

    if (FAILED(CoInitialize(NULL)))
        throw std::runtime_error("[COM] Failed To Init COM");

    if (FAILED(CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&factory))))
        throw std::runtime_error("[WIC] Could Not Create IWICImagingFactory");

    // Convert from char* to wchar_t*
    const size_t length = mbstowcs(nullptr, filename, 0);
    wchar_t* filenameW = new wchar_t[length];
    mbstowcs(filenameW, filename, length);

    if (FAILED(factory->CreateDecoderFromFilename(filenameW, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &bitmapDecoder)))
        throw std::runtime_error("[WIC] Could Not Read / Open Image");

    if (FAILED(bitmapDecoder->GetFrame(0, &frameDecoder)))
        throw std::runtime_error("[WIC] Could Not Get First Frame Of Image");

    if (FAILED(frameDecoder->GetSize((UINT*)&this->m_width, (UINT*)&this->m_height)))
        throw std::runtime_error("[WIC] Could Not Get Image Width/Height");

    this->m_nPixels = this->m_width * this->m_height;

    if (FAILED(WICConvertBitmapSource(GUID_WICPixelFormat32bppRGBA, frameDecoder.Get(), &decodedConvertedFrame)))
        throw std::runtime_error("[WIC] Could Not Create Bitmap Converter");

    this->m_buff = std::make_unique<Coloru8[]>(this->m_nPixels * sizeof(Coloru8));

    const WICRect sampleRect{ 0, 0, this->m_width, this->m_height };

    if (FAILED(decodedConvertedFrame->CopyPixels(&sampleRect, this->m_width * sizeof(Coloru8), this->m_nPixels * sizeof(Coloru8), (BYTE*)this->m_buff.get())))
        throw std::runtime_error("[WIC] Could Not Copy Pixels From Bitmap");
}

WindowsImage::WindowsImage(const uint16_t width, const uint16_t height, const Coloru8& fillColor)
{
    this->m_width = width;
    this->m_height = height;
    this->m_nPixels = this->m_width * this->m_height;

    const size_t bufferSize = this->m_nPixels * sizeof(Coloru8);
    this->m_buff = std::make_unique<Coloru8[]>(bufferSize);

    std::fill_n(this->m_buff.get(), this->m_nPixels, fillColor);
}

void WindowsImage::Write(const char* filename) const
{
    if (FAILED(CoInitialize(NULL)))
        throw std::runtime_error("[COM] Failed To Init COM");

    Microsoft::WRL::ComPtr<IWICImagingFactory>    factory;
    Microsoft::WRL::ComPtr<IWICBitmapEncoder>     bitmapEncoder;
    Microsoft::WRL::ComPtr<IWICBitmapFrameEncode> bitmapFrame;
    Microsoft::WRL::ComPtr<IWICStream>            outputStream;

    if (FAILED(CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&factory))))
        throw std::runtime_error("[WIC] Could Not Create IWICImagingFactory");

    if (FAILED(factory->CreateStream(&outputStream)))
        throw std::runtime_error("[WIC] Failed To Create Output Stream");

    // Convert from char* to wchar_t*
    const size_t length = mbstowcs(nullptr, filename, 0);
    wchar_t* filenameW = new wchar_t[length];
    mbstowcs(filenameW, filename, length);
    if (FAILED(outputStream->InitializeFromFilename(filenameW, GENERIC_WRITE)))
        throw std::runtime_error("[WIC] Failed To Initialize Output Stream From Filename");

    char fileExtension[10u]; // assumes the extension has less than 10-1=9 characters
    std::memset(fileExtension, 0u, 10);
    const size_t offset = std::string_view(filename).find_last_of('.');
    std::memcpy(fileExtension, filename + offset, strlen(filename) - offset + 1);

    // This should be fine thanks to sso (small string optimization)
    const std::unordered_map<std::string, REFGUID> extensionToREFUGUIDMap{
        { ".bmp", GUID_ContainerFormatBmp  }, { ".png",  GUID_ContainerFormatPng  },
        { ".ico", GUID_ContainerFormatIco  }, { ".jpeg", GUID_ContainerFormatJpeg },
        { ".jpg", GUID_ContainerFormatJpeg }, { ".tiff", GUID_ContainerFormatTiff },
        { ".gif", GUID_ContainerFormatGif  }, { ".wmp",  GUID_ContainerFormatWmp  }
    };

    if (extensionToREFUGUIDMap.find(fileExtension) == std::end(extensionToREFUGUIDMap))
        throw std::runtime_error("[WIC] Your Image Extension Is Not Supported");

    if (FAILED(factory->CreateEncoder(extensionToREFUGUIDMap.at(fileExtension), NULL, &bitmapEncoder)))
        throw std::runtime_error("[WIC] Failed To Create Bitmap Encoder");

    if (FAILED(bitmapEncoder->Initialize(outputStream.Get(), WICBitmapEncoderNoCache)))
        throw std::runtime_error("[WIC] Failed To Initialize Bitmap ");

    if (FAILED(bitmapEncoder->CreateNewFrame(&bitmapFrame, NULL)))
        throw std::runtime_error("[WIC] Failed To Create A New Frame");

    if (FAILED(bitmapFrame->Initialize(NULL)))
        throw std::runtime_error("[WIC] Failed To Initialize A Bitmap's Frame");

    if (FAILED(bitmapFrame->SetSize(this->m_width, this->m_height)))
        throw std::runtime_error("[WIC] Failed To Set A Bitmap's Frame's Size");

    WICPixelFormatGUID pixelFormat = GUID_WICPixelFormat32bppBGRA;
    if (FAILED(bitmapFrame->SetPixelFormat(&pixelFormat)))
        throw std::runtime_error("[WIC] Failed To Set Pixel Format On A Bitmap Frame's");

    if (!IsEqualGUID(pixelFormat, GUID_WICPixelFormat32bppBGRA))
        throw std::runtime_error("[WIC] The Requested Pixel Format Is Not Supported");

    const UINT stride     = this->m_width   * sizeof(Coloru8);
    const UINT bufferSize = this->m_nPixels * sizeof(Coloru8);
    if (FAILED(bitmapFrame->WritePixels(this->m_height, stride, bufferSize, (BYTE*)this->m_buff.get())))
        throw std::runtime_error("[WIC] Failed To Write Pixels To A Bitmap's Frame");

    if (FAILED(bitmapFrame->Commit()))
        throw std::runtime_error("[WIC] Failed To Commit A Bitmap's Frame");

    if (FAILED(bitmapEncoder->Commit()))
        throw std::runtime_error("[WIC] Failed To Commit Bitmap Encoder");
}