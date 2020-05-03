#pragma once

#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	/*
	 * To prevent a "use after free" (and many mental breakdowns) please overload the "void operator=" function with an r-value reference (like the one for this class)
	 * in any class that inherits from this base class.
	 */
	template <typename T>
	class D3D12ObjectWrapper {
	protected:
		T* m_pObject = nullptr;

		char* name;

	public:
		D3D12ObjectWrapper() = default;

		/* This function overloads the assignement operator with an r-value reference to itself
		 * It copies the pointer from the "other" and sets it to nullptr.
		 * This is done to ensure that the resource isn't freed while this object is being created.
		 * (Preventing a "use after free")
		*/
		D3D12ObjectWrapper& operator=(D3D12ObjectWrapper<T>&& other) noexcept
		{
			this->m_pObject = other.m_pObject;
			other.m_pObject = nullptr;

			return *this;
		}

		~D3D12ObjectWrapper()
		{
			if (this->m_pObject)
			{
				this->m_pObject->Release();
				this->m_pObject = nullptr;
			}
		}

		[[nodiscard]] T* operator->() { return this->m_pObject; }

		[[nodiscard]] T*  Get()    noexcept { return this->m_pObject;  }
		[[nodiscard]] T** GetPtr() noexcept { return &this->m_pObject; }

		[[nodiscard]] operator IUnknown* () const noexcept { return (IUnknown*) this->m_pObject; }

		[[nodiscard]] operator T* () const noexcept { return this->m_pObject; }
	};

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS