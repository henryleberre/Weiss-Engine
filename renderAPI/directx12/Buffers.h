#pragma once

#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef DirectX12ObjectWrapper<ID3D12Resource> DirectX12VertexBufferObjectWrapper;

class DirectX12VertexBuffer : public DirectX12ObjectWrapper<ID3D12Resource> {
private:
	D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

	DirectX12ObjectWrapper<ID3D12Resource> m_pUploadHeap;

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
	void SetData(const void* buff, const size_t nVertices, DirectX12CommandList& pCommandList);
};

typedef DirectX12ObjectWrapper<ID3D12Resource> DirectX12IndexBufferObjectWrapper;

class DirectX12IndexBuffer : public DirectX12IndexBufferObjectWrapper {
private:
	D3D12_INDEX_BUFFER_VIEW m_indexBufferView;

	DirectX12ObjectWrapper<ID3D12Resource> m_pUploadHeap;

	size_t m_nIndices;

public:
	DirectX12IndexBuffer(DirectX12DeviceObjectWrapper& pDevice,
						 DirectX12CommandListObjectWrapper& pCommandList,
						 DirectX12CommandQueueObjectWrapper& pCommandQueue,
						 const size_t nIndices, const void* buff = nullptr);

	void operator=(DirectX12IndexBuffer&& other) noexcept;

	void CreateView();
	D3D12_INDEX_BUFFER_VIEW GetView();

	void Bind(DirectX12CommandListObjectWrapper& pCommandList);
	void SetData(const uint32_t* buff, const size_t nIndices, DirectX12CommandList& pCommandList);
};

#endif // __WEISS__OS_WINDOWS