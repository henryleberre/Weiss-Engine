#include "RenderAPI.h"

#ifdef __WEISS__OS_WINDOWS

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
	: RenderAPI(RenderAPIName::DIRECTX12) {
}

void DirectX12RenderAPI::InitRenderAPI(Window* pWindow, const std::vector<RenderPipelineDesc>& pipelineDescs)
{
	this->m_pDevice         = DirectX12Device(this->m_pAdapter);
	this->m_pDepthBuffer    = DirectX12DepthBuffer(this->m_pDevice, pWindow);
	this->m_pCommandQueue   = DirectX12CommandQueue(this->m_pDevice, D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);
	this->m_pSwapChain      = DirectX12SwapChain(this->m_pDevice, this->m_pCommandQueue, pWindow, static_cast<UINT>(WEISS__FRAME_BUFFER_COUNT));
	this->m_pDescriptorHeap = DirectX12DescriptorHeap(this->m_pDevice, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, static_cast<UINT>(WEISS__FRAME_BUFFER_COUNT));
	this->m_pInputAssemblerRootSignature = DirectX12RootSignature(this->m_pDevice, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	this->CreateRenderTargets();

	this->m_pGraphicsCommandSubmitter        = DirectX12CommandSubmitter(this->m_pDevice);
	this->m_pResourceLoadingCommandSubmitter = DirectX12CommandSubmitter(this->m_pDevice);

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
		this->m_pRenderPipelines.push_back(std::make_unique<DirectX12RenderPipeline>(this->m_pDevice, this->m_pInputAssemblerRootSignature, pipelineDesc.vsFilename, pipelineDesc.sies, pipelineDesc.psFilename, pipelineDesc.topology));
}	

void DirectX12RenderAPI::Draw(const Drawable& drawable, const size_t nVertices)
{
	DirectX12CommandList& pGfxCommandList = this->m_pGraphicsCommandSubmitter.GetCommandList();

	pGfxCommandList->SetGraphicsRootSignature(this->m_pInputAssemblerRootSignature);
	this->m_pRenderPipelines[drawable.pipelineIndex]->Bind(pGfxCommandList);
	this->m_pVertexBuffers[drawable.vertexBufferIndex]->Bind(pGfxCommandList);

	if (drawable.indexBufferIndex.has_value()) {
		this->m_pIndexBuffers[drawable.indexBufferIndex.value()]->Bind(pGfxCommandList);
		pGfxCommandList->DrawIndexedInstanced(nVertices, 1, 0, 0, 0);
	} else {
		pGfxCommandList->DrawInstanced(nVertices, 1u, 0, 0);
	}
}

void DirectX12RenderAPI::BeginDrawing()
{
	// Wait For Next Frame
	this->currentFrameIndex = this->m_pSwapChain->GetCurrentBackBufferIndex();

	DirectX12RenderTarget& renderTarget    = this->m_pRenderTargets[this->currentFrameIndex];
	DirectX12CommandList&  pGfxCommandList = this->m_pGraphicsCommandSubmitter.GetCommandList();

	pGfxCommandList.TransitionResource(renderTarget, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	
	this->m_currentRtvHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(this->m_pDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), static_cast<INT>(this->currentFrameIndex), this->m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
	
	this->m_pDepthBuffer.Clear(pGfxCommandList);
	pGfxCommandList->RSSetViewports    (1u, &this->m_viewport);
	pGfxCommandList->RSSetScissorRects (1u, &this->m_scissors);
	pGfxCommandList->OMSetRenderTargets(1u, &m_currentRtvHandle, FALSE, this->m_pDepthBuffer);
	
	this->Fill();
}

void DirectX12RenderAPI::EndDrawing()
{
	DirectX12RenderTarget&     renderTarget     = this->m_pRenderTargets[this->currentFrameIndex];
	DirectX12CommandList&      pGfxCommandList  = this->m_pGraphicsCommandSubmitter.GetCommandList();
	DirectX12Fence&            pFence           = this->m_pGraphicsCommandSubmitter.GetFence(this->currentFrameIndex);
	DirectX12CommandAllocator& commandAllocator = this->m_pGraphicsCommandSubmitter.GetCommandAllocator(this->currentFrameIndex);

	pGfxCommandList.TransitionResource(renderTarget, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	pGfxCommandList.Close();

	this->m_pGraphicsCommandSubmitter.Execute(this->m_pCommandQueue, this->currentFrameIndex);
}

void DirectX12RenderAPI::Present(const bool vSync)
{
	this->m_pSwapChain.Present(vSync);

	this->m_pGraphicsCommandSubmitter.WaitForCompletion(currentFrameIndex);
	this->m_pGraphicsCommandSubmitter.Reset(this->currentFrameIndex);
}

size_t DirectX12RenderAPI::CreateVertexBuffer(const size_t vertexSize, const size_t nVertices, const void* buff)
{
	DirectX12CommandList& pResCommandList = this->m_pResourceLoadingCommandSubmitter.GetCommandList();

	this->m_pVertexBuffers.push_back(std::make_unique<DirectX12VertexBuffer>(this->m_pDevice, pResCommandList, this->m_pCommandQueue, vertexSize, nVertices, buff));

	this->m_pResourceLoadingCommandSubmitter.Close();
	this->m_pResourceLoadingCommandSubmitter.Execute(this->m_pCommandQueue, this->currentFrameIndex);
	this->m_pVertexBuffers[this->m_pVertexBuffers.size() - 1u]->CreateView();

	this->m_pResourceLoadingCommandSubmitter.Reset(this->currentFrameIndex);

	return this->m_pVertexBuffers.size() - 1u;
}

size_t DirectX12RenderAPI::CreateIndexBuffer(const size_t nIndices, const void* buff)
{
	DirectX12CommandList& pResCommandList = this->m_pResourceLoadingCommandSubmitter.GetCommandList();

	this->m_pIndexBuffers.push_back(std::make_unique<DirectX12IndexBuffer>(this->m_pDevice, pResCommandList, this->m_pCommandQueue, nIndices, buff));

	this->m_pResourceLoadingCommandSubmitter.Close();
	this->m_pResourceLoadingCommandSubmitter.Execute(this->m_pCommandQueue, this->currentFrameIndex);
	this->m_pIndexBuffers[this->m_pIndexBuffers.size() - 1u]->CreateView();

	this->m_pResourceLoadingCommandSubmitter.Reset(this->currentFrameIndex);

	return this->m_pIndexBuffers.size() - 1u;
}

void DirectX12RenderAPI::Fill(const Colorf32& color)
{
	DirectX12CommandList& pGfxCommandList = this->m_pGraphicsCommandSubmitter.GetCommandList();

	pGfxCommandList->ClearRenderTargetView(this->m_currentRtvHandle, (float*)&color, 0, nullptr);
}

#endif // __WEISS__OS_WINDOWS