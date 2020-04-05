#include "CommandAllocator.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12CommandAllocator::DirectX12CommandAllocator(const std::shared_ptr<DirectX12Device>& pDevice, const D3D12_COMMAND_LIST_TYPE& type)
{
	if (pDevice->Get()->CreateCommandAllocator(type, IID_PPV_ARGS(&this->m_pCommandAllocator)) != S_OK)
		throw std::runtime_error("[DIRECTX 12] Could Not Create Command Allocator");
}

Microsoft::WRL::ComPtr<ID3D12CommandAllocator> DirectX12CommandAllocator::Get() const noexcept
{
	return this->m_pCommandAllocator;
}

DirectX12CommandAllocator::operator Microsoft::WRL::ComPtr<ID3D12CommandAllocator>() const noexcept
{
	return this->m_pCommandAllocator;
}

#endif // __WEISS__OS_WINDOWS