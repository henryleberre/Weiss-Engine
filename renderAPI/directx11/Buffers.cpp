#include "Buffers.h"

#ifdef __WEISS__OS_WINDOWS

DirectX11VertexBuffer::DirectX11VertexBuffer()
{

}

DirectX11VertexBuffer::DirectX11VertexBuffer(DirectX11VertexBuffer&& other)
{
	this->m_pObject = other.m_pObject;
	other.m_pObject = nullptr;

	this->m_vertexData = other.m_vertexData;
	this->m_vertexSize = other.m_vertexSize;
}

DirectX11VertexBuffer::DirectX11VertexBuffer(DirectX11DeviceObjectWrapper& pDevice,
											 DirectX11DeviceContextObjectWrapper* pDeviceContext,
											 const size_t nVertices, const size_t vertexSize)
	: m_vertexSize(vertexSize), m_pDeviceContext(pDeviceContext)
{
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0u;
	bd.ByteWidth = static_cast<UINT>(nVertices * this->m_vertexSize);
	bd.StructureByteStride = static_cast<UINT>(this->m_vertexSize);

	this->m_vertexData.resize(bd.ByteWidth);
	std::memset(this->m_vertexData.data(), 0, bd.ByteWidth);

	if (FAILED(pDevice->CreateBuffer(&bd, nullptr, &this->m_pObject)))
		throw std::runtime_error("Unable To Create Vertex Buffer");
}

void DirectX11VertexBuffer::operator=(DirectX11VertexBuffer&& other) noexcept
{
	this->m_pObject = other.m_pObject;
	other.m_pObject = nullptr;
}

void DirectX11VertexBuffer::Bind()
{
	const UINT stride = static_cast<UINT>(this->m_vertexSize);
	const UINT offset = 0u;

	(*this->m_pDeviceContext)->IASetVertexBuffers(0u, 1u, &this->m_pObject, &stride, &offset);
}

void DirectX11VertexBuffer::Update()
{
	D3D11_MAPPED_SUBRESOURCE resource;
	if (FAILED((*this->m_pDeviceContext)->Map(this->m_pObject, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource)))
		throw std::runtime_error("Could Not Map Vertex Buffer Memory");

	std::memcpy(resource.pData, this->m_vertexData.data(), this->m_vertexData.size());
	(*this->m_pDeviceContext)->Unmap(this->m_pObject, 0);
}

DirectX11IndexBuffer::DirectX11IndexBuffer()
{

}

DirectX11IndexBuffer::DirectX11IndexBuffer(DirectX11IndexBuffer&& other)
{
	this->m_pObject = other.m_pObject;
	other.m_pObject = nullptr;

	this->m_indexData = other.m_indexData;
	this->m_nIndices  = other.m_nIndices;
}

DirectX11IndexBuffer::DirectX11IndexBuffer(DirectX11DeviceObjectWrapper& pDevice,
										   DirectX11DeviceContextObjectWrapper* pDeviceContext,
										   const size_t nIndices)
	: m_nIndices(nIndices), m_pDeviceContext(pDeviceContext)
{
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0u;
	bd.ByteWidth = static_cast<UINT>(this->m_nIndices * sizeof(uint32_t));
	bd.StructureByteStride = static_cast<UINT>(sizeof(uint32_t));

	this->m_indexData.resize(bd.ByteWidth);
	std::memset(this->m_indexData.data(), 0, bd.ByteWidth);

	if (FAILED(pDevice->CreateBuffer(&bd, nullptr, &this->m_pObject)))
		throw std::runtime_error("Unable To Create Index Buffer");
}

void DirectX11IndexBuffer::operator=(DirectX11IndexBuffer&& other) noexcept
{
	this->m_pObject = other.m_pObject;
	other.m_pObject = nullptr;
}

void DirectX11IndexBuffer::Bind()
{
	(*this->m_pDeviceContext)->IASetIndexBuffer(this->m_pObject, DXGI_FORMAT_R32_UINT, 0u);
}

void DirectX11IndexBuffer::Update()
{
	D3D11_MAPPED_SUBRESOURCE resource;
	if (FAILED((*this->m_pDeviceContext)->Map(this->m_pObject, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource)))
		throw std::runtime_error("Could Not Map Index Buffer Memory");

	std::memcpy(resource.pData, this->m_indexData.data(), this->m_indexData.size());
	(*this->m_pDeviceContext)->Unmap(this->m_pObject, 0);
}

DirectX11ConstantBuffer::DirectX11ConstantBuffer()
{

}

DirectX11ConstantBuffer::DirectX11ConstantBuffer(DirectX11ConstantBuffer&& other)
{
	this->m_pObject = other.m_pObject;
	other.m_pObject = nullptr;
	
	this->m_slotPS  = other.m_slotPS;
	this->m_slotVS  = other.m_slotVS;
	this->m_objSize = other.m_objSize;
	this->m_shaderBindingType  = other.m_shaderBindingType;
	this->m_constantBufferData = other.m_constantBufferData;
}

DirectX11ConstantBuffer::DirectX11ConstantBuffer(DirectX11DeviceObjectWrapper& pDevice,
												 DirectX11DeviceContextObjectWrapper* pDeviceContext,
												 const size_t objSize, const size_t slotVS, const size_t slotPS, const ShaderBindingType& shaderBindingType)
	: m_objSize(objSize), m_slotVS(slotVS), m_slotPS(slotPS), m_shaderBindingType(shaderBindingType), m_pDeviceContext(pDeviceContext)
{
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0u;
	bd.ByteWidth = static_cast<UINT>(this->m_objSize);

	this->m_constantBufferData.resize(bd.ByteWidth);
	std::memset(this->m_constantBufferData.data(), 0, bd.ByteWidth);

	if (FAILED(pDevice->CreateBuffer(&bd, nullptr, &this->m_pObject)))
		throw std::runtime_error("[DIRECTX 11] Unable To Create Constant Buffer");
}

void DirectX11ConstantBuffer::operator=(DirectX11ConstantBuffer&& other) noexcept
{
	this->m_pObject = other.m_pObject;
	other.m_pObject = nullptr;
}

void DirectX11ConstantBuffer::Bind()
{
	if (this->m_shaderBindingType.test(0u)) // Vertex Shader Bit (1 << 0u)
		(*this->m_pDeviceContext)->VSSetConstantBuffers((UINT)this->m_slotVS, 1u, &this->m_pObject);

	if (this->m_shaderBindingType.test(1u)) // Pixel Shader Bit (1 << 1u)
		(*this->m_pDeviceContext)->PSSetConstantBuffers((UINT)this->m_slotPS, 1u, &this->m_pObject);
}

void DirectX11ConstantBuffer::Update(const size_t frameIndex)
{
	D3D11_MAPPED_SUBRESOURCE resource;
	if (FAILED((*this->m_pDeviceContext)->Map(this->m_pObject, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &resource)))
		throw std::runtime_error("[DIRECTX 11] Failed To Map Constant Buffer Memory");

	std::memcpy(resource.pData, this->m_constantBufferData.data(), this->m_objSize);
	(*this->m_pDeviceContext)->Unmap(this->m_pObject, 0u);
}

#endif // __WEISS__OS_WINDOWS