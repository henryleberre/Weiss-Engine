#pragma once

#include "Device.h"
#include "CommandList.h"
#include "../../../window/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX12DepthBuffer {
private:
	DirectX12ObjectWrapper<ID3D12Resource>       m_pDepthStencilBuffer;
	DirectX12ObjectWrapper<ID3D12DescriptorHeap> m_pDescriptorHeap;

	CD3DX12_CPU_DESCRIPTOR_HANDLE m_dsvHandle;

public:
	DirectX12DepthBuffer() {  }

	DirectX12DepthBuffer(DirectX12Device& pDevice, Window* pWindow);

	void Clear(DirectX12CommandListObjectWrapper& pCommandList);

	operator CD3DX12_CPU_DESCRIPTOR_HANDLE* () noexcept;
};

#endif // __WEISS__OS_WINDOWS