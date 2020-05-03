#pragma once

#include "ObjectWrapper.h"
#include "../../common/Include.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	typedef D3D12ObjectWrapper<IDXGIAdapter1> D3D12AdapterObjectWrapper;

	class D3D12Adapter : public D3D12AdapterObjectWrapper {
	public:
		D3D12Adapter();

		D3D12Adapter& operator=(D3D12Adapter&& other) noexcept;
	};

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS