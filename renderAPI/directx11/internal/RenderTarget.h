#pragma once

#include "SwapChain.h"
#include "../../common/Include.h"
#include "../../../common/Include.h"

typedef DirectX11ObjectWrapper<ID3D11RenderTargetView> DirectX11RenderTargetbjectWrapper;

class DirectX11RenderTarget : public DirectX11RenderTargetbjectWrapper {
public:
	DirectX11RenderTarget() {  }

	DirectX11RenderTarget(DirectX11DeviceObjectWrapper& pDevice, DirectX11SwapChainObjectWrapper& pSwapChain)
	{
		Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;

		if (pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer) != S_OK)
			throw std::runtime_error("Could Not Get BackBuffer");

		if (pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &this->m_pObject) != S_OK)
			throw std::runtime_error("Could Not Create RenderTargetView");
	}

	void SetCurrent(DirectX11DeviceContextObjectWrapper& pDeviceContext) const noexcept
	{
		pDeviceContext->OMSetRenderTargets(1u, &this->m_pObject, NULL);
	}
};