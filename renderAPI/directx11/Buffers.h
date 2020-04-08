#pragma once

#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef DirectX11ObjectWrapper<ID3D11Buffer> DirectX11VertexBufferObjectWrapper;
typedef DirectX11ObjectWrapper<ID3D11Buffer> DirectX11IndexBufferObjectWrapper;

class DirectX11VertexBuffer : public DirectX11VertexBufferObjectWrapper {
private:
	size_t m_vertexSize = 0u, m_nVertices = 0u;

public:
	DirectX11VertexBuffer(DirectX11DeviceObjectWrapper& pDevice, const size_t vertexSize, const size_t nVertices, const void* buff = nullptr);

	void operator=(DirectX11VertexBuffer&& other) noexcept;

	void Bind(DirectX11DeviceContextObjectWrapper& pDeviceContext);
	size_t GetCount();
	
	void SetData(const void* buff, const size_t nVertices, DirectX11DeviceContextObjectWrapper& pDeviceContext);
};

class DirectX11IndexBuffer : public DirectX11IndexBufferObjectWrapper {
private:
	size_t m_nIndices = 0u;

public:
	DirectX11IndexBuffer(DirectX11DeviceObjectWrapper& pDevice, const size_t nIndices, const void* buff = nullptr);

	void operator=(DirectX11IndexBuffer&& other) noexcept;

	void Bind(DirectX11DeviceContextObjectWrapper& pDeviceContext);
	size_t GetCount();
	void   SetData(const uint32_t* buff, const size_t nIndices, DirectX11DeviceContextObjectWrapper& pDeviceContext);
};

#endif // __WEISS__OS_WINDOWS