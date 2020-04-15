#include "RenderPipeline.h"

#ifdef __WEISS__OS_WINDOWS

DirectX11RenderPipeline::DirectX11RenderPipeline(DirectX11DeviceObjectWrapper& pDevice,
												 DirectX11DeviceContextObjectWrapper* pDeviceContext,
												 const RenderPipelineDesc& desc)
	: m_pDeviceContext(pDeviceContext), m_constantBufferIndices(desc.constantBufferIndices)
{
	switch (desc.topology)
	{
	case PrimitiveTopology::TRIANGLES:
		this->m_topology = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		break;
	case PrimitiveTopology::TRIANGLE_STRIP:
		this->m_topology = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
		break;
	default:
		throw std::runtime_error("[DIRECTX 11] Requested Primitive Topology Is Not Supported");
		break;
	}

	this->m_pVertexShader = DirectX11VertexShader(pDevice, pDeviceContext, desc.vsFilename, desc.sies);
	this->m_pPixelShader  = DirectX11PixelShader (pDevice, pDeviceContext, desc.psFilename);
}

void DirectX11RenderPipeline::Bind(std::vector<ConstantBuffer*>& constantBuffers) noexcept
{
	this->m_pVertexShader.Bind();
	this->m_pPixelShader.Bind();

	for (uint32_t cbIndex : this->m_constantBufferIndices)
		dynamic_cast<DirectX11ConstantBuffer*>(constantBuffers[cbIndex])->Bind();

	(*this->m_pDeviceContext)->IASetPrimitiveTopology(this->m_topology);
}

#endif // __WEISS__OS_WINDOWS