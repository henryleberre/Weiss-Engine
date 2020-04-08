#pragma once

#include "ObjectWrapper.h"
#include "../../common/Include.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef DirectX11ObjectWrapper<ID3D11Device>        DirectX11DeviceObjectWrapper;
typedef DirectX11ObjectWrapper<ID3D11DeviceContext> DirectX11DeviceContextObjectWrapper;

#endif // __WEISS__OS_WINDOWS