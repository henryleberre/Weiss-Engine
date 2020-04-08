#include "RenderAPI.h"

#ifdef __WEISS__OS_WINDOWS

void DirectX12RenderAPI::WaitForNextFrame()
{
	this->currentFrameIndex = this->m_pSwapChain->GetCurrentBackBufferIndex();

	if (this->m_pFences[currentFrameIndex]->GetCompletedValue() < this->m_expectedFenceValues[this->currentFrameIndex])
	{
		if (this->m_pFences[currentFrameIndex]->SetEventOnCompletion(this->m_expectedFenceValues[this->currentFrameIndex], this->m_pFences[this->currentFrameIndex].GetEvent()) != S_OK)
			throw std::runtime_error("[DIRECTX 12] Failed To Set Event On Completion For Fence");

		WaitForSingleObject(this->m_pFences[this->currentFrameIndex].GetEvent(), INFINITE);
	}

	this->m_expectedFenceValues[this->currentFrameIndex]++;
}

void DirectX12RenderAPI::CreateRenderTargets()
{
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(this->m_pDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
	
	UINT rtvDescriptorSize = this->m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	for (uint16_t i = 0; i < WEISS__FRAME_BUFFER_COUNT; i++)
	{
		this->m_pRenderTargets[i] = DirectX12RenderTarget(this->m_pDevice, this->m_pSwapChain, this->m_pDescriptorHeap, rtvHandle, i);
		rtvHandle.Offset(1, rtvDescriptorSize);
	}
}

DirectX12RenderAPI::DirectX12RenderAPI()
	: RenderAPI(RenderAPIName::DIRECTX12) {  }

void DirectX12RenderAPI::InitRenderAPI(Window* pWindow, const std::vector<RenderPipelineDesc>& pipelineDescs)
{
	this->m_pDevice         = DirectX12Device(this->m_pAdapter);
	this->m_pCommandQueue   = DirectX12CommandQueue(this->m_pDevice, D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);
	this->m_pSwapChain      = DirectX12SwapChain(this->m_pDevice, this->m_pCommandQueue, pWindow, static_cast<UINT>(WEISS__FRAME_BUFFER_COUNT));
	this->m_pDescriptorHeap = DirectX12DescriptorHeap(this->m_pDevice, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, static_cast<UINT>(WEISS__FRAME_BUFFER_COUNT));
	this->m_pInputAssemblerRootSignature = DirectX12RootSignature(this->m_pDevice, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	this->CreateRenderTargets();

	for (uint16_t i = 0; i < WEISS__FRAME_BUFFER_COUNT; i++)
		this->m_pCommandAllocators[i] = DirectX12CommandAllocator(this->m_pDevice, D3D12_COMMAND_LIST_TYPE_DIRECT);

	this->m_pCommandList = DirectX12CommandList(this->m_pDevice, this->m_pCommandAllocators[0], D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);

	for (uint16_t i = 0; i < WEISS__FRAME_BUFFER_COUNT; i++) {
		this->m_pFences[i] = DirectX12Fence(this->m_pDevice, 0u, D3D12_FENCE_FLAGS::D3D12_FENCE_FLAG_NONE);
		this->m_expectedFenceValues[i] = 0u;
	}

	this->currentFrameIndex = this->m_pSwapChain->GetCurrentBackBufferIndex();

	this->m_viewport.TopLeftX = 0;
	this->m_viewport.TopLeftY = 0;
	this->m_viewport.Width  = pWindow->GetClientWidth();
	this->m_viewport.Height = pWindow->GetClientHeight();
	this->m_viewport.MinDepth = 0.0f;
	this->m_viewport.MaxDepth = 1.0f;

	this->m_scissors.left = 0;
	this->m_scissors.top  = 0;
	this->m_scissors.right  = pWindow->GetClientWidth();
	this->m_scissors.bottom = pWindow->GetClientHeight();

	// Create Pipelines
	for (const RenderPipelineDesc& pipelineDesc : pipelineDescs)
		this->m_pRenderPipelines.push_back(DirectX12RenderPipeline(this->m_pDevice, this->m_pInputAssemblerRootSignature, pipelineDesc.vsFilename, pipelineDesc.sies, pipelineDesc.psFilename, pipelineDesc.topology));
}	

void DirectX12RenderAPI::Draw(const Drawable& drawable, const size_t nVertices)
{
	this->m_pCommandList->SetGraphicsRootSignature(this->m_pInputAssemblerRootSignature);
	this->m_pRenderPipelines[drawable.pipelineIndex].Bind(this->m_pCommandList);
	this->m_pVertexBuffers[drawable.vertexBufferIndex].Bind(this->m_pCommandList);

	if (drawable.indexBufferIndex.has_value()) {

	} else {
		this->m_pCommandList->DrawInstanced(3u, nVertices / 3u, 0, 0);
	}
}

void DirectX12RenderAPI::BeginFrame()
{
	DirectX12CommandList&      commandList      = this->m_pCommandList;
	DirectX12RenderTarget&     renderTarget     = this->m_pRenderTargets[this->currentFrameIndex];
	DirectX12CommandAllocator& commandAllocator = this->m_pCommandAllocators[this->currentFrameIndex];

	this->WaitForNextFrame();

	commandAllocator.Reset();
	commandList.Reset(commandAllocator);

	commandList.TransitionResource(renderTarget, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

	this->m_currentRtvHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(this->m_pDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), static_cast<INT>(this->currentFrameIndex), this->m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));

	commandList->RSSetViewports(1, &this->m_viewport);
	commandList->RSSetScissorRects(1, &this->m_scissors);
	commandList->OMSetRenderTargets(1, &m_currentRtvHandle, FALSE, nullptr);

	this->Fill();
}

void DirectX12RenderAPI::EndFrame()
{
	DirectX12CommandList& commandList = this->m_pCommandList;
	DirectX12RenderTarget& renderTarget = this->m_pRenderTargets[this->currentFrameIndex];
	DirectX12CommandAllocator& commandAllocator = this->m_pCommandAllocators[this->currentFrameIndex];

	commandList.TransitionResource(renderTarget, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	commandList.Close();

	ID3D12CommandList* ppCommandLists[] = { this->m_pCommandList };
	this->m_pCommandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	if (this->m_pCommandQueue->Signal(this->m_pFences[this->currentFrameIndex], this->m_expectedFenceValues[this->currentFrameIndex]) != S_OK)
		throw std::runtime_error("[DIRECTX 12] Signaling The Command Queue Fence Failed");

	this->m_pSwapChain.Present();
}

size_t DirectX12RenderAPI::CreateVertexBuffer(const size_t vertexSize, const size_t nVertices, const void* buff)
{
	this->m_pVertexBuffers.push_back(DirectX12VertexBuffer(this->m_pDevice, this->m_pCommandList, this->m_pCommandQueue, vertexSize, nVertices, buff));

	this->m_pCommandList->Close();

	ID3D12CommandList* ppCommandLists[] = { this->m_pCommandList };
	this->m_pCommandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	this->m_expectedFenceValues[this->currentFrameIndex]++;
	if (this->m_pCommandQueue->Signal(this->m_pFences[currentFrameIndex], m_expectedFenceValues[currentFrameIndex]) != S_OK)
		throw std::runtime_error("FAIL");

	this->m_pVertexBuffers[this->m_pVertexBuffers.size() - 1u].CreateView();

	return this->m_pVertexBuffers.size() - 1u;
}

size_t DirectX12RenderAPI::CreateIndexBuffer(const size_t nIndices, const void* buff)
{
	return this->m_pIndexBuffers.size() - 1u;
}

void DirectX12RenderAPI::Fill(const Colorf32& color)
{
	this->m_pCommandList->ClearRenderTargetView(this->m_currentRtvHandle, (float*)&color, 0, nullptr);
}

#endif // __WEISS__OS_WINDOWS