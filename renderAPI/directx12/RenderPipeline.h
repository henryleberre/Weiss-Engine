#pragma once

#include "Buffers.h"
#include "Texture.h"
#include "TextureSampler.h"
#include "internal/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	typedef D3D12ObjectWrapper<ID3D12PipelineState> D3D12RenderPipelineObjectWrapper;

	class D3D12RenderPipeline : public D3D12RenderPipelineObjectWrapper {
	private:
		D3D_PRIMITIVE_TOPOLOGY m_topology;

		D3D12RootSignature m_pRootSignature;

		std::vector<uint32_t> m_constantBufferIndices;
		std::vector<uint32_t> m_textureIndices;

		D3D12DescriptorHeap m_gpuDescHeap;

	public:
		D3D12RenderPipeline();

		D3D12RenderPipeline(D3D12RenderPipeline&& other);

		D3D12RenderPipeline(D3D12DeviceObjectWrapper& pDevice, const RenderPipelineDesc& pipelineDesc,
							std::vector<ConstantBuffer*>& pConstantBuffers, std::vector<Texture*> pTextures, std::vector<D3D12TextureSampler*> pTextureSamplers);

		void operator=(D3D12RenderPipeline&& other) noexcept;

		void Bind(D3D12DeviceObjectWrapper& pDevice, D3D12CommandListObjectWrapper& pCommandList, std::vector<ConstantBuffer*>& pConstantBuffers,
				  std::vector<Texture*> pTextures, const size_t frameIndex) noexcept;
	};

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS