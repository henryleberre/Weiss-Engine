#pragma once

#include "ObjectWrapper.h"
#include "../../common/Include.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef DirectX12ObjectWrapper<IDXGIAdapter1> DirectX12AdapterObjectWrapper;

class DirectX12Adapter : public DirectX12AdapterObjectWrapper {
public:
	DirectX12Adapter();

	void operator=(DirectX12Adapter&& other) noexcept;
};

#endif // __WEISS__OS_WINDOWS