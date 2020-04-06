#pragma once

#include "Shaders.h"
#include "Buffers.h"
#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

struct DirectX11RenderPipeline {
	std::unique_ptr<DirectX11VertexShader> pVertexShader;
	std::unique_ptr<DirectX11PixelShader>  pPixelShader;
	D3D11_PRIMITIVE_TOPOLOGY topology;
};

class DirectX11RenderAPI : public RenderAPI {
private:
	std::shared_ptr<DirectX11Device>       m_pDevice;
	std::shared_ptr<DirectX11SwapChain>    m_pSwapChain;
	std::shared_ptr<DirectX11RenderTarget> m_pRenderTarget;
	std::shared_ptr<DirectX11DepthBuffer>  m_pDepthBuffer;

	std::vector<DirectX11RenderPipeline> m_renderPipelines;

public:
	DirectX11RenderAPI();

	virtual void InitRenderAPI(Window* pWindow) override;

	virtual void Draw(const Drawable& drawable, const size_t nVertices) override;

	virtual void BeginFrame() override;
	virtual void EndFrame()   override;

	virtual size_t CreateRenderPipeline(const char* vsFilename, const std::vector<ShaderInputElement>& sies, const char* psFilename, const PrimitiveTopology& topology = PrimitiveTopology::TRIANGLES) override;

	virtual size_t CreateVertexBuffer(const size_t vertexSize, const size_t nVertices, const void* buff = nullptr) override;
	virtual size_t CreateIndexBuffer (const size_t nIndices, const void* buff = nullptr) override;

	virtual void Fill(const Colorf32& color = { 1.f, 1.f, 1.f, 1.f }) override;

	[[nodiscard]] std::shared_ptr<DirectX11Device> GetDevice() noexcept;
};

#endif // __WEISS__OS_WINDOWS