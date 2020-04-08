#pragma once

#include "../../common/Include.h"

template <typename T>
class DirectX12ObjectWrapper {
protected:
	T* m_pObject = nullptr;

public:
	DirectX12ObjectWrapper() = default;

	virtual ~DirectX12ObjectWrapper()
	{
		if (this->m_pObject)
		{
			this->m_pObject->Release();
			this->m_pObject = nullptr;
		}
	}

	T* operator->() { return this->m_pObject; }

	operator IUnknown* () noexcept { return (IUnknown*) this->m_pObject; }

	operator T* () noexcept { return this->m_pObject; }
};