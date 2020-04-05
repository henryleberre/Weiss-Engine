#include "RenderAPI.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12RenderAPI::DirectX12RenderAPI()
	: RenderAPI(RenderAPIName::DIRECTX12) {  }

void DirectX12RenderAPI::InitRenderAPI(Window* pWindow)
{
	this->m_pAdapter        = std::make_shared<DirectX12Adapater>();
	this->m_pDevice         = std::make_shared<DirectX12Device>(this->m_pAdapter);
	this->m_pCommandQueue   = std::make_shared<DirectX12CommandQueue>(this->m_pDevice, D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);
	this->m_pSwapChain      = std::make_shared<DirectX12SwapChain>(this->m_pDevice, this->m_pCommandQueue, pWindow, 3u);
	this->m_pDescriptorHeap = std::make_shared<DirectX12DescriptorHeap>(this->m_pDevice, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 3u);

	for (uint16_t i = 0; i < 3u; i++)
	{
		this->m_pRenderTargets.push_back(std::make_shared<DirectX12RenderTarget>(this->m_pDevice, this->m_pSwapChain, this->m_pDescriptorHeap, i));

		this->m_pCommandAllocators.push_back(std::make_shared<DirectX12CommandAllocator>(this->m_pDevice, D3D12_COMMAND_LIST_TYPE_DIRECT));
	}
}

void DirectX12RenderAPI::Draw(const Drawable& drawable, const size_t nVertices)
{

}

void DirectX12RenderAPI::SwapBuffers()
{

}

size_t DirectX12RenderAPI::CreateRenderPipeline(const char* vsFilename, const std::vector<ShaderInputElement>& sies, const char* psFilename, const PrimitiveTopology& topology)
{
	return this->m_renderPipelines.size() - 1u;
}

size_t DirectX12RenderAPI::CreateVertexBuffer(const size_t vertexSize, const size_t nVertices, const void* buff)
{
	return this->m_vertexBuffers.size() - 1u;
}

size_t DirectX12RenderAPI::CreateIndexBuffer(const size_t nIndices, const void* buff)
{
	return this->m_indexBuffers.size() - 1u;
}

#endif // __WEISS__OS_WINDOWS