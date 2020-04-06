#pragma once

#include "Device.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX12Fence {
private:
	Microsoft::WRL::ComPtr<ID3D12Fence> m_pFence;

	HANDLE m_fenceEvent;

public:
	DirectX12Fence(const std::shared_ptr<DirectX12Device>& pDevice, const UINT64 initialValue, const D3D12_FENCE_FLAGS flags);

	HANDLE GetEvent() const noexcept;

	Microsoft::WRL::ComPtr<ID3D12Fence> Get() const noexcept;

	operator Microsoft::WRL::ComPtr<ID3D12Fence>() const noexcept;
};

#endif // __WEISS__OS_WINDOWS