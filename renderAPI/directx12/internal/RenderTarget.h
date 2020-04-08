#pragma once

#include "Device.h"
#include "SwapChain.h"
#include "DescriptorHeap.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef DirectX12ObjectWrapper<ID3D12Resource> DirectX12RenderTargetObjectWrapper;

class DirectX12RenderTarget : public DirectX12RenderTargetObjectWrapper {
public:
	DirectX12RenderTarget() {  }

	DirectX12RenderTarget(DirectX12DeviceObjectWrapper&         pDevice,
						  DirectX12SwapChainObjectWrapper&      pSwapChain,
						  DirectX12DescriptorHeapObjectWrapper& pDescriptorHeap,
						  const CD3DX12_CPU_DESCRIPTOR_HANDLE& rtvHandle,
						  const uint16_t frameIndex);

	void operator=(DirectX12RenderTarget&& other) noexcept;
};

#endif // __WEISS__OS_WINDOWS