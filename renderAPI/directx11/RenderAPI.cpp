#include "RenderAPI.h"

#ifdef __WEISS__OS_WINDOWS

DirectX11RenderAPI::DirectX11RenderAPI() : RenderAPI(RenderAPIName::DIRECTX11) {}

void DirectX11RenderAPI::InitRenderAPI(Window* pWindow, const std::vector<RenderPipelineDesc>& pipelineDescs)
{
	this->m_pDevice       = std::make_shared<DirectX11Device>();
	this->m_pSwapChain    = std::make_shared<DirectX11SwapChain>(this->m_pDevice, pWindow);
	this->m_pRenderTarget = std::make_shared<DirectX11RenderTarget>(this->m_pDevice, this->m_pSwapChain);
	this->m_pDepthBuffer  = std::make_shared<DirectX11DepthBuffer>(pWindow, this->m_pDevice, this->m_pRenderTarget);

	this->m_pRenderTarget->SetCurrent();

	// Create Viewport
	D3D11_VIEWPORT vp;
	vp.Width = static_cast<FLOAT>(pWindow->GetClientWidth());
	vp.Height = static_cast<FLOAT>(pWindow->GetClientHeight());
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;

	this->m_pDevice->GetDeviceContext()->RSSetViewports(1u, &vp);

	this->m_pDepthBuffer->Bind();

	// Create Pipelines
	this->m_pRenderPipelines.reserve(pipelineDescs.size());
	for (const RenderPipelineDesc& pipelineDesc : pipelineDescs)
		this->m_pRenderPipelines.push_back(std::make_unique<DirectX11RenderPipeline>(this->m_pDevice, pipelineDesc));
}

void DirectX11RenderAPI::Draw(const Drawable& drawable, const size_t nVertices)
{
	this->m_pRenderPipelines[drawable.pipelineIndex]->Bind();
	this->m_pVertexBuffers[drawable.vertexBufferIndex]->Bind();
	
	if (drawable.indexBufferIndex.has_value()) {
		this->m_pIndexBuffers[drawable.indexBufferIndex.value()]->Bind();
		this->m_pDevice->GetDeviceContext()->DrawIndexed(static_cast<UINT>(nVertices), 0u, 0u);
	} else {
		this->m_pDevice->GetDeviceContext()->Draw(static_cast<UINT>(nVertices), 0u);
	}
}

void DirectX11RenderAPI::BeginFrame()
{
	this->Fill();
}

void DirectX11RenderAPI::EndFrame()
{
	this->m_pDepthBuffer->Clear();
	this->m_pSwapChain->Present();
}

size_t DirectX11RenderAPI::CreateVertexBuffer(const size_t vertexSize, const size_t nVertices, const void* buff)
{
	this->m_pVertexBuffers.push_back(std::make_unique<DirectX11VertexBuffer>(this->m_pDevice, vertexSize, nVertices, buff));

	return this->m_pVertexBuffers.size() - 1u;
}

size_t DirectX11RenderAPI::CreateIndexBuffer(const size_t nIndices, const void* buff)
{
	this->m_pIndexBuffers.push_back(std::make_unique<DirectX11IndexBuffer>(this->m_pDevice, nIndices, buff));

	return this->m_pIndexBuffers.size() - 1u;
}

void DirectX11RenderAPI::Fill(const Colorf32& color)
{
	this->m_pDevice->GetDeviceContext()->ClearRenderTargetView(this->m_pRenderTarget->GetRenderTarget().Get(), (float*)&color);
}

[[nodiscard]] std::shared_ptr<DirectX11Device> DirectX11RenderAPI::GetDevice() noexcept { return this->m_pDevice; }

#endif // __WEISS__OS_WINDOWS