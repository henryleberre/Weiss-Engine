#pragma once

#include "Shaders.h"
#include "Buffers.h"
#include "RenderPipeline.h"
#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D11    {

	class D3D11RenderPipeline;

	class D3D11RenderAPI : public RenderAPI {
	private:
		D3D11DeviceObjectWrapper        m_pDevice;
		D3D11DeviceContextObjectWrapper m_pDeviceContext;
		D3D11SwapChain    m_pSwapChain;
		D3D11RenderTarget m_pRenderTarget;
		D3D11DepthBuffer  m_pDepthBuffer;

		std::vector<D3D11RenderPipeline> m_pRenderPipelines;

		public:
			D3D11RenderAPI();

			virtual void InitRenderAPI(Window* pWindow, const uint16_t maxFps) override;
			virtual void InitPipelines(const std::vector<RenderPipelineDesc>& pipelineDescs) override;

			virtual void Draw(const Drawable& drawable, const size_t nVertices) override;

			virtual void BeginDrawing() override;
			virtual void EndDrawing()   override;
			virtual void Present(const bool vSync) override;

			virtual size_t CreateVertexBuffer(const size_t nVertices, const size_t vertexSize) override;
			virtual size_t CreateIndexBuffer(const size_t nIndices) override;
			virtual size_t CreateConstantBuffer(const size_t objSize, const size_t slotVS, const size_t slotPS, const ShaderBindingType& shaderBindingType) override;

			virtual void Fill(const Colorf32& color = { 1.f, 1.f, 1.f, 1.f }) override;
	};

}; // D3D11
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS