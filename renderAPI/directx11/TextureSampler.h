#pragma once

#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D11    {

	typedef D3D11ObjectWrapper<ID3D11SamplerState> D3D11SamplerStateObjectWrapper;

	class D3D11TextureSampler : public D3D11SamplerStateObjectWrapper {
	private:
		D3D11DeviceContextObjectWrapper* m_pDeviceContext = nullptr;

		size_t m_slot = 0u;

	public:
		D3D11TextureSampler() = default;

		D3D11TextureSampler(D3D11DeviceObjectWrapper& pDevice,
							D3D11DeviceContextObjectWrapper* pDeviceContext,
							const TextureFilter& filter, const size_t slot);

		void Bind() const noexcept;
	};

}; // D3D11
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS