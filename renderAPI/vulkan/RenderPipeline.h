#pragma once

#include "TextureSampler.h"
#include "internal/Include.h"
#include "../common/Include.h"

namespace WS       {
namespace Internal {
namespace VK       {

	class VKRenderPipeline {
	private:
		const VKDevice* m_pDevice = nullptr;

		VkPipelineLayout m_layout   = VK_NULL_HANDLE;
		VkPipeline       m_pipeline = VK_NULL_HANDLE;

	public:
		VKRenderPipeline() = default;

		VKRenderPipeline& operator=(VKRenderPipeline&& other);

		VKRenderPipeline(const VKDevice& device, const VKSwapChain& swapChain, const RenderPipelineDesc& pipelineDesc,
						 std::vector<ConstantBuffer*>& pConstantBuffers, std::vector<Texture*> pTextures, std::vector<VKTextureSampler*> pTextureSamplers);

		~VKRenderPipeline();

	private:
		static VkShaderModule CreateShaderModule(const VKDevice& device, const char* filename);
	};

}; // VK
}; // Internal
}; // WS