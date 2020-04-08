#include "CommandList.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12CommandList::DirectX12CommandList(DirectX12DeviceObjectWrapper& pDevice,
										   DirectX12CommandAllocatorObjectWrapper& pCommandAllocator,
										   const D3D12_COMMAND_LIST_TYPE& type)
{
	if (pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, pCommandAllocator, NULL, IID_PPV_ARGS(&this->m_pObject)) != S_OK)
		throw std::runtime_error("[DIRECTX 12] Failed To Create Command List");
}

void DirectX12CommandList::Close() const
{
	if (FAILED(this->m_pObject->Close()))
		throw std::runtime_error("[DIRECTX 12] Failed To Close Command List");
}

void DirectX12CommandList::Reset(DirectX12CommandAllocatorObjectWrapper& pCommandAllocator) const
{
	if (FAILED(this->m_pObject->Reset(pCommandAllocator, NULL)))
		throw std::runtime_error("[DIRECTX 12] Failed To Reset Command List");
}

void DirectX12CommandList::TransitionResource(ID3D12Resource* pResource, const D3D12_RESOURCE_STATES& before, const D3D12_RESOURCE_STATES& after)
{
	this->m_pObject->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pResource, before, after));
}


#endif // __WEISS__OS_WINDOWS