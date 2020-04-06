#pragma once

#include "Shaders.h"
#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

struct DirectX12RenderPipeline {
	//std::unique_ptr<DirectX11VertexShader> pVertexShader;
	//std::unique_ptr<DirectX11PixelShader>  pPixelShader;
	PrimitiveTopology topology;
};

class DirectX12RenderAPI : public RenderAPI {
private:
	std::shared_ptr<DirectX12Adapater>       m_pAdapter;
	std::shared_ptr<DirectX12Device>         m_pDevice;
	std::shared_ptr<DirectX12CommandQueue>   m_pCommandQueue;
	std::shared_ptr<DirectX12SwapChain>      m_pSwapChain;
	std::shared_ptr<DirectX12DescriptorHeap> m_pDescriptorHeap;
	std::array<std::shared_ptr<DirectX12RenderTarget>,     WEISS__FRAME_BUFFER_COUNT> m_pRenderTargets;
	std::array<std::shared_ptr<DirectX12CommandAllocator>, WEISS__FRAME_BUFFER_COUNT> m_pCommandAllocators;
	std::array<std::shared_ptr<DirectX12Fence>,            WEISS__FRAME_BUFFER_COUNT> m_pFences;
	std::array<UINT64, WEISS__FRAME_BUFFER_COUNT> m_expectedFenceValues;
	std::shared_ptr<DirectX12CommandList> m_pCommandList;
	//std::shared_ptr<DirectX12RenderTarget> m_pRenderTarget;
	//std::shared_ptr<DirectX12DepthBuffer>  m_pDepthBuffer;
	
	std::vector<DirectX12RenderPipeline> m_renderPipelines;

	size_t currentFrameIndex = 0u;

	CD3DX12_CPU_DESCRIPTOR_HANDLE m_currentRtvHandle;

private:
	void WaitForNextFrame();

public:
	DirectX12RenderAPI();

	virtual void InitRenderAPI(Window* pWindow) override;

	virtual void Draw(const Drawable& drawable, const size_t nVertices) override;

	virtual void BeginFrame() override;
	virtual void EndFrame()   override;

	virtual size_t CreateRenderPipeline(const char* vsFilename, const std::vector<ShaderInputElement>& sies, const char* psFilename, const PrimitiveTopology& topology = PrimitiveTopology::TRIANGLES) override;

	virtual size_t CreateVertexBuffer(const size_t vertexSize, const size_t nVertices, const void* buff = nullptr) override;
	virtual size_t CreateIndexBuffer(const size_t nIndices, const void* buff = nullptr) override;

	virtual void Fill(const Colorf32& color = { 1.f, 1.f, 1.f, 1.f }) override;
};

#endif // __WEISS__OS_WINDOWS