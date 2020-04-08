#include "SwapChain.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12SwapChain::DirectX12SwapChain(DirectX12DeviceObjectWrapper&       pDevice,
									   DirectX12CommandQueueObjectWrapper& pCommandQueue,
									   const Window* pWindow, const UINT bufferCount)
{
	Microsoft::WRL::ComPtr<IDXGIFactory4> dxgiFactory4;

	UINT createFactoryFlags = 0;
#if defined(_DEBUG)
	createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif

	if (FAILED(CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&dxgiFactory4))))
		throw std::runtime_error("[DIRECTX12] Could Not Create DXGIFactory2");

	
	DXGI_MODE_DESC backBufferDesc = {};
	backBufferDesc.Width = pWindow->GetClientWidth();
	backBufferDesc.Height = pWindow->GetClientHeight();
	backBufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	DXGI_SAMPLE_DESC sampleDesc = {};
	sampleDesc.Count = 1;

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = WEISS__FRAME_BUFFER_COUNT;
	swapChainDesc.BufferDesc = backBufferDesc;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.OutputWindow = reinterpret_cast<const WindowsWindow*>(pWindow)->GetHandle();
	swapChainDesc.SampleDesc = sampleDesc;
	swapChainDesc.Windowed = true; 

	if (FAILED(dxgiFactory4->CreateSwapChain(pCommandQueue, &swapChainDesc, (IDXGISwapChain**) &this->m_pObject)))
		throw std::runtime_error("[DIRECTX 12] Failed To Create Swap Chain");
}

void DirectX12SwapChain::operator=(DirectX12SwapChain&& other) noexcept
{
	this->m_pObject = other.m_pObject;
	other.m_pObject = nullptr;
}

void DirectX12SwapChain::Present() const
{
	if (FAILED(this->m_pObject->Present(0, 0)))
		throw std::runtime_error("[DIRECTX 12] Presentation Failed");
}

#endif // __WEISS__OS_WINDOWS