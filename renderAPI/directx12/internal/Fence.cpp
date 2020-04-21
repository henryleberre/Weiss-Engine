#include "Fence.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	D3D12Fence::D3D12Fence(D3D12DeviceObjectWrapper& pDevice, const UINT64 initialValue, const D3D12_FENCE_FLAGS flags)
		: bRealFence(true)
	{
		if (pDevice->CreateFence(initialValue, flags, IID_PPV_ARGS(&this->m_pObject)) != S_OK)
			throw std::runtime_error("[DIRECTX 12] Failed To Create Fence");

		this->m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		if (this->m_fenceEvent == nullptr)
			throw std::runtime_error("[DIRECTX 12] Failed To Create Fence Event");
	}

	D3D12Fence::~D3D12Fence()
	{
		CloseHandle(this->m_fenceEvent);
	}

	void D3D12Fence::operator=(D3D12Fence&& other) noexcept
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = nullptr;
	}

	HANDLE D3D12Fence::GetEvent() const noexcept
	{
		return this->m_fenceEvent;
	}

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS