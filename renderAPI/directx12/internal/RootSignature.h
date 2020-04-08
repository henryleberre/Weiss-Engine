#pragma once

#include "Device.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef DirectX12ObjectWrapper<ID3D12RootSignature> DirectX12RootSignatureObjectWrapper;

class DirectX12RootSignature : public DirectX12RootSignatureObjectWrapper {
public:
	DirectX12RootSignature() {  }

	DirectX12RootSignature(DirectX12DeviceObjectWrapper& pDevice, const D3D12_ROOT_SIGNATURE_FLAGS& flags);
};

#endif // __WEISS__OS_WINDOWS