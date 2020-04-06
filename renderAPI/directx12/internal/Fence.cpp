#include "Fence.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12Fence::DirectX12Fence(const std::shared_ptr<DirectX12Device>& pDevice, const UINT64 initialValue, const D3D12_FENCE_FLAGS flags)
{
	if (pDevice->Get()->CreateFence(initialValue, flags, IID_PPV_ARGS(&this->m_pFence)) != S_OK)
		throw std::runtime_error("[DIRECTX 12] Failed To Create Fence");

	this->m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	if (this->m_fenceEvent == nullptr)
		throw std::runtime_error("[DIRECTX 12] Failed To Create Fence Event");
}

DirectX12Fence::~DirectX12Fence()
{
	CloseHandle(this->m_fenceEvent);
}

HANDLE DirectX12Fence::GetEvent() const noexcept
{
	return this->m_fenceEvent;
}

Microsoft::WRL::ComPtr<ID3D12Fence> DirectX12Fence::Get() const noexcept
{
	return this->m_pFence;
}

DirectX12Fence::operator Microsoft::WRL::ComPtr<ID3D12Fence>() const noexcept
{
	return this->m_pFence;
}

#endif // __WEISS__OS_WINDOWS