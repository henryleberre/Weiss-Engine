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

		Vec2u16 m_dimensions{ 0u, 0u };

	public:
		VKSurface() = default;
		VKSurface(VKInstance* pInstance, Window* pWindow);

		void operator=(VKSurface&& other) noexcept;

		[[nodiscard]] inline Vec2u16 GetDimensions() const noexcept { return this->m_dimensions; }

		~VKSurface();
	};

}; // VK
}; // Internal
}; // WS