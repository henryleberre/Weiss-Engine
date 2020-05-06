#include "CommandPool.h"

namespace WS       {
namespace Internal {
namespace VK       {

	VKCommandPool::VKCommandPool(const VKDevice& device, const uint32_t queueFamilyIndex)
		: m_pDevice(&device)
	{
		VkCommandPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.flags = 0;
		poolInfo.queueFamilyIndex = queueFamilyIndex;

		if (VK_FAILED(vkCreateCommandPool(device, &poolInfo, nullptr, &this->m_pObject)))
			throw std::runtime_error("[VULKAN] Failed To Create Command Pool");
	}

	VKCommandPool& VKCommandPool::operator=(VKCommandPool&& other) noexcept
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = VK_NULL_HANDLE;

		this->m_pDevice = std::move(other.m_pDevice);

		return *this;
	}

	VKCommandPool::~VKCommandPool()
	{
		vkDestroyCommandPool(*this->m_pDevice, this->m_pObject, nullptr);
	}

}; // VK
}; // Internal
}; // WS