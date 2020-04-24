#include "CommandAllocator.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	D3D12CommandAllocator::D3D12CommandAllocator(D3D12DeviceObjectWrapper& pDevice, const D3D12_COMMAND_LIST_TYPE& type)
	{
		if (pDevice->CreateCommandAllocator(type, IID_PPV_ARGS(&this->m_pObject)) != S_OK)
			throw std::runtime_error("[DIRECTX 12] Could Not Create Command Allocator");
	}

	void D3D12CommandAllocator::Reset() const
	{
		if (FAILED(this->m_pObject->Reset()))
			throw std::runtime_error("[DIRECTX 12] Could Not Reset Command Allocator");
	}

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS