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
	std::vector<std::shared_ptr<DirectX12RenderTarget>>     m_pRenderTargets;
	std::vector<std::shared_ptr<DirectX12CommandAllocator>> m_pCommandAllocators;
	//std::shared_ptr<DirectX12RenderTarget> m_pRenderTarget;
	//std::shared_ptr<DirectX12DepthBuffer>  m_pDepthBuffer;
	
	std::vector<DirectX12RenderPipeline> m_renderPipelines;

public:
	DirectX12RenderAPI();

	virtual void InitRenderAPI(Window* pWindow) override;

	virtual void Draw(const Drawable& drawable, const size_t nVertices) override;

	virtual void SwapBuffers() override;

	virtual size_t CreateRenderPipeline(const char* vsFilename, const std::vector<ShaderInputElement>& sies, const char* psFilename, const PrimitiveTopology& topology = PrimitiveTopology::TRIANGLES) override;

	virtual size_t CreateVertexBuffer(const size_t vertexSize, const size_t nVertices, const void* buff = nullptr) override;
	virtual size_t CreateIndexBuffer(const size_t nIndices, const void* buff = nullptr) override;
};

#endif // __WEISS__OS_WINDOWS