#include "Instance.h"

namespace WS       {
namespace Internal {
namespace VK       {

	VKInstance::VKInstance()
	{
		
	}

	VKInstance::VKInstance(const char* appName)
	{
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

		if (VK_FAILED(vkCreateInstance(&createInfo, nullptr, &this->m_pObject)))
			throw std::runtime_error("[VULKAN] Failed To Create Instance");

		uint32_t extensionCount = 0;
		if (VK_FAILED(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr)))
			throw std::runtime_error("[VULKAN] Failed To Enumerate Instance Extension Propreties");

		std::vector<VkExtensionProperties> extensions(extensionCount);
		if (VK_FAILED(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data())))
			throw std::runtime_error("[VULKAN] Failed To Enumerate Instance Extension Propreties");

		std::cout << "available extensions:\n";

		for (const auto& extension : extensions) {
			std::cout << '\t' << extension.extensionName << '\n';
		}
	}

	void VKInstance::operator=(VKInstance&& instance) noexcept
	{
		this->m_pObject    = instance.m_pObject;
		instance.m_pObject = nullptr;
	}

	VKInstance::~VKInstance()
	{
		vkDestroyInstance(this->m_pObject, nullptr);
	}

}; // VK
}; // Internal
}; // WS