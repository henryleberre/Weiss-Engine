#include "CommandBuffer.h"

namespace WS       {
namespace Internal {
namespace VK       {

	VKCommandBuffer::VKCommandBuffer(const VKDevice& device, const VKCommandPool& commandPool)
		: m_pDevice(&device)
	{
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = commandPool;
		allocInfo.commandBufferCount = 1u;
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;

		if (VK_FAILED(vkAllocateCommandBuffers(device, &allocInfo, &this->m_pObject)))
			throw std::runtime_error("[VULKAN] Failed To Create Command Buffer");
	}

	VKCommandBuffer& VKCommandBuffer::operator=(VKCommandBuffer&& other) noexcept
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = VK_NULL_HANDLE;

		this->m_pDevice = other.m_pDevice;

		return *this;
	}

	void VKCommandBuffer::BeginRecording() const
	{
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.flags = 0;
		beginInfo.pInheritanceInfo = nullptr;
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (VK_FAILED(vkBeginCommandBuffer(this->m_pObject, &beginInfo)))
			throw std::runtime_error("[VULKAN] Failed To Begin Command Buffer Recording");
	}

	void VKCommandBuffer::BeginRenderPass(const VKSwapChain& swapChain, const VkFramebuffer& frameBuffer, const VkRenderPass& renderPass) const noexcept
	{
		VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.renderPass  = renderPass;
		renderPassInfo.framebuffer = frameBuffer;
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues    = &clearColor;
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = swapChain.GetImageExtent();
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;

		vkCmdBeginRenderPass(this->m_pObject, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
	}

	void VKCommandBuffer::BeginColorRenderPass(const VKSwapChain& swapChain, const size_t frameIndex) const noexcept
	{
		this->BeginRenderPass(swapChain, swapChain.GetColorFrameBuffer(frameIndex), VKRenderPass::s_colorRenderPass);
	}

	void VKCommandBuffer::EndRenderPass()
	{
		vkCmdEndRenderPass(this->m_pObject);
	}

	void VKCommandBuffer::EndRecording() const
	{
		if (VK_FAILED(vkEndCommandBuffer(this->m_pObject)))
			throw std::runtime_error("[VULKAN] Failed To End Command Buffer Recording");
	}

}; // VK
}; // Internal
}; // WS