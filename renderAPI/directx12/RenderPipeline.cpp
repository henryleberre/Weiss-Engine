#include "RenderPipeline.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	D3D12RenderPipeline::D3D12RenderPipeline()
	{

	}

	D3D12RenderPipeline::D3D12RenderPipeline(D3D12RenderPipeline&& other)
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = nullptr;

		this->m_topology = other.m_topology;
		this->m_pRootSignature = std::move(other.m_pRootSignature);
		this->m_constantBufferIndices = other.m_constantBufferIndices;
		this->m_textureIndices = other.m_textureIndices;
	}

	D3D12RenderPipeline::D3D12RenderPipeline(D3D12DeviceObjectWrapper& pDevice, const RenderPipelineDesc& pipelineDesc,
											 std::vector<ConstantBuffer*>& pConstantBuffers, std::vector<Texture*> pTextures)
		: m_constantBufferIndices(pipelineDesc.constantBufferIndices), m_textureIndices(pipelineDesc.textureIndices)
	{
		// Specify Compilation Flags
		UINT compileFlags = 0u;

#ifdef _DEBUG

		compileFlags |= D3DCOMPILE_DEBUG;

#endif // _DEBUG

		// Vertex Shader
		Microsoft::WRL::ComPtr<ID3DBlob> pVertexShaderByteCode;
		Microsoft::WRL::ComPtr<ID3DBlob> pErrorBuff;

		wchar_t vsFilenameW[FILENAME_MAX];
		{
			size_t convertedCharP = 0;
			mbstowcs_s(&convertedCharP, vsFilenameW, strlen(pipelineDesc.vsFilename) + 1u, pipelineDesc.vsFilename, _TRUNCATE);
		}

		if (FAILED(D3DCompileFromFile(vsFilenameW, nullptr, nullptr, "main", "vs_5_0", compileFlags,
			0, &pVertexShaderByteCode, &pErrorBuff)))
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
			mbstowcs_s(&convertedCharP, psFilenameW, strlen(pipelineDesc.psFilename) + 1u, pipelineDesc.psFilename, _TRUNCATE);
		}

		if (FAILED(D3DCompileFromFile(psFilenameW, nullptr, nullptr, "main", "ps_5_0", compileFlags,
			0, &pPixelShaderByteCode, &pErrorBuff)))
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
		std::vector<D3D12_INPUT_ELEMENT_DESC> inputElementDescriptors(pipelineDesc.sies.size());
		for (uint32_t i = 0; i < inputElementDescriptors.size(); i++)
		{
			inputElementDescriptors[i] = D3D12_INPUT_ELEMENT_DESC{};
			inputElementDescriptors[i].SemanticName = pipelineDesc.sies[i].name;

			switch (pipelineDesc.sies[i].type)
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
		inputLayoutDesc.NumElements        = static_cast<UINT>(pipelineDesc.sies.size());
		inputLayoutDesc.pInputElementDescs = inputElementDescriptors.data();

		// Pipeline
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
		psoDesc.InputLayout    = inputLayoutDesc;
		psoDesc.VS = vertexShaderBytecode;
		psoDesc.PS = pixelShaderBytecode;

		switch (pipelineDesc.topology)
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

		psoDesc.RTVFormats[0]    = DXGI_FORMAT_R8G8B8A8_UNORM;
		psoDesc.SampleDesc.Count = 1;
		psoDesc.SampleMask       = 0xffffffff;
		psoDesc.RasterizerState  = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		psoDesc.BlendState       = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		psoDesc.DepthStencilState.DepthEnable   = FALSE;
		psoDesc.DepthStencilState.StencilEnable = FALSE;
		psoDesc.NumRenderTargets = 1;

		// Root Signature
		std::vector<D3D12_DESCRIPTOR_RANGE1> descriptorRangesCBV(pipelineDesc.constantBufferIndices.size());
		std::vector<D3D12_DESCRIPTOR_RANGE1> descriptorRangesTEX(pipelineDesc.textureIndices.size());

		std::vector<D3D12_ROOT_PARAMETER1> rootParameters;

		{
			for (size_t i = 0; i < pipelineDesc.constantBufferIndices.size(); i++)
			{
				D3D12ConstantBuffer* pConstantBufferX12 = dynamic_cast<D3D12ConstantBuffer*>(pConstantBuffers[pipelineDesc.constantBufferIndices[i]]);

				descriptorRangesCBV[i].RangeType      = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
				descriptorRangesCBV[i].NumDescriptors = 1u;
				descriptorRangesCBV[i++].BaseShaderRegister = (UINT)pConstantBufferX12->GetSlot();
			}

			D3D12_ROOT_PARAMETER1 constantBufferRootParam;
			constantBufferRootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			constantBufferRootParam.DescriptorTable.NumDescriptorRanges = (UINT)descriptorRangesCBV.size();
			constantBufferRootParam.DescriptorTable.pDescriptorRanges   = descriptorRangesCBV.data();
			constantBufferRootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY::D3D12_SHADER_VISIBILITY_ALL;

			rootParameters.push_back(constantBufferRootParam);
		}

		{
			for (size_t i = 0; i < pipelineDesc.textureIndices.size(); i++)
			{
				D3D12_DESCRIPTOR_RANGE1& texDescriptorRange = descriptorRangesTEX[i];

				texDescriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
				texDescriptorRange.NumDescriptors = 1u;
				texDescriptorRange.BaseShaderRegister = (UINT)dynamic_cast<D3D12Texture*>(pTextures[i])->GetSlot();
				texDescriptorRange.RegisterSpace = 0;
				texDescriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
			}

			D3D12_ROOT_PARAMETER1 textureRootParam;
			textureRootParam.ParameterType    = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			textureRootParam.DescriptorTable.NumDescriptorRanges = (UINT)descriptorRangesTEX.size();
			textureRootParam.DescriptorTable.pDescriptorRanges   = descriptorRangesTEX.data();
			textureRootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

			rootParameters.push_back(textureRootParam);
		}

		this->m_pRootSignature = D3D12RootSignature(pDevice, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT, rootParameters);

		psoDesc.pRootSignature = this->m_pRootSignature;

		// create the pso
		HRESULT hr = pDevice->CreateGraphicsPipelineState(&psoDesc, __uuidof(ID3D12PipelineState), (void**)&this->m_pObject);

		if (FAILED(hr))
			throw std::runtime_error("[DIRECTX 12] Failed To Create Graphics Pipeline State");
	}

	void D3D12RenderPipeline::operator=(D3D12RenderPipeline&& other) noexcept
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = nullptr;
	}

	void D3D12RenderPipeline::Bind(D3D12CommandListObjectWrapper& pCommandList, std::vector<ConstantBuffer*>& pConstantBuffers,
								   std::vector<Texture*> pTextures, const size_t frameIndex) const noexcept
	{
		pCommandList->SetGraphicsRootSignature(this->m_pRootSignature);
		pCommandList->SetPipelineState(this->m_pObject);

		for (const size_t cbIndex : this->m_constantBufferIndices)
			dynamic_cast<D3D12ConstantBuffer*>(pConstantBuffers[cbIndex])->Bind(frameIndex);

		for (const size_t texIndex : this->m_textureIndices)
			dynamic_cast<D3D12Texture*>(pTextures[texIndex])->Bind();

		pCommandList->IASetPrimitiveTopology(this->m_topology);
	}

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS