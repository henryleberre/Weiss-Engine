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

	D3D12RenderPipeline::D3D12RenderPipeline(D3D12Device& pDevice, const RenderPipelineDesc& pipelineDesc,
											 std::vector<ConstantBuffer*>& pConstantBuffers, std::vector<Texture*> pTextures, std::vector<D3D12TextureSampler*> pTextureSamplers)
		: m_pDevice(&pDevice), m_constantBufferIndices(pipelineDesc.constantBufferIndices), m_textureIndices(pipelineDesc.textureIndices),
		  m_pConstantBuffers(pConstantBuffers), m_pTextures(pTextures), m_pTextureSamplers(pTextureSamplers)
	{
		// Specify Compilation Flags
		UINT compileFlags = 0u;

#ifdef __WEISS__DEBUG_MODE

		compileFlags |= D3DCOMPILE_DEBUG;

#endif // __WEISS__DEBUG_MODE

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
#ifdef __WEISS__DEBUG_MODE
			OutputDebugStringA((char*)pErrorBuff->GetBufferPointer());
#endif // __WEISS__DEBUG_MODE

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
#ifdef __WEISS__DEBUG_MODE

			OutputDebugStringA((char*)pErrorBuff->GetBufferPointer());

#endif // __WEISS__DEBUG_MODE

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
		std::vector<D3D12_DESCRIPTOR_RANGE1> descriptorRanges(pipelineDesc.constantBufferIndices.size() + pipelineDesc.textureIndices.size());

		std::vector<D3D12_ROOT_PARAMETER1> rootParameters;

		{
			size_t j = 0u;
			for (size_t i = 0; i < pipelineDesc.constantBufferIndices.size(); i++)
			{
				D3D12ConstantBuffer*     pConstantBufferX12 = dynamic_cast<D3D12ConstantBuffer*>(pConstantBuffers[pipelineDesc.constantBufferIndices[i]]);
				D3D12_DESCRIPTOR_RANGE1& cbvDescriptorRange = descriptorRanges[j++];

				cbvDescriptorRange.RangeType      = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
				cbvDescriptorRange.NumDescriptors = 1u;
				cbvDescriptorRange.RegisterSpace  = 0u;
				cbvDescriptorRange.BaseShaderRegister = (UINT)pConstantBufferX12->GetSlot();
				cbvDescriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
			}

			for (size_t i = 0; i < pipelineDesc.textureIndices.size(); i++)
			{
				D3D12_DESCRIPTOR_RANGE1& texDescriptorRange = descriptorRanges[j++];
				texDescriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
				texDescriptorRange.NumDescriptors = 1u;
				texDescriptorRange.BaseShaderRegister = (UINT)dynamic_cast<D3D12Texture*>(pTextures[pipelineDesc.textureIndices[i]])->GetSlot();
				texDescriptorRange.RegisterSpace = 0;
				texDescriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
			}

			D3D12_ROOT_PARAMETER1 constantBufferRootParam;
			constantBufferRootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			constantBufferRootParam.DescriptorTable.NumDescriptorRanges = (UINT)descriptorRanges.size();
			constantBufferRootParam.DescriptorTable.pDescriptorRanges   = descriptorRanges.data();
			constantBufferRootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY::D3D12_SHADER_VISIBILITY_ALL;

			rootParameters.push_back(constantBufferRootParam);
		}

		std::vector<D3D12_STATIC_SAMPLER_DESC> samplers(pipelineDesc.textureSamplerIndices.size());
		for (size_t i = 0u; i < samplers.size(); i++)
			samplers[i] = pTextureSamplers[pipelineDesc.textureSamplerIndices[i]]->GetSamplerDesc();

		this->m_pRootSignature = D3D12RootSignature(pDevice, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT, rootParameters, samplers);

		psoDesc.pRootSignature = this->m_pRootSignature;

		// create the pso
		if (FAILED(pDevice->CreateGraphicsPipelineState(&psoDesc, __uuidof(ID3D12PipelineState), (void**)&this->m_pObject)))
			throw std::runtime_error("[DIRECTX 12] Failed To Create Graphics Pipeline State");

		for (size_t frameIndex = 0u; frameIndex < WEISS__FRAME_BUFFER_COUNT; frameIndex++)
		{
			D3D12DescriptorHeap& gpuDescHeap = this->m_gpuDescHeaps[frameIndex];

			gpuDescHeap = D3D12DescriptorHeap(pDevice, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, this->m_constantBufferIndices.size() + this->m_textureIndices.size(),
											  D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE);

			CD3DX12_CPU_DESCRIPTOR_HANDLE gpuDescHeapHandleEnd(gpuDescHeap->GetCPUDescriptorHandleForHeapStart());
			const UINT incrementSize = pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

			for (const size_t cbIndex : this->m_constantBufferIndices) {
				D3D12ConstantBuffer& cbBuffer = *dynamic_cast<D3D12ConstantBuffer*>(pConstantBuffers[cbIndex]);

				pDevice->CopyDescriptorsSimple(1u, gpuDescHeapHandleEnd, cbBuffer.GetDescriptorHeap(frameIndex)->GetCPUDescriptorHandleForHeapStart(), D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

				gpuDescHeapHandleEnd.Offset(1u, incrementSize);
			}

			for (const size_t texIndex : this->m_textureIndices) {
				D3D12Texture& texture = *dynamic_cast<D3D12Texture*>(pTextures[texIndex]);

				pDevice->CopyDescriptorsSimple(1u, gpuDescHeapHandleEnd, texture.GetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart(), D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

				gpuDescHeapHandleEnd.Offset(1u, incrementSize);
			}
		}
	}

	D3D12RenderPipeline& D3D12RenderPipeline::operator=(D3D12RenderPipeline&& other) noexcept
	{
		this->m_pObject = std::move(other.m_pObject);

		this->m_topology = other.m_topology;
		this->m_pRootSignature = std::move(other.m_pRootSignature);
		this->m_constantBufferIndices = other.m_constantBufferIndices;
		this->m_textureIndices = other.m_textureIndices;

		size_t i = 0u;
		for (D3D12DescriptorHeap& gpuHeap : this->m_gpuDescHeaps)
			gpuHeap = std::move(other.m_gpuDescHeaps[i++]);

		return *this;
	}

	void D3D12RenderPipeline::Bind(D3D12CommandList& pCommandList, const size_t frameIndex) noexcept
	{
		for (uint32_t cbIndex : this->m_constantBufferIndices)
			dynamic_cast<D3D12ConstantBuffer*>(this->m_pConstantBuffers[cbIndex])->UpdateIfNeeded(frameIndex);

		pCommandList->SetGraphicsRootSignature(this->m_pRootSignature);
		pCommandList->SetPipelineState(this->m_pObject);
		pCommandList->SetDescriptorHeaps(1u, this->m_gpuDescHeaps[frameIndex].GetPtr());
		pCommandList->SetGraphicsRootDescriptorTable(0u, this->m_gpuDescHeaps[frameIndex]->GetGPUDescriptorHandleForHeapStart());
		pCommandList->IASetPrimitiveTopology(this->m_topology);
	}

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS