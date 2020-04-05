#pragma once

#include "Adapter.h"
#include "../../common/Include.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX12Device {
private:
	Microsoft::WRL::ComPtr<ID3D12Device2> m_pDevice;

public:
	DirectX12Device(const std::shared_ptr<DirectX12Adapater>& pAdapter);

	operator Microsoft::WRL::ComPtr<ID3D12Device2>() const noexcept;
	Microsoft::WRL::ComPtr<ID3D12Device2> Get() const noexcept;
};

#endif // __WEISS__OS_WINDOWS