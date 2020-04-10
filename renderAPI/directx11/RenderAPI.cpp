#include "RenderAPI.h"

#ifdef __WEISS__OS_WINDOWS

DirectX11RenderAPI::DirectX11RenderAPI() : RenderAPI(RenderAPIName::DIRECTX11) {}

void DirectX11RenderAPI::InitRenderAPI(Window* pWindow, const std::vector<RenderPipelineDesc>& pipelineDescs)
{
	if (D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, this->m_pDevice.GetPtr(), nullptr, this->m_pDeviceContext.GetPtr()) != S_OK)
		throw std::runtime_error("Could Not Create Device");

	this->m_pSwapChain    = DirectX11SwapChain(this->m_pDevice, pWindow);
	this->m_pRenderTarget = DirectX11RenderTarget(this->m_pDevice, this->m_pSwapChain);
	this->m_pDepthBuffer  = DirectX11DepthBuffer(pWindow, this->m_pDevice);

	this->m_pRenderTarget.SetCurrent(this->m_pDeviceContext);

	// Create Viewport
	D3D11_VIEWPORT vp;
	vp.Width = static_cast<FLOAT>(pWindow->GetClientWidth());
	vp.Height = static_cast<FLOAT>(pWindow->GetClientHeight());
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;

	this->m_pDeviceContext->RSSetViewports(1u, &vp);

	this->m_pDepthBuffer.Bind(this->m_pDeviceContext, this->m_pRenderTarget);

	// Create Pipelines
	this->m_pRenderPipelines.reserve(pipelineDescs.size());
	for (const RenderPipelineDesc& pipelineDesc : pipelineDescs)
		this->m_pRenderPipelines.push_back(DirectX11RenderPipeline(this->m_pDevice, pipelineDesc));
}

void DirectX11RenderAPI::Draw(const Drawable& drawable, const size_t nVertices)
{
	this->m_pRenderPipelines[drawable.pipelineIndex].Bind(this->m_pDeviceContext);
	this->m_pVertexBuffers[drawable.vertexBufferIndex]->Bind(this->m_pDeviceContext);
	
	for (const size_t constantBufferIndex : drawable.constantBufferIndices)
		this->m_pConstantBuffers[constantBufferIndex]->Bind(this->m_pDeviceContext);

	if (drawable.indexBufferIndex.has_value()) {
		this->m_pIndexBuffers[drawable.indexBufferIndex.value()]->Bind(this->m_pDeviceContext);

		this->m_pDeviceContext->DrawIndexed(static_cast<UINT>(nVertices), 0u, 0u);
	} else {
		this->m_pDeviceContext->Draw(static_cast<UINT>(nVertices), 0u);
	}
}

void DirectX11RenderAPI::BeginDrawing()
{
	this->Fill();
}

void DirectX11RenderAPI::EndDrawing()
{
	this->m_pDepthBuffer.Clear(this->m_pDeviceContext);
}

void DirectX11RenderAPI::Present(const bool vSync)
{
	this->m_pSwapChain.Present(vSync);
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

size_t DirectX11RenderAPI::CreateConstantBuffer(const size_t objSize, const size_t slotVS, const size_t slotPS, const ShaderBindingType& shaderBindingType, const void* data)
{
	this->m_pConstantBuffers.push_back(std::make_unique<DirectX11ConstantBuffer>(this->m_pDevice, objSize, slotVS, slotPS, shaderBindingType, data));

	return this->m_pConstantBuffers.size() - 1u;
}

void DirectX11RenderAPI::SetVertexBufferData(const size_t index, const size_t nVertices, const void* buff)
{
	this->m_pVertexBuffers[index]->SetData(buff, nVertices, this->m_pDeviceContext);
}

void DirectX11RenderAPI::SetIndexBufferData(const size_t index, const size_t nIndices, const uint32_t* buff)
{
	this->m_pIndexBuffers[index]->SetData(buff, nIndices, this->m_pDeviceContext);
}

void DirectX11RenderAPI::SetConstantBufferData(const size_t index, const void* data)
{
	this->m_pConstantBuffers[index]->SetData(data, this->m_pDeviceContext);
}

void DirectX11RenderAPI::Fill(const Colorf32& color)
{
	this->m_pDeviceContext->ClearRenderTargetView(this->m_pRenderTarget, (float*)&color);
}

#endif // __WEISS__OS_WINDOWS