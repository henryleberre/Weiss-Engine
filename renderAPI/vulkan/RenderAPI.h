#pragma once

#include "Shaders.h"
#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

struct VulkanRenderPipeline {
	std::unique_ptr<VulkanVertexShader> pVertexShader;
	std::unique_ptr<VulkanPixelShader>  pPixelShader;
	PrimitiveTopology topology;

	VkPipeline pipeline;
};

class VulkanRenderAPI : public RenderAPI {
private:
	std::shared_ptr<VulkanDevice> m_pDevice;
	std::shared_ptr<VulkanSurface> m_pSurface;
	std::shared_ptr<VulkanInstance> m_pInstance;
	std::shared_ptr<VulkanSwapChain> m_pSwapChain;

	std::vector<VulkanRenderPipeline> m_renderPipelines;

public:
	VulkanRenderAPI();

	virtual void InitRenderAPI(Window* pWindow) override;

	virtual void Draw(const Drawable& drawable, const size_t nVertices) = 0;

	virtual void SwapBuffers() override;

	virtual size_t CreateRenderPipeline(const char* vsFilename, const std::vector<ShaderInputElement>& sies, const char* psFilename, const PrimitiveTopology& topology = PrimitiveTopology::TRIANGLES) override;

	virtual size_t CreateVertexBuffer(const size_t vertexSize, const size_t nVertices, const void* buff = nullptr) override;
	virtual size_t CreateIndexBuffer(const size_t nIndices, const void* buff = nullptr) override;
};