#pragma once

#include "Shaders.h"
#include "Buffers.h"
#include "RenderPipeline.h"
#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX11RenderPipeline;

class DirectX11RenderAPI : public RenderAPI {
private:
	DirectX11DeviceObjectWrapper m_pDevice;
	DirectX11DeviceContextObjectWrapper m_pDeviceContext;
	DirectX11SwapChain    m_pSwapChain;
	DirectX11RenderTarget m_pRenderTarget;
	DirectX11DepthBuffer  m_pDepthBuffer;

	std::vector<DirectX11RenderPipeline> m_pRenderPipelines;

public:
	DirectX11RenderAPI();
	
	virtual void InitRenderAPI(Window* pWindow) override;
	virtual void InitPipelines(const std::vector<RenderPipelineDesc>& pipelineDescs) override;

	virtual void Draw(const Drawable& drawable, const size_t nVertices) override;

	virtual void BeginDrawing() override;
	virtual void EndDrawing()   override;
	virtual void Present(const bool vSync) override;

	virtual size_t CreateVertexBuffer(const size_t nVertices, const size_t vertexSize) override;
	virtual size_t CreateIndexBuffer (const size_t nIndices) override;
	virtual size_t CreateConstantBuffer(const size_t objSize, const size_t slotVS, const size_t slotPS, const ShaderBindingType& shaderBindingType) override;

	virtual void Fill(const Colorf32& color = { 1.f, 1.f, 1.f, 1.f }) override;
};

#endif // __WEISS__OS_WINDOWS