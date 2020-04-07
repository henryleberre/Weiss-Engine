#include "RenderPipeline.h"

#ifdef __WEISS__OS_WINDOWS

DirectX11RenderPipeline::DirectX11RenderPipeline(const std::shared_ptr<DirectX11Device>& pDevice, const RenderPipelineDesc& desc)
	: m_pDevice(pDevice)
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

	this->m_pVertexShader = std::make_unique<DirectX11VertexShader>(this->m_pDevice, desc.vsFilename, desc.sies);
	this->m_pPixelShader  = std::make_unique<DirectX11PixelShader> (this->m_pDevice, desc.psFilename);
}

void DirectX11RenderPipeline::Bind() noexcept
{
	this->m_pVertexShader->Bind();
	this->m_pPixelShader->Bind();

	this->m_pDevice->GetDeviceContext()->IASetPrimitiveTopology(this->m_topology);
}

#endif // __WEISS__OS_WINDOWS