#include "DescriptorHeap.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12DescriptorHeap::DirectX12DescriptorHeap(const std::shared_ptr<DirectX12Device>& pDevice, const D3D12_DESCRIPTOR_HEAP_TYPE type, const uint32_t numDescriptors)
{
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.NumDescriptors = numDescriptors;
	desc.Type = type;

	if (pDevice->Get()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&this->m_descriptorHeap)) != S_OK)
		throw std::runtime_error("[DIRECTX12] Could Not Create Descriptor Heap");
}

DirectX12DescriptorHeap::operator Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>() const noexcept
{
	return this->m_descriptorHeap;
}

Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> DirectX12DescriptorHeap::Get() const noexcept
{
	return this->m_descriptorHeap;
}

#endif // __WEISS__OS_WINDOWS