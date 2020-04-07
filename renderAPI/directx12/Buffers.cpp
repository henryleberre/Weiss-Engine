#include "Buffers.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12VertexBuffer::DirectX12VertexBuffer(const std::shared_ptr<DirectX12Device>& pDevice, const std::shared_ptr<DirectX12CommandList>& pCommandList, const std::shared_ptr<DirectX12CommandQueue>& pCommandQueue, const size_t vertexSize, const size_t nVertices, const void* buff)
	: m_vertexSize(vertexSize), m_bufferSize(vertexSize* nVertices)
{
	if (pDevice->Get()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), // a default heap
		D3D12_HEAP_FLAG_NONE, // no flags
		&CD3DX12_RESOURCE_DESC::Buffer(m_bufferSize), // resource description for a buffer
		D3D12_RESOURCE_STATE_COPY_DEST, // we will start this heap in the copy destination state since we will copy data
										// from the upload heap to this heap
		nullptr, // optimized clear value must be null for this type of resource. used for render targets and depth/stencil buffers
		IID_PPV_ARGS(&this->m_pVertexBuffer)) != S_OK)
		throw std::runtime_error("FAIL");

	this->m_pVertexBuffer->SetName(L"Vertex Buffer Resource Heap");

	ID3D12Resource* vBufferUploadHeap;
	if (pDevice->Get()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), // upload heap
		D3D12_HEAP_FLAG_NONE, // no flags
		&CD3DX12_RESOURCE_DESC::Buffer(m_bufferSize), // resource description for a buffer
		D3D12_RESOURCE_STATE_GENERIC_READ, // GPU will read from this buffer and copy its contents to the default heap
		nullptr,
		IID_PPV_ARGS(&vBufferUploadHeap)) != S_OK)
		throw std::runtime_error("FAIL");

	vBufferUploadHeap->SetName(L"Vertex Buffer Upload Resource Heap");

	// store vertex buffer in upload heap
	D3D12_SUBRESOURCE_DATA vertexData = {};
	vertexData.pData = buff; // pointer to our vertex array
	vertexData.RowPitch = m_bufferSize; // size of all our triangle vertex data
	vertexData.SlicePitch = m_bufferSize; // also the size of our triangle vertex data

	UpdateSubresources(pCommandList->Get().Get(), this->m_pVertexBuffer.Get(), vBufferUploadHeap, 0, 0, 1, &vertexData);

	pCommandList->Get()->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(this->m_pVertexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER));
}

void DirectX12VertexBuffer::CreateView()
{
	this->m_vertexBufferView.BufferLocation = this->m_pVertexBuffer->GetGPUVirtualAddress();
	this->m_vertexBufferView.StrideInBytes  = m_vertexSize;
	this->m_vertexBufferView.SizeInBytes    = m_bufferSize;
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