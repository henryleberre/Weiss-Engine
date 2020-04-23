#pragma once

#include "Device.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	typedef D3D12ObjectWrapper<ID3D12Resource> D3D12CommittedResourceObjectWrapper;

	class D3D12CommittedResource : public D3D12CommittedResourceObjectWrapper {
	public:
		D3D12CommittedResource() = default;

		D3D12CommittedResource(D3D12CommittedResource&& other) noexcept;

		D3D12CommittedResource(D3D12DeviceObjectWrapper& pDevice,   const D3D12_HEAP_TYPE& heapType,
							   const D3D12_HEAP_FLAGS&   flags,     const D3D12_RESOURCE_DESC& desc,
							   const D3D12_RESOURCE_STATES& states, const char* name = "(PLACEHOLDER NAME)");

		void operator=(D3D12CommittedResource&& other) noexcept;
	};

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS