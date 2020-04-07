#pragma once

#include "../../common/Include.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX12Adapater {
private:
	Microsoft::WRL::ComPtr<IDXGIAdapter1> m_pAdapter;

public:
	DirectX12Adapater();

	operator Microsoft::WRL::ComPtr<IDXGIAdapter1>() const noexcept;
	Microsoft::WRL::ComPtr<IDXGIAdapter1> Get() const noexcept;
};

#endif // __WEISS__OS_WINDOWS