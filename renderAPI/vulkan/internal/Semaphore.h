#pragma once

#include "Device.h"
#include "ObjectWrapper.h"

namespace WS       {
namespace Internal {
namespace VK       {

	typedef VKObjectWrapper<VkSemaphore> VKSemaphoreObjectWrapper;

	class VKSemaphore : public VKSemaphoreObjectWrapper {
	private:
		const VKDevice* m_pDevice = nullptr;

	public:
		VKSemaphore() = default;

		VKSemaphore(const VKDevice& device);

		VKSemaphore& operator=(const VKSemaphore& other) noexcept;
		VKSemaphore& operator=(VKSemaphore&& other) noexcept;

		~VKSemaphore();
	};

}; // VK
}; // Internal
}; // WS