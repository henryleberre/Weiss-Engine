#include "RenderPipeline.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D11    {

	D3D11RenderPipeline::D3D11RenderPipeline(D3D11DeviceObjectWrapper& pDevice,
											 D3D11DeviceContextObjectWrapper* pDeviceContext,
											 const RenderPipelineDesc& desc)
		: m_pDeviceContext(pDeviceContext),      m_constantBufferIndices(desc.constantBufferIndices),
		  m_textureIndices(desc.textureIndices), m_textureSamplerIndices(desc.textureSamplerIndices)
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

		this->m_pVertexShader = D3D11VertexShader(pDevice, pDeviceContext, desc.vsFilename, desc.sies);
		this->m_pPixelShader  = D3D11PixelShader(pDevice, pDeviceContext, desc.psFilename);
	}

	void D3D11RenderPipeline::Bind(std::vector<ConstantBuffer*>& constantBuffers,
								   std::vector<Texture*>& textures,
								   std::vector<D3D11TextureSampler*> textureSamplers) noexcept
	{
		this->m_pVertexShader.Bind();
		this->m_pPixelShader.Bind();

		for (uint32_t cbIndex : this->m_constantBufferIndices)
			dynamic_cast<D3D11ConstantBuffer*>(constantBuffers[cbIndex])->Bind();

		for (uint32_t texIndex : this->m_textureIndices)
			dynamic_cast<D3D11Texture*>(textures[texIndex])->Bind();

		for (uint32_t texSamplerIndex : this->m_textureSamplerIndices)
			textureSamplers[texSamplerIndex]->Bind();

		(*this->m_pDeviceContext)->IASetPrimitiveTopology(this->m_topology);
	}

}; // D3D11
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS