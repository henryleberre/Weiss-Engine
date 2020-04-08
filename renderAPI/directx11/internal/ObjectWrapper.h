#pragma once

#include "../../common/Include.h"

template <typename T>
class DirectX11ObjectWrapper {
protected:
	T* m_pObject = nullptr;

public:
	DirectX11ObjectWrapper() = default;

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