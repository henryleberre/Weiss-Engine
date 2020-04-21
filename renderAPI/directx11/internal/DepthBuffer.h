#pragma once

#include "RenderTarget.h"
#include "../../common/Include.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D11    {

	class D3D11DepthBuffer {
	private:
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_pDepthStencilView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_pDepthStencilState;

	public:
		D3D11DepthBuffer() = default;

		D3D11DepthBuffer(Window* pWindow, D3D11DeviceObjectWrapper& pDevice);

		void Clear(D3D11DeviceContextObjectWrapper& pDeviceContext);

		void Bind(D3D11DeviceContextObjectWrapper& pDeviceContext, D3D11RenderTargetbjectWrapper& pRenderTarget);
	};

}; // D3D11
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS