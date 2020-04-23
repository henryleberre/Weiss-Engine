#pragma once

#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D11    {

	typedef D3D11ObjectWrapper<ID3D11Buffer> D3D11VertexBufferObjectWrapper;
	typedef D3D11ObjectWrapper<ID3D11Buffer> D3D11IndexBufferObjectWrapper;
	typedef D3D11ObjectWrapper<ID3D11Buffer> D3D11ConstantBufferObjectWrapper;

	class D3D11VertexBuffer : public D3D11VertexBufferObjectWrapper,
							  public VertexBuffer {
	private:
		size_t m_vertexSize = 0u;

		D3D11DeviceContextObjectWrapper* m_pDeviceContext = nullptr;

	public:
		D3D11VertexBuffer() = default;

		D3D11VertexBuffer(D3D11VertexBuffer&& other) noexcept;

		D3D11VertexBuffer(D3D11DeviceObjectWrapper& pDevice,
						  D3D11DeviceContextObjectWrapper* pDeviceContext,
						  const size_t nVertices, const size_t vertexSize);

		void operator=(D3D11VertexBuffer&& other) noexcept;

		void Bind();

		virtual void Update() override;
	};

	class D3D11IndexBuffer : public D3D11IndexBufferObjectWrapper,
							 public IndexBuffer {
	private:
		size_t m_nIndices = 0u;

		D3D11DeviceContextObjectWrapper* m_pDeviceContext = nullptr;

	public:
		D3D11IndexBuffer() = default;

		D3D11IndexBuffer(D3D11IndexBuffer&& other) noexcept;

		D3D11IndexBuffer(D3D11DeviceObjectWrapper& pDevice,
						 D3D11DeviceContextObjectWrapper* pDeviceContext,
						 const size_t nIndices);

		void operator=(D3D11IndexBuffer&& other) noexcept;

		void Bind();

		virtual void Update() override;
	};

	class D3D11ConstantBuffer : public D3D11ConstantBufferObjectWrapper,
								public ConstantBuffer {
	private:
		size_t m_objSize = 0u;

		size_t m_slot = 0u;

		D3D11DeviceContextObjectWrapper* m_pDeviceContext = nullptr;

	public:
		D3D11ConstantBuffer() = default;

		D3D11ConstantBuffer(D3D11ConstantBuffer&& other) noexcept;

		D3D11ConstantBuffer(D3D11DeviceObjectWrapper& pDevice,
							D3D11DeviceContextObjectWrapper* pDeviceContext,
							const size_t objSize, const size_t slot);

		void operator=(D3D11ConstantBuffer&& other) noexcept;

		void Bind();

		virtual void Update() override;
	};

}; // D3D11
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS