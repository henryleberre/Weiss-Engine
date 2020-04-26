#include "TextureSampler.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D11    {

    D3D11TextureSampler::D3D11TextureSampler(D3D11DeviceObjectWrapper& pDevice,
                                             D3D11DeviceContextObjectWrapper* pDeviceContext,
                                             const TextureFilter& filter, const size_t slot)
        : m_pDeviceContext(pDeviceContext), m_slot(slot)
    {
        D3D11_FILTER filterD3D11;

        switch (filter)
        {
        case TextureFilter::POINT:
            filterD3D11 = D3D11_FILTER_MIN_MAG_MIP_POINT;
            break;
        case TextureFilter::BILINEAR:
            filterD3D11 = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
            break;
        case TextureFilter::TRILINEAR:
            filterD3D11 = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
            break;
        default:
            throw std::runtime_error("[DIRECTX 11] Your Filtering Method Is Not Supported");
        }

        D3D11_SAMPLER_DESC samplerDescriptor;
        samplerDescriptor.Filter   = filterD3D11;
        samplerDescriptor.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDescriptor.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDescriptor.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDescriptor.MaxAnisotropy = D3D11_MAX_MAXANISOTROPY;
        samplerDescriptor.ComparisonFunc = D3D11_COMPARISON_NEVER;
        samplerDescriptor.MipLODBias = 0.0f;
        samplerDescriptor.MinLOD = 0.0f;
        samplerDescriptor.MaxLOD = D3D11_FLOAT32_MAX;

        if (FAILED(pDevice->CreateSamplerState(&samplerDescriptor, &this->m_pObject)))
            throw std::runtime_error("[DIRECTX 11] Failed To Create Sampler State");
	}

    void D3D11TextureSampler::Bind() const noexcept
    {
        (*this->m_pDeviceContext)->VSSetSamplers(this->m_slot, 1u, &this->m_pObject);
        (*this->m_pDeviceContext)->PSSetSamplers(this->m_slot, 1u, &this->m_pObject);
    }

}; // D3D11
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS