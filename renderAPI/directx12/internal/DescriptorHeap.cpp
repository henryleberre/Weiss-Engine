#include "DescriptorHeap.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	D3D12DescriptorHeap::D3D12DescriptorHeap(D3D12DeviceObjectWrapper& pDevice, const D3D12_DESCRIPTOR_HEAP_TYPE type, const uint32_t numDescriptors, const D3D12_DESCRIPTOR_HEAP_FLAGS& flags)
	{
		D3D12_DESCRIPTOR_HEAP_DESC desc = {};
		desc.NumDescriptors = numDescriptors;
		desc.Type  = type;
		desc.Flags = flags;

		if (pDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&this->m_pObject)) != S_OK)
			throw std::runtime_error("[D3D12] Could Not Create Descriptor Heap");
	}

	void D3D12DescriptorHeap::operator=(D3D12DescriptorHeap&& other) noexcept
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = nullptr;
	}

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS