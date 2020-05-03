#pragma once

#include "Device.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	typedef D3D12ObjectWrapper<ID3D12DescriptorHeap> D3D12DescriptorHeapObjectWrapper;

	class D3D12DescriptorHeap : public D3D12DescriptorHeapObjectWrapper {
	public:
		D3D12DescriptorHeap() {  }

		D3D12DescriptorHeap(D3D12DeviceObjectWrapper& pDevice, const D3D12_DESCRIPTOR_HEAP_TYPE type,
								const uint32_t numDescriptors, const D3D12_DESCRIPTOR_HEAP_FLAGS& flags = D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_NONE);

		D3D12DescriptorHeap& operator=(D3D12DescriptorHeap&& other) noexcept;
	};

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS