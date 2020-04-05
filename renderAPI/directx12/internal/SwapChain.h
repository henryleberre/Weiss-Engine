#pragma once

#include "Device.h"
#include "CommandQueue.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX12SwapChain {
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain4> m_pSwapChain;

public:
	DirectX12SwapChain(const std::shared_ptr<DirectX12Device>& pDevice,
					   const std::shared_ptr<DirectX12CommandQueue>& pCommandQueue,
					   const Window* pWindow, const UINT bufferCount);

	Microsoft::WRL::ComPtr<IDXGISwapChain4> Get() const noexcept { return this->m_pSwapChain; }

	operator Microsoft::WRL::ComPtr<IDXGISwapChain4>() const noexcept { return this->m_pSwapChain; }
};

#endif // __WEISS__OS_WINDOWS