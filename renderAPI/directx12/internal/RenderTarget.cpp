#include "RenderTarget.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12RenderTarget::DirectX12RenderTarget(const std::shared_ptr<DirectX12Device>& pDevice,
											 const std::shared_ptr<DirectX12SwapChain>& pSwapChain,
											 const std::shared_ptr<DirectX12DescriptorHeap>& pDescriptorHeap,
											 const CD3DX12_CPU_DESCRIPTOR_HANDLE& rtvHandle,
											 const uint16_t frameIndex)
{
	if (pSwapChain->Get()->GetBuffer(frameIndex, IID_PPV_ARGS(&this->m_pRenderTarget)) != S_OK)
		throw std::runtime_error("[DIRECTX 12] Failed To Get Back Buffer");

	pDevice->Get()->CreateRenderTargetView(this->m_pRenderTarget.Get(), nullptr, rtvHandle);
}

Microsoft::WRL::ComPtr<ID3D12Resource> DirectX12RenderTarget::Get() const noexcept { return this->m_pRenderTarget; }

DirectX12RenderTarget::operator Microsoft::WRL::ComPtr<ID3D12Resource>() const noexcept { return this->m_pRenderTarget; }

#endif // __WEISS__OS_WINDOWS