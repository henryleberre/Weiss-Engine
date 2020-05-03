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
	public:
		T m_pObject = VK_NULL_HANDLE;

	public:
		VKObjectWrapper() = default;

		VKObjectWrapper(T& obj) : m_pObject(obj) {  }

		VKObjectWrapper<T>& operator=(VKObjectWrapper<T>&& other)
		{
			this->m_pObject = other.m_pObject;
			other.m_pObject = VK_NULL_HANDLE;

			return *this;
		}

		T* GetPtr() noexcept { return this->m_pObject; }

		T* operator->() { return &this->m_pObject; }

		operator       T& ()       noexcept { return this->m_pObject; }
		operator const T& () const noexcept { return this->m_pObject; }
	};

}; // VK
}; // Internal
}; // WS