#pragma once

#include "internal/Fence.h"
#include "../../common/Include.h"
#include "internal/CommandList.h"
#include "internal/CommandAllocator.h"

class DirectX12CommandSubmitter {
private:
	DirectX12CommandList m_pCommandList;

	std::array<UINT64, WEISS__FRAME_BUFFER_COUNT> m_fenceValues;
	std::array<std::unique_ptr<DirectX12Fence>, WEISS__FRAME_BUFFER_COUNT> m_pFences;

	std::array<DirectX12CommandAllocator, WEISS__FRAME_BUFFER_COUNT> m_pCommandAllocators;

public:
	DirectX12CommandSubmitter();
	DirectX12CommandSubmitter(DirectX12DeviceObjectWrapper& pDevice);

	void Close();
	void Reset(const size_t frameIndex);

	void Execute(DirectX12CommandQueueObjectWrapper& pCommandQueue, const size_t frameIndex);

	void WaitForCompletion(const size_t frameIndex);

	DirectX12CommandList& GetCommandList() { return this->m_pCommandList; }
	DirectX12CommandList* GetCommandListPr() { return &this->m_pCommandList; }
	DirectX12Fence&       GetFence(const size_t frameIndex) { return *this->m_pFences[frameIndex]; }
};