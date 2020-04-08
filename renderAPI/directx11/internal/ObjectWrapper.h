#pragma once

#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

/*
 * To prevent a "use after free" (and many mental breakdowns) please overload the "void operator=" function with an r-value reference (like the one for this class)
 * in any class that inherits from this base class.
 */
template <typename T>
class DirectX11ObjectWrapper {
protected:
	T* m_pObject = nullptr;

public:
	DirectX11ObjectWrapper() = default;

	/* This function overloads the assignement operator with an r-value reference to itself
	 * It copies the pointer from the "other" and sets it to nullptr.
	 * This is done to ensure that the resource isn't freed while this object is being created.
	 * (Preventing a "use after free")
	*/
	void operator=(DirectX11ObjectWrapper<T>&& other)
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = nullptr;
	}

	virtual ~DirectX11ObjectWrapper()
	{
		if (this->m_pObject)
		{
			this->m_pObject->Release();
			this->m_pObject = nullptr;
		}
	}

	T*  Get() noexcept { return this->m_pObject; }
	T** GetPtr() noexcept { return &this->m_pObject; }

	T* operator->() { return this->m_pObject;  }

	operator T* () noexcept { return this->m_pObject;  }
};

#endif // __WEISS__OS_WINDOWS