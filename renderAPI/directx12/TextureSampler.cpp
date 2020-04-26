#include "TextureSampler.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	D3D12TextureSampler::D3D12TextureSampler(const TextureFilter& filter)
	{
		switch (filter)
		{
		case TextureFilter::POINT:
			this->m_samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
			break;
		case TextureFilter::BILINEAR:
			this->m_samplerDesc.Filter = D3D12_FILTER_MIN_MAG_LINEAR_MIP_POINT;
			break;
		case TextureFilter::TRILINEAR:
			this->m_samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
			break;
		default:
			throw std::runtime_error("[DIRECTX 12] Your Filtering Method Is Not Supported");
		}
		 
		this->m_samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		this->m_samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		this->m_samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		this->m_samplerDesc.MipLODBias = 0;
		this->m_samplerDesc.MaxAnisotropy  = D3D12_MAX_MAXANISOTROPY;
		this->m_samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
		this->m_samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
		this->m_samplerDesc.MinLOD = 0.0f;
		this->m_samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
		this->m_samplerDesc.ShaderRegister = 0;
		this->m_samplerDesc.RegisterSpace  = 0;
		this->m_samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	}

	D3D12_STATIC_SAMPLER_DESC D3D12TextureSampler::GetSamplerDesc() const noexcept
	{
		return this->m_samplerDesc;
	}

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS