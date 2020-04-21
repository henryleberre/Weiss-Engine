#include "RenderTarget.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	D3D12RenderTarget::D3D12RenderTarget(D3D12DeviceObjectWrapper& pDevice,
										 D3D12SwapChainObjectWrapper& pSwapChain,
										 D3D12DescriptorHeapObjectWrapper& pDescriptorHeap,
										 const CD3DX12_CPU_DESCRIPTOR_HANDLE& rtvHandle,
										 const uint16_t frameIndex)
	{
		if (pSwapChain->GetBuffer(frameIndex, IID_PPV_ARGS(&this->m_pObject)) != S_OK)
			throw std::runtime_error("[DIRECTX 12] Failed To Get Back Buffer");

		pDevice->CreateRenderTargetView(this->m_pObject, nullptr, rtvHandle);
	}

	void D3D12RenderTarget::operator=(D3D12RenderTarget&& other) noexcept
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = nullptr;
	}

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS