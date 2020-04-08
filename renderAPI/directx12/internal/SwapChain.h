#pragma once

#include "Device.h"
#include "CommandQueue.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef DirectX12ObjectWrapper<IDXGISwapChain3> DirectX12SwapChainObjectWrapper;

class DirectX12SwapChain : public DirectX12SwapChainObjectWrapper {
public:
	DirectX12SwapChain() {  }

	DirectX12SwapChain(DirectX12DeviceObjectWrapper&       pDevice,
					   DirectX12CommandQueueObjectWrapper& pCommandQueue,
					   const Window* pWindow, const UINT bufferCount);

	void operator=(DirectX12SwapChain&& other) noexcept;
	
	void Present() const;
};

#endif // __WEISS__OS_WINDOWS