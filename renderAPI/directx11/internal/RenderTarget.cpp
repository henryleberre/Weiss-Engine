#include "RenderTarget.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D11    {

	D3D11RenderTarget::D3D11RenderTarget(D3D11DeviceObjectWrapper& pDevice, D3D11SwapChainObjectWrapper& pSwapChain)
	{
		Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;

		if (FAILED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer)))
			throw std::runtime_error("[DIRECTX 11] Could Not Get BackBuffer");

		if (FAILED(pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &this->m_pObject)))
			throw std::runtime_error("[DIRECTX 11] Could Not Create RenderTargetView");
	}

	void D3D11RenderTarget::operator=(D3D11RenderTarget&& other) noexcept
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = nullptr;
	}

	void D3D11RenderTarget::SetCurrent(D3D11DeviceContextObjectWrapper& pDeviceContext) const noexcept
	{
		pDeviceContext->OMSetRenderTargets(1u, &this->m_pObject, NULL);
	}

}; // D3D11
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS