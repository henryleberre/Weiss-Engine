#pragma once

#include "Instance.h"
#include "ObjectWrapper.h"
#include "../../../window/Include.h"

namespace WS       {
namespace Internal {
namespace VK       {

	typedef VKObjectWrapper<VkSurfaceKHR> VKSurfaceObjectWrapper;

	class VKSurface : public VKSurfaceObjectWrapper {
	private:
		VKInstance* m_pInstance = nullptr;

	public:
		VKSurface();

		VKSurface(VKInstance* pInstance, Window* pWindow);

		void operator=(VKSurface&& other) noexcept;

		~VKSurface();
	};

}; // VK
}; // Internal
}; // WS