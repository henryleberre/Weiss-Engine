#include "Image.h"

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
    wchar_t* filenameW  = new wchar_t[length];
    mbstowcs(filenameW, filename, length);

    if (FAILED(factory->CreateDecoderFromFilename(filenameW, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &bitmapDecoder)))
        throw std::runtime_error("[WIC] Could Not Read / Open Image");

    if (bitmapDecoder->GetFrame(0, &frameDecoder) != S_OK)
        throw std::runtime_error("[WIC] Could Not Get First Frame Of Image");

    if (frameDecoder->GetSize((UINT*)&this->m_width, (UINT*)&this->m_height) != S_OK)
        throw std::runtime_error("[WIC] Could Not Get Image Width/Height");

    this->m_nPixels = this->m_width * this->m_height;

    if (WICConvertBitmapSource(GUID_WICPixelFormat32bppRGBA, frameDecoder.Get(), &decodedConvertedFrame) != S_OK)
        throw std::runtime_error("[WIC] Could Not Create Bitmap Converter");

    this->m_buff = std::make_unique<Coloru8[]>(this->m_nPixels * sizeof(Coloru8));

    const WICRect sampleRect{ 0, 0, this->m_width, this->m_height };

    if (decodedConvertedFrame->CopyPixels(&sampleRect, this->m_width * sizeof(Coloru8), this->m_nPixels * sizeof(Coloru8), (BYTE*)this->m_buff.get()) != S_OK)
        throw std::runtime_error("[WIC] Could Not Copy Pixels From Bitmap");
}