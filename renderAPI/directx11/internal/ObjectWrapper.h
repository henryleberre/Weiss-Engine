#pragma once

#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D11    {

	/*
	 * To prevent a "use after free" (and many mental breakdowns) please overload the "void operator=" function with an r-value reference (like the one for this class)
	 * in any class that inherits from this base class.
	 */
	template <typename T>
	class D3D11ObjectWrapper {
	protected:
		T* m_pObject = nullptr;

	public:
		D3D11ObjectWrapper() = default;

		/* This function overloads the assignement operator with an r-value reference to itself
		 * It copies the pointer from the "other" and sets it to nullptr.
		 * This is done to ensure that the resource isn't freed while this object is being created.
		 * (Preventing a "use after free")
		*/
		void operator=(D3D11ObjectWrapper<T>&& other)
		{
			this->m_pObject = other.m_pObject;
			other.m_pObject = nullptr;
		}

		virtual ~D3D11ObjectWrapper()
		{
			if (this->m_pObject)
			{
				this->m_pObject->Release();
				this->m_pObject = nullptr;
			}
		}

		T*  Get()    noexcept { return this->m_pObject;  }
		T** GetPtr() noexcept { return &this->m_pObject; }

		T* operator->() { return this->m_pObject; }

		operator T* () noexcept { return this->m_pObject; }
	};

}; // D3D11
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS