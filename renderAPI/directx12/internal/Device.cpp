#include "Device.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12Device::DirectX12Device(DirectX12AdapterObjectWrapper& pAdapter)
{
	if (FAILED(D3D12CreateDevice(pAdapter, D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device2), (void**)&this->m_pObject)))
		throw std::runtime_error("[DIRECTX12] Failed To Create Device");

#if defined(_DEBUG)
	Microsoft::WRL::ComPtr<ID3D12InfoQueue> pInfoQueue;
	if (SUCCEEDED(this->m_pObject->QueryInterface(IID_PPV_ARGS(&pInfoQueue))))
	{
		pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, TRUE);
		pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, TRUE);
		pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, TRUE);

		//D3D12_MESSAGE_CATEGORY Categories[] = {};

		D3D12_MESSAGE_SEVERITY Severities[] =
		{
			D3D12_MESSAGE_SEVERITY_INFO
		};

		D3D12_MESSAGE_ID DenyIds[] = {
			D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_MISMATCHINGCLEARVALUE,   
			D3D12_MESSAGE_ID_MAP_INVALID_NULLRANGE,                         
			D3D12_MESSAGE_ID_UNMAP_INVALID_NULLRANGE,                      
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

void DirectX12Device::operator=(DirectX12Device&& other) noexcept
{
	this->m_pObject = other.m_pObject;
	other.m_pObject = nullptr;
}

#endif // __WEISS__OS_WINDOWS