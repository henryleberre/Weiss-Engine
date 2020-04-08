#include "RenderPipeline.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12RenderPipeline::DirectX12RenderPipeline(DirectX12DeviceObjectWrapper& pDevice,
												 DirectX12RootSignatureObjectWrapper& pRootSignature,
												 const char* vsFilename, const std::vector<ShaderInputElement>& sies,
												 const char* psFilename, const PrimitiveTopology& topology)
{
	// Specify Compilation Flags
	size_t compileFlags = D3DCOMPILE_SKIP_OPTIMIZATION;
#ifdef _DEBUG
	compileFlags = compileFlags | D3DCOMPILE_DEBUG;
#endif // _DEBUG

	// Vertex Shader
	Microsoft::WRL::ComPtr<ID3DBlob> pVertexShaderByteCode;
	Microsoft::WRL::ComPtr<ID3DBlob> pErrorBuff;

	wchar_t vsFilenameW[FILENAME_MAX];
	{
		size_t convertedCharP = 0;
		mbstowcs_s(&convertedCharP, vsFilenameW, strlen(vsFilename) + 1u, vsFilename, _TRUNCATE);
	}

	if (D3DCompileFromFile(vsFilenameW, nullptr, nullptr, "main", "vs_5_0", compileFlags,
		0, &pVertexShaderByteCode, &pErrorBuff) != S_OK)
	{
#ifdef _DEBUG
		OutputDebugStringA((char*)pErrorBuff->GetBufferPointer());
#endif // _DEBUG

		throw std::runtime_error("[DIRECTX 12] Failed To Compile Vertex Shader");
	}

	D3D12_SHADER_BYTECODE vertexShaderBytecode = {};
	vertexShaderBytecode.BytecodeLength  = pVertexShaderByteCode->GetBufferSize();
	vertexShaderBytecode.pShaderBytecode = pVertexShaderByteCode->GetBufferPointer();

	// Pixel Shader
	Microsoft::WRL::ComPtr<ID3DBlob> pPixelShaderByteCode;

	wchar_t psFilenameW[FILENAME_MAX];
	{
		size_t convertedCharP = 0;
		mbstowcs_s(&convertedCharP, psFilenameW, strlen(psFilename) + 1u, psFilename, _TRUNCATE);
	}

	if (D3DCompileFromFile(psFilenameW, nullptr, nullptr, "main", "ps_5_0", compileFlags,
		0, &pPixelShaderByteCode, &pErrorBuff) != S_OK)
	{
#ifdef _DEBUG
		OutputDebugStringA((char*)pErrorBuff->GetBufferPointer());
#endif // _DEBUG

		throw std::runtime_error("[DIRECTX 12] Failed To Compile Pixel Shader");
	}

	D3D12_SHADER_BYTECODE pixelShaderBytecode = {};
	pixelShaderBytecode.BytecodeLength  = pPixelShaderByteCode->GetBufferSize();
	pixelShaderBytecode.pShaderBytecode = pPixelShaderByteCode->GetBufferPointer();

	// Input Layout
	std::vector<D3D12_INPUT_ELEMENT_DESC> inputElementDescriptors(sies.size());
	for (uint32_t i = 0; i < inputElementDescriptors.size(); i++)
	{
		inputElementDescriptors[i] = D3D12_INPUT_ELEMENT_DESC{};
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
			throw std::runtime_error("[DIRECTX 12] Input Element Type Not Supported");
		}

		inputElementDescriptors[i].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
		inputElementDescriptors[i].InputSlotClass    = D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
	}

	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc = {};
	inputLayoutDesc.NumElements        = sies.size();
	inputLayoutDesc.pInputElementDescs = inputElementDescriptors.data();

	// Pipeline
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
	psoDesc.InputLayout    = inputLayoutDesc;
	psoDesc.pRootSignature = pRootSignature;
	psoDesc.VS = vertexShaderBytecode;
	psoDesc.PS = pixelShaderBytecode;

	switch (topology)
	{
	case PrimitiveTopology::TRIANGLES:
		psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		this->m_topology = D3D_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		break;
	case PrimitiveTopology::TRIANGLE_STRIP:
		psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		this->m_topology = D3D_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
		break;
	default:
		throw std::runtime_error("[DIRECTX 12] The Primitive Topology Type You Resquested Is Not Supported");
		break;
	}

	psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	psoDesc.SampleDesc.Count = 1;
	psoDesc.SampleMask = 0xffffffff;
	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	psoDesc.DepthStencilState.DepthEnable = FALSE;
	psoDesc.DepthStencilState.StencilEnable = FALSE;
	psoDesc.NumRenderTargets = 1;

	// create the pso
	if (pDevice->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&this->m_pObject)) != S_OK)
		throw std::runtime_error("[DIRECTX 12] Failed To Create Graphics Pipeline State");
}

void DirectX12RenderPipeline::Bind(DirectX12CommandListObjectWrapper& pCommandList) const noexcept
{
	pCommandList->SetPipelineState(this->m_pObject);
	pCommandList->IASetPrimitiveTopology(this->m_topology);
}

#endif // __WEISS__OS_WINDOWS