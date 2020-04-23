#include "RenderAPI.h"

namespace WS       {
namespace Internal {
namespace VK       {

	VKRenderAPI::VKRenderAPI()
		: RenderAPI(RenderAPIName::VULKAN)
	{
		this->m_instance = VKInstance("App Made With Weiss Engine");
		
	}

	void VKRenderAPI::InitRenderAPI(Window* pWindow, const uint16_t maxFps)
	{

	}

	void VKRenderAPI::InitPipelines(const std::vector<RenderPipelineDesc>& pipelineDescs)
	{

	}

	void VKRenderAPI::Draw(const Drawable& drawable, const size_t nVertices)
	{

	}

	void VKRenderAPI::BeginDrawing()
	{

	}

	void VKRenderAPI::EndDrawing()
	{
	
	}

	void VKRenderAPI::Present(const bool vSync)
	{

	}

	size_t VKRenderAPI::CreateVertexBuffer(const size_t nVertices, const size_t vertexSize)
	{
		return 0u;
	}

	size_t VKRenderAPI::CreateIndexBuffer(const size_t nIndices)
	{
		return 0u;
	}

	size_t VKRenderAPI::CreateConstantBuffer(const size_t objSize, const size_t slot)
	{
		return 0u;
	}

	void VKRenderAPI::Fill(const Colorf32& color)
	{

	}

}; // VK
}; // INTERNAL
}; // WS