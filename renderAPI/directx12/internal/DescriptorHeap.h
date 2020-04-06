#pragma once

#include "Device.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX12DescriptorHeap {
private:
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_descriptorHeap;

public:
	DirectX12DescriptorHeap(const std::shared_ptr<DirectX12Device>& pDevice, const D3D12_DESCRIPTOR_HEAP_TYPE type, const uint32_t numDescriptors);

	operator Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>() const noexcept;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> Get() const noexcept;
};

#endif // __WEISS__OS_WINDOWS