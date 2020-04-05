#pragma once

#include "Device.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX12CommandQueue {
private:
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_commandQueue;

public:
	DirectX12CommandQueue(const std::shared_ptr<DirectX12Device>& pDevice, const D3D12_COMMAND_LIST_TYPE& type);

	operator Microsoft::WRL::ComPtr<ID3D12CommandQueue>() const noexcept;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> Get() const noexcept;
};

#endif // __WEISS__OS_WINDOWS