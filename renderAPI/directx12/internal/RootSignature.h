#pragma once

#include "Device.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX12RootSignature {
private:
	Microsoft::WRL::ComPtr<ID3D12RootSignature> m_pRootSignature;

public:
	DirectX12RootSignature(const std::shared_ptr<DirectX12Device>& pDevice, const D3D12_ROOT_SIGNATURE_FLAGS& flags);

	Microsoft::WRL::ComPtr<ID3D12RootSignature> Get() const noexcept;

	operator Microsoft::WRL::ComPtr<ID3D12RootSignature>() const noexcept;
};

#endif // __WEISS__OS_WINDOWS