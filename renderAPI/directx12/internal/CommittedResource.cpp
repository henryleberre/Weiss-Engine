#include "CommittedResource.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	D3D12CommittedResource::D3D12CommittedResource(D3D12CommittedResource&& other) noexcept
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = nullptr;
	}

	D3D12CommittedResource::D3D12CommittedResource(D3D12DeviceObjectWrapper& pDevice,   const D3D12_HEAP_TYPE& heapType,
												   const D3D12_HEAP_FLAGS& flags,       const D3D12_RESOURCE_DESC& desc,
												   const D3D12_RESOURCE_STATES& states, const char* name)
	{
		if (FAILED(pDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(heapType), flags, &desc, states,
													nullptr, IID_PPV_ARGS(&this->m_pObject))))
		{
			const std::string errorString = "[DIRECTX 12] Failed To Create A Committed Resource Named " + std::string(name);

			throw std::runtime_error(errorString.c_str());
		}
	
		const std::wstring nameW(&name[0], &name[strlen(name) + 1u]);
		this->m_pObject->SetName(nameW.c_str());
	}
	
	void D3D12CommittedResource::operator=(D3D12CommittedResource&& other) noexcept
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = nullptr;
	}

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS