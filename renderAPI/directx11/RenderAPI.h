#pragma once

#include "Shaders.h"
#include "Buffers.h"
#include "RenderPipeline.h"
#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX11RenderAPI : public RenderAPI {
private:
	DirectX11DeviceObjectWrapper m_pDevice;
	DirectX11DeviceContextObjectWrapper m_pDeviceContext;
	DirectX11SwapChain    m_pSwapChain;
	DirectX11RenderTarget m_pRenderTarget;
	DirectX11DepthBuffer  m_pDepthBuffer;

	std::vector<std::unique_ptr<DirectX11VertexBuffer>>   m_pVertexBuffers;
	std::vector<std::unique_ptr<DirectX11IndexBuffer>>    m_pIndexBuffers;
	std::vector<std::unique_ptr<DirectX11ConstantBuffer>> m_pConstantBuffers;
	std::vector<DirectX11RenderPipeline> m_pRenderPipelines;

public:
	DirectX11RenderAPI();

	virtual void InitRenderAPI(Window* pWindow, const std::vector<RenderPipelineDesc>& pipelineDescs) override;

	virtual void Draw(const Drawable& drawable, const size_t nVertices) override;

	virtual void BeginDrawing() override;
	virtual void EndDrawing()   override;
	virtual void Present(const bool vSync) override;

	virtual size_t CreateVertexBuffer(const size_t vertexSize, const size_t nVertices, const void* buff = nullptr) override;
	virtual size_t CreateIndexBuffer (const size_t nIndices, const void* buff = nullptr) override;
	virtual size_t CreateConstantBuffer(const size_t objSize, const size_t slotVS, const size_t slotPS, const ShaderBindingType& shaderBindingType, const void* data = nullptr) override;

	virtual void SetVertexBufferData(const size_t index, const size_t nVertices, const void*     buff) override;
	virtual void SetIndexBufferData (const size_t index, const size_t nIndices,  const uint32_t* buff) override;
	virtual void SetConstantBufferData(const size_t index, const void* data) override;

	virtual void Fill(const Colorf32& color = { 1.f, 1.f, 1.f, 1.f }) override;
};

#endif // __WEISS__OS_WINDOWS