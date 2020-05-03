#pragma once

#include "Device.h"
#include "../../common/Include.h"
#include "../../../window/Include.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D11    {

	typedef D3D11ObjectWrapper<IDXGISwapChain> D3D11SwapChainObjectWrapper;

	class D3D11SwapChain : public D3D11SwapChainObjectWrapper {
	public:
		D3D11SwapChain() = default;

		D3D11SwapChain(D3D11DeviceObjectWrapper& pDevice, Window* pWindow);

		D3D11SwapChain& operator=(D3D11SwapChain&& other) noexcept;

		void Present(const bool vSync);
	};

}; // D3D11
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS