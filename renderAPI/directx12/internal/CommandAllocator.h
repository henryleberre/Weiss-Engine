#pragma once

#include "Device.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef DirectX12ObjectWrapper<ID3D12CommandAllocator> DirectX12CommandAllocatorObjectWrapper;

class DirectX12CommandAllocator : public DirectX12CommandAllocatorObjectWrapper {
public:
	DirectX12CommandAllocator() {  }

	DirectX12CommandAllocator(DirectX12DeviceObjectWrapper& pDevice, const D3D12_COMMAND_LIST_TYPE& type);

	void operator=(DirectX12CommandAllocator&& other) noexcept;

	void Reset() const;
};

#endif // __WEISS__OS_WINDOWS