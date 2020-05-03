#pragma once

#include "Device.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	typedef D3D12ObjectWrapper<ID3D12Fence> D3D12FenceObjectWrapper;

	class D3D12Fence : public D3D12FenceObjectWrapper {
	private:
		HANDLE m_fenceEvent = nullptr;

		bool bRealFence = false;

	public:
		D3D12Fence() = default;

		D3D12Fence(D3D12DeviceObjectWrapper& pDevice, const UINT64 initialValue, const D3D12_FENCE_FLAGS flags);
		
		~D3D12Fence();

		D3D12Fence& operator=(D3D12Fence&& other) noexcept;

		HANDLE GetEvent() const noexcept;
	};

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS