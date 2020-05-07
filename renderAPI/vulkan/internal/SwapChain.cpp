#include "SwapChain.h"

namespace WS       {
namespace Internal {
namespace VK       {

	VKSwapChain::VKSwapChain(VKDevice& pDevice, VKSurface& pSurface)
		: m_pDevice(&pDevice), m_pSurface(&pSurface)
	{
		this->m_presentQueue = pDevice.GetPresentQueue();

		this->m_semaphore = VKSemaphore(pDevice);

		this->CreateSwapChain();
		this->CreateImagesAndViews();
		this->CreateFrameBuffers();
	}

	VKSwapChain& VKSwapChain::operator=(VKSwapChain&& other) noexcept
	{
		this->m_nImages = std::move(other.m_nImages);
		this->m_images = std::move(other.m_images);
		this->m_imageViews = std::move(other.m_imageViews);
		this->m_pDevice = std::move(other.m_pDevice);
		this->m_pObject = std::move(other.m_pObject);
		this->m_pSurface = std::move(other.m_pSurface);
		this->m_surfaceFormat = std::move(other.m_surfaceFormat);
		this->m_colorFrameBuffers = std::move(other.m_colorFrameBuffers);
		this->m_currentImageIndex = std::move(other.m_currentImageIndex);
		this->m_semaphore = std::move(other.m_semaphore);
		this->m_presentQueue = std::move(other.m_presentQueue);

		other.m_pObject = VK_NULL_HANDLE;

		return *this;
	}

	void VKSwapChain::CreateFrameBuffers()
	{
		m_colorFrameBuffers.resize(this->m_images.size());

		VkFramebufferCreateInfo framebufferInfo{};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.width  = this->m_imageExtent2D.width;
		framebufferInfo.height = this->m_imageExtent2D.height;
		framebufferInfo.layers = 1;

		this->m_colorFrameBuffers.resize(this->m_imageViews.size());
		for (size_t i = 0; i < this->m_colorFrameBuffers.size(); i++)
		{
			VkImageView attachments[] = {
				this->m_imageViews[i]
			};

			framebufferInfo.pAttachments = attachments;
			framebufferInfo.renderPass   = VKRenderPass::s_colorRenderPass;

			if (VK_FAILED(vkCreateFramebuffer(*this->m_pDevice, &framebufferInfo, nullptr, &this->m_colorFrameBuffers[i])))
				throw std::runtime_error("[VULKAN] Failed To Create A Frame Buffer");
		}
	}

	void VKSwapChain::GetNextImage()
	{
		if (VK_FAILED(vkAcquireNextImageKHR(*this->m_pDevice, this->m_pObject, UINT64_MAX, this->m_semaphore, VK_NULL_HANDLE, &this->m_currentImageIndex)))
			throw std::runtime_error("[VULKAN] Failed To Acquire Next Swap Chain Image");
	}

	void VKSwapChain::Present()
	{
		VkPresentInfoKHR presentInfo{};
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores    = this->m_semaphore.GetPtr();
		presentInfo.swapchainCount     = 1;
		presentInfo.pSwapchains   = &this->m_pObject;
		presentInfo.pImageIndices = &this->m_currentImageIndex;
		presentInfo.pResults = nullptr;
		presentInfo.sType    = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

		if (VK_FAILED(vkQueuePresentKHR(this->m_presentQueue, &presentInfo)))
			throw std::runtime_error("[VULKAN] Failed To Present Swap Chain Frame Buffer");
	}

	[[nodiscard]] uint32_t VKSwapChain::GetCurrentImageIndex() const noexcept
	{
		return this->m_currentImageIndex;
	}

	[[nodiscard]] VkExtent2D VKSwapChain::GetImageExtent() const noexcept
	{
		return this->m_imageExtent2D;
	}

	[[nodiscard]] VkSurfaceFormatKHR VKSwapChain::GetFormat() const noexcept
	{
		return this->m_surfaceFormat;
	}

	[[nodiscard]] VkFramebuffer VKSwapChain::GetColorFrameBuffer(const size_t frameIndex) const noexcept
	{
		return this->m_colorFrameBuffers[frameIndex];
	}

	VKSwapChain::~VKSwapChain()
	{
		for (VkImageView& imageView : this->m_imageViews)
			if (imageView != VK_NULL_HANDLE)
				vkDestroyImageView(*this->m_pDevice, imageView, nullptr);

		if (this->m_pObject != VK_NULL_HANDLE)
			vkDestroySwapchainKHR(*this->m_pDevice, this->m_pObject, nullptr);

		for (VkFramebuffer& frameBuffer : m_colorFrameBuffers)
			if (frameBuffer != VK_NULL_HANDLE)
				vkDestroyFramebuffer(*this->m_pDevice, frameBuffer, nullptr);
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
		this->m_imageExtent2D.width  = this->m_pSurface->GetDimensions().x;
		this->m_imageExtent2D.height = this->m_pSurface->GetDimensions().y;

		VkSwapchainCreateInfoKHR createInfo = {};
		createInfo.sType              = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface            = surface;
		createInfo.minImageCount      = WEISS__FRAME_BUFFER_COUNT;
		createInfo.imageFormat        = this->m_surfaceFormat.format;
		createInfo.imageColorSpace    = this->m_surfaceFormat.colorSpace;
		createInfo.imageExtent        = this->m_imageExtent2D;
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

	void VKSwapChain::CreateImagesAndViews()
	{
		vkGetSwapchainImagesKHR(*this->m_pDevice, this->m_pObject, &this->m_nImages, nullptr);
		this->m_images.resize(this->m_nImages);
		this->m_imageViews.resize(this->m_nImages);
		vkGetSwapchainImagesKHR(*this->m_pDevice, this->m_pObject, &this->m_nImages, this->m_images.data());

		for (size_t i = 0; i < this->m_nImages; i++)
		{
			VkImageViewCreateInfo createInfo{};
			createInfo.sType    = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image    = this->m_images[i];
			createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			createInfo.format   = this->m_surfaceFormat.format;
			createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel   = 0;
			createInfo.subresourceRange.levelCount     = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount     = 1;

			if (VK_FAILED(vkCreateImageView(*this->m_pDevice, &createInfo, nullptr, &this->m_imageViews[i])))
				throw std::runtime_error("[VULKAN] Failed To Create An Image View");
		}
	}

}; // VK
}; // Internal
}; // WS