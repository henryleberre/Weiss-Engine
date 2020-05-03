#pragma once

#include "Device.h"
#include "RenderTarget.h"
#include "CommandAllocator.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	typedef D3D12ObjectWrapper<ID3D12GraphicsCommandList> D3D12CommandListObjectWrapper;

	class D3D12CommandList : public D3D12CommandListObjectWrapper {
	public:
		D3D12CommandList() {  }

		D3D12CommandList(D3D12DeviceObjectWrapper& pDevice,
						 D3D12CommandAllocatorObjectWrapper& pCommandAllocator,
						 const D3D12_COMMAND_LIST_TYPE& type);

		~D3D12CommandList() = default;

		D3D12CommandList& operator=(D3D12CommandList&& other) noexcept;

		void Close();

		void Reset(D3D12CommandAllocatorObjectWrapper& pCommandAllocator) const;

		void TransitionResource(ID3D12Resource* pResource, const D3D12_RESOURCE_STATES& before, const D3D12_RESOURCE_STATES& after);
	};

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS