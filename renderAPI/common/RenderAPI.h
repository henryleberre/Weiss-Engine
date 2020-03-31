#pragma once

#include "Shaders.h"
#include "Drawable.h"
#include "../../common/Include.h"
#include "../../window/Include.h"

class RenderAPI {
private:
	RenderAPIName m_apiName;

protected:
	std::vector<IndexBuffer*>  m_indexBuffers;
	std::vector<VertexBuffer*> m_vertexBuffers;

public:
	RenderAPI(const RenderAPIName& apiName) : m_apiName(apiName) {  }

	virtual ~RenderAPI()
	{
		for (VertexBuffer*   pVBuff   : this->m_vertexBuffers)   { delete pVBuff; }
		for (IndexBuffer*    pIBuff   : this->m_indexBuffers)    { delete pIBuff; }
	}

	// ----- Virtual Functions ----- //

    virtual void InitRenderAPI(Window* pWindow) = 0;

    virtual void Draw(const Drawable& drawable, const size_t nVertices) = 0;

    virtual void SwapBuffers() = 0;

	virtual size_t CreateRenderPipeline(const char* vsFilename, const std::vector<ShaderInputElement>& sies, const char* psFilename, const PrimitiveTopology& topology = PrimitiveTopology::TRIANGLES) = 0;

	virtual size_t CreateVertexBuffer(const size_t vertexSize, const size_t nVertices, const void* buff = nullptr) = 0;
	virtual size_t CreateIndexBuffer (const size_t nIndices, const void* buff = nullptr) = 0;

	// ----- Getter Functions ----- //

	[[nodiscard]] RenderAPIName GetRenderAPIName() const noexcept { return this->m_apiName; }
	[[nodiscard]] VertexBuffer* GetVertexBuffer(const size_t index) const noexcept { return this->m_vertexBuffers[index]; }
	[[nodiscard]] IndexBuffer*  GetIndexBuffer (const size_t index) const noexcept { return this->m_indexBuffers[index];  }

public:
    // Defined Per Render API
    static RenderAPI* Create(const RenderAPIName& renderAPIName);
};