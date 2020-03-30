#pragma once

#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX11VertexBuffer : public VertexBuffer {
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pVertexBuffer;

	size_t m_vertexSize = 0u, m_nVertices = 0u;

	std::shared_ptr<DirectX11Device> m_pDevice;

public:
	DirectX11VertexBuffer(const std::shared_ptr<DirectX11Device>& pDevice, const size_t vertexSize, const size_t nVertices, const void* buff = nullptr);

	virtual void   Bind()     override;
	virtual size_t GetCount() override;
	virtual void   SetData(const void* buff, const size_t nVertices) override;
};

class DirectX11IndexBuffer : public IndexBuffer {
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pIndexBuffer;

	size_t m_nIndices = 0u;

	std::shared_ptr<DirectX11Device> m_pDevice;

public:
	DirectX11IndexBuffer(const std::shared_ptr<DirectX11Device>& pDevice, const size_t nIndices, const void* buff = nullptr);

	virtual void   Bind()     override;
	virtual size_t GetCount() override;
	virtual void   SetData(const uint32_t* buff, const size_t nIndices) override;
};

#endif // __WEISS__OS_WINDOWS