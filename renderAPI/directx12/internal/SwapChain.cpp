#include "SwapChain.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	D3D12SwapChain::D3D12SwapChain(D3D12DeviceObjectWrapper&       pDevice,
								   D3D12CommandQueueObjectWrapper& pCommandQueue,
								   const Window* pWindow, const UINT bufferCount)
	{
		Microsoft::WRL::ComPtr<IDXGIFactory4> dxgiFactory4;

		UINT createFactoryFlags = 0;

#if defined(_DEBUG)

		createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;

#endif // _DEBUG

		if (FAILED(CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&dxgiFactory4))))
			throw std::runtime_error("[D3D12] Could Not Create DXGIFactory2");
	
		DXGI_MODE_DESC backBufferDesc = {};
		backBufferDesc.Width  = pWindow->GetClientWidth();
		backBufferDesc.Height = pWindow->GetClientHeight();
		backBufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		DXGI_SAMPLE_DESC sampleDesc = {};
		sampleDesc.Count = 1;

		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferCount  = WEISS__FRAME_BUFFER_COUNT;
		swapChainDesc.BufferDesc   = backBufferDesc;
		swapChainDesc.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.SwapEffect   = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.OutputWindow = reinterpret_cast<const WIN::WindowsWindow*>(pWindow)->GetHandle();
		swapChainDesc.SampleDesc   = sampleDesc;
		swapChainDesc.Windowed     = true; 

		if (FAILED(dxgiFactory4->CreateSwapChain(pCommandQueue, &swapChainDesc, (IDXGISwapChain**) &this->m_pObject)))
			throw std::runtime_error("[DIRECTX 12] Failed To Create Swap Chain");
	}

	void D3D12SwapChain::operator=(D3D12SwapChain&& other) noexcept
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = nullptr;
	}

	void D3D12SwapChain::Present(const bool vSync) const
	{
		if (FAILED(this->m_pObject->Present(vSync ? 1 : 0u, 0u)))
			throw std::runtime_error("[DIRECTX 12] Presentation Failed");
	}

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS