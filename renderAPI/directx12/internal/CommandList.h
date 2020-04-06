#pragma once

#include "Device.h"
#include "CommandAllocator.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX12CommandList {
private:
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_pCommandList;

public:
	DirectX12CommandList(const std::shared_ptr<DirectX12Device>& pDevice,
						 const std::shared_ptr<DirectX12CommandAllocator>& pCommandAllocator,
						 const D3D12_COMMAND_LIST_TYPE& type);

	void Reset(const std::shared_ptr<DirectX12CommandAllocator>& pCommandAllocator) const;

	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> Get() const noexcept;

	operator Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>() const noexcept;
};

#endif // __WEISS__OS_WINDOWS