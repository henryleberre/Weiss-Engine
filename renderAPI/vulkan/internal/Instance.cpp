#include "Instance.h"

namespace WS       {
namespace Internal {
namespace VK       {

	VKInstance::VKInstance()
	{
		
	}

	VKInstance::VKInstance(const char* appName)
	{
		const std::vector<VkExtensionProperties> availableExtensionsPropreties = VKInstance::GetAvailableExtensionsPropreties();
		const std::vector<const char*>           requiredExtensions           = VKInstance::GetRequiredExtensions();

		for (const char* requiredExtension : requiredExtensions)
		{
			bool bFound = false;

			for (const VkExtensionProperties& availableExtensionPropreties : availableExtensionsPropreties)
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

		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "My Super App Using Weiss Engine";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "Weiss Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledExtensionCount   = requiredExtensions.size();
		createInfo.ppEnabledExtensionNames = requiredExtensions.data();

		if (VK_FAILED(vkCreateInstance(&createInfo, nullptr, &this->m_pObject)))
			throw std::runtime_error("[VULKAN] Failed To Create Instance");
	}

	void VKInstance::operator=(VKInstance&& instance) noexcept
	{
		this->m_pObject    = instance.m_pObject;
		instance.m_pObject = VK_NULL_HANDLE;
	}

	VKInstance::~VKInstance()
	{
		if (this->m_pObject != VK_NULL_HANDLE)
			vkDestroyInstance(this->m_pObject, nullptr);
	}

	std::vector<VkExtensionProperties> VKInstance::GetAvailableExtensionsPropreties() noexcept
	{
		uint32_t extensionCount = 0;
		if (VK_FAILED(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr)))
			throw std::runtime_error("[VULKAN] Failed To Enumerate Instance Extension Propreties");

		std::vector<VkExtensionProperties> extensions(extensionCount);
		if (VK_FAILED(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data())))
			throw std::runtime_error("[VULKAN] Failed To Enumerate Instance Extension Propreties");

		return extensions;
	}

	std::vector<const char*> VKInstance::GetRequiredExtensions() noexcept
	{
		std::vector<const char*> extensions;

#ifdef __WEISS__DEBUG_MODE

		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

#endif // _DEBUG

#ifdef __WEISS__OS_WINDOWS

		extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
		extensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);

#endif // __WEISS__OS_WINDOWS

		return extensions;
	}

}; // VK
}; // Internal
}; // WS