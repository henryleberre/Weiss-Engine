#pragma once

#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX11VertexBuffer {
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pVertexBuffer;

	size_t m_vertexSize = 0u, m_nVertices = 0u;

public:
	DirectX11VertexBuffer(DirectX11DeviceObjectWrapper& pDevice, const size_t vertexSize, const size_t nVertices, const void* buff = nullptr);

	void Bind(DirectX11DeviceContextObjectWrapper& pDeviceContext);
	size_t GetCount();
	
	void SetData(const void* buff, const size_t nVertices, DirectX11DeviceContextObjectWrapper& pDeviceContext);
};

class DirectX11IndexBuffer {
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pIndexBuffer;

	size_t m_nIndices = 0u;

public:
	DirectX11IndexBuffer(DirectX11DeviceObjectWrapper& pDevice, const size_t nIndices, const void* buff = nullptr);

	void Bind(DirectX11DeviceContextObjectWrapper& pDeviceContext);
	size_t GetCount();
	void   SetData(const uint32_t* buff, const size_t nIndices, DirectX11DeviceContextObjectWrapper& pDeviceContext);
};

#endif // __WEISS__OS_WINDOWS