#include "RenderAPI.h"

#ifdef __WEISS__OS_WINDOWS

void DirectX11RenderAPI::SetPrimitiveTopology(const PrimitiveTopology& topology)
{
	D3D11_PRIMITIVE_TOPOLOGY d3d11PrimitiveTopology;

	switch (topology)
	{
	case PrimitiveTopology::TRIANGLES:
		d3d11PrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		break;
	case PrimitiveTopology::TRIANGLE_STRIP:
		d3d11PrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
		break;
	default:
		throw std::runtime_error("The Primitive Topology Type You Resquested Is Not Supported For DirectX11");
		break;
	}

	this->m_pDevice->GetDeviceContext()->IASetPrimitiveTopology(d3d11PrimitiveTopology);
}

DirectX11RenderAPI::DirectX11RenderAPI() : RenderAPI(RenderAPIName::DIRECTX11) {}

void DirectX11RenderAPI::InitRenderAPI(Window* pWindow)
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
}

void DirectX11RenderAPI::Draw(const Drawable& drawable, const size_t nVertices)
{
	this->m_renderPipelines[drawable.shaderPairIndex].pVertexShader->Bind();
	this->m_renderPipelines[drawable.shaderPairIndex].pPixelShader->Bind();

	this->SetPrimitiveTopology(this->m_renderPipelines[drawable.shaderPairIndex].topology);

	this->m_vertexBuffers[drawable.vertexBufferIndex]->Bind();
	if (drawable.indexBufferIndex.has_value()) {
		this->m_indexBuffers[drawable.indexBufferIndex.value()]->Bind();

		this->m_pDevice->GetDeviceContext()->DrawIndexed(nVertices, 0u, 0u);
	} else {
		this->m_pDevice->GetDeviceContext()->Draw(nVertices, 0u);
	}
}

void DirectX11RenderAPI::SwapBuffers()
{
	this->m_pDepthBuffer->Clear();
	this->m_pSwapChain->Present();
}

size_t DirectX11RenderAPI::CreateRenderPipeline(const char* vsFilename, const std::vector<ShaderInputElement>& sies, const char* psFilename, const PrimitiveTopology& topology)
{
	this->m_renderPipelines.push_back({
		new DirectX11VertexShader(this->m_pDevice, vsFilename, sies),
		new DirectX11PixelShader (this->m_pDevice, psFilename),
		topology
	});

	return this->m_renderPipelines.size() - 1u;
}

size_t DirectX11RenderAPI::CreateVertexBuffer(const size_t vertexSize, const size_t nVertices, const void* buff)
{
	this->m_vertexBuffers.push_back(new DirectX11VertexBuffer(this->m_pDevice, vertexSize, nVertices, buff));

	return this->m_vertexBuffers.size() - 1u;
}

size_t DirectX11RenderAPI::CreateIndexBuffer(const size_t nIndices, const void* buff)
{
	this->m_indexBuffers.push_back(new DirectX11IndexBuffer(this->m_pDevice, nIndices, buff));

	return this->m_indexBuffers.size() - 1u;
}

[[nodiscard]] std::shared_ptr<DirectX11Device> DirectX11RenderAPI::GetDevice() noexcept { return this->m_pDevice; }

#endif // __WEISS__OS_WINDOWS