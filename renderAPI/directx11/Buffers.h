#pragma once

#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef DirectX11ObjectWrapper<ID3D11Buffer> DirectX11VertexBufferObjectWrapper;
typedef DirectX11ObjectWrapper<ID3D11Buffer> DirectX11IndexBufferObjectWrapper;
typedef DirectX11ObjectWrapper<ID3D11Buffer> DirectX11ConstantBufferObjectWrapper;

class DirectX11VertexBuffer : public DirectX11VertexBufferObjectWrapper {
private:
	size_t m_vertexSize = 0u, m_nVertices = 0u;

public:
	DirectX11VertexBuffer(DirectX11DeviceObjectWrapper& pDevice, const size_t vertexSize, const size_t nVertices, const void* buff = nullptr);

	void operator=(DirectX11VertexBuffer&& other) noexcept;

	void Bind(DirectX11DeviceContextObjectWrapper& pDeviceContext);
	
	void SetData(const void* buff, const size_t nVertices, DirectX11DeviceContextObjectWrapper& pDeviceContext);
};

class DirectX11IndexBuffer : public DirectX11IndexBufferObjectWrapper {
private:
	size_t m_nIndices = 0u;

public:
	DirectX11IndexBuffer(DirectX11DeviceObjectWrapper& pDevice, const size_t nIndices, const void* buff = nullptr);

	void operator=(DirectX11IndexBuffer&& other) noexcept;

	void Bind(DirectX11DeviceContextObjectWrapper& pDeviceContext);

	void SetData(const uint32_t* buff, const size_t nIndices, DirectX11DeviceContextObjectWrapper& pDeviceContext);
};

class DirectX11ConstantBuffer : public DirectX11ConstantBufferObjectWrapper {
private:
	size_t m_objSize = 0u;

	size_t m_slotVS = 0u, m_slotPS = 0u;

	ShaderBindingType m_shaderBindingType;

public:
	DirectX11ConstantBuffer(DirectX11DeviceObjectWrapper& pDevice, const size_t objSize, const size_t slotVS, const size_t slotPS, const ShaderBindingType& shaderBindingType, const void* data = nullptr);

	void operator=(DirectX11ConstantBuffer&& other) noexcept;

	void Bind(DirectX11DeviceContextObjectWrapper& pDeviceContext);

	void SetData(const void* data, DirectX11DeviceContextObjectWrapper& pDeviceContext);
};

#endif // __WEISS__OS_WINDOWS