#pragma once

#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"
#include "internal/CommittedResource.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	class D3D12VertexBuffer : public D3D12CommittedResource,
							  public VertexBuffer {
	private:
		D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

		D3D12CommittedResource m_pUploadHeap;

		UINT m_vertexSize = 0u;

		D3D12CommandList* m_pCommandList = nullptr;

	public:
		D3D12VertexBuffer() = default;

		D3D12VertexBuffer(D3D12VertexBuffer&& other) noexcept;

		D3D12VertexBuffer(D3D12DeviceObjectWrapper& pDevice,
						  D3D12CommandList* pCommandList,
						  const size_t nVertices, const size_t vertexSize);

		void operator=(D3D12VertexBuffer&& other) noexcept;

		void Bind();

		virtual void Update() override;
	};

	class D3D12IndexBuffer : public D3D12CommittedResource,
							 public IndexBuffer {
	private:
		D3D12_INDEX_BUFFER_VIEW m_indexBufferView;

		D3D12CommittedResource m_pUploadHeap;

		size_t m_nIndices = 0u;

		D3D12CommandList* m_pCommandList = nullptr;

	public:
		D3D12IndexBuffer() = default;

		D3D12IndexBuffer(D3D12IndexBuffer&& other) noexcept;

		D3D12IndexBuffer(D3D12DeviceObjectWrapper& pDevice,
						 D3D12CommandList* pCommandList,
						 const size_t nIndices);

		void operator=(D3D12IndexBuffer&& other) noexcept;

		void Bind();

		virtual void Update() override;
	};

	class D3D12ConstantBuffer : public ConstantBuffer {
	private:
		size_t m_objSize = 0u;

		size_t m_slot = 0u;
		
		D3D12CommandList* m_pCommandList;

		std::array<D3D12DescriptorHeap,             WEISS__FRAME_BUFFER_COUNT> m_descriptorHeaps;
		std::array<D3D12_CONSTANT_BUFFER_VIEW_DESC, WEISS__FRAME_BUFFER_COUNT> m_constantBufferViews;
		std::array<D3D12CommittedResource,          WEISS__FRAME_BUFFER_COUNT> m_pUploadHeaps;

	public:
		D3D12ConstantBuffer() = default;

		D3D12ConstantBuffer(D3D12ConstantBuffer&& other) noexcept;

		D3D12ConstantBuffer(D3D12DeviceObjectWrapper& pDevice,
							D3D12CommandList* pCommandList,
							const size_t objSize, const size_t slot);

		void operator=(D3D12ConstantBuffer&& other) noexcept;

		void Bind(const size_t frameIndex);

		size_t GetSlot() const noexcept;

		virtual void Update() override;
	};

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS