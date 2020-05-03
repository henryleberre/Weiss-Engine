#include "Surface.h"

namespace WS       {
namespace Internal {
namespace VK       {

	VKSurface::VKSurface(VKInstance* pInstance, Window* pWindow)
		: m_pInstance(pInstance)
	{
#ifdef __WEISS__OS_WINDOWS

		VkWin32SurfaceCreateInfoKHR createInfo = {};
		createInfo.sType     = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		createInfo.hwnd      = reinterpret_cast<const WS::WIN::WindowsWindow*>(pWindow)->GetHandle();
		createInfo.hinstance = GetModuleHandle(NULL);

		if (VK_FAILED(vkCreateWin32SurfaceKHR(*this->m_pInstance, &createInfo, nullptr, &this->m_pObject)))
			throw std::runtime_error("[VULKAN] Failed To Create Window Surface");

#endif // __WEISS__OS_WINDOWS
	}

	VKSurface& VKSurface::operator=(VKSurface&& other) noexcept
	{
		this->m_pInstance = other.m_pInstance;
		this->m_pObject   = other.m_pObject;
		other.m_pObject   = VK_NULL_HANDLE;

		return *this;
	}

	VKSurface::~VKSurface()
	{
		if (this->m_pObject != VK_NULL_HANDLE)
			vkDestroySurfaceKHR(*this->m_pInstance, this->m_pObject, nullptr);
	}

}; // VK
}; // Internal
}; // WS