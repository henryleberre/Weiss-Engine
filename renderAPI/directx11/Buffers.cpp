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
	if (FAILED(pDevice->CreateBuffer(&bd, pInitialData, &this->m_pObject)))
		throw std::runtime_error("Unable To Create Vertex Buffer");
}

void DirectX11VertexBuffer::operator=(DirectX11VertexBuffer&& other) noexcept
{
	this->m_pObject = other.m_pObject;
	other.m_pObject = nullptr;
}

void DirectX11VertexBuffer::Bind(DirectX11DeviceContextObjectWrapper& pDeviceContext)
{
	const UINT stride = static_cast<UINT>(this->m_vertexSize);
	const UINT offset = 0u;

	pDeviceContext->IASetVertexBuffers(0u, 1u, &this->m_pObject, &stride, &offset);
}

void DirectX11VertexBuffer::SetData(const void* buff, const size_t nVertices, DirectX11DeviceContextObjectWrapper& pDeviceContext)
{
	if (buff == nullptr) return;

	D3D11_MAPPED_SUBRESOURCE resource;
	if (FAILED(pDeviceContext->Map(this->m_pObject, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource)))
		throw std::runtime_error("Could Not Map Vertex Buffer Memory");

	std::memcpy(resource.pData, buff, nVertices * this->m_vertexSize);
	pDeviceContext->Unmap(this->m_pObject, 0);
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
	if (FAILED(pDevice->CreateBuffer(&bd, pInitialData, &this->m_pObject)))
		throw std::runtime_error("Unable To Create Index Buffer");
}

void DirectX11IndexBuffer::operator=(DirectX11IndexBuffer&& other) noexcept
{
	this->m_pObject = other.m_pObject;
	other.m_pObject = nullptr;
}

void DirectX11IndexBuffer::Bind(DirectX11DeviceContextObjectWrapper& pDeviceContext)
{
	pDeviceContext->IASetIndexBuffer(this->m_pObject, DXGI_FORMAT_R32_UINT, 0u);
}

void DirectX11IndexBuffer::SetData(const uint32_t* buff, const size_t nIndices, DirectX11DeviceContextObjectWrapper& pDeviceContext)
{
	if (buff == nullptr) return;

	D3D11_MAPPED_SUBRESOURCE resource;
	if (FAILED(pDeviceContext->Map(this->m_pObject, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource)))
		throw std::runtime_error("Could Not Map Index Buffer Memory");

	std::memcpy(resource.pData, buff, nIndices * sizeof(uint32_t));
	pDeviceContext->Unmap(this->m_pObject, 0);
}

DirectX11ConstantBuffer::DirectX11ConstantBuffer(DirectX11DeviceObjectWrapper& pDevice, const size_t objSize, const size_t slotVS, const size_t slotPS, const ShaderBindingType& shaderBindingType, const void* data)
	: m_objSize(objSize), m_slotVS(slotVS), m_slotPS(slotPS), m_shaderBindingType(shaderBindingType)
{
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0u;
	bd.ByteWidth = this->m_objSize;

	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = data;

	const D3D11_SUBRESOURCE_DATA* pInitialData = (data != nullptr) ? &sd : nullptr;
	if (FAILED(pDevice->CreateBuffer(&bd, pInitialData, &this->m_pObject)))
		throw std::runtime_error("[DIRECTX 11] Unable To Create Constant Buffer");
}

void DirectX11ConstantBuffer::operator=(DirectX11ConstantBuffer&& other) noexcept
{
	this->m_pObject = other.m_pObject;
	other.m_pObject = nullptr;
}

void DirectX11ConstantBuffer::Bind(DirectX11DeviceContextObjectWrapper& pDeviceContext)
{
	if (this->m_shaderBindingType.test(0u)) // Vertex Shader Bit (1 << 0u)
		pDeviceContext->VSSetConstantBuffers(this->m_slotVS, 1u, &this->m_pObject);

	if (this->m_shaderBindingType.test(1u)) // Pixel Shader Bit (1 << 1u)
		pDeviceContext->PSSetConstantBuffers(this->m_slotPS, 1u, &this->m_pObject);
}

void DirectX11ConstantBuffer::SetData(const void* data, DirectX11DeviceContextObjectWrapper& pDeviceContext)
{
	if (data == nullptr) return;

	D3D11_MAPPED_SUBRESOURCE resource;
	if (FAILED(pDeviceContext->Map(this->m_pObject, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &resource)))
		throw std::runtime_error("[DIRECTX 11] Failed To Map Constant Buffer Memory");

	std::memcpy(resource.pData, data, this->m_objSize);
	pDeviceContext->Unmap(this->m_pObject, 0u);
}

#endif // __WEISS__OS_WINDOWS