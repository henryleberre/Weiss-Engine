#pragma once

#include "Shaders.h"
#include "RenderAPI.h"
#include "internal/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS


namespace WS       {
namespace Internal {
namespace D3D11    {

	class D3D11RenderPipeline {
	private:
		D3D11VertexShader    m_pVertexShader;
		D3D11PixelShader     m_pPixelShader;
		D3D11_PRIMITIVE_TOPOLOGY m_topology;

		D3D11DeviceContextObjectWrapper* m_pDeviceContext;

		std::vector<uint32_t> m_constantBufferIndices;

	public:
		D3D11RenderPipeline(D3D11DeviceObjectWrapper& pDevice,
							D3D11DeviceContextObjectWrapper* m_pDeviceContext,
							const RenderPipelineDesc& desc);

		void Bind(std::vector<ConstantBuffer*>& constantBuffers) noexcept;
	};

}; // D3D11
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS