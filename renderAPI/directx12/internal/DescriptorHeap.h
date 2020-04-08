#pragma once

#include "Device.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef DirectX12ObjectWrapper<ID3D12DescriptorHeap> DirectX12DescriptorHeapObjectWrapper;

class DirectX12DescriptorHeap : public DirectX12DescriptorHeapObjectWrapper {
public:
	DirectX12DescriptorHeap() {  }

	DirectX12DescriptorHeap(DirectX12DeviceObjectWrapper& pDevice, const D3D12_DESCRIPTOR_HEAP_TYPE type, const uint32_t numDescriptors);
};

#endif // __WEISS__OS_WINDOWS