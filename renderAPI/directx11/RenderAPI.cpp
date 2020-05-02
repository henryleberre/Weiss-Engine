#include "RenderAPI.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D11    {

	D3D11RenderAPI::D3D11RenderAPI() : RenderAPI(RenderAPIName::DIRECTX11) {}

	void D3D11RenderAPI::InitRenderAPI(Window* pWindow, const uint16_t maxFps)
	{
		if (D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, this->m_pDevice.GetPtr(), nullptr, this->m_pDeviceContext.GetPtr()) != S_OK)
			throw std::runtime_error("Could Not Create Device");

		this->m_pSwapChain    = D3D11SwapChain(this->m_pDevice, pWindow);
		this->m_pRenderTarget = D3D11RenderTarget(this->m_pDevice, this->m_pSwapChain);
		this->m_pDepthBuffer  = D3D11DepthBuffer(pWindow, this->m_pDevice);

		this->m_pRenderTarget.SetCurrent(this->m_pDeviceContext);

		// Create Viewport
		D3D11_VIEWPORT vp;
		vp.Width    = static_cast<FLOAT>(pWindow->GetClientWidth());
		vp.Height   = static_cast<FLOAT>(pWindow->GetClientHeight());
		vp.MinDepth = 0;
		vp.MaxDepth = 1;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;

		this->m_pDeviceContext->RSSetViewports(1u, &vp);

		this->m_pDepthBuffer.Bind(this->m_pDeviceContext, this->m_pRenderTarget);
	}

	void D3D11RenderAPI::InitPipelines(const std::vector<RenderPipelineDesc>& pipelineDescs)
	{
		this->m_pRenderPipelines.reserve(pipelineDescs.size());
		for (const RenderPipelineDesc& pipelineDesc : pipelineDescs)
			this->m_pRenderPipelines.emplace_back(this->m_pDevice, &this->m_pDeviceContext, pipelineDesc);
	}

	void D3D11RenderAPI::Draw(const Drawable& drawable, const size_t nVertices)
	{
		this->m_pRenderPipelines[drawable.pipelineIndex].Bind(this->m_pConstantBuffers, this->m_pTextures, this->m_pTextureSamplers);
		dynamic_cast<D3D11VertexBuffer*>(this->m_pVertexBuffers[drawable.vertexBufferIndex])->Bind();

		if (drawable.indexBufferIndex.has_value()) {
			dynamic_cast<D3D11IndexBuffer*>(this->m_pIndexBuffers[drawable.indexBufferIndex.value()])->Bind();

			this->m_pDeviceContext->DrawIndexed(static_cast<UINT>(nVertices), 0u, 0u);
		} else {
			this->m_pDeviceContext->Draw(static_cast<UINT>(nVertices), 0u);
		}
	}

	void D3D11RenderAPI::BeginDrawing()
	{
		this->Fill();
	}

	void D3D11RenderAPI::EndDrawing()
	{
		this->m_pDepthBuffer.Clear(this->m_pDeviceContext);
	}

	void D3D11RenderAPI::Present(const bool vSync)
	{
		this->m_pSwapChain.Present(vSync);
	}

	size_t D3D11RenderAPI::CreateVertexBuffer(const size_t nVertices, const size_t vertexSize)
	{
		this->m_pVertexBuffers.push_back(new D3D11VertexBuffer(this->m_pDevice, &this->m_pDeviceContext, nVertices, vertexSize));

		return this->m_pVertexBuffers.size() - 1u;
	}

	size_t D3D11RenderAPI::CreateIndexBuffer(const size_t nIndices)
	{
		this->m_pIndexBuffers.push_back(new D3D11IndexBuffer(this->m_pDevice, &this->m_pDeviceContext, nIndices));

		return this->m_pIndexBuffers.size() - 1u;
	}

	size_t D3D11RenderAPI::CreateConstantBuffer(const size_t objSize, const size_t slot)
	{
		this->m_pConstantBuffers.push_back(new D3D11ConstantBuffer(this->m_pDevice, &this->m_pDeviceContext, objSize, slot));

		return this->m_pConstantBuffers.size() - 1u;
	}

	size_t D3D11RenderAPI::CreateTexture(const size_t width, const size_t height, const size_t slot, const bool useMipmaps)
	{
		this->m_pTextures.push_back(new D3D11Texture(this->m_pDevice, &this->m_pDeviceContext, width, height, slot, useMipmaps));

		return this->m_pTextures.size() - 1u;
	}

	size_t D3D11RenderAPI::CreateTextureSampler(const TextureFilter& filter, const size_t slot)
	{
		this->m_pTextureSamplers.push_back(new D3D11TextureSampler(this->m_pDevice, &this->m_pDeviceContext, filter, slot));

		return this->m_pTextureSamplers.size() - 1u;
	}

	void D3D11RenderAPI::Fill(const Colorf32& color)
	{
		this->m_pDeviceContext->ClearRenderTargetView(this->m_pRenderTarget, (float*)&color);
	}

}; // D3D11
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS