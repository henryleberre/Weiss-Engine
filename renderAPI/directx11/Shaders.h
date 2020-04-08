#pragma once

#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX11VertexShader {
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_pShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>  m_pInputLayout;

public:
	DirectX11VertexShader() {  }

	DirectX11VertexShader(DirectX11DeviceObjectWrapper& pDevice, const char* sourceFilename, const std::vector<ShaderInputElement>& sies);

	void Bind(DirectX11DeviceContextObjectWrapper& pDeviceContext);
};

class DirectX11PixelShader {
private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pShader;

public:
	DirectX11PixelShader() {  }

	DirectX11PixelShader(DirectX11DeviceObjectWrapper& pDevice, const char* sourceFilename);

	void Bind(DirectX11DeviceContextObjectWrapper& pDeviceContext);
};

#endif // __WEISS__OS_WINDOWS