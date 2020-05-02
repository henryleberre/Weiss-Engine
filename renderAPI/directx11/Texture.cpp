#include "Texture.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D11    {

    D3D11Texture::D3D11Texture(D3D11DeviceObjectWrapper& pDevice,
                               D3D11DeviceContextObjectWrapper* pDeviceContext,
                               const size_t width, const size_t height, const size_t slot, const bool useMipmaps)
        : m_pDeviceContext(pDeviceContext), m_pDevice(&pDevice), m_slot(slot)
    {
        D3D11_TEXTURE2D_DESC texture2DDescriptor = {};
        texture2DDescriptor.Width     = width;
        texture2DDescriptor.Height    = height;
        texture2DDescriptor.MipLevels = useMipmaps ? 0 : 1;
        texture2DDescriptor.ArraySize = 1u;
        texture2DDescriptor.Format    = DXGI_FORMAT_R8G8B8A8_UNORM;
        texture2DDescriptor.SampleDesc.Count   = 1u;
        texture2DDescriptor.SampleDesc.Quality = 0;
        texture2DDescriptor.Usage     = D3D11_USAGE_DEFAULT;
        texture2DDescriptor.BindFlags = useMipmaps ? D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET : D3D11_BIND_SHADER_RESOURCE;
        texture2DDescriptor.MiscFlags = useMipmaps ? D3D11_RESOURCE_MISC_GENERATE_MIPS : 0;

        if (FAILED(pDevice->CreateTexture2D(&texture2DDescriptor, nullptr, &this->m_texture2D)))
            throw std::runtime_error("[DIRECTX 11] Failed To Create Texture");

        D3D11_SHADER_RESOURCE_VIEW_DESC SRVDescriptor = {};
        SRVDescriptor.Format                    = DXGI_FORMAT_R8G8B8A8_UNORM;
        SRVDescriptor.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
        SRVDescriptor.Texture2D.MostDetailedMip = 0;
        SRVDescriptor.Texture2D.MipLevels       = useMipmaps ? -1 : 1;

        if (FAILED(pDevice->CreateShaderResourceView(this->m_texture2D.Get(), &SRVDescriptor, &this->m_pObject)))
            throw std::runtime_error("[DIRECTX 11] Failed To Create Shader Resource View");
	}

    void D3D11Texture::Bind() const noexcept
    {
        (*this->m_pDeviceContext)->VSSetShaderResources(this->m_slot, 1u, &this->m_pObject);
        (*this->m_pDeviceContext)->PSSetShaderResources(this->m_slot, 1u, &this->m_pObject);
    }

	void D3D11Texture::Update(const Image& image)
	{
        D3D11_SUBRESOURCE_DATA* subResourceData = new D3D11_SUBRESOURCE_DATA();
        subResourceData->pSysMem          = static_cast<void*>(image.GetBuffer());
        subResourceData->SysMemPitch      = image.GetWidth() * sizeof(Coloru8);
        subResourceData->SysMemSlicePitch = 0;

        this->m_pDeviceContext->Get()->UpdateSubresource(this->m_texture2D.Get(), 0u, nullptr, subResourceData->pSysMem, subResourceData->SysMemPitch, 0u);

        if (this->m_useMipmaps)
            this->m_pDeviceContext->Get()->GenerateMips(this->m_pObject);
	}

}; // D3D11
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS