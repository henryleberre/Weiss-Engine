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

	void VKCommandBuffer::EndRecording() const
	{
		if (VK_FAILED(vkEndCommandBuffer(this->m_pObject)))
			throw std::runtime_error("[VULKAN] Failed To End Command Buffer Recording");
	}

}; // VK
}; // Internal
}; // WS