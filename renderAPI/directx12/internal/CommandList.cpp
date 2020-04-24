#include "CommandList.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	D3D12CommandList::D3D12CommandList(D3D12DeviceObjectWrapper& pDevice,
									   D3D12CommandAllocatorObjectWrapper& pCommandAllocator,
									   const D3D12_COMMAND_LIST_TYPE& type)
	{
		if (FAILED(pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, pCommandAllocator, NULL, IID_PPV_ARGS(&this->m_pObject))))
			throw std::runtime_error("[DIRECTX 12] Failed To Create Command List");
	}

	void D3D12CommandList::operator=(D3D12CommandList&& other) noexcept
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = nullptr;
	}

	void D3D12CommandList::Close()
	{
		if (FAILED(this->m_pObject->Close()))
			throw std::runtime_error("[DIRECTX 12] Failed To Close Command List");
	}

	void D3D12CommandList::Reset(D3D12CommandAllocatorObjectWrapper& pCommandAllocator) const
	{
		if (FAILED(this->m_pObject->Reset(pCommandAllocator, NULL)))
			throw std::runtime_error("[DIRECTX 12] Failed To Reset Command List");
	}

	void D3D12CommandList::TransitionResource(ID3D12Resource* pResource, const D3D12_RESOURCE_STATES& before, const D3D12_RESOURCE_STATES& after)
	{
		this->m_pObject->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pResource, before, after));
	}

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS