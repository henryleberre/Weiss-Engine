#include "Adapter.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12Adapater::DirectX12Adapater()
{
	HRESULT hr;
	IDXGIFactory4* dxgiFactory;
	if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory))))
		throw std::runtime_error("[DIRECTX 12] Failed To Create DXGIFactory1");

	int adapterIndex = 0;

	while (dxgiFactory->EnumAdapters1(adapterIndex, &this->m_pAdapter) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_ADAPTER_DESC1 desc;
		this->m_pAdapter->GetDesc1(&desc);

		if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			continue;

		if (SUCCEEDED(D3D12CreateDevice(this->m_pAdapter.Get(), D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr)))
			return;

		adapterIndex++;
	}

	throw std::runtime_error("[DIRECTX 12] Failed To Create Adapter");
}

DirectX12Adapater::operator Microsoft::WRL::ComPtr<IDXGIAdapter1>() const noexcept
{
	return this->m_pAdapter;
}

Microsoft::WRL::ComPtr<IDXGIAdapter1> DirectX12Adapater::Get() const noexcept
{
	return this->m_pAdapter;
}

#endif // __WEISS__OS_WINDOWS