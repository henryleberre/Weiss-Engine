#pragma once

#include "Shaders.h"
#include "internal/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX11RenderPipeline {
private:
	DirectX11VertexShader m_pVertexShader;
	DirectX11PixelShader  m_pPixelShader;
	D3D11_PRIMITIVE_TOPOLOGY m_topology;

	DirectX11DeviceContextObjectWrapper* m_pDeviceContext;

public:
	DirectX11RenderPipeline(DirectX11DeviceObjectWrapper& pDevice,
							DirectX11DeviceContextObjectWrapper* m_pDeviceContext,
							const RenderPipelineDesc& desc);

	void Bind() noexcept;
};

#endif // __WEISS__OS_WINDOWS