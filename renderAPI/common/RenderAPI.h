#pragma once

#include "Shaders.h"
#include "Buffers.h"
#include "Drawable.h"
#include "../../common/Include.h"
#include "../../window/Include.h"

struct RenderPipelineDesc {
	const char* vsFilename;
	std::vector<ShaderInputElement> sies;
	const char* psFilename;
	PrimitiveTopology topology = PrimitiveTopology::TRIANGLES;
};

struct RenderAPIHandle;

template <typename VB, typename IB, typename CB>
class RenderAPI {
private:
	RenderAPIName m_apiName;

protected:
	std::vector<VB> m_pVertexBuffers;
	std::vector<IB> m_pIndexBuffers;
	std::vector<CB> m_pConstantBuffers;

public:
	RenderAPI(const RenderAPIName& apiName) : m_apiName(apiName) {}

	virtual ~RenderAPI() {  }

	// ----- Virtual Functions ----- //

    virtual void InitRenderAPI(Window* pWindow, const std::vector<RenderPipelineDesc>& pipelineDescs) = 0;

    virtual void Draw(const Drawable& drawable, const size_t nVertices) = 0;

	/*
	 * This structure is used to take advantage of recent rendering apis such as directx12 and vulkan.
	 * By submitting draw commands to the GPU asynchronously while other functions can be called on the cpu side
	 * (such as game logic and physics). The present method is then called to swap buffers.
	 */
	virtual void BeginDrawing() = 0;
    virtual void EndDrawing()   = 0;
	virtual void Present(const bool vSync) = 0;

	virtual size_t CreateVertexBuffer(const size_t nVertices, const size_t vertexSize) = 0;
	virtual size_t CreateIndexBuffer (const size_t nIndices) = 0;
	virtual size_t CreateConstantBuffer(const size_t objSize, const size_t slotVS, const size_t slotPS, const ShaderBindingType& shaderBindingType) = 0;

	virtual void Fill(const Colorf32& color = { 1.f, 1.f, 1.f, 1.f }) = 0;

	// ----- Non-Virtual Functions ----- //

	inline VertexBuffer& GetVertexBuffer(const size_t vertexBufferIndex) noexcept
	{
		return dynamic_cast<VertexBuffer&>(this->m_pVertexBuffers[vertexBufferIndex]);
	}

	inline IndexBuffer& GetIndexBuffer(const size_t indexBufferIndex) noexcept
	{
		return dynamic_cast<IndexBuffer&>(this->m_pIndexBuffers[indexBufferIndex]);
	}

	inline ConstantBuffer& GetConstantBuffer(const size_t constantBufferIndex) noexcept
	{
		return dynamic_cast<ConstantBuffer&>(this->m_pConstantBuffers[constantBufferIndex]);
	}

	// ----- Non-Virtual Virtual Overloads ----- //

	inline size_t CreateVertexBuffer(const void* buff, const size_t nVertices, const size_t vertexSize)
	{
		const size_t i = this->CreateVertexBuffer(nVertices, vertexSize);

		this->GetVertexBuffer(i).Set(buff, nVertices * vertexSize);
		this->GetVertexBuffer(i).Update();

		return i;
	}

	template <typename CONTAINER>
	inline size_t CreateVertexBuffer(const CONTAINER& container)
	{
		return this->CreateVertexBuffer(container.data(), container.size() * sizeof(container[0]), sizeof(container[0]));
	}

	inline size_t CreateIndexBuffer(const void* buff, const size_t nIndices)
	{
		const size_t i = this->CreateIndexBuffer(nIndices);

		this->GetIndexBuffer(i).Set(buff, nIndices);
		this->GetIndexBuffer(i).Update();

		return i;
	}

	template <typename CONTAINER>
	inline size_t CreateIndexBuffer(const CONTAINER& container)
	{
		return this->CreateIndexBuffer(container.data(), container.size());
	}

	template <typename T>
	inline size_t CreateConstantBuffer(const T& obj, const size_t slotVS, const size_t slotPS, const ShaderBindingType& shaderBindingType)
	{
		const size_t constantBufferIndex = this->CreateConstantBuffer(sizeof(T), slotVS, slotPS, shaderBindingType);
		this->GetConstantBuffer(constantBufferIndex).Set(obj);
		this->GetConstantBuffer(constantBufferIndex).Update();

		return constantBufferIndex;
	}

	// ----- Getter Functions ----- //

	[[nodiscard]] RenderAPIName GetRenderAPIName() const noexcept { return this->m_apiName; }
};