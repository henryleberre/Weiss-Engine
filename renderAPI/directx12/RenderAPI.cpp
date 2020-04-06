#include "RenderAPI.h"

#ifdef __WEISS__OS_WINDOWS

void DirectX12RenderAPI::WaitForNextFrame()
{
	this->currentFrameIndex = this->m_pSwapChain->Get()->GetCurrentBackBufferIndex();

	if (this->m_pFences[currentFrameIndex]->Get()->GetCompletedValue() < this->m_expectedFenceValues[this->currentFrameIndex])
	{
		if (this->m_pFences[currentFrameIndex]->Get()->SetEventOnCompletion(this->m_expectedFenceValues[this->currentFrameIndex], this->m_pFences[this->currentFrameIndex]->GetEvent()) != S_OK)
			throw std::runtime_error("[DIRECTX 12] Failed To Set Event On Completion For Fence");

		WaitForSingleObject(this->m_pFences[this->currentFrameIndex]->GetEvent(), INFINITE);
	}

	this->m_expectedFenceValues[this->currentFrameIndex]++;
}

void DirectX12RenderAPI::CreateRenderTargets()
{
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(this->m_pDescriptorHeap->Get()->GetCPUDescriptorHandleForHeapStart());
	
	UINT rtvDescriptorSize = this->m_pDevice->Get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	for (uint16_t i = 0; i < WEISS__FRAME_BUFFER_COUNT; i++)
	{
		this->m_pRenderTargets[i] = std::make_shared<DirectX12RenderTarget>(this->m_pDevice, this->m_pSwapChain, this->m_pDescriptorHeap, rtvHandle, i);
		rtvHandle.Offset(1, rtvDescriptorSize);
	}
}

DirectX12RenderAPI::DirectX12RenderAPI()
	: RenderAPI(RenderAPIName::DIRECTX12) {  }

void DirectX12RenderAPI::InitRenderAPI(Window* pWindow)
{
	this->m_pAdapter        = std::make_shared<DirectX12Adapater>();
	this->m_pDevice         = std::make_shared<DirectX12Device>(this->m_pAdapter);
	this->m_pCommandQueue   = std::make_shared<DirectX12CommandQueue>(this->m_pDevice, D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);
	this->m_pSwapChain      = std::make_shared<DirectX12SwapChain>(this->m_pDevice, this->m_pCommandQueue, pWindow, static_cast<UINT>(WEISS__FRAME_BUFFER_COUNT));
	this->m_pDescriptorHeap = std::make_shared<DirectX12DescriptorHeap>(this->m_pDevice, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, static_cast<UINT>(WEISS__FRAME_BUFFER_COUNT));

	this->CreateRenderTargets();

	for (uint16_t i = 0; i < WEISS__FRAME_BUFFER_COUNT; i++)
		this->m_pCommandAllocators[i] = std::make_shared<DirectX12CommandAllocator>(this->m_pDevice, D3D12_COMMAND_LIST_TYPE_DIRECT);

	this->m_pCommandList = std::make_shared<DirectX12CommandList>(this->m_pDevice, this->m_pCommandAllocators[0], D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);
	this->m_pCommandList->Get()->Close();

	for (uint16_t i = 0; i < WEISS__FRAME_BUFFER_COUNT; i++) {
		this->m_pFences[i] = std::make_shared<DirectX12Fence>(this->m_pDevice, 0u, D3D12_FENCE_FLAGS::D3D12_FENCE_FLAG_NONE);
		this->m_expectedFenceValues[i] = 0u;
	}

	this->currentFrameIndex = this->m_pSwapChain->Get()->GetCurrentBackBufferIndex();
}

void DirectX12RenderAPI::Draw(const Drawable& drawable, const size_t nVertices)
{

}

void DirectX12RenderAPI::BeginFrame()
{
	this->WaitForNextFrame();

	this->m_pCommandAllocators[currentFrameIndex]->Reset();
	this->m_pCommandList->Reset(this->m_pCommandAllocators[currentFrameIndex]);

	this->m_pCommandList->Get()->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(this->m_pRenderTargets[this->currentFrameIndex]->Get().Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

	this->m_currentRtvHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(this->m_pDescriptorHeap->Get()->GetCPUDescriptorHandleForHeapStart(), static_cast<INT>(this->currentFrameIndex), this->m_pDevice->Get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));

	this->m_pCommandList->Get()->OMSetRenderTargets(1, &m_currentRtvHandle, FALSE, nullptr);

	this->Fill();
}

void DirectX12RenderAPI::EndFrame()
{
	this->m_pCommandList->Get()->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(this->m_pRenderTargets[this->currentFrameIndex]->Get().Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

	if (this->m_pCommandList->Get()->Close() != S_OK)
		throw std::runtime_error("[DIRECTX 12] Failed To Close Command List");

	ID3D12CommandList* ppCommandLists[] = { this->m_pCommandList->Get().Get() };
	this->m_pCommandQueue->Get()->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	if (this->m_pCommandQueue->Get()->Signal(this->m_pFences[this->currentFrameIndex]->Get().Get(), this->m_expectedFenceValues[this->currentFrameIndex]) != S_OK)
		throw std::runtime_error("[DIRECTX 12] Signaling The Command Queue Fence Failed");

	if (this->m_pSwapChain->Get()->Present(0, 0) != S_OK)
		throw std::runtime_error("[DIRECTX 12] Presentation Failed");
}

size_t DirectX12RenderAPI::CreateRenderPipeline(const char* vsFilename, const std::vector<ShaderInputElement>& sies, const char* psFilename, const PrimitiveTopology& topology)
{
	return this->m_renderPipelines.size() - 1u;
}

size_t DirectX12RenderAPI::CreateVertexBuffer(const size_t vertexSize, const size_t nVertices, const void* buff)
{
	return this->m_vertexBuffers.size() - 1u;
}

size_t DirectX12RenderAPI::CreateIndexBuffer(const size_t nIndices, const void* buff)
{
	return this->m_indexBuffers.size() - 1u;
}

void DirectX12RenderAPI::Fill(const Colorf32& color)
{
	this->m_pCommandList->Get()->ClearRenderTargetView(this->m_currentRtvHandle, (float*)&color, 0, nullptr);
}

#endif // __WEISS__OS_WINDOWS