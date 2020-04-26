#pragma once

#include "Device.h"
#include "CommandList.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	typedef D3D12ObjectWrapper<ID3D12Resource> D3D12CommittedResourceObjectWrapper;

	class D3D12CommittedResource : public D3D12CommittedResourceObjectWrapper {
	private:
		D3D12_RESOURCE_STATES m_originalState = D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_COMMON;
		D3D12_RESOURCE_STATES m_currentState  = D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_COMMON;

	public:
		D3D12CommittedResource() = default;

		D3D12CommittedResource(D3D12DeviceObjectWrapper&    pDevice, const D3D12_HEAP_TYPE& heapType,
							   const D3D12_HEAP_FLAGS&      flags,   const D3D12_RESOURCE_DESC* descPtr,
							   const D3D12_RESOURCE_STATES& states,  const char* name = "(PLACEHOLDER NAME)");

		void operator=(D3D12CommittedResource&& other) noexcept;

		inline void TransitionTo  (D3D12CommandListObjectWrapper& pCommandList, const D3D12_RESOURCE_STATES& state) noexcept;
		inline void TransitionBack(D3D12CommandListObjectWrapper& pCommandList) noexcept;
	};

	inline void D3D12CommittedResource::TransitionTo(D3D12CommandListObjectWrapper& pCommandList, const D3D12_RESOURCE_STATES& state) noexcept
	{
		pCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(this->m_pObject, this->m_currentState, state));
	
		this->m_currentState = state;
	}

	inline void D3D12CommittedResource::TransitionBack(D3D12CommandListObjectWrapper& pCommandList) noexcept
	{
		this->TransitionTo(pCommandList, this->m_originalState);
	}

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS