#include "Buffers.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12VertexBuffer::DirectX12VertexBuffer()
{

}

DirectX12VertexBuffer::DirectX12VertexBuffer(DirectX12VertexBuffer&& other)
{
	this->m_pObject = other.m_pObject;
	other.m_pObject = nullptr;

	this->m_pUploadHeap      = std::move(other.m_pUploadHeap);
	this->m_pCommandList     = other.m_pCommandList;
	this->m_vertexSize       = other.m_vertexSize;
	this->m_vertexBufferView = other.m_vertexBufferView;
}

DirectX12VertexBuffer::DirectX12VertexBuffer(DirectX12DeviceObjectWrapper& pDevice,
											 DirectX12CommandList* pCommandList,
											 const size_t nVertices, const size_t vertexSize)
	: m_vertexSize(vertexSize), m_pCommandList(pCommandList)
{
	const UINT bufferSize = vertexSize * nVertices;

	if (FAILED(pDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(bufferSize), D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER,
		nullptr, IID_PPV_ARGS(&this->m_pObject))))
		throw std::runtime_error("[DIRECTX 12] Failed To Create Vertex Buffer Resource");

	this->m_pObject->SetName(L"Vertex Buffer Resource Heap");

	if (FAILED(pDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(bufferSize), D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr, IID_PPV_ARGS(this->m_pUploadHeap.GetPtr()))))
		throw std::runtime_error("[DIRECTX 12] Failed To Create Vertex Buffer Upload Heap");

	m_pUploadHeap->SetName(L"Vertex Buffer Upload Resource Heap");

	this->m_vertexData.resize(bufferSize);
	std::memset(this->m_vertexData.data(), 0u, bufferSize);
}

void DirectX12VertexBuffer::operator=(DirectX12VertexBuffer&& other) noexcept
{
	this->m_pObject = other.m_pObject;
	other.m_pObject = nullptr;

	this->m_pUploadHeap      = std::move(other.m_pUploadHeap);
	this->m_pCommandList     = other.m_pCommandList;
	this->m_vertexSize       = other.m_vertexSize;
	this->m_vertexBufferView = other.m_vertexBufferView;
}

void DirectX12VertexBuffer::CreateView()
{
	this->m_vertexBufferView.StrideInBytes  = this->m_vertexSize;
	this->m_vertexBufferView.SizeInBytes    = this->m_vertexData.size();
	this->m_vertexBufferView.BufferLocation = this->m_pObject->GetGPUVirtualAddress();
}

D3D12_VERTEX_BUFFER_VIEW DirectX12VertexBuffer::GetView()
{
	return this->m_vertexBufferView;
}

void DirectX12VertexBuffer::Bind()
{
	(*this->m_pCommandList)->IASetVertexBuffers(0u, 1u, &this->m_vertexBufferView);
}

void DirectX12VertexBuffer::Update()
{
	(*this->m_pCommandList).TransitionResource(this->m_pObject, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, D3D12_RESOURCE_STATE_COPY_DEST);

	D3D12_SUBRESOURCE_DATA vertexData = {};
	vertexData.pData      = this->m_vertexData.data();
	vertexData.RowPitch   = this->m_vertexData.size();
	vertexData.SlicePitch = vertexData.RowPitch;

	UpdateSubresources(*this->m_pCommandList, this->m_pObject, this->m_pUploadHeap, 0, 0, 1, &vertexData);

	(*this->m_pCommandList).TransitionResource(this->m_pObject, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
}



DirectX12IndexBuffer::DirectX12IndexBuffer()
{

}

DirectX12IndexBuffer::DirectX12IndexBuffer(DirectX12IndexBuffer&& other)
{
	this->m_pObject = other.m_pObject;
	other.m_pObject = nullptr;

	this->m_nIndices        = other.m_nIndices;
	this->m_pUploadHeap     = std::move(other.m_pUploadHeap);
	this->m_pCommandList    = other.m_pCommandList;
	this->m_indexBufferView = other.m_indexBufferView;
}

DirectX12IndexBuffer::DirectX12IndexBuffer(DirectX12DeviceObjectWrapper& pDevice,
										   DirectX12CommandList* pCommandList,
										   const size_t nIndices)
	: m_nIndices(nIndices), m_pCommandList(pCommandList)
{
	const UINT bufferSize = nIndices * sizeof(uint32_t);

	if (FAILED(pDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE,
												&CD3DX12_RESOURCE_DESC::Buffer(bufferSize), D3D12_RESOURCE_STATE_INDEX_BUFFER,
												nullptr, IID_PPV_ARGS(&this->m_pObject))))
		throw std::runtime_error("[DIRECTX 12] Failed To Create Index Buffer Resource");

	this->m_pObject->SetName(L"Index Buffer Resource Heap");

	if (FAILED(pDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE,
												&CD3DX12_RESOURCE_DESC::Buffer(bufferSize), D3D12_RESOURCE_STATE_GENERIC_READ,
												nullptr, IID_PPV_ARGS(this->m_pUploadHeap.GetPtr()))))
		throw std::runtime_error("[DIRECTX 12] Failed To Create Index Buffer Upload Heap");

	this->m_pUploadHeap->SetName(L"Index Buffer Upload Resource Heap");

	this->m_indexData.resize(bufferSize);
	std::memset(this->m_indexData.data(), 0u, bufferSize);
}

void DirectX12IndexBuffer::operator=(DirectX12IndexBuffer&& other) noexcept
{
	this->m_pObject = other.m_pObject;
	other.m_pObject = nullptr;

	this->m_nIndices        = other.m_nIndices;
	this->m_pUploadHeap     = std::move(other.m_pUploadHeap);
	this->m_pCommandList    = other.m_pCommandList;
	this->m_indexBufferView = other.m_indexBufferView;
}

void DirectX12IndexBuffer::Bind()
{
	(*this->m_pCommandList)->IASetIndexBuffer(&this->m_indexBufferView);
}

void DirectX12IndexBuffer::CreateView()
{
	this->m_indexBufferView.Format         = DXGI_FORMAT_R32_UINT;
	this->m_indexBufferView.SizeInBytes    = this->m_indexData.size();
	this->m_indexBufferView.BufferLocation = this->m_pObject->GetGPUVirtualAddress();
}

D3D12_INDEX_BUFFER_VIEW DirectX12IndexBuffer::GetView()
{
	return this->m_indexBufferView;
}

void DirectX12IndexBuffer::Update()
{
	(*this->m_pCommandList).TransitionResource(this->m_pObject, D3D12_RESOURCE_STATE_INDEX_BUFFER, D3D12_RESOURCE_STATE_COPY_DEST);

	D3D12_SUBRESOURCE_DATA indexData = {};
	indexData.pData      = this->m_indexData.data();
	indexData.RowPitch   = this->m_indexData.size();
	indexData.SlicePitch = indexData.RowPitch;

	UpdateSubresources(*this->m_pCommandList, this->m_pObject, this->m_pUploadHeap, 0, 0, 1, &indexData);

	(*this->m_pCommandList).TransitionResource(this->m_pObject, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_INDEX_BUFFER);
}

DirectX12ConstantBuffer::DirectX12ConstantBuffer()
{

}

DirectX12ConstantBuffer::DirectX12ConstantBuffer(DirectX12ConstantBuffer&& other)
{
	///
}

DirectX12ConstantBuffer::DirectX12ConstantBuffer(DirectX12DeviceObjectWrapper& pDevice,
												 DirectX12CommandList* pCommandList,
												 const size_t objSize, const size_t slotVS, const size_t slotPS,
												 const ShaderBindingType& shaderBindingType)
	: m_objSize(objSize), m_slotVS(slotVS), m_slotPS(slotPS), m_shaderBindingType(shaderBindingType), m_pCommandList(pCommandList)
{

}

void DirectX12ConstantBuffer::CreateView()
{

}

D3D12_CONSTANT_BUFFER_VIEW_DESC DirectX12ConstantBuffer::GetView()
{
	return this->m_constantBufferView;
}

void DirectX12ConstantBuffer::Bind()
{

}

void DirectX12ConstantBuffer::Update()
{

}

#endif // __WEISS__OS_WINDOWS