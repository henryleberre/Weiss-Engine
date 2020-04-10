#pragma once

#include "Shaders.h"
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

class RenderAPI {
private:
	RenderAPIName m_apiName;

public:
	RenderAPI(const RenderAPIName& apiName) : m_apiName(apiName) {  }

	virtual ~RenderAPI()
	{
		
	}

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

	virtual size_t CreateVertexBuffer(const size_t vertexSize, const size_t nVertices, const void* buff = nullptr) = 0;
	virtual size_t CreateIndexBuffer (const size_t nIndices, const void* buff = nullptr) = 0;
	virtual size_t CreateConstantBuffer(const size_t objSize, const size_t slotVS, const size_t slotPS, const ShaderBindingType& shaderBindingType, const void* buff = nullptr) = 0;

	virtual void SetVertexBufferData(const size_t index, const size_t nVertices, const void*     buff) = 0;
	virtual void SetIndexBufferData (const size_t index, const size_t nIndices,  const uint32_t* buff) = 0;
	virtual void SetConstantBufferData(const size_t index, const void* data) = 0;

	virtual void Fill(const Colorf32& color = { 1.f, 1.f, 1.f, 1.f }) = 0;

	// ----- Functions That Use The Virtual Functions ----- //

	template <typename T>
	inline size_t CreateConstantBuffer(const T& data, const size_t slotVS, const size_t slotPS, const ShaderBindingType& shaderBindingType)
	{
		return this->CreateConstantBuffer(sizeof(T), slotVS, slotPS, shaderBindingType, &data);
	}

	template <typename CONTAINER>
	inline size_t CreateVertexBuffer(const CONTAINER& vertices)
	{
		return this->CreateVertexBuffer(sizeof(vertices[0]), vertices.size(), vertices.data());
	}

	template <typename CONTAINER>
	inline size_t CreateIndexBuffer(const CONTAINER& indices)
	{
		return this->CreateIndexBuffer(indices.size(), indices.data());
	}

	template <typename CONTAINER>
	inline void SetVertexBufferData(const size_t index, const CONTAINER& vertices)
	{
		this->SetVertexBufferData(index, vertices.size(), vertices.data());
	}

	template <typename CONTAINER>
	inline void SetIndexBufferData(const size_t index, const CONTAINER& indices)
	{
		this->SetIndexBufferData(index, indices.size(), indices.data());
	}

	// ----- Getter Functions ----- //

	[[nodiscard]] RenderAPIName GetRenderAPIName() const noexcept { return this->m_apiName; }

public:
    // Defined Per Render API
    static RenderAPIHandle Create(const RenderAPIName& renderAPIName);
};

struct RenderAPIHandle {
	RenderAPI* pRenderAPI;

	~RenderAPIHandle()
	{
		delete this->pRenderAPI;
	}

	RenderAPI* operator->() noexcept { return this->pRenderAPI; }

	operator RenderAPI* () noexcept {
		return this->pRenderAPI;
	}
};