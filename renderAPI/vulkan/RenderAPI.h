#pragma once

#include "RenderPipeline.h"
#include "internal/Include.h"
#include "../common/Include.h"

namespace WS       {
namespace Internal {
namespace VK       {

	class VKRenderAPI : public RenderAPI {
	private:
		VKInstance  m_instance;
		VKSurface   m_surface;
		VKDevice    m_device;
		VKSwapChain m_swapChain;

	public:
		VKRenderAPI();

		~VKRenderAPI();

		virtual void InitRenderAPI(Window* pWindow, const uint16_t maxFps) override;
		virtual void InitPipelines(const std::vector<RenderPipelineDesc>& pipelineDescs) override;

		virtual void Draw(const Drawable& drawable, const size_t nVertices) override;

		virtual void BeginDrawing() override;
		virtual void EndDrawing()   override;
		virtual void Present(const bool vSync) override;

		virtual size_t CreateVertexBuffer  (const size_t nVertices, const size_t vertexSize) override;
		virtual size_t CreateIndexBuffer   (const size_t nIndices) override;
		virtual size_t CreateConstantBuffer(const size_t objSize, const size_t slot) override;
		virtual size_t CreateTexture       (const size_t width, const size_t height, const size_t slot, const bool useMipmaps = false) override;
		virtual size_t CreateTextureSampler(const TextureFilter& filter, const size_t slot) override;

		virtual void Fill(const Colorf32& color = { 1.f, 1.f, 1.f, 1.f }) override;
	};

}; // VK
}; // Internal
}; // WS