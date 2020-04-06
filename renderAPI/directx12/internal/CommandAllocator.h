#pragma once

#include "Device.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX12CommandAllocator {
private:
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_pCommandAllocator;

public:
	DirectX12CommandAllocator(const std::shared_ptr<DirectX12Device>& pDevice, const D3D12_COMMAND_LIST_TYPE& type);

	void Reset() const;

	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> Get() const noexcept;

	operator Microsoft::WRL::ComPtr<ID3D12CommandAllocator>() const noexcept;
};

#endif // __WEISS__OS_WINDOWS