#pragma once

#include "ObjectWrapper.h"
#include "Instance.h"

namespace WS       {
namespace Internal {
namespace VK       {

	typedef VKObjectWrapper<VkPhysicalDevice> VKPhysicalDeviceObjectWrapper;

	class VKPhysicalDevice : public VKPhysicalDeviceObjectWrapper {
	public:
		VKPhysicalDevice() = default;

		VKPhysicalDevice(const VKInstanceObjectWrapper& instance);
	};

	typedef VKObjectWrapper<VkDevice> VKLogicalDeviceObjectWrapper;

	class VKLogicalDevice : public VKLogicalDeviceObjectWrapper {

	};

}; // VK
}; // Internal
}; // WS