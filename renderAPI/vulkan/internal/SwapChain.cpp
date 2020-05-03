#include "SwapChain.h"

namespace WS       {
namespace Internal {
namespace VK       {

	VKSwapChain::VKSwapChain(VKDevice& pDevice, VKSurface& pSurface)
		: m_pDevice(&pDevice), m_pSurface(&pSurface)
	{
		this->CreateSwapChain();
	}

	VKSwapChain& VKSwapChain::operator=(VKSwapChain&& other) noexcept
	{
		this->m_images = std::move(other.m_images);
		this->m_imageViews = std::move(other.m_imageViews);
		this->m_pDevice = std::move(other.m_pDevice);
		this->m_pObject = std::move(other.m_pObject);
		this->m_pSurface = std::move(other.m_pSurface);
		this->m_surfaceFormat = std::move(other.m_surfaceFormat);

		return *this;
	}

	VKSwapChain::~VKSwapChain()
	{
		for (VkImageView& imageView : this->m_imageViews)
			if (imageView != VK_NULL_HANDLE)
				vkDestroyImageView(*this->m_pDevice, imageView, nullptr);

		if (this->m_pObject != VK_NULL_HANDLE)
			vkDestroySwapchainKHR(*this->m_pDevice, this->m_pObject, nullptr);
	}

	VkPresentModeKHR VKSwapChain::PickPresentingMode() const
	{
		const VkSurfaceKHR&     surface        = *this->m_pSurface;
		const VkPhysicalDevice& physicalDevice = this->m_pDevice->GetPhysicalDeviceData().m_physicalDevice;

		uint32_t nSupportedPresentingModes;
		vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &nSupportedPresentingModes, nullptr);

		if (nSupportedPresentingModes == 0u)
			throw std::runtime_error("[VULKAN] No Compatible Presenting Mode Could Be Found");

		std::vector<VkPresentModeKHR> supportedPresentingModes(nSupportedPresentingModes);
		vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &nSupportedPresentingModes, supportedPresentingModes.data());

		if (supportedPresentingModes.size() == 0u)
			throw std::runtime_error("[VULKAN] No Compatible Presenting Mode Could Be Found");

		for (const VkPresentModeKHR mode : supportedPresentingModes)
			if (mode == VkPresentModeKHR::VK_PRESENT_MODE_MAILBOX_KHR)
				return mode;

		return supportedPresentingModes[0];
	}

	VkSurfaceFormatKHR VKSwapChain::PickSurfaceFormat() const
	{
		const VkSurfaceKHR&     surface        = *this->m_pSurface;
		const VkPhysicalDevice& physicalDevice = this->m_pDevice->GetPhysicalDeviceData().m_physicalDevice;

		uint32_t nSupportedFormats;
		vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &nSupportedFormats, nullptr);

		if (nSupportedFormats == 0u) return {};

		std::vector<VkSurfaceFormatKHR> supportedFormats(nSupportedFormats);
		vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &nSupportedFormats, supportedFormats.data());

		if (supportedFormats.size() == 0u)
			throw std::runtime_error("[VULKAN] No Supported Surface Format Where Found");

		for (const VkSurfaceFormatKHR& surfaceFormat : supportedFormats)
			if (surfaceFormat.format == VK_FORMAT_B8G8R8A8_SRGB && surfaceFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
				return surfaceFormat;

		return supportedFormats[0];
	}

	void VKSwapChain::CreateSwapChain()
	{
		VKDevice&     device  = *this->m_pDevice;
		VkSurfaceKHR& surface = *this->m_pSurface;

		this->m_surfaceFormat = this->PickSurfaceFormat();

		VkSwapchainCreateInfoKHR createInfo = {};
		createInfo.sType              = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface            = surface;
		createInfo.minImageCount      = 2u;
		createInfo.imageFormat        = this->m_surfaceFormat.format;
		createInfo.imageColorSpace    = this->m_surfaceFormat.colorSpace;
		createInfo.imageExtent.width  = this->m_pSurface->GetDimensions().x;
		createInfo.imageExtent.height = this->m_pSurface->GetDimensions().y;
		createInfo.imageArrayLayers   = 1;
		createInfo.imageUsage         = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		createInfo.preTransform       = VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
		createInfo.compositeAlpha     = VkCompositeAlphaFlagBitsKHR::VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode        = this->PickPresentingMode();
		createInfo.clipped            = VK_TRUE;
		createInfo.oldSwapchain       = VK_NULL_HANDLE;

		const VKPhysicalDeviceDataWrapper& physicalDeviceData = device.GetPhysicalDeviceData();

		std::array<uint32_t, 2u> sharingQueueFamilyIndices{
			*physicalDeviceData.m_presentQueueIndex,
			*physicalDeviceData.m_graphicsQueueIndex
		};

		if (*physicalDeviceData.m_graphicsQueueIndex == *physicalDeviceData.m_presentQueueIndex)
		{
			createInfo.imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0u;
			createInfo.pQueueFamilyIndices   = nullptr;
		} else {
			createInfo.imageSharingMode      = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2u;

			createInfo.pQueueFamilyIndices = sharingQueueFamilyIndices.data();
		}
		 
		if (VK_FAILED(vkCreateSwapchainKHR(device, &createInfo, nullptr, &this->m_pObject)))
			throw std::runtime_error("[VULKAN] Failed To Create Swap Chain");
	}

}; // VK
}; // Internal
}; // WS