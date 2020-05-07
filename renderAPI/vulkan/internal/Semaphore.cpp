#include "Semaphore.h"

namespace WS       {
namespace Internal {
namespace VK       {

	VKSemaphore::VKSemaphore(const VKDevice& device)
		: m_pDevice(&device)
	{
		VkSemaphoreCreateInfo semaphoreInfo{};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		if (VK_FAILED(vkCreateSemaphore(device, &semaphoreInfo, nullptr, &this->m_pObject)))
			throw std::runtime_error("[VULKAN] Failed To Create Sempahore");
	}

	VKSemaphore& VKSemaphore::operator=(const VKSemaphore& other) noexcept
	{
		this->m_pObject = std::move(other.m_pObject);
		this->m_pDevice = std::move(other.m_pDevice);

		return *this;
	}

	VKSemaphore& VKSemaphore::operator=(VKSemaphore&& other) noexcept
	{
		this->m_pObject = std::move(other.m_pObject);
		other.m_pObject = VK_NULL_HANDLE;

		this->m_pDevice = std::move(other.m_pDevice);

		return *this;
	}

	VKSemaphore::~VKSemaphore()
	{
		if (this->m_pObject != VK_NULL_HANDLE)
			vkDestroySemaphore(*this->m_pDevice, this->m_pObject, nullptr);
	}

}; // VK
}; // Internal
}; // WS