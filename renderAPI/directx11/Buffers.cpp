#include "Buffers.h"

#ifdef __WEISS__OS_WINDOWS

DirectX11VertexBuffer::DirectX11VertexBuffer(DirectX11DeviceObjectWrapper& pDevice, const size_t vertexSize, const size_t nVertices, const void* buff)
	: m_vertexSize(vertexSize), m_nVertices(nVertices)
{
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0u;
	bd.ByteWidth = static_cast<UINT>(this->m_vertexSize * this->m_vertexSize);
	bd.StructureByteStride = static_cast<UINT>(this->m_vertexSize);

	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = buff;

	const D3D11_SUBRESOURCE_DATA* pInitialData = (buff != nullptr) ? &sd : nullptr;
	if (pDevice->CreateBuffer(&bd, pInitialData, &this->m_pVertexBuffer) != S_OK)
		throw std::runtime_error("Unable To Create Vertex Buffer");
}

void DirectX11VertexBuffer::Bind(DirectX11DeviceContextObjectWrapper& pDeviceContext)
{
	const UINT stride = static_cast<UINT>(this->m_vertexSize);
	const UINT offset = 0u;

	pDeviceContext->IASetVertexBuffers(0u, 1u, this->m_pVertexBuffer.GetAddressOf(), &stride, &offset);
}

size_t DirectX11VertexBuffer::GetCount() { return this->m_nVertices; }

void DirectX11VertexBuffer::SetData(const void* buff, const size_t nVertices, DirectX11DeviceContextObjectWrapper& pDeviceContext)
{
	D3D11_MAPPED_SUBRESOURCE resource;
	if (pDeviceContext->Map(this->m_pVertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource) != S_OK)
		throw std::runtime_error("Could Not Map Vertex Buffer Memory");

	std::memcpy(resource.pData, buff, nVertices * this->m_vertexSize);
	pDeviceContext->Unmap(this->m_pVertexBuffer.Get(), 0);
}

DirectX11IndexBuffer::DirectX11IndexBuffer(DirectX11DeviceObjectWrapper& pDevice, const size_t nIndices, const void* buff)
	: m_nIndices(nIndices)
{
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0u;
	bd.ByteWidth = static_cast<UINT>(this->m_nIndices * sizeof(uint32_t));
	bd.StructureByteStride = static_cast<UINT>(sizeof(uint32_t));

	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = buff;

	const D3D11_SUBRESOURCE_DATA* pInitialData = (buff != nullptr) ? &sd : nullptr;
	if (pDevice->CreateBuffer(&bd, pInitialData, &this->m_pIndexBuffer) != S_OK)
		throw std::runtime_error("Unable To Create Index Buffer");
}

void DirectX11IndexBuffer::Bind(DirectX11DeviceContextObjectWrapper& pDeviceContext)
{
	pDeviceContext->IASetIndexBuffer(this->m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0u);
}

size_t DirectX11IndexBuffer::GetCount() { return this->m_nIndices; }

void DirectX11IndexBuffer::SetData(const uint32_t* buff, const size_t nIndices, DirectX11DeviceContextObjectWrapper& pDeviceContext)
{
	D3D11_MAPPED_SUBRESOURCE resource;
	if (pDeviceContext->Map(this->m_pIndexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource) != S_OK)
		throw std::runtime_error("Could Not Map Index Buffer Memory");

	std::memcpy(resource.pData, buff, nIndices * sizeof(uint32_t));
	pDeviceContext->Unmap(this->m_pIndexBuffer.Get(), 0);
}

#endif // __WEISS__OS_WINDOWS