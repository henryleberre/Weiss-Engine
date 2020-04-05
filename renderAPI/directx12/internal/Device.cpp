#include "Device.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12Device::DirectX12Device(const std::shared_ptr<DirectX12Adapater>& pAdapter)
{
	if (D3D12CreateDevice(pAdapter->Get().Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&this->m_pDevice)) != S_OK)
		throw std::runtime_error("[DIRECTX12] Failed To Create Device");

	// Enable debug messages in debug mode.
#if defined(_DEBUG)
	Microsoft::WRL::ComPtr<ID3D12InfoQueue> pInfoQueue;
	if (SUCCEEDED(d3d12Device2.As(&pInfoQueue)))
	{
		pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, TRUE);
		pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, TRUE);
		pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, TRUE);

		// Suppress whole categories of messages
		//D3D12_MESSAGE_CATEGORY Categories[] = {};

		// Suppress messages based on their severity level
		D3D12_MESSAGE_SEVERITY Severities[] =
		{
			D3D12_MESSAGE_SEVERITY_INFO
		};

		// Suppress individual messages by their ID
		D3D12_MESSAGE_ID DenyIds[] = {
			D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_MISMATCHINGCLEARVALUE,   // I'm really not sure how to avoid this message.
			D3D12_MESSAGE_ID_MAP_INVALID_NULLRANGE,                         // This warning occurs when using capture frame while graphics debugging.
			D3D12_MESSAGE_ID_UNMAP_INVALID_NULLRANGE,                       // This warning occurs when using capture frame while graphics debugging.
		};

		D3D12_INFO_QUEUE_FILTER NewFilter = {};
		//NewFilter.DenyList.NumCategories = _countof(Categories);
		//NewFilter.DenyList.pCategoryList = Categories;
		NewFilter.DenyList.NumSeverities = _countof(Severities);
		NewFilter.DenyList.pSeverityList = Severities;
		NewFilter.DenyList.NumIDs = _countof(DenyIds);
		NewFilter.DenyList.pIDList = DenyIds;

		if (pInfoQueue->PushStorageFilter(&NewFilter) != S_OK)
			throw std::runtime_error("[DIRECTX12] Could Not Push Storage FIlter");
	}
#endif
}

DirectX12Device::operator Microsoft::WRL::ComPtr<ID3D12Device2>() const noexcept
{
	return this->m_pDevice;
}

Microsoft::WRL::ComPtr<ID3D12Device2> DirectX12Device::Get() const noexcept
{
	return this->m_pDevice;
}

#endif // __WEISS__OS_WINDOWS