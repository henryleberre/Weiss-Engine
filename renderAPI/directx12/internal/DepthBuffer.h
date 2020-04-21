#pragma once

#include "Device.h"
#include "CommandList.h"
#include "../../../window/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	class D3D12DepthBuffer {
	private:
		D3D12ObjectWrapper<ID3D12Resource>       m_pDepthStencilBuffer;
		D3D12ObjectWrapper<ID3D12DescriptorHeap> m_pDescriptorHeap;

		CD3DX12_CPU_DESCRIPTOR_HANDLE m_dsvHandle;

	public:
		D3D12DepthBuffer() {  }

		D3D12DepthBuffer(D3D12Device& pDevice, Window* pWindow);

		void Clear(D3D12CommandListObjectWrapper& pCommandList);

		operator CD3DX12_CPU_DESCRIPTOR_HANDLE* () noexcept;
	};

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS