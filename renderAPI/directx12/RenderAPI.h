#pragma once

#include "Buffers.h"
#include "RenderPipeline.h"
#include "internal/Include.h"
#include "CommandSubmitter.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX12RenderAPI : public RenderAPI<DirectX12VertexBuffer, DirectX12IndexBuffer, DirectX12ConstantBuffer> {
private:
	DirectX12Adapter        m_pAdapter;
	DirectX12Device         m_pDevice;
	DirectX12CommandQueue   m_pCommandQueue;
	DirectX12SwapChain      m_pSwapChain;
	DirectX12DescriptorHeap m_pDescriptorHeap;
	DirectX12DepthBuffer    m_pDepthBuffer;

	std::array<DirectX12RenderTarget, WEISS__FRAME_BUFFER_COUNT> m_pRenderTargets;

	DirectX12CommandSubmitter m_commandSubmitter;
	DirectX12CommandSubmitter m_bvcSubmitter;

	DirectX12RootSignature    m_pInputAssemblerRootSignature;

	std::vector<DirectX12RenderPipeline> m_renderPipelines;

	size_t currentFrameIndex = 0u;

	CD3DX12_CPU_DESCRIPTOR_HANDLE m_currentRtvHandle;

	D3D12_RECT     m_scissors;
	D3D12_VIEWPORT m_viewport;

	std::vector<size_t> m_newVertexBufferIndices;
	std::vector<size_t> m_newIndexBufferIndices;

private:
	void CreateRenderTargets();

public:
	DirectX12RenderAPI();

	virtual void InitRenderAPI(Window* pWindow, const std::vector<RenderPipelineDesc>& pipelineDescs) override;

	virtual void Draw(const Drawable& drawable, const size_t nVertices) override;

	virtual void BeginDrawing() override;
	virtual void EndDrawing()   override;
	virtual void Present(const bool vSync) override;

	virtual size_t CreateVertexBuffer(const size_t nVertices, const size_t vertexSize) override;
	virtual size_t CreateIndexBuffer (const size_t nIndices) override;
	virtual size_t CreateConstantBuffer(const size_t objSize, const size_t slotVS, const size_t slotPS, const ShaderBindingType& shaderBindingType) override;

	virtual void Fill(const Colorf32& color = { 1.f, 1.f, 1.f, 1.f }) override;
};

#endif // __WEISS__OS_WINDOWS
