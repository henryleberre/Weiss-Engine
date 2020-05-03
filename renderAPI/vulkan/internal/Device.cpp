#include "Device.h"

namespace WS       {
namespace Internal {
namespace VK       {

	VKQueue::VKQueue(VKDevice& device, const size_t queueIndex)
	{
		vkGetDeviceQueue(device, queueIndex, 0, &this->m_pObject);
	}

	void VKQueue::operator=(VKQueue& other)
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = VK_NULL_HANDLE;
	}

	VKQueue& VKQueue::operator=(VKQueue&& other)
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = VK_NULL_HANDLE;

		return *this;
	}


	VKPhysicalDeviceDataWrapper::VKPhysicalDeviceDataWrapper()
	{
		
	}

	VKPhysicalDeviceDataWrapper::VKPhysicalDeviceDataWrapper(const VkPhysicalDevice& physicalDevice, const VKSurface& surface)
		: m_physicalDevice(physicalDevice)
	{
		vkGetPhysicalDeviceFeatures  (physicalDevice, &this->m_features);
		vkGetPhysicalDeviceProperties(physicalDevice, &this->m_propreties);

		uint32_t familyCount;
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &familyCount, nullptr);

		this->m_queueFamilyPropreties.resize(familyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &familyCount, this->m_queueFamilyPropreties.data());

		uint32_t i = 0u;
		for (const VkQueueFamilyProperties& queueFamily : this->m_queueFamilyPropreties)
		{
			const VkQueueFlags queueFlags = queueFamily.queueFlags;

			if (queueFlags & VK_QUEUE_GRAPHICS_BIT)
				this->m_graphicsQueueIndex = i;


			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &presentSupport);

			if (presentSupport)
				this->m_presentQueueIndex = i;

			i++;
		}
		
		switch (this->m_propreties.deviceType)
		{
		case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
			this->m_rating += 10u;
			break;
		case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
			this->m_rating += 3;
			break;
		}

		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

		this->m_extensionPropreties.resize(extensionCount);
		vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, this->m_extensionPropreties.data());
	}

	VKDevice::VKDevice()
	{

	}

	VKDevice::VKDevice(const VKInstance& instance, const VKSurface& surface)
	{
		this->PickPhysicalDevice(instance, surface);
		this->CreateLogicalDeviceAndQueues(instance);
	}

	VKDevice& VKDevice::operator=(VKDevice&& device) noexcept
	{
		this->m_graphicsQueue = device.m_graphicsQueue;
		this->m_physicalDeviceData = device.m_physicalDeviceData;
		this->m_presentQueue = device.m_presentQueue;
		this->m_queues = device.m_queues;
		this->m_pObject = device.m_pObject;
		device.m_pObject = nullptr;

		return *this;
	}

	VKDevice::~VKDevice()
	{

	}

	void VKDevice::PickPhysicalDevice(const VKInstance& instance, const VKSurface& surface)
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

		// Pick
		std::multimap<uint64_t, VKPhysicalDeviceDataWrapper> candidates;
		for (const VkPhysicalDevice& physicalDevice : devices)
		{
			const VKPhysicalDeviceDataWrapper physicalDeviceDataWrapper(physicalDevice, surface);

			if (physicalDeviceDataWrapper.m_graphicsQueueIndex.has_value() && physicalDeviceDataWrapper.m_presentQueueIndex.has_value())
				candidates.insert({ physicalDeviceDataWrapper.m_rating, physicalDeviceDataWrapper });
		}

		if (candidates.size() == 0u)
			throw std::runtime_error("[VULKAN] No Suitable Vulkan Compatible GPU Was Found");

		this->m_physicalDeviceData = candidates.rbegin()->second;
	}

	void VKDevice::CreateLogicalDeviceAndQueues(const VKInstance& instance)
	{
		/* Check Extension Support */
		const std::vector<const char*> requiredExtensions  = VKDevice::GetRequiredExtensions();

		for (const char* requiredExtension : requiredExtensions)
		{
			bool bFound = false;

			for (VkExtensionProperties& availableExtensionPropreties : this->m_physicalDeviceData.m_extensionPropreties)
			{
				if (strcmp(requiredExtension, availableExtensionPropreties.extensionName) == 0)
				{
					bFound = true;
					break;
				}
			}

			if (!bFound)
			{
				const std::string errorString = "[VULKAN] Extension \"" + std::string(requiredExtension) + std::string("\" Is Not Supported");
				throw std::runtime_error(errorString.c_str());
			}
		}

		/* Create Logical Device */

		std::array<VkDeviceQueueCreateInfo, 2u> queueCreateInfos;

		uint32_t i = 0u;
		for (VkDeviceQueueCreateInfo& queueCreateInfo : queueCreateInfos)
		{
			queueCreateInfo = {};
			queueCreateInfo.sType      = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueCount = 1u;
			queueCreateInfo.queueFamilyIndex = this->m_physicalDeviceData.m_queueIndices[i++].value();

			float queuePriority = 1.0f;
			queueCreateInfo.pQueuePriorities = &queuePriority;
		}

		VkPhysicalDeviceFeatures deviceFeatures = {};

		VkDeviceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos       = queueCreateInfos.data();
		createInfo.queueCreateInfoCount    = queueCreateInfos.size();
		createInfo.pEnabledFeatures        = &deviceFeatures;
		createInfo.enabledLayerCount       = 0u;
		createInfo.ppEnabledLayerNames     = nullptr;
		createInfo.enabledExtensionCount   = requiredExtensions.size();
		createInfo.ppEnabledExtensionNames = requiredExtensions.data();

		if (VK_FAILED(vkCreateDevice(this->m_physicalDeviceData.m_physicalDevice, &createInfo, nullptr, &this->m_pObject)))
			throw std::runtime_error("|VULKAN] Failed To Create Logical Device");

		/* Create The Queues */

		for (size_t i = 0u; i < queueCreateInfos.size(); i++)
			this->m_queues[i] = VKQueue(*this, this->m_physicalDeviceData.m_queueIndices[i].value());
	}

	std::vector<const char*> VKDevice::GetRequiredExtensions()  noexcept
	{
		return { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
	}

}; // VK
}; // Internal
}; // WS