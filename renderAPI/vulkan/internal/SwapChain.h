#pragma once

#include "Device.h"
#include "Surface.h"
#include "Semaphore.h"
#include "RenderPass.h"
#include "ObjectWrapper.h"
#include "../../common/Include.h"

namespace WS       {
namespace Internal {
namespace VK       {
	
	typedef VKObjectWrapper<VkSwapchainKHR> VKSwapChainObjectWrapper;

	class VKSwapChain : public VKSwapChainObjectWrapper {
	private:
		uint32_t m_nImages = 0u;

		std::vector<VkImage>       m_images;
		std::vector<VkImageView>   m_imageViews;

		std::vector<VkFramebuffer> m_colorFrameBuffers;

		VkSurfaceFormatKHR m_surfaceFormat;

		VKDevice*  m_pDevice  = nullptr;
		VKSurface* m_pSurface = nullptr;

		VkExtent2D m_imageExtent2D;

		uint32_t m_currentImageIndex = 0u;

		VKSemaphore m_semaphore;

		VKQueue m_presentQueue;

	public:
		VKSwapChain() = default;
		VKSwapChain(VKDevice& pDevice, VKSurface& pSurface);

		VKSwapChain& operator=(VKSwapChain&& other) noexcept;

		void CreateFrameBuffers();

		void GetNextImage();

		void Present();

		[[nodiscard]] uint32_t           GetCurrentImageIndex() const noexcept;
		[[nodiscard]] VkExtent2D         GetImageExtent() const noexcept;
		[[nodiscard]] VkSurfaceFormatKHR GetFormat()      const noexcept;
		[[nodiscard]] VkFramebuffer      GetColorFrameBuffer(const size_t frameIndex) const noexcept;

		~VKSwapChain();

	private:
		VkPresentModeKHR   PickPresentingMode() const;
		VkSurfaceFormatKHR PickSurfaceFormat()  const;

		void CreateSwapChain();

		void CreateImagesAndViews();
	};

}; // VK
}; // Internal
}; // WS