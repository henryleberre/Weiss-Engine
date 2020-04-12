#include "Buffers.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12VertexBuffer::DirectX12VertexBuffer(DirectX12DeviceObjectWrapper& pDevice,
											 DirectX12CommandListObjectWrapper& pCommandList,
											 DirectX12CommandQueueObjectWrapper& pCommandQueue,
											 const size_t vertexSize, const size_t nVertices, const void* buff)
	: m_vertexSize(vertexSize), m_bufferSize(vertexSize* nVertices), m_nVertices(nVertices)
{
	if (FAILED(pDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE,
												&CD3DX12_RESOURCE_DESC::Buffer(m_bufferSize), (buff != nullptr) ? D3D12_RESOURCE_STATE_COPY_DEST : D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER,
												nullptr, IID_PPV_ARGS(&this->m_pObject))))
		throw std::runtime_error("[DIRECTX 12] Failed To Create Vertex Buffer Resource");

	this->m_pObject->SetName(L"Vertex Buffer Resource Heap");

	if (FAILED(pDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE,
												&CD3DX12_RESOURCE_DESC::Buffer(m_bufferSize), D3D12_RESOURCE_STATE_GENERIC_READ,
												nullptr, IID_PPV_ARGS(this->m_pUploadHeap.GetPtr()))))
		throw std::runtime_error("[DIRECTX 12] Failed To Create Vertex Buffer Upload Heap");

	m_pUploadHeap->SetName(L"Vertex Buffer Upload Resource Heap");

	if (buff != nullptr)
	{
		D3D12_SUBRESOURCE_DATA vertexData = {};
		vertexData.pData = buff;
		vertexData.RowPitch = m_bufferSize;
		vertexData.SlicePitch = m_bufferSize;

		UpdateSubresources(pCommandList, this->m_pObject, this->m_pUploadHeap, 0, 0, 1, &vertexData);

		pCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(this->m_pObject, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER));
	}
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

void DirectX12VertexBuffer::SetData(const void* buff, const size_t nVertices, DirectX12CommandList& pCommandList)
{
	if (buff == nullptr) return;

	pCommandList.TransitionResource(this->m_pObject, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, D3D12_RESOURCE_STATE_COPY_DEST);

	D3D12_SUBRESOURCE_DATA vertexData = {};
	vertexData.pData = buff;
	vertexData.RowPitch = nVertices * this->m_vertexSize;
	vertexData.SlicePitch = nVertices * this->m_vertexSize;

	UpdateSubresources(pCommandList, this->m_pObject, this->m_pUploadHeap, 0, 0, 1, &vertexData);

	pCommandList.TransitionResource(this->m_pObject, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
}


DirectX12IndexBuffer::DirectX12IndexBuffer(DirectX12DeviceObjectWrapper& pDevice,
										   DirectX12CommandListObjectWrapper& pCommandList,
										   DirectX12CommandQueueObjectWrapper& pCommandQueue,
										   const size_t nIndices, const void* buff)
	: m_nIndices(nIndices)
{
	const UINT bufferSize = nIndices * sizeof(uint32_t);

	if (FAILED(pDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE,
												&CD3DX12_RESOURCE_DESC::Buffer(bufferSize), (buff != nullptr) ? D3D12_RESOURCE_STATE_COPY_DEST : D3D12_RESOURCE_STATE_INDEX_BUFFER,
												nullptr, IID_PPV_ARGS(&this->m_pObject))))
		throw std::runtime_error("[DIRECTX 12] Failed To Create Index Buffer Resource");

	this->m_pObject->SetName(L"Index Buffer Resource Heap");

	if (FAILED(pDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE,
												&CD3DX12_RESOURCE_DESC::Buffer(bufferSize), D3D12_RESOURCE_STATE_GENERIC_READ,
												nullptr, IID_PPV_ARGS(this->m_pUploadHeap.GetPtr()))))
		throw std::runtime_error("[DIRECTX 12] Failed To Create Index Buffer Upload Heap");

	this->m_pUploadHeap->SetName(L"Index Buffer Upload Resource Heap");

	if (buff != nullptr)
	{
		D3D12_SUBRESOURCE_DATA indexData = {};
		indexData.pData = buff;
		indexData.RowPitch = bufferSize;
		indexData.SlicePitch = bufferSize;

		UpdateSubresources(pCommandList, this->m_pObject, this->m_pUploadHeap, 0, 0, 1, &indexData);

		pCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(this->m_pObject, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_INDEX_BUFFER));
	}
}

void DirectX12IndexBuffer::operator=(DirectX12IndexBuffer&& other) noexcept
{
	this->m_pObject = other.m_pObject;
	other.m_pObject = nullptr;
}

void DirectX12IndexBuffer::CreateView()
{
	this->m_indexBufferView.BufferLocation = this->m_pObject->GetGPUVirtualAddress();
	this->m_indexBufferView.Format         = DXGI_FORMAT_R32_UINT;
	this->m_indexBufferView.SizeInBytes    = m_nIndices * sizeof(uint32_t);
}

void DirectX12IndexBuffer::Bind(DirectX12CommandListObjectWrapper& pCommandList)
{
	pCommandList->IASetIndexBuffer(&this->m_indexBufferView);
}

D3D12_INDEX_BUFFER_VIEW DirectX12IndexBuffer::GetView()
{
	return this->m_indexBufferView;
}

void DirectX12IndexBuffer::SetData(const uint32_t* buff, const size_t nIndices, DirectX12CommandList& pCommandList)
{
	if (buff == nullptr) return;

	pCommandList.TransitionResource(this->m_pObject, D3D12_RESOURCE_STATE_INDEX_BUFFER, D3D12_RESOURCE_STATE_COPY_DEST);

	D3D12_SUBRESOURCE_DATA indexData = {};
	indexData.pData = buff;
	indexData.RowPitch = nIndices * sizeof(uint32_t);
	indexData.SlicePitch = nIndices * sizeof(uint32_t);

	UpdateSubresources(pCommandList, this->m_pObject, this->m_pUploadHeap, 0, 0, 1, &indexData);

	pCommandList.TransitionResource(this->m_pObject, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_INDEX_BUFFER);
}

DirectX12ConstantBuffer::DirectX12ConstantBuffer(DirectX12DeviceObjectWrapper& pDevice,
												 DirectX12CommandListObjectWrapper& pCommandList,
												 DirectX12CommandQueueObjectWrapper& pCommandQueue,
												 const size_t objSize, const size_t slotVS, const size_t slotPS,
												 const ShaderBindingType& shaderBindingType, const void* data)
	: m_objSize(objSize), m_slotVS(slotVS), m_slotPS(slotPS), m_shaderBindingType(shaderBindingType)
{

}

void DirectX12ConstantBuffer::CreateView()
{

}

D3D12_CONSTANT_BUFFER_VIEW_DESC DirectX12ConstantBuffer::GetView()
{
	return this->m_constantBufferView;
}

void DirectX12ConstantBuffer::Bind(DirectX12CommandListObjectWrapper& pCommandList)
{

}

void DirectX12ConstantBuffer::SetData(const void* data, DirectX12CommandList& pCommandList)
{

}

#endif // __WEISS__OS_WINDOWS