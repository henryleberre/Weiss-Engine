#include "DescriptorHeap.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12DescriptorHeap::DirectX12DescriptorHeap(DirectX12DeviceObjectWrapper& pDevice, const D3D12_DESCRIPTOR_HEAP_TYPE type, const uint32_t numDescriptors)
{
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.NumDescriptors = numDescriptors;
	desc.Type = type;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	if (pDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&this->m_pObject)) != S_OK)
		throw std::runtime_error("[DIRECTX12] Could Not Create Descriptor Heap");
}

#endif // __WEISS__OS_WINDOWS