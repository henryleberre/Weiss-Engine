#pragma once

#include "Device.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	typedef D3D12ObjectWrapper<ID3D12CommandAllocator> D3D12CommandAllocatorObjectWrapper;

	class D3D12CommandAllocator : public D3D12CommandAllocatorObjectWrapper {
	public:
		D3D12CommandAllocator() {  }

		D3D12CommandAllocator(D3D12DeviceObjectWrapper& pDevice, const D3D12_COMMAND_LIST_TYPE& type);

		void operator=(D3D12CommandAllocator&& other) noexcept;

		void Reset() const;
	};

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS