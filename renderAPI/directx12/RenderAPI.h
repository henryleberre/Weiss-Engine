#pragma once

#include "Buffers.h"
#include "RenderPipeline.h"
#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX12RenderAPI : public RenderAPI {
private:
	DirectX12Adapter        m_pAdapter;
	DirectX12Device         m_pDevice;
	DirectX12CommandQueue   m_pCommandQueue;
	DirectX12SwapChain      m_pSwapChain;
	DirectX12DescriptorHeap m_pDescriptorHeap;
	std::array<DirectX12RenderTarget,     WEISS__FRAME_BUFFER_COUNT> m_pRenderTargets;
	std::array<DirectX12CommandAllocator, WEISS__FRAME_BUFFER_COUNT> m_pCommandAllocators;
	std::array<std::unique_ptr<DirectX12Fence>, WEISS__FRAME_BUFFER_COUNT> m_pFences;
	std::array<UINT64, WEISS__FRAME_BUFFER_COUNT> m_expectedFenceValues;
	DirectX12RootSignature m_pInputAssemblerRootSignature;
	DirectX12CommandList m_pCommandList;
	
	std::vector<std::unique_ptr<DirectX12VertexBuffer>> m_pVertexBuffers;
	std::vector<std::unique_ptr<DirectX12IndexBuffer>>  m_pIndexBuffers;

	std::vector<std::unique_ptr<DirectX12RenderPipeline>> m_pRenderPipelines;

	size_t currentFrameIndex = 0u;

	CD3DX12_CPU_DESCRIPTOR_HANDLE m_currentRtvHandle;

	D3D12_RECT     m_scissors;
	D3D12_VIEWPORT m_viewport;

private:
	void WaitForNextFrame();

	void CreateRenderTargets();

public:
	DirectX12RenderAPI();

	virtual void InitRenderAPI(Window* pWindow, const std::vector<RenderPipelineDesc>& pipelineDescs) override;

	virtual void Draw(const Drawable& drawable, const size_t nVertices) override;

	virtual void BeginFrame() override;
	virtual void EndFrame()   override;

	virtual size_t CreateVertexBuffer(const size_t vertexSize, const size_t nVertices, const void* buff = nullptr) override;
	virtual size_t CreateIndexBuffer(const size_t nIndices, const void* buff = nullptr) override;

	virtual void Fill(const Colorf32& color = { 1.f, 1.f, 1.f, 1.f }) override;
};

#endif // __WEISS__OS_WINDOWS