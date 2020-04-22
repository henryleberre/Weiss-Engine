#pragma once

#include "Device.h"
#include "CommandQueue.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	typedef D3D12ObjectWrapper<IDXGISwapChain3> D3D12SwapChainObjectWrapper;

	class D3D12SwapChain : public D3D12SwapChainObjectWrapper {
	public:
		D3D12SwapChain() {  }

		D3D12SwapChain(D3D12DeviceObjectWrapper& pDevice,
						   D3D12CommandQueueObjectWrapper& pCommandQueue,
						   const Window* pWindow, const uint16_t maxFps, const UINT bufferCount);

		void operator=(D3D12SwapChain&& other) noexcept;

		void Present(const bool vSync) const;
	};

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS