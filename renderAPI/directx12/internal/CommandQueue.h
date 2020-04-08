#pragma once

#include "Device.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef DirectX12ObjectWrapper<ID3D12CommandQueue> DirectX12CommandQueueObjectWrapper;

class DirectX12CommandQueue : public DirectX12CommandQueueObjectWrapper {
public:
	DirectX12CommandQueue() {  }

	DirectX12CommandQueue(DirectX12DeviceObjectWrapper& pDevice, const D3D12_COMMAND_LIST_TYPE& type);

	void operator=(DirectX12CommandQueue&& other) noexcept;
};

#endif // __WEISS__OS_WINDOWS