#pragma once

#include "Shaders.h"
#include "internal/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX11RenderPipeline {
private:
	std::unique_ptr<DirectX11VertexShader> m_pVertexShader;
	std::unique_ptr<DirectX11PixelShader>  m_pPixelShader;
	D3D11_PRIMITIVE_TOPOLOGY m_topology;

	const std::shared_ptr<DirectX11Device> m_pDevice;

public:
	DirectX11RenderPipeline(const std::shared_ptr<DirectX11Device>& pDevice, const RenderPipelineDesc& desc);

	void Bind() noexcept;
};

#endif // __WEISS__OS_WINDOWS