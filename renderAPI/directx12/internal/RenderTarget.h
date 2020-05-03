#pragma once

#include "Device.h"
#include "SwapChain.h"
#include "DescriptorHeap.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	typedef D3D12ObjectWrapper<ID3D12Resource> D3D12RenderTargetObjectWrapper;

	class D3D12RenderTarget : public D3D12RenderTargetObjectWrapper {
	public:
		D3D12RenderTarget() {  }

		D3D12RenderTarget(D3D12DeviceObjectWrapper&         pDevice,
						  D3D12SwapChainObjectWrapper&      pSwapChain,
						  D3D12DescriptorHeapObjectWrapper& pDescriptorHeap,
						  const CD3DX12_CPU_DESCRIPTOR_HANDLE& rtvHandle,
						  const uint16_t frameIndex);

		D3D12RenderTarget& operator=(D3D12RenderTarget&& other) noexcept;
	};

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS