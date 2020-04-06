#pragma once

#include "Device.h"
#include "SwapChain.h"
#include "DescriptorHeap.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX12RenderTarget {
private:
	Microsoft::WRL::ComPtr<ID3D12Resource> m_pRenderTarget;

public:
	DirectX12RenderTarget(const std::shared_ptr<DirectX12Device>&         pDevice,
						  const std::shared_ptr<DirectX12SwapChain>&      pSwapChain,
						  const std::shared_ptr<DirectX12DescriptorHeap>& pDescriptorHeap,
						  const CD3DX12_CPU_DESCRIPTOR_HANDLE& rtvHandle,
						  const uint16_t frameIndex);

	Microsoft::WRL::ComPtr<ID3D12Resource> Get() const noexcept;

	operator Microsoft::WRL::ComPtr<ID3D12Resource>() const noexcept;
};

#endif // __WEISS__OS_WINDOWS