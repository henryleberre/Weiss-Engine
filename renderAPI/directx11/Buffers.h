#pragma once

#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef DirectX11ObjectWrapper<ID3D11Buffer> DirectX11VertexBufferObjectWrapper;
typedef DirectX11ObjectWrapper<ID3D11Buffer> DirectX11IndexBufferObjectWrapper;
typedef DirectX11ObjectWrapper<ID3D11Buffer> DirectX11ConstantBufferObjectWrapper;

class DirectX11VertexBuffer : public DirectX11VertexBufferObjectWrapper,
							  public VertexBufferData {
private:
	size_t m_vertexSize;

public:
	DirectX11VertexBuffer(DirectX11DeviceObjectWrapper& pDevice, const size_t nVertices, const size_t vertexSize);

	void operator=(DirectX11VertexBuffer&& other) noexcept;

	void Bind(DirectX11DeviceContextObjectWrapper& pDeviceContext);
	
	void Update(DirectX11DeviceContextObjectWrapper& pDeviceContext);
};

class DirectX11IndexBuffer : public DirectX11IndexBufferObjectWrapper,
							 public IndexBufferData {
private:
	size_t m_nIndices = 0u;

public:
	DirectX11IndexBuffer(DirectX11DeviceObjectWrapper& pDevice, const size_t nIndices);

	void operator=(DirectX11IndexBuffer&& other) noexcept;

	void Bind(DirectX11DeviceContextObjectWrapper& pDeviceContext);

	void Update(DirectX11DeviceContextObjectWrapper& pDeviceContext);
};

class DirectX11ConstantBuffer : public DirectX11ConstantBufferObjectWrapper,
								public ConstantBufferData {
private:
	size_t m_objSize = 0u;

	size_t m_slotVS = 0u, m_slotPS = 0u;

	ShaderBindingType m_shaderBindingType;

public:
	DirectX11ConstantBuffer(DirectX11DeviceObjectWrapper& pDevice, const size_t objSize, const size_t slotVS, const size_t slotPS, const ShaderBindingType& shaderBindingType);

	void operator=(DirectX11ConstantBuffer&& other) noexcept;

	void Bind(DirectX11DeviceContextObjectWrapper& pDeviceContext);

	void Update(DirectX11DeviceContextObjectWrapper& pDeviceContext);
};

#endif // __WEISS__OS_WINDOWS