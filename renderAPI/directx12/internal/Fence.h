#pragma once

#include "Device.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef DirectX12ObjectWrapper<ID3D12Fence> DirectX12FenceObjectWrapper;

class DirectX12Fence : public DirectX12FenceObjectWrapper {
	HANDLE m_fenceEvent = nullptr;

	bool bRealFence = false;

public:
	DirectX12Fence() = default;

	DirectX12Fence(DirectX12DeviceObjectWrapper& pDevice, const UINT64 initialValue, const D3D12_FENCE_FLAGS flags);
	~DirectX12Fence();

	void operator=(DirectX12Fence&& other) noexcept;

	HANDLE GetEvent() const noexcept;
};

#endif // __WEISS__OS_WINDOWS