#include "Buffers.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12VertexBuffer::DirectX12VertexBuffer(DirectX12DeviceObjectWrapper& pDevice,
											 DirectX12CommandListObjectWrapper& pCommandList,
											 DirectX12CommandQueueObjectWrapper& pCommandQueue,
											 const size_t vertexSize, const size_t nVertices, const void* buff)
	: m_vertexSize(vertexSize), m_bufferSize(vertexSize* nVertices), m_nVertices(nVertices)
{
	if (pDevice->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(m_bufferSize),
		D3D12_RESOURCE_STATE_COPY_DEST,
		nullptr, 
		IID_PPV_ARGS(&this->m_pObject)) != S_OK)
		throw std::runtime_error("FAIL");

	this->m_pObject->SetName(L"Vertex Buffer Resource Heap");

	ID3D12Resource* vBufferUploadHeap;
	if (pDevice->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(m_bufferSize),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vBufferUploadHeap)) != S_OK)
		throw std::runtime_error("FAIL");

	vBufferUploadHeap->SetName(L"Vertex Buffer Upload Resource Heap");

	D3D12_SUBRESOURCE_DATA vertexData = {};
	vertexData.pData = buff;
	vertexData.RowPitch = m_bufferSize;
	vertexData.SlicePitch = m_bufferSize;

	UpdateSubresources(pCommandList, this->m_pObject, vBufferUploadHeap, 0, 0, 1, &vertexData);

	pCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(this->m_pObject, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER));
}

void DirectX12VertexBuffer::operator=(DirectX12VertexBuffer&& other) noexcept
{
	this->m_pObject = other.m_pObject;
	other.m_pObject = nullptr;
}

void DirectX12VertexBuffer::CreateView()
{
	this->m_vertexBufferView.BufferLocation = this->m_pObject->GetGPUVirtualAddress();
	this->m_vertexBufferView.StrideInBytes  = m_vertexSize;
	this->m_vertexBufferView.SizeInBytes    = m_bufferSize;
}

D3D12_VERTEX_BUFFER_VIEW DirectX12VertexBuffer::GetView()
{
	return this->m_vertexBufferView;
}

void DirectX12VertexBuffer::Bind(DirectX12CommandListObjectWrapper& pCommandList)
{
	pCommandList->IASetVertexBuffers(0u, 1u, &this->m_vertexBufferView);
}

size_t DirectX12VertexBuffer::GetCount()
{
	return this->m_nVertices;
}

void   DirectX12VertexBuffer::SetData(const void* buff, const size_t nVertices)
{

}

#endif // __WEISS__OS_WINDOWS