#include "RenderTarget.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12RenderTarget::DirectX12RenderTarget(DirectX12DeviceObjectWrapper& pDevice,
											 DirectX12SwapChainObjectWrapper& pSwapChain,
											 DirectX12DescriptorHeapObjectWrapper& pDescriptorHeap,
											 const CD3DX12_CPU_DESCRIPTOR_HANDLE& rtvHandle,
											 const uint16_t frameIndex)
{
	if (pSwapChain->GetBuffer(frameIndex, IID_PPV_ARGS(&this->m_pObject)) != S_OK)
		throw std::runtime_error("[DIRECTX 12] Failed To Get Back Buffer");

	pDevice->CreateRenderTargetView(this->m_pObject, nullptr, rtvHandle);
}

void DirectX12RenderTarget::operator=(DirectX12RenderTarget&& other) noexcept
{
	this->m_pObject = other.m_pObject;
	other.m_pObject = nullptr;
}

#endif // __WEISS__OS_WINDOWS