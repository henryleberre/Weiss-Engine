#pragma once

#include "Device.h"
#include "RenderTarget.h"
#include "CommandAllocator.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef DirectX12ObjectWrapper<ID3D12GraphicsCommandList> DirectX12CommandListObjectWrapper;

class DirectX12CommandList : public DirectX12CommandListObjectWrapper {
public:
	DirectX12CommandList() {  }

	DirectX12CommandList(DirectX12DeviceObjectWrapper& pDevice,
						 DirectX12CommandAllocatorObjectWrapper& pCommandAllocator,
						 const D3D12_COMMAND_LIST_TYPE& type);

	~DirectX12CommandList() = default;

	void operator=(DirectX12CommandList&& other) noexcept;

	void Close();

	void Reset(DirectX12CommandAllocatorObjectWrapper& pCommandAllocator) const;

	void TransitionResource(ID3D12Resource* pResource, const D3D12_RESOURCE_STATES& before, const D3D12_RESOURCE_STATES& after);
};

#endif // __WEISS__OS_WINDOWS