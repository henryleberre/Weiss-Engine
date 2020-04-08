#include "CommandQueue.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12CommandQueue::DirectX12CommandQueue(DirectX12DeviceObjectWrapper& pDevice, const D3D12_COMMAND_LIST_TYPE& type)
{
	D3D12_COMMAND_QUEUE_DESC desc = {};
	desc.Type = type;
	desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.NodeMask = 0;

	if (FAILED(pDevice->CreateCommandQueue(&desc, IID_PPV_ARGS(&this->m_pObject))))
		throw std::runtime_error("[DIRECTX12] Could Not Create Command Queue");
}

void DirectX12CommandQueue::operator=(DirectX12CommandQueue&& other) noexcept
{
	this->m_pObject = other.m_pObject;
	other.m_pObject = nullptr;
}

#endif // __WEISS__OS_WINDOWS