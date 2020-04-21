#pragma once

#include "ObjectWrapper.h"
#include "../../common/Include.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D11    {

	typedef D3D11ObjectWrapper<ID3D11Device>        D3D11DeviceObjectWrapper;
	typedef D3D11ObjectWrapper<ID3D11DeviceContext> D3D11DeviceContextObjectWrapper;

}; // D3D11
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS