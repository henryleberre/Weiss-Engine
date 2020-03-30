#pragma once

#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX11VertexShader : public VertexShader {
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_pShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>  m_pInputLayout;

	std::shared_ptr<DirectX11Device> m_pDevice;

public:
	DirectX11VertexShader(const std::shared_ptr<DirectX11Device>& pDevice, const char* sourceFilename, const std::vector<ShaderInputElement>& sies);

	virtual void Bind() override;
};

class DirectX11PixelShader : public PixelShader {
private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pShader;

	std::shared_ptr<DirectX11Device> m_pDevice;

public:
	DirectX11PixelShader(const std::shared_ptr<DirectX11Device>& pDevice, const char* sourceFilename);

	virtual void Bind() override;
};

#endif // __WEISS__OS_WINDOWS