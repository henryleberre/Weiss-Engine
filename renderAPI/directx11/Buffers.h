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
		size_t m_vertexSize;

		D3D11DeviceContextObjectWrapper* m_pDeviceContext = nullptr;

	public:
		D3D11VertexBuffer();

		D3D11VertexBuffer(D3D11VertexBuffer&& other);

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
		D3D11IndexBuffer();

		D3D11IndexBuffer(D3D11IndexBuffer&& other);

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

		size_t m_slotVS = 0u, m_slotPS = 0u;

		ShaderBindingType m_shaderBindingType;

		D3D11DeviceContextObjectWrapper* m_pDeviceContext = nullptr;

	public:
		D3D11ConstantBuffer();

		D3D11ConstantBuffer(D3D11ConstantBuffer&& other);

		D3D11ConstantBuffer(D3D11DeviceObjectWrapper& pDevice,
							D3D11DeviceContextObjectWrapper* pDeviceContext,
							const size_t objSize, const size_t slotVS, const size_t slotPS, const ShaderBindingType& shaderBindingType);

		void operator=(D3D11ConstantBuffer&& other) noexcept;

		void Bind();

		virtual void Update() override;
	};

}; // D3D11
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS