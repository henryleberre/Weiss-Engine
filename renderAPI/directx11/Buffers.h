#pragma once

#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef DirectX11ObjectWrapper<ID3D11Buffer> DirectX11VertexBufferObjectWrapper;
typedef DirectX11ObjectWrapper<ID3D11Buffer> DirectX11IndexBufferObjectWrapper;
typedef DirectX11ObjectWrapper<ID3D11Buffer> DirectX11ConstantBufferObjectWrapper;

class DirectX11VertexBuffer : public DirectX11VertexBufferObjectWrapper,
							  public VertexBuffer {
private:
	size_t m_vertexSize;

	DirectX11DeviceContextObjectWrapper* m_pDeviceContext = nullptr;

public:
	DirectX11VertexBuffer();

	DirectX11VertexBuffer(DirectX11VertexBuffer&& other);

	DirectX11VertexBuffer(DirectX11DeviceObjectWrapper& pDevice,
						  DirectX11DeviceContextObjectWrapper* pDeviceContext,
						  const size_t nVertices, const size_t vertexSize);

	void operator=(DirectX11VertexBuffer&& other) noexcept;

	void Bind();
	
	virtual void Update() override;
};

class DirectX11IndexBuffer : public DirectX11IndexBufferObjectWrapper,
							 public IndexBuffer {
private:
	size_t m_nIndices = 0u;

	DirectX11DeviceContextObjectWrapper* m_pDeviceContext = nullptr;

public:
	DirectX11IndexBuffer();

	DirectX11IndexBuffer(DirectX11IndexBuffer&& other);

	DirectX11IndexBuffer(DirectX11DeviceObjectWrapper& pDevice,
						 DirectX11DeviceContextObjectWrapper* pDeviceContext, 
						 const size_t nIndices);

	void operator=(DirectX11IndexBuffer&& other) noexcept;

	void Bind();

	virtual void Update() override;
};

class DirectX11ConstantBuffer : public DirectX11ConstantBufferObjectWrapper,
								public ConstantBuffer {
private:
	size_t m_objSize = 0u;

	size_t m_slotVS = 0u, m_slotPS = 0u;

	ShaderBindingType m_shaderBindingType;

	DirectX11DeviceContextObjectWrapper* m_pDeviceContext = nullptr;

public:
	DirectX11ConstantBuffer();

	DirectX11ConstantBuffer(DirectX11ConstantBuffer&& other);

	DirectX11ConstantBuffer(DirectX11DeviceObjectWrapper& pDevice,
							DirectX11DeviceContextObjectWrapper* pDeviceContext,
							const size_t objSize, const size_t slotVS, const size_t slotPS, const ShaderBindingType& shaderBindingType);

	void operator=(DirectX11ConstantBuffer&& other) noexcept;

	void Bind();

	virtual void Update() override;
};

#endif // __WEISS__OS_WINDOWS