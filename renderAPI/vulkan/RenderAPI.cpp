#include "RenderAPI.h"

namespace WS       {
namespace Internal {
namespace VK       {

	VKRenderAPI::VKRenderAPI()
		: RenderAPI(RenderAPIName::VULKAN)
	{
		
	}

	VKRenderAPI::~VKRenderAPI()
	{
		VKRenderPass::DestroyRenderPasses(this->m_device);
	}

	void VKRenderAPI::InitRenderAPI(Window* pWindow, const uint16_t maxFps)
	{
		this->m_instance  = VKInstance("App Made With Weiss Engine");
		this->m_surface   = VKSurface(&this->m_instance, pWindow);
		this->m_device    = VKDevice(this->m_instance, this->m_surface);
		this->m_swapChain = VKSwapChain(this->m_device, this->m_surface);

		VKRenderPass::CreateRenderPasses(this->m_device, this->m_swapChain);
		this->m_swapChain.CreateFrameBuffers();
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
		this->m_swapChain.Present();
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

	size_t VKRenderAPI::CreateTexture(const size_t width, const size_t height, const size_t slot, const bool useMipmaps)
	{
		return 0u;
	}

	size_t VKRenderAPI::CreateTextureSampler(const TextureFilter& filter, const size_t slot)
	{
		return 0u;
	}

	void VKRenderAPI::Fill(const Colorf32& color)
	{

	}

}; // VK
}; // INTERNAL
}; // WS