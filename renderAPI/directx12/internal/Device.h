#pragma once

#include "Adapter.h"
#include "../../common/Include.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef DirectX12ObjectWrapper<ID3D12Device2> DirectX12DeviceObjectWrapper;


class DirectX12Device : public DirectX12DeviceObjectWrapper {
public:
	DirectX12Device() {  }

	DirectX12Device(DirectX12AdapterObjectWrapper& pAdapter);
};

#endif // __WEISS__OS_WINDOWS