#include "SwapChain.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D11    {

	D3D11SwapChain::D3D11SwapChain(D3D11DeviceObjectWrapper& pDevice, Window* pWindow)
	{
		Microsoft::WRL::ComPtr<IDXGIDevice>  dxgiDevice;
		Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter;
		Microsoft::WRL::ComPtr<IDXGIFactory> dxgiFactory;

		if (FAILED(pDevice->QueryInterface(IID_PPV_ARGS(&dxgiDevice))))
			throw std::runtime_error("Could Not Get IDXGIDevice From D3D11Device");

		if (FAILED(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf())))
			throw std::runtime_error("Could Not Get DXGIAdapter From DXGIDevice");

		if (FAILED(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), &dxgiFactory)))
			throw std::runtime_error("Could Not Get DXGIAdapter's Parent");

		DXGI_SWAP_CHAIN_DESC scd{};
		scd.BufferDesc.Width  = 0;
		scd.BufferDesc.Height = 0;
		scd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		scd.BufferDesc.RefreshRate.Numerator   = 0;
		scd.BufferDesc.RefreshRate.Denominator = 0;
		scd.BufferDesc.Scaling          = DXGI_MODE_SCALING_UNSPECIFIED;
		scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		scd.SampleDesc.Count   = 1;
		scd.SampleDesc.Quality = 0;
		scd.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.BufferCount  = 1;
		scd.OutputWindow = reinterpret_cast<WS::WIN::WindowsWindow*>(pWindow)->GetHandle();
		scd.Windowed     = TRUE;
		scd.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
		scd.Flags = 0;

		if (FAILED(dxgiFactory->CreateSwapChain(pDevice, &scd, &this->m_pObject)))
			throw std::runtime_error("[DIRECTX 11] Failed To Create Swap Chain");
	}

	D3D11SwapChain& D3D11SwapChain::operator=(D3D11SwapChain&& other) noexcept
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = nullptr;

		return *this;
	}

	void D3D11SwapChain::Present(const bool vSync)
	{
		if (FAILED(this->m_pObject->Present(vSync ? 1u : 0u, 0u)))
			throw std::runtime_error("Failed To Swap Buffers");
	}

}; // D3D11
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS