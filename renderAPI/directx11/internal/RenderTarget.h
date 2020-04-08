#pragma once

#include "SwapChain.h"
#include "../../common/Include.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef DirectX11ObjectWrapper<ID3D11RenderTargetView> DirectX11RenderTargetbjectWrapper;

class DirectX11RenderTarget : public DirectX11RenderTargetbjectWrapper {
public:
	DirectX11RenderTarget() {  }

	DirectX11RenderTarget(DirectX11DeviceObjectWrapper& pDevice, DirectX11SwapChainObjectWrapper& pSwapChain)
	{
		Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;

		if (FAILED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer)))
			throw std::runtime_error("[DIRECTX 11] Could Not Get BackBuffer");

		if (FAILED(pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &this->m_pObject)))
			throw std::runtime_error("[DIRECTX 11] Could Not Create RenderTargetView");
	}

	void operator=(DirectX11RenderTarget&& other) noexcept
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = nullptr;
	}

	void SetCurrent(DirectX11DeviceContextObjectWrapper& pDeviceContext) const noexcept
	{
		pDeviceContext->OMSetRenderTargets(1u, &this->m_pObject, NULL);
	}
};

#endif // __WEISS__OS_WINDOWS