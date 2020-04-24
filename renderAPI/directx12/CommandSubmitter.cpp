#include "CommandSubmitter.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	D3D12CommandSubmitter::D3D12CommandSubmitter(D3D12DeviceObjectWrapper& pDevice)
	{
		for (uint16_t i = 0; i < WEISS__FRAME_BUFFER_COUNT; i++)
			this->m_pCommandAllocators[i] = D3D12CommandAllocator(pDevice, D3D12_COMMAND_LIST_TYPE_DIRECT);

		this->m_pCommandList = D3D12CommandList(pDevice, this->m_pCommandAllocators[0], D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);

		for (uint16_t i = 0; i < WEISS__FRAME_BUFFER_COUNT; i++) {
			this->m_pFences[i] = std::make_unique<D3D12Fence>(pDevice, 0u, D3D12_FENCE_FLAGS::D3D12_FENCE_FLAG_NONE);
			this->m_fenceValues[i] = 0u;
		}
	}

	void D3D12CommandSubmitter::Close()
	{
		this->m_pCommandList.Close();
	}

	void D3D12CommandSubmitter::Reset(const size_t frameIndex)
	{
		this->m_pCommandAllocators[frameIndex].Reset();
		this->m_pCommandList.Reset(this->m_pCommandAllocators[frameIndex]);
	}

	void D3D12CommandSubmitter::Execute(D3D12CommandQueueObjectWrapper& pCommandQueue, const size_t frameIndex)
	{
		ID3D12CommandList* ppCommandLists[] = { this->m_pCommandList };
		pCommandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

		D3D12Fence& pFence     = *this->m_pFences[frameIndex];
		UINT64&         fenceValue = this->m_fenceValues[frameIndex];

		if (FAILED(pCommandQueue->Signal(pFence, fenceValue)))
			throw std::runtime_error("[DIRECTX 12] Failed To Signal The Fence");
	}

	void D3D12CommandSubmitter::WaitForCompletion(const size_t frameIndex)
	{
		D3D12Fence& pFence     = *this->m_pFences[frameIndex];
		UINT64&     fenceValue = this->m_fenceValues[frameIndex];

		if (pFence->GetCompletedValue() < fenceValue) {
			if (FAILED(pFence->SetEventOnCompletion(fenceValue, pFence.GetEvent()))) {
				throw std::runtime_error("[DIRECTX 12] Failed To Set Event On Completion For Fence");

				WaitForSingleObject(pFence.GetEvent(), INFINITE);
			}

			fenceValue++;
		}
	}

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS