#pragma once

#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX11VertexShader {
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_pShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>  m_pInputLayout;

	DirectX11DeviceContextObjectWrapper* m_pDeviceContext = nullptr;

public:
	DirectX11VertexShader() {  }

	DirectX11VertexShader(DirectX11DeviceObjectWrapper& pDevice,
						  DirectX11DeviceContextObjectWrapper* pDeviceContext,
						  const char* sourceFilename, const std::vector<ShaderInputElement>& sies);

	void Bind() const noexcept;
};

class DirectX11PixelShader {
private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pShader;

	DirectX11DeviceContextObjectWrapper* m_pDeviceContext = nullptr;

public:
	DirectX11PixelShader() {  }

	DirectX11PixelShader(DirectX11DeviceObjectWrapper& pDevice,
						 DirectX11DeviceContextObjectWrapper* pDeviceContext,
						 const char* sourceFilename);

	void Bind() const noexcept;
};

#endif // __WEISS__OS_WINDOWS