#pragma once

#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX12VertexBuffer : public VertexBuffer {
private:
	Microsoft::WRL::ComPtr<ID3D12Resource> m_pVertexBuffer;

	D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

	UINT m_vertexSize, m_bufferSize;

public:
	DirectX12VertexBuffer(const std::shared_ptr<DirectX12Device>& pDevice,
						  const std::shared_ptr<DirectX12CommandList>& pCommandList,
						  const std::shared_ptr<DirectX12CommandQueue>& pCommandQueue,
						  const size_t vertexSize, const size_t nVertices, const void* buff = nullptr);

	void CreateView();

	D3D12_VERTEX_BUFFER_VIEW GetView() { return this->m_vertexBufferView; }

	void Bind(const std::shared_ptr<DirectX12CommandList>& pCommandList);
	virtual size_t GetCount() override;
	virtual void   SetData(const void* buff, const size_t nVertices) override;
};

class DirectX12IndexBuffer : public IndexBuffer {
public:
	DirectX12IndexBuffer() {}

	virtual size_t GetCount() override { return 0u; }
	virtual void   SetData(const uint32_t* buff, const size_t nIndices) override {}
};

#endif // __WEISS__OS_WINDOWS