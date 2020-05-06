#pragma once

#include "Device.h"
#include "SwapChain.h"
#include "ObjectWrapper.h"

namespace WS       {
namespace Internal {
namespace VK       {

	class VKSwapChain;

	class VKRenderPass {
	public:
		static VkRenderPass s_colorRenderPass;

	public:
		static void CreateRenderPasses(const VKDevice& device, const VKSwapChain& swapChain);

		static void DestroyRenderPasses(const VKDevice& device);
	};

}; // VK
}; // Internal
}; // WS