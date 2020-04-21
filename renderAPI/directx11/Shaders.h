#pragma once

#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D11    {

	class D3D11VertexShader {
	private:
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_pShader;
		Microsoft::WRL::ComPtr<ID3D11InputLayout>  m_pInputLayout;

		D3D11DeviceContextObjectWrapper* m_pDeviceContext = nullptr;

	public:
		D3D11VertexShader() {  }

		D3D11VertexShader(D3D11DeviceObjectWrapper& pDevice,
						  D3D11DeviceContextObjectWrapper* pDeviceContext,
						  const char* sourceFilename, const std::vector<ShaderInputElement>& sies);

		void Bind() const noexcept;
	};

	class D3D11PixelShader {
	private:
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pShader;

		D3D11DeviceContextObjectWrapper* m_pDeviceContext = nullptr;

	public:
		D3D11PixelShader() {  }

		D3D11PixelShader(D3D11DeviceObjectWrapper& pDevice,
						 D3D11DeviceContextObjectWrapper* pDeviceContext,
						 const char* sourceFilename);

		void Bind() const noexcept;
	};

}; // D3D11
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS