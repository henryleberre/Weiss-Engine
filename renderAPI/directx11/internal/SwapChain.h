#pragma once

#include "Device.h"
#include "../../common/Include.h"
#include "../../../window/Include.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef DirectX11ObjectWrapper<IDXGISwapChain> DirectX11SwapChainObjectWrapper;

class DirectX11SwapChain : public DirectX11SwapChainObjectWrapper {
public:
	DirectX11SwapChain() {  }

	DirectX11SwapChain(DirectX11DeviceObjectWrapper& pDevice, Window* pWindow)
	{
		Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice;
		Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter;
		Microsoft::WRL::ComPtr<IDXGIFactory> dxgiFactory;

		if (FAILED(pDevice->QueryInterface(IID_PPV_ARGS(&dxgiDevice))))
			throw std::runtime_error("Could Not Get IDXGIDevice From D3D11Device");

		if (FAILED(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf())))
			throw std::runtime_error("Could Not Get DXGIAdapter From DXGIDevice");

		if (FAILED(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), &dxgiFactory)))
			throw std::runtime_error("Could Not Get DXGIAdapter's Parent");

		DXGI_SWAP_CHAIN_DESC scd{};
		scd.BufferDesc.Width = 0;
		scd.BufferDesc.Height = 0;
		scd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		scd.BufferDesc.RefreshRate.Numerator = 0;
		scd.BufferDesc.RefreshRate.Denominator = 0;
		scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		scd.SampleDesc.Count = 1;
		scd.SampleDesc.Quality = 0;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.BufferCount = 1;
		scd.OutputWindow = reinterpret_cast<WindowsWindow*>(pWindow)->GetHandle();
		scd.Windowed = TRUE;
		scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		scd.Flags = 0;

		if (FAILED(dxgiFactory->CreateSwapChain(pDevice, &scd, &this->m_pObject)))
			throw std::runtime_error("[DIRECTX 11] Failed To Create Swap Chain");
	}

	void operator=(DirectX11SwapChain&& other) noexcept
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = nullptr;
	}

	void Present(const bool vSync)
	{
		if (this->m_pObject->Present(vSync ? 1u : 0u, 0u) != S_OK)
			throw std::runtime_error("Failed To Swap Buffers");
	}
};

#endif // __WEISS__OS_WINDOWS