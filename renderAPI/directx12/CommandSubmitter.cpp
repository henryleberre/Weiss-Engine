#include "CommandSubmitter.h"

DirectX12CommandSubmitter::DirectX12CommandSubmitter()
{

}

DirectX12CommandSubmitter::DirectX12CommandSubmitter(DirectX12DeviceObjectWrapper& pDevice)
{
	for (uint16_t i = 0; i < WEISS__FRAME_BUFFER_COUNT; i++)
	{
		this->m_pCommandAllocators[i] = DirectX12CommandAllocator(pDevice, D3D12_COMMAND_LIST_TYPE_DIRECT);
	}

	this->m_pCommandList = DirectX12CommandList(pDevice, this->m_pCommandAllocators[0], D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);

	for (uint16_t i = 0; i < WEISS__FRAME_BUFFER_COUNT; i++) {
		this->m_pFences[i] = std::make_unique<DirectX12Fence>(pDevice, 0u, D3D12_FENCE_FLAGS::D3D12_FENCE_FLAG_NONE);
		this->m_fenceValues[i] = 1u;
	}
}

void DirectX12CommandSubmitter::Close()
{
	this->m_pCommandList.Close();
}

void DirectX12CommandSubmitter::Reset(const size_t frameIndex)
{
	this->m_pCommandAllocators[frameIndex].Reset();
	this->m_pCommandList.Reset(this->m_pCommandAllocators[frameIndex]);
}

void DirectX12CommandSubmitter::Execute(DirectX12CommandQueueObjectWrapper& pCommandQueue, const size_t frameIndex)
{
	ID3D12CommandList* ppCommandLists[] = { this->m_pCommandList };
	pCommandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	DirectX12Fence& pFence     = *this->m_pFences[frameIndex];
	UINT64&         fenceValue = this->m_fenceValues[frameIndex];

	if (FAILED(pCommandQueue->Signal(pFence, fenceValue)))
		throw std::runtime_error("[DIRECTX 12] Failed To Signal The Fence");
}

void DirectX12CommandSubmitter::WaitForCompletion(const size_t frameIndex)
{
	DirectX12Fence& pFence     = *this->m_pFences[frameIndex];
	UINT64&         fenceValue = this->m_fenceValues[frameIndex];

	if (pFence->GetCompletedValue() < fenceValue)
	{
		if (FAILED(pFence->SetEventOnCompletion(fenceValue, pFence.GetEvent())))
			throw std::runtime_error("[DIRECTX 12] Failed To Set Event On Completion For Fence");

		WaitForSingleObject(pFence.GetEvent(), INFINITE);
	}

	fenceValue++;
}