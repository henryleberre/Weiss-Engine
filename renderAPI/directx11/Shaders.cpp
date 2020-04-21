#include "Shaders.h"

#ifdef __WEISS__OS_WINDOWS


namespace WS       {
namespace Internal {
namespace D3D11    {

	D3D11VertexShader::D3D11VertexShader(D3D11DeviceObjectWrapper& pDevice,
										 D3D11DeviceContextObjectWrapper* pDeviceContext,
										 const char* sourceFilename, const std::vector<ShaderInputElement>& sies)
		: m_pDeviceContext(pDeviceContext)
	{
		Microsoft::WRL::ComPtr<ID3DBlob> pBlob;

		// Create Shader
		std::ifstream fileStream(sourceFilename);
		std::string   sourceCode((std::istreambuf_iterator<char>(fileStream)), (std::istreambuf_iterator<char>()));

		if (D3DCompile(sourceCode.c_str(), sourceCode.size(), NULL, NULL, NULL, "main", "vs_5_0", 0, 0, &pBlob, NULL) != S_OK)
			throw std::runtime_error("Could Not Compile Vertex Shader");

		if (pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &this->m_pShader) != S_OK)
			throw std::runtime_error("Could Not Create Vertex Shader");

		// Create Input Layout
		std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDescriptors(sies.size());
		for (uint32_t i = 0; i < inputElementDescriptors.size(); i++)
		{
			inputElementDescriptors[i] = D3D11_INPUT_ELEMENT_DESC{};
			inputElementDescriptors[i].SemanticName = sies[i].name;

			switch (sies[i].type)
			{
			case ShaderInputElementType::FLOAT_32:
				inputElementDescriptors[i].Format = DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
				break;
			case ShaderInputElementType::UINT_32:
				inputElementDescriptors[i].Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
				break;
			case ShaderInputElementType::VECTOR_2D_FLOAT_32:
				inputElementDescriptors[i].Format = DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
				break;
			case ShaderInputElementType::VECTOR_3D_FLOAT_32:
				inputElementDescriptors[i].Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
				break;
			case ShaderInputElementType::VECTOR_4D_FLOAT_32:
				inputElementDescriptors[i].Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
				break;
			default:
				throw std::runtime_error("Input Element Type Not Supported");
			}

			inputElementDescriptors[i].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			inputElementDescriptors[i].InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
		}

		if (pDevice->CreateInputLayout(inputElementDescriptors.data(), (UINT)inputElementDescriptors.size(), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &this->m_pInputLayout) != S_OK)
			throw std::runtime_error("Could Not Create Input Layout");
	}

	void D3D11VertexShader::Bind() const noexcept
	{
		(*this->m_pDeviceContext)->IASetInputLayout(this->m_pInputLayout.Get());
		(*this->m_pDeviceContext)->VSSetShader(this->m_pShader.Get(), nullptr, 0u);
	}

	D3D11PixelShader::D3D11PixelShader(D3D11DeviceObjectWrapper& pDevice,
									   D3D11DeviceContextObjectWrapper* pDeviceContext,
									   const char* sourceFilename)
		: m_pDeviceContext(pDeviceContext)
	{
		Microsoft::WRL::ComPtr<ID3DBlob> pBlob;

		std::ifstream fileStream(sourceFilename);
		std::string sourceCode((std::istreambuf_iterator<char>(fileStream)), (std::istreambuf_iterator<char>()));

		if (D3DCompile(sourceCode.c_str(), sourceCode.size(), NULL, NULL, NULL, "main", "ps_5_0", 0, 0, &pBlob, NULL) != S_OK)
			throw std::runtime_error("Could Not Compile Pixel Shader");

		if (pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &this->m_pShader) != S_OK)
			throw std::runtime_error("Could Not Create Pixel Shader");
		}

	void D3D11PixelShader::Bind() const noexcept
	{
		(*this->m_pDeviceContext)->PSSetShader(this->m_pShader.Get(), nullptr, 0u);
	}

}; // D3D11
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS