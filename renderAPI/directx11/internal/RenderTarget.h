#pragma once

#include "SwapChain.h"
#include "../../common/Include.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D11    {

	typedef D3D11ObjectWrapper<ID3D11RenderTargetView> D3D11RenderTargetbjectWrapper;

	class D3D11RenderTarget : public D3D11RenderTargetbjectWrapper {
	public:
		D3D11RenderTarget() = default;

		D3D11RenderTarget(D3D11DeviceObjectWrapper& pDevice, D3D11SwapChainObjectWrapper& pSwapChain);

		void operator=(D3D11RenderTarget&& other) noexcept;

		void SetCurrent(D3D11DeviceContextObjectWrapper& pDeviceContext) const noexcept;
	};

}; // D3D11
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS