#pragma once

#include "internal/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX12RenderPipeline {
private:
	Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pPipelineState;

	D3D_PRIMITIVE_TOPOLOGY m_topology;

public:
	DirectX12RenderPipeline(const std::shared_ptr<DirectX12Device>& pDevice,
							const std::shared_ptr<DirectX12RootSignature>& pRootSignature,
							const char* vsFilename, const std::vector<ShaderInputElement>& sies,
							const char* psFilename, const PrimitiveTopology& topology);

	void Bind(const std::shared_ptr<DirectX12CommandList>& pCommandList) const noexcept;

	Microsoft::WRL::ComPtr<ID3D12PipelineState> Get() const noexcept;

	operator Microsoft::WRL::ComPtr<ID3D12PipelineState>() const noexcept;
};

#endif // __WEISS__OS_WINDOWS