#pragma once

#include "Device.h"
#include "Surface.h"
#include "ObjectWrapper.h"
#include "../../common/Include.h"

namespace WS       {
namespace Internal {
namespace VK       {
	
	typedef VKObjectWrapper<VkSwapchainKHR> VKSwapChainObjectWrapper;

	class VKSwapChain : public VKSwapChainObjectWrapper {
	private:
		std::vector<VkImage>     m_images;
		std::vector<VkImageView> m_imageViews;

		VkSurfaceFormatKHR m_surfaceFormat;

		VKDevice*  m_pDevice  = nullptr;
		VKSurface* m_pSurface = nullptr;

	public:
		VKSwapChain() = default;
		VKSwapChain(VKDevice& pDevice, VKSurface& pSurface);

		VKSwapChain& operator=(VKSwapChain&& other) noexcept;

		~VKSwapChain();

	private:
		VkPresentModeKHR   PickPresentingMode() const;
		VkSurfaceFormatKHR PickSurfaceFormat()  const;

		void CreateSwapChain();
	};

}; // VK
}; // Internal
}; // WS