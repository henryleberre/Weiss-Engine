#include "Adapter.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12Adapater::DirectX12Adapater()
{
	UINT createFactoryFlags = 0;

#if defined(_DEBUG)
	createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif

	Microsoft::WRL::ComPtr<IDXGIFactory4> dxgiFactory;
	if (CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&dxgiFactory)) != S_OK)
		throw std::runtime_error("[DIRECTX12] Failed To Create IDXGIFactory4");

	Microsoft::WRL::ComPtr<IDXGIAdapter1> dxgiAdapter1;
	Microsoft::WRL::ComPtr<IDXGIAdapter4> dxgiAdapter4;

	size_t maxDedicatedVideoMemory = 0;
	for (UINT i = 0; dxgiFactory->EnumAdapters1(i, &dxgiAdapter1) != DXGI_ERROR_NOT_FOUND; ++i)
	{
		DXGI_ADAPTER_DESC1 dxgiAdapterDesc1;
		dxgiAdapter1->GetDesc1(&dxgiAdapterDesc1);

		if ((dxgiAdapterDesc1.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) == 0 &&
			SUCCEEDED(D3D12CreateDevice(dxgiAdapter1.Get(),
				D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), nullptr)) &&
			dxgiAdapterDesc1.DedicatedVideoMemory > maxDedicatedVideoMemory)
		{
			maxDedicatedVideoMemory = dxgiAdapterDesc1.DedicatedVideoMemory;
			if (dxgiAdapter1.As(&dxgiAdapter4) != S_OK)
				throw std::runtime_error("[DIRECTX12] Failed To interpret dxgiAdapter4 as dxgiAdapter1");
		}
	}
}

DirectX12Adapater::operator Microsoft::WRL::ComPtr<IDXGIAdapter4>() const noexcept
{
	return this->m_pAdapter;
}

Microsoft::WRL::ComPtr<IDXGIAdapter4> DirectX12Adapater::Get() const noexcept
{
	return this->m_pAdapter;
}

#endif // __WEISS__OS_WINDOWS