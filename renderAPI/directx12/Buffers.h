#pragma once

#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	typedef D3D12ObjectWrapper<ID3D12Resource> D3D12VertexBufferObjectWrapper;
	typedef D3D12ObjectWrapper<ID3D12Resource> D3D12IndexBufferObjectWrapper;

	class D3D12VertexBuffer : public D3D12ObjectWrapper<ID3D12Resource>,
							  public VertexBuffer {
	private:
		D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

		D3D12ObjectWrapper<ID3D12Resource> m_pUploadHeap;

		UINT m_vertexSize;

		D3D12CommandList* m_pCommandList = nullptr;

	public:
		D3D12VertexBuffer();

		D3D12VertexBuffer(D3D12VertexBuffer&& other);

		D3D12VertexBuffer(D3D12DeviceObjectWrapper& pDevice,
						  D3D12CommandList* pCommandList,
						  const size_t nVertices, const size_t vertexSize);

		void operator=(D3D12VertexBuffer&& other) noexcept;

		D3D12_VERTEX_BUFFER_VIEW GetView();

		void Bind();

		virtual void Update() override;
	};

	class D3D12IndexBuffer : public D3D12IndexBufferObjectWrapper,
							 public IndexBuffer {
	private:
		D3D12_INDEX_BUFFER_VIEW m_indexBufferView;

		D3D12ObjectWrapper<ID3D12Resource> m_pUploadHeap;

		size_t m_nIndices;

		D3D12CommandList* m_pCommandList;

	public:
		D3D12IndexBuffer();

		D3D12IndexBuffer(D3D12IndexBuffer&& other);

		D3D12IndexBuffer(D3D12DeviceObjectWrapper& pDevice,
						 D3D12CommandList* pCommandList,
						 const size_t nIndices);

		void operator=(D3D12IndexBuffer&& other) noexcept;

		D3D12_INDEX_BUFFER_VIEW GetView();

		void Bind();

		virtual void Update() override;
	};

	class D3D12ConstantBuffer : public ConstantBuffer {
	private:
		size_t m_objSize = 0u;

		size_t m_slotVS = 0u, m_slotPS = 0u;

		ShaderBindingType m_shaderBindingType;

		D3D12CommandList* m_pCommandList;

		std::array<D3D12DescriptorHeap,                WEISS__FRAME_BUFFER_COUNT> m_descriptorHeaps;
		std::array<D3D12_CONSTANT_BUFFER_VIEW_DESC,    WEISS__FRAME_BUFFER_COUNT> m_constantBufferViews;
		std::array<D3D12ObjectWrapper<ID3D12Resource>, WEISS__FRAME_BUFFER_COUNT> m_pUploadHeaps;

	public:
		D3D12ConstantBuffer();

		D3D12ConstantBuffer(D3D12ConstantBuffer&& other);

		D3D12ConstantBuffer(D3D12DeviceObjectWrapper& pDevice,
							D3D12CommandList* pCommandList,
							const size_t objSize, const size_t slotVS, const size_t slotPS,
							const ShaderBindingType& shaderBindingType);

		D3D12_CONSTANT_BUFFER_VIEW_DESC GetView(const size_t index);

		void Bind(const size_t frameIndex);

		ShaderBindingType GetShaderBindingType() const noexcept;

		size_t GetSlotVS() const noexcept;
		size_t GetSlotPS() const noexcept;

		virtual void Update() override;
	};

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS