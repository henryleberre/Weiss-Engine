#pragma once

#include "ObjectWrapper.h"
#include "../../common/Include.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef DirectX12ObjectWrapper<IDXGIAdapter1> DirectX12AdapterObjectWrapper;

class DirectX12Adapater : public DirectX12AdapterObjectWrapper {
public:
	DirectX12Adapater();
};

#endif // __WEISS__OS_WINDOWS