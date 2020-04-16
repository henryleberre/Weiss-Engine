#pragma once

#include "Buffers.h"
#include "internal/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef DirectX12ObjectWrapper<ID3D12PipelineState> DirectX12RenderPipelineObjectWrapper;

class DirectX12RenderPipeline : public DirectX12RenderPipelineObjectWrapper {
private:
	D3D_PRIMITIVE_TOPOLOGY m_topology;

	DirectX12RootSignature m_pRootSignature;

	std::vector<uint32_t> m_constantBufferIndices;

public:
	DirectX12RenderPipeline();

	DirectX12RenderPipeline(DirectX12RenderPipeline&& other);

	DirectX12RenderPipeline(DirectX12DeviceObjectWrapper& pDevice, const RenderPipelineDesc& pipelineDesc, std::vector<ConstantBuffer*>& pConstantBuffers);

	void operator=(DirectX12RenderPipeline&& other) noexcept;

	void Bind(DirectX12CommandListObjectWrapper& pCommandList, std::vector<ConstantBuffer*>& pConstantBuffers, const size_t frameIndex) const noexcept;
};

#endif // __WEISS__OS_WINDOWS