#pragma once

#include "RenderTarget.h"
#include "../../common/Include.h"
#include "../../../common/Include.h"

class DirectX11DepthBuffer {
private:
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_pDepthStencilView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_pDepthStencilState;

public:
	DirectX11DepthBuffer() {  }

	DirectX11DepthBuffer(Window* pWindow, DirectX11DeviceObjectWrapper& pDevice)
	{
		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = TRUE;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
		dsDesc.StencilReadMask = 0xFF;
		dsDesc.StencilWriteMask = 0xFF;
		dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		if (FAILED(pDevice->CreateDepthStencilState(&dsDesc, &this->m_pDepthStencilState)))
			throw std::runtime_error("Could Not Create DepthStencilState");

		Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthStencil;
		D3D11_TEXTURE2D_DESC descDepth = {};
		descDepth.Width  = pWindow->GetClientWidth();
		descDepth.Height = pWindow->GetClientHeight();
		descDepth.MipLevels = 1u;
		descDepth.ArraySize = 1u;
		descDepth.Format = DXGI_FORMAT_D32_FLOAT;
		descDepth.SampleDesc.Count = 1u;
		descDepth.SampleDesc.Quality = 0u;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		if (FAILED(pDevice->CreateTexture2D(&descDepth, nullptr, &pDepthStencil)))
			throw std::runtime_error("Could Not Create Texture2D");

		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
		descDSV.Format = DXGI_FORMAT_D32_FLOAT;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0u;

		if (FAILED(pDevice->CreateDepthStencilView(pDepthStencil.Get(), &descDSV, &this->m_pDepthStencilView)))
			throw std::runtime_error("Could Not Create DepthStencilView");
	}

	void Clear(DirectX11DeviceContextObjectWrapper& pDeviceContext)
	{
		pDeviceContext->ClearDepthStencilView(this->m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
	}

	void Bind(DirectX11DeviceContextObjectWrapper& pDeviceContext, DirectX11RenderTargetbjectWrapper& pRenderTarget)
	{
		pDeviceContext->OMSetRenderTargets(1u, pRenderTarget.GetPtr(), this->m_pDepthStencilView.Get());
		pDeviceContext->OMSetDepthStencilState(this->m_pDepthStencilState.Get(), 1u);
	}
};