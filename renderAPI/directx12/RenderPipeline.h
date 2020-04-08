#pragma once

#include "internal/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef DirectX12ObjectWrapper<ID3D12PipelineState> DirectX12RenderPipelineObjectWrapper;

class DirectX12RenderPipeline : public DirectX12RenderPipelineObjectWrapper {
private:
	D3D_PRIMITIVE_TOPOLOGY m_topology;

public:
	DirectX12RenderPipeline(DirectX12DeviceObjectWrapper&        pDevice,
							DirectX12RootSignatureObjectWrapper& pRootSignature,
							const char* vsFilename, const std::vector<ShaderInputElement>& sies,
							const char* psFilename, const PrimitiveTopology& topology);

	void operator=(DirectX12RenderPipeline&& other) noexcept;

	void Bind(DirectX12CommandListObjectWrapper& pCommandList) const noexcept;
};

#endif // __WEISS__OS_WINDOWS