#pragma once

#include "Adapter.h"
#include "../../common/Include.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	typedef D3D12ObjectWrapper<ID3D12Device2> D3D12DeviceObjectWrapper;

	class D3D12Device : public D3D12DeviceObjectWrapper {
	public:
		D3D12Device() {  }

		D3D12Device(D3D12AdapterObjectWrapper& pAdapter);

		void operator=(D3D12Device&& other) noexcept;
	};

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS