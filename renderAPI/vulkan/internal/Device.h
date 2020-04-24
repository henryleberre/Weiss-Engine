#pragma once

#include "Surface.h"
#include "Instance.h"
#include "ObjectWrapper.h"

namespace WS       {
namespace Internal {
namespace VK       {

	class VKDevice;

	typedef VKObjectWrapper<VkQueue> VKQueueObjectWrapper;

	class VKQueue : public VKQueueObjectWrapper {
	public:
		VKQueue() = default;
		VKQueue(VKDevice& device, const size_t queueIndex);

		void operator=(VKQueue& other);
		void operator=(VKQueue&& other);
	};
	
	struct VKPhysicalDeviceDataWrapper {
		VkPhysicalDevice                     m_physicalDevice;
		VkPhysicalDeviceFeatures             m_features;
		VkPhysicalDeviceProperties           m_propreties;
		std::vector<VkQueueFamilyProperties> m_queueFamilyPropreties;

		union {
			struct {
				std::optional<uint32_t> m_graphicsQueueIndex;
				std::optional<uint32_t> m_presentQueueIndex;
			};
			struct { std::optional<uint32_t> m_queueIndices[2]; };
		};

		uint32_t m_rating = 0u;

		VKPhysicalDeviceDataWrapper();
		VKPhysicalDeviceDataWrapper(const VkPhysicalDevice& physicalDevice, const VKSurface& surface);
	};

	typedef VKObjectWrapper<VkDevice> VKDeviceObjectWrapper;

	class VKDevice : public VKDeviceObjectWrapper {
	private:
		VKPhysicalDeviceDataWrapper m_physicalDeviceData;
		
		union {
			struct { VKQueue m_graphicsQueue, m_presentQueue; };
			struct { std::array<VKQueue, 2u> m_queues; };
		};

	public:
		VKDevice();
		VKDevice(const VKInstance& instance, const VKSurface& surface);

		void operator=(VKDevice&& device) noexcept;

		~VKDevice();

	private:
		void PickPhysicalDevice(const VKInstance& instance, const VKSurface& surface);
		void CreateLogicalDeviceAndQueues(const VKInstance& instance);
	};

}; // VK
}; // Internal
}; // WS