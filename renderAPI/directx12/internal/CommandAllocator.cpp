#include "CommandAllocator.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12CommandAllocator::DirectX12CommandAllocator(DirectX12DeviceObjectWrapper& pDevice, const D3D12_COMMAND_LIST_TYPE& type)
{
	if (pDevice->CreateCommandAllocator(type, IID_PPV_ARGS(&this->m_pObject)) != S_OK)
		throw std::runtime_error("[DIRECTX 12] Could Not Create Command Allocator");
}

void DirectX12CommandAllocator::operator=(DirectX12CommandAllocator&& other) noexcept
{
	this->m_pObject = other.m_pObject;
	other.m_pObject = nullptr;
}

void DirectX12CommandAllocator::Reset() const
{
	if (FAILED(this->m_pObject->Reset()))
		throw std::runtime_error("[DIRECTX 12] Could Not Reset Command Allocator");
}

#endif // __WEISS__OS_WINDOWS