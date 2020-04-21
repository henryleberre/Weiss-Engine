#pragma once

#include "internal/Fence.h"
#include "../../common/Include.h"
#include "internal/CommandList.h"
#include "internal/CommandAllocator.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	class D3D12CommandSubmitter {
	private:
		D3D12CommandList m_pCommandList;

		std::array<UINT64,                      WEISS__FRAME_BUFFER_COUNT> m_fenceValues;
		std::array<std::unique_ptr<D3D12Fence>, WEISS__FRAME_BUFFER_COUNT> m_pFences;

		std::array<D3D12CommandAllocator, WEISS__FRAME_BUFFER_COUNT> m_pCommandAllocators;

	public:
		D3D12CommandSubmitter();
		D3D12CommandSubmitter(D3D12DeviceObjectWrapper& pDevice);

		void Close();
		void Reset(const size_t frameIndex);

		void Execute(D3D12CommandQueueObjectWrapper& pCommandQueue, const size_t frameIndex);

		void WaitForCompletion(const size_t frameIndex);

		D3D12CommandList& GetCommandList()   { return this->m_pCommandList;  }
		D3D12CommandList* GetCommandListPr() { return &this->m_pCommandList; }
		D3D12Fence&       GetFence(const size_t frameIndex) { return *this->m_pFences[frameIndex]; }
	};

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS