#include "SwapChain.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12SwapChain::DirectX12SwapChain(const std::shared_ptr<DirectX12Device>& pDevice,
									   const std::shared_ptr<DirectX12CommandQueue>& pCommandQueue,
									   const Window* pWindow, const UINT bufferCount)
{
	Microsoft::WRL::ComPtr<IDXGIFactory4> dxgiFactory4;

	UINT createFactoryFlags = 0;
#if defined(_DEBUG)
	createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif

	if (CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&dxgiFactory4)) != S_OK)
		throw std::runtime_error("[DIRECTX12] Could Not Create DXGIFactory2");

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.Width  = pWindow->GetClientWidth();
	swapChainDesc.Height = pWindow->GetClientHeight();
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.Stereo = FALSE;
	swapChainDesc.SampleDesc = { 1, 0 };
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = bufferCount;
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapChainDesc.Flags = 0; // TODO:: TEARING

	Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain1;
	if (dxgiFactory4->CreateSwapChainForHwnd(pCommandQueue->Get().Get(), reinterpret_cast<const WindowsWindow*>(pWindow)->GetHandle(), &swapChainDesc, nullptr, nullptr, &swapChain1) != S_OK)
		throw std::runtime_error("[DIRECTX12] Could Not Create SwapChain");

	if (swapChain1.As(&this->m_pSwapChain) != S_OK)
		throw std::runtime_error("[DIRECTX12] Could Not Cast To SwapChain");
}

#endif // __WEISS__OS_WINDOWS