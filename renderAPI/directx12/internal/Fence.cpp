#include "Fence.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12Fence::DirectX12Fence(DirectX12DeviceObjectWrapper& pDevice, const UINT64 initialValue, const D3D12_FENCE_FLAGS flags)
	: bRealFence(true)
{
	if (pDevice->CreateFence(initialValue, flags, IID_PPV_ARGS(&this->m_pObject)) != S_OK)
		throw std::runtime_error("[DIRECTX 12] Failed To Create Fence");

	this->m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	if (this->m_fenceEvent == nullptr)
		throw std::runtime_error("[DIRECTX 12] Failed To Create Fence Event");
}

DirectX12Fence::~DirectX12Fence()
{
	CloseHandle(this->m_fenceEvent);
}

void DirectX12Fence::operator=(DirectX12Fence&& other) noexcept
{
	this->m_pObject = other.m_pObject;
	other.m_pObject = nullptr;
}

HANDLE DirectX12Fence::GetEvent() const noexcept
{
	return this->m_fenceEvent;
}

#endif // __WEISS__OS_WINDOWS