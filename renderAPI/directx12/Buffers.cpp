#include "Buffers.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12VertexBuffer::DirectX12VertexBuffer(const std::shared_ptr<DirectX12Device>& pDevice, const std::shared_ptr<DirectX12CommandList>& pCommandList, const size_t vertexSize, const size_t nVertices, const void* buff)
{
	const UINT bufferSize = vertexSize * nVertices;

	
}

void DirectX12VertexBuffer::Bind(const std::shared_ptr<DirectX12CommandList>& pCommandList)
{
	pCommandList->Get()->IASetVertexBuffers(0u, 1u, &this->m_vertexBufferView);
}

size_t DirectX12VertexBuffer::GetCount()
{
	return 0;
}

void   DirectX12VertexBuffer::SetData(const void* buff, const size_t nVertices)
{

}

#endif // __WEISS__OS_WINDOWS