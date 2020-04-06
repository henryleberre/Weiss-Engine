#include "CommandList.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12CommandList::DirectX12CommandList(const std::shared_ptr<DirectX12Device>& pDevice,
										   const std::shared_ptr<DirectX12CommandAllocator>& pCommandAllocator,
										   const D3D12_COMMAND_LIST_TYPE& type)
{
	if (pDevice->Get()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, pCommandAllocator->Get().Get(), NULL, IID_PPV_ARGS(&this->m_pCommandList)) != S_OK)
		throw std::runtime_error("[DIRECTX 12] Failed To Create Command List");
}

void DirectX12CommandList::Reset(const std::shared_ptr<DirectX12CommandAllocator>& pCommandAllocator) const
{
	if (this->m_pCommandList->Reset(pCommandAllocator->Get().Get(), NULL) != S_OK)
		throw std::runtime_error("[DIRECTX 12] Failed To Reset Command List");
}

Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> DirectX12CommandList::Get() const noexcept
{
	return this->m_pCommandList;
}

DirectX12CommandList::operator Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>() const noexcept
{
	return this->m_pCommandList;
}

#endif // __WEISS__OS_WINDOWS