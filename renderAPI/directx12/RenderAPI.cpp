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

	this->m_bvcSubmitter     = DirectX12CommandSubmitter(this->m_pDevice);
	this->m_commandSubmitter = DirectX12CommandSubmitter(this->m_pDevice);

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
		this->m_renderPipelines.emplace_back(this->m_pDevice, this->m_pInputAssemblerRootSignature, pipelineDesc.vsFilename, pipelineDesc.sies, pipelineDesc.psFilename, pipelineDesc.topology);
}	

void DirectX12RenderAPI::Draw(const Drawable& drawable, const size_t nVertices)
{
	DirectX12CommandList& pGfxCommandList = this->m_commandSubmitter.GetCommandList();

	pGfxCommandList->SetGraphicsRootSignature(this->m_pInputAssemblerRootSignature);
	this->m_renderPipelines[drawable.pipelineIndex].Bind(pGfxCommandList);
	this->m_pVertexBuffers[drawable.vertexBufferIndex].Bind();

	if (drawable.indexBufferIndex.has_value()) {
		this->m_pIndexBuffers[drawable.indexBufferIndex.value()].Bind();
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
	DirectX12CommandList&  pGfxCommandList = this->m_commandSubmitter.GetCommandList();

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
	DirectX12RenderTarget& renderTarget     = this->m_pRenderTargets[this->currentFrameIndex];
	DirectX12CommandList&  pGfxCommandList  = this->m_commandSubmitter.GetCommandList();
	DirectX12Fence&        pFence           = this->m_commandSubmitter.GetFence(this->currentFrameIndex);

	this->m_newVertexBufferIndices.clear();
	this->m_newIndexBufferIndices.clear();

	pGfxCommandList.TransitionResource(renderTarget, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);

	this->m_commandSubmitter.Close();
	this->m_commandSubmitter.Execute(this->m_pCommandQueue, this->currentFrameIndex);
}

void DirectX12RenderAPI::Present(const bool vSync)
{
	this->m_pSwapChain.Present(vSync);

	this->m_commandSubmitter.WaitForCompletion(currentFrameIndex);
	this->m_commandSubmitter.Reset(this->currentFrameIndex);
}

size_t DirectX12RenderAPI::CreateVertexBuffer(const size_t nVertices, const size_t vertexSize)
{
	const size_t vertexBufferIndex = this->m_pVertexBuffers.size();

	this->m_pVertexBuffers.emplace_back(this->m_pDevice, &this->m_commandSubmitter.GetCommandList(), vertexSize, nVertices);
	this->m_newVertexBufferIndices.push_back(vertexBufferIndex);

	this->m_commandSubmitter.Close();
	this->m_commandSubmitter.Execute(this->m_pCommandQueue, this->currentFrameIndex);
	this->m_pVertexBuffers[this->m_pVertexBuffers.size() - 1u].CreateView();

	this->m_commandSubmitter.Reset(this->currentFrameIndex);

	return vertexBufferIndex;
}

size_t DirectX12RenderAPI::CreateIndexBuffer(const size_t nIndices)
{
	const size_t indexBufferIndex = this->m_pIndexBuffers.size();

	this->m_pIndexBuffers.emplace_back(this->m_pDevice, &this->m_commandSubmitter.GetCommandList(), nIndices);
	this->m_newIndexBufferIndices.push_back(indexBufferIndex);

	this->m_commandSubmitter.Close();
	this->m_commandSubmitter.Execute(this->m_pCommandQueue, this->currentFrameIndex);
	this->m_pIndexBuffers[this->m_pIndexBuffers.size() - 1u].CreateView();

	this->m_commandSubmitter.Reset(this->currentFrameIndex);

	return indexBufferIndex;
}

size_t DirectX12RenderAPI::CreateConstantBuffer(const size_t objSize, const size_t slotVS, const size_t slotPS, const ShaderBindingType& shaderBindingType)
{	
	this->m_pConstantBuffers.emplace_back(this->m_pDevice, &this->m_bvcSubmitter.GetCommandList(), objSize, slotVS, slotPS, shaderBindingType);

	return this->m_pConstantBuffers.size() - 1u;
}

void DirectX12RenderAPI::Fill(const Colorf32& color)
{
	DirectX12CommandList& pGfxCommandList = this->m_commandSubmitter.GetCommandList();

	pGfxCommandList->ClearRenderTargetView(this->m_currentRtvHandle, (float*)&color, 0, nullptr);
}

#endif // __WEISS__OS_WINDOWS