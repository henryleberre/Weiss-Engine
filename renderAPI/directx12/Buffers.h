#pragma once

#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

typedef DirectX12ObjectWrapper<ID3D12Resource> DirectX12VertexBufferObjectWrapper;
typedef DirectX12ObjectWrapper<ID3D12Resource> DirectX12IndexBufferObjectWrapper;

class DirectX12VertexBuffer : public DirectX12ObjectWrapper<ID3D12Resource>,
							  public VertexBuffer {
private:
	D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

	DirectX12ObjectWrapper<ID3D12Resource> m_pUploadHeap;

	UINT m_vertexSize;

	DirectX12CommandList* m_pCommandList = nullptr;

public:
	DirectX12VertexBuffer();

	DirectX12VertexBuffer(DirectX12VertexBuffer&& other);

	DirectX12VertexBuffer(DirectX12DeviceObjectWrapper& pDevice,
						  DirectX12CommandList* pCommandList,
						  const size_t nVertices, const size_t vertexSize);

	void operator=(DirectX12VertexBuffer&& other) noexcept;

	D3D12_VERTEX_BUFFER_VIEW GetView();

	void Bind();

	virtual void Update() override;
};


class DirectX12IndexBuffer : public DirectX12IndexBufferObjectWrapper,
							 public IndexBuffer {
private:
	D3D12_INDEX_BUFFER_VIEW m_indexBufferView;

	DirectX12ObjectWrapper<ID3D12Resource> m_pUploadHeap;

	size_t m_nIndices;

	DirectX12CommandList* m_pCommandList;

public:
	DirectX12IndexBuffer();

	DirectX12IndexBuffer(DirectX12IndexBuffer&& other);

	DirectX12IndexBuffer(DirectX12DeviceObjectWrapper& pDevice,
						 DirectX12CommandList* pCommandList,
						 const size_t nIndices);

	void operator=(DirectX12IndexBuffer&& other) noexcept;

	D3D12_INDEX_BUFFER_VIEW GetView();

	void Bind();

	virtual void Update() override;
};

class DirectX12ConstantBuffer : public ConstantBuffer {
private:
	DirectX12ObjectWrapper<ID3D12Resource> m_pUploadHeap;

	size_t m_objSize = 0u;

	size_t m_slotVS = 0u, m_slotPS = 0u;

	ShaderBindingType m_shaderBindingType;

	D3D12_CONSTANT_BUFFER_VIEW_DESC m_constantBufferView;

	DirectX12CommandList* m_pCommandList;

public:
	DirectX12ConstantBuffer();

	DirectX12ConstantBuffer(DirectX12ConstantBuffer&& other);

	DirectX12ConstantBuffer(DirectX12DeviceObjectWrapper& pDevice,
							DirectX12CommandList* pCommandList,
							const size_t objSize, const size_t slotVS, const size_t slotPS,
							const ShaderBindingType& shaderBindingType);

	void CreateView();
	D3D12_CONSTANT_BUFFER_VIEW_DESC GetView();

	void Bind();

	virtual void Update() override;
};

#endif // __WEISS__OS_WINDOWS