#pragma once

#include "Device.h"
#include "CommandQueue.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX12SwapChain {
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain3> m_pSwapChain;

public:
	DirectX12SwapChain(const std::shared_ptr<DirectX12Device>& pDevice,
					   const std::shared_ptr<DirectX12CommandQueue>& pCommandQueue,
					   const Window* pWindow, const UINT bufferCount);

	void Present() const;

	Microsoft::WRL::ComPtr<IDXGISwapChain3> Get() const noexcept;

	operator Microsoft::WRL::ComPtr<IDXGISwapChain3>() const noexcept;
};

#endif // __WEISS__OS_WINDOWS