#include "CommandQueue.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	D3D12CommandQueue::D3D12CommandQueue(D3D12DeviceObjectWrapper& pDevice, const D3D12_COMMAND_LIST_TYPE& type)
	{
		D3D12_COMMAND_QUEUE_DESC desc = {};
		desc.Type     = type;
		desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
		desc.Flags    = D3D12_COMMAND_QUEUE_FLAG_NONE;
		desc.NodeMask = 0;

		if (FAILED(pDevice->CreateCommandQueue(&desc, IID_PPV_ARGS(&this->m_pObject))))
			throw std::runtime_error("[D3D12] Could Not Create Command Queue");
	}

	void D3D12CommandQueue::operator=(D3D12CommandQueue&& other) noexcept
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = nullptr;
	}

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS