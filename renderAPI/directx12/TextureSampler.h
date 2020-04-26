#pragma once

#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	class D3D12TextureSampler {
	private:
		D3D12_STATIC_SAMPLER_DESC m_samplerDesc;

	public:
		D3D12TextureSampler() = default;

		D3D12TextureSampler(const TextureFilter& filter);

		D3D12_STATIC_SAMPLER_DESC GetSamplerDesc() const noexcept;
	};

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS