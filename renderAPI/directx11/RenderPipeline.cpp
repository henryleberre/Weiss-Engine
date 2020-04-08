#include "RenderPipeline.h"

#ifdef __WEISS__OS_WINDOWS

DirectX11RenderPipeline::DirectX11RenderPipeline(DirectX11DeviceObjectWrapper& pDevice, const RenderPipelineDesc& desc)
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

	this->m_pVertexShader = DirectX11VertexShader(pDevice, desc.vsFilename, desc.sies);
	this->m_pPixelShader  = DirectX11PixelShader (pDevice, desc.psFilename);
}

void DirectX11RenderPipeline::Bind(DirectX11DeviceContextObjectWrapper& pDeviceContext) noexcept
{
	this->m_pVertexShader.Bind(pDeviceContext);
	this->m_pPixelShader.Bind(pDeviceContext);

	pDeviceContext->IASetPrimitiveTopology(this->m_topology);
}

#endif // __WEISS__OS_WINDOWS