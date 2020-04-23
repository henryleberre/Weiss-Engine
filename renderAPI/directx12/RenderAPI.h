#pragma once

#include "Buffers.h"
#include "RenderPipeline.h"
#include "internal/Include.h"
#include "CommandSubmitter.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	class D3D12RenderAPI : public RenderAPI {
	private:
		D3D12Adapter        m_pAdapter;
		D3D12Device         m_pDevice;
		D3D12CommandQueue   m_pCommandQueue;
		D3D12SwapChain      m_pSwapChain;
		D3D12DescriptorHeap m_pDescriptorHeap;
		D3D12DepthBuffer    m_pDepthBuffer;

		std::array<D3D12RenderTarget, WEISS__FRAME_BUFFER_COUNT> m_pRenderTargets;

		D3D12CommandSubmitter m_commandSubmitter;

		std::vector<D3D12RenderPipeline> m_renderPipelines;

		size_t currentFrameIndex = 0u;

		CD3DX12_CPU_DESCRIPTOR_HANDLE m_currentRtvHandle;

		D3D12_RECT     m_scissors;
		D3D12_VIEWPORT m_viewport;

	private:
		void CreateRenderTargets();

	public:
		D3D12RenderAPI();

		virtual void InitRenderAPI(Window* pWindow, const uint16_t maxFps = 144u) override;
		virtual void InitPipelines(const std::vector<RenderPipelineDesc>& pipelineDescs) override;

		virtual void Draw(const Drawable& drawable, const size_t nVertices) override;

		virtual void BeginDrawing() override;
		virtual void EndDrawing()   override;
		virtual void Present(const bool vSync) override;

		virtual size_t CreateVertexBuffer  (const size_t nVertices, const size_t vertexSize) override;
		virtual size_t CreateIndexBuffer   (const size_t nIndices) override;
		virtual size_t CreateConstantBuffer(const size_t objSize, const size_t slot) override;

		virtual void Fill(const Colorf32& color = { 1.f, 1.f, 1.f, 1.f }) override;
	};

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS
