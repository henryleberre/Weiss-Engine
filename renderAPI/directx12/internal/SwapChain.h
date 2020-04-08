#pragma once

#include "Device.h"
#include "CommandQueue.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef DirectX12ObjectWrapper<IDXGISwapChain3> DirectX12SwapChainObjectWrapper;

class DirectX12SwapChain : public DirectX12SwapChainObjectWrapper {
public:
	DirectX12SwapChain() {  }

	DirectX12SwapChain(const DirectX12DeviceObjectWrapper&       pDevice,
					   const DirectX12CommandQueueObjectWrapper& pCommandQueue,
					   const Window* pWindow, const UINT bufferCount);

	void Present() const;
};

#endif // __WEISS__OS_WINDOWS