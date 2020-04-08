#pragma once

#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef DirectX12ObjectWrapper<ID3D12Resource> DirectX12VertexBufferObjectWrapper;

class DirectX12VertexBuffer : public VertexBuffer,
							  public DirectX12ObjectWrapper<ID3D12Resource> {
private:
	D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

	UINT m_vertexSize, m_bufferSize, m_nVertices;

public:
	DirectX12VertexBuffer(DirectX12DeviceObjectWrapper& pDevice,
						  DirectX12CommandListObjectWrapper& pCommandList,
						  DirectX12CommandQueueObjectWrapper& pCommandQueue,
						  const size_t vertexSize, const size_t nVertices, const void* buff = nullptr);

	void operator=(DirectX12VertexBuffer&& other) noexcept;

	void CreateView();

	D3D12_VERTEX_BUFFER_VIEW GetView();

	void Bind(DirectX12CommandListObjectWrapper& pCommandList);
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