#pragma once

#include "../../common/Include.h"

namespace WS       {
namespace Internal {
namespace VK       {

	/*
	 * To prevent a "use after free" (and many mental breakdowns) please overload the "void operator=" function with an r-value reference (like the one for this class)
	 * in any class that inherits from this base class.
	 */
	template <typename T>
	class VKObjectWrapper {
	protected:
		T m_pObject = VK_NULL_HANDLE;

	public:
		VKObjectWrapper() = default;

		T* operator->() { return &this->m_pObject; }

		operator const T () const noexcept { return this->m_pObject; }
	};

}; // VK
}; // Internal
}; // WS