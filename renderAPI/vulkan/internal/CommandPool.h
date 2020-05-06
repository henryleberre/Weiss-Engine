#pragma once

#include "Device.h"
#include "ObjectWrapper.h"

namespace WS       {
namespace Internal {
namespace VK       {

	typedef VKObjectWrapper<VkCommandPool> VKCommandPoolObjectWrapper;

	class VKCommandPool : public VKCommandPoolObjectWrapper
	{
	private:
		const VKDevice* m_pDevice = nullptr;

	public:
		VKCommandPool() = default;

		VKCommandPool(const VKDevice& device, const uint32_t queueFamilyIndex);

		VKCommandPool& operator=(VKCommandPool&& other) noexcept;

		~VKCommandPool();
	};

}; // VK
}; // Internal
}; // WS