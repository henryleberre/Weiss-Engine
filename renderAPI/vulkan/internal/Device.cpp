#include "Device.h"

namespace WS       {
namespace Internal {
namespace VK       {

	VKPhysicalDevice::VKPhysicalDevice(const VKInstanceObjectWrapper& instance)
	{
		// Get Physical Devices
		uint32_t deviceCount = 0;
		if (VK_FAILED(vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr)))
			throw std::runtime_error("[VULKAN] Failed To Enumerate Physical Devices");

		if (deviceCount == 0u)
			throw std::runtime_error("[VULKAN] No Vulkan Compatible Devices Where Found");

		std::vector<VkPhysicalDevice> devices(deviceCount);
		if (VK_FAILED(vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data())))
			throw std::runtime_error("[VULKAN] Failed To Enumerate Physical Devices");

		// Pick Physical Device
		std::multimap<uint64_t, VkPhysicalDevice> candidates;
		for (const VkPhysicalDevice& device : devices)
		{
			VkPhysicalDeviceFeatures   deviceFeatures;
			VkPhysicalDeviceProperties deviceProperties;
			vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
			vkGetPhysicalDeviceProperties(device, &deviceProperties);

			uint64_t deviceRating = 0u;
			if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
				deviceRating += 10000u;

			if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
				deviceRating += 2500u;

			if (deviceFeatures.geometryShader)
				candidates.insert({ deviceRating, device });
		}

		if (candidates.size() == 0u)
			throw std::runtime_error("[VULKAN] No Suitable Vulkan Compatible GPU Was Found");

		this->m_pObject = candidates.rbegin()->second;
	}

}; // VK
}; // Internal
}; // WS