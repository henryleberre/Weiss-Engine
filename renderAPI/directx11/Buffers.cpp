#include "Buffers.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D11    {

	D3D11VertexBuffer::D3D11VertexBuffer(D3D11DeviceObjectWrapper& pDevice,
										 D3D11DeviceContextObjectWrapper* pDeviceContext,
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

	D3D11VertexBuffer& D3D11VertexBuffer::operator=(D3D11VertexBuffer&& other) noexcept
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = nullptr;
		this->m_vertexData = std::move(other.m_vertexData);
		this->m_vertexSize = std::move(other.m_vertexSize);

		return *this;
	}

	void D3D11VertexBuffer::Bind()
	{
		const UINT stride = static_cast<UINT>(this->m_vertexSize);
		const UINT offset = 0u;

		(*this->m_pDeviceContext)->IASetVertexBuffers(0u, 1u, &this->m_pObject, &stride, &offset);
	}

	void D3D11VertexBuffer::Update()
	{
		D3D11_MAPPED_SUBRESOURCE resource;
		if (FAILED((*this->m_pDeviceContext)->Map(this->m_pObject, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource)))
			throw std::runtime_error("Could Not Map Vertex Buffer Memory");

		std::memcpy(resource.pData, this->m_vertexData.data(), this->m_vertexData.size());
		(*this->m_pDeviceContext)->Unmap(this->m_pObject, 0);
	}

	D3D11IndexBuffer::D3D11IndexBuffer(D3D11DeviceObjectWrapper& pDevice,
									   D3D11DeviceContextObjectWrapper* pDeviceContext,
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

	D3D11IndexBuffer& D3D11IndexBuffer::operator=(D3D11IndexBuffer&& other) noexcept
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = nullptr;
	
		other.m_nIndices  = other.m_nIndices;
		other.m_indexData = std::move(other.m_indexData);

		return *this;
	}

	void D3D11IndexBuffer::Bind()
	{
		(*this->m_pDeviceContext)->IASetIndexBuffer(this->m_pObject, DXGI_FORMAT_R32_UINT, 0u);
	}

	void D3D11IndexBuffer::Update()
	{
		D3D11_MAPPED_SUBRESOURCE resource;
		if (FAILED((*this->m_pDeviceContext)->Map(this->m_pObject, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource)))
			throw std::runtime_error("Could Not Map Index Buffer Memory");

		std::memcpy(resource.pData, this->m_indexData.data(), this->m_indexData.size());
		(*this->m_pDeviceContext)->Unmap(this->m_pObject, 0);
	}

	D3D11ConstantBuffer::D3D11ConstantBuffer(D3D11DeviceObjectWrapper& pDevice,
											 D3D11DeviceContextObjectWrapper* pDeviceContext,
											 const size_t objSize, const size_t slot)
		: m_objSize(objSize), m_slot(slot), m_pDeviceContext(pDeviceContext)
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

	D3D11ConstantBuffer& D3D11ConstantBuffer::operator=(D3D11ConstantBuffer&& other) noexcept
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = nullptr;

		this->m_slot    = other.m_slot;
		this->m_objSize = other.m_objSize;
		this->m_constantBufferData = std::move(other.m_constantBufferData);
		
		return *this;
	}

	void D3D11ConstantBuffer::Bind()
	{
		(*this->m_pDeviceContext)->VSSetConstantBuffers((UINT)this->m_slot, 1u, &this->m_pObject);
	}

	void D3D11ConstantBuffer::Update()
	{
		D3D11_MAPPED_SUBRESOURCE resource;
		if (FAILED((*this->m_pDeviceContext)->Map(this->m_pObject, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &resource)))
			throw std::runtime_error("[DIRECTX 11] Failed To Map Constant Buffer Memory");

		std::memcpy(resource.pData, this->m_constantBufferData.data(), this->m_objSize);
		(*this->m_pDeviceContext)->Unmap(this->m_pObject, 0u);
	}

}; // D3D11
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS