#pragma once

#include "Shaders.h"
#include "Buffers.h"
#include "Texture.h"
#include "Drawable.h"
#include "../../image/Include.h"
#include "../../common/Include.h"
#include "../../window/Include.h"

namespace WS {

	struct RenderPipelineDesc {
		const char* vsFilename;
		std::vector<ShaderInputElement> sies;
		const char* psFilename;
		std::vector<uint32_t> constantBufferIndices;
		std::vector<uint32_t> textureIndices;
		std::vector<uint32_t> textureSamplerIndices;
		PrimitiveTopology topology = PrimitiveTopology::TRIANGLES;
	};

	class RenderAPIHandle;

	class RenderAPI {
	private:
		RenderAPIName m_apiName;

	protected:
		std::vector<VertexBuffer*>   m_pVertexBuffers;
		std::vector<IndexBuffer*>    m_pIndexBuffers;
		std::vector<ConstantBuffer*> m_pConstantBuffers;
		std::vector<Texture*>        m_pTextures;

	public:
		RenderAPI(const RenderAPIName& apiName) : m_apiName(apiName) {}

		virtual ~RenderAPI()
		{

		}

		// ----- Virtual Functions ----- //

		virtual void InitRenderAPI(Window* pWindow, const uint16_t maxFps = 144u) = 0;
		virtual void InitPipelines(const std::vector<RenderPipelineDesc>& pipelineDescs) = 0;

		virtual void Draw(const Drawable& drawable, const size_t nVertices) = 0;

		/*
		 * This structure is used to take advantage of recent rendering apis such as directx12 and vulkan.
		 * By submitting draw commands to the GPU asynchronously while other functions can be called on the cpu side
		 * (such as game logic and physics). The present method is then called to swap buffers.
		 * This is why dealing with gpu memory after calling "EndFrame()" is undefined behavior.
		 */
		virtual void BeginDrawing() = 0;
		virtual void EndDrawing()   = 0;
		virtual void Present(const bool vSync) = 0;

		virtual size_t CreateVertexBuffer  (const size_t nVertices, const size_t vertexSize) = 0;
		virtual size_t CreateIndexBuffer   (const size_t nIndices) = 0;
		virtual size_t CreateConstantBuffer(const size_t objSize, const size_t slot) = 0;
		virtual size_t CreateTexture       (const size_t width, const size_t height, const size_t slot, const bool useMipmaps = false) = 0;
		virtual size_t CreateTextureSampler(const TextureFilter& filter, const size_t slot) = 0;

		virtual void Fill(const Colorf32& color = { 1.f, 1.f, 1.f, 1.f }) = 0;

		// ----- Non-Virtual Functions ----- //

		inline VertexBuffer& GetVertexBuffer(const size_t vertexBufferIndex) noexcept
		{
			return *this->m_pVertexBuffers[vertexBufferIndex];
		}

		inline IndexBuffer& GetIndexBuffer(const size_t indexBufferIndex) noexcept
		{
			return *this->m_pIndexBuffers[indexBufferIndex];
		}

		inline ConstantBuffer& GetConstantBuffer(const size_t constantBufferIndex) noexcept
		{
			return *this->m_pConstantBuffers[constantBufferIndex];
		}

		inline Texture& GetTexture(const size_t textureIndex) noexcept
		{
			return *this->m_pTextures[textureIndex];
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

		inline size_t CreateTexture(Image& image, const size_t slot, const bool useMipmaps = false)
		{
			const size_t textureIndex = this->CreateTexture(image.GetWidth(), image.GetHeight(), false);
			this->GetTexture(textureIndex).Update(image);

			return textureIndex;
		}

		// ----- Getter Functions ----- //

		[[nodiscard]] RenderAPIName GetRenderAPIName() const noexcept { return this->m_apiName; }

		// ----- Creation ----- //
		static RenderAPIHandle Create(const RenderAPIName& apiName);
	};

	class RenderAPIHandle {
	private:
		RenderAPI* m_pRenderAPI = nullptr;

	public:
		RenderAPIHandle() {  }
		RenderAPIHandle(RenderAPI* pRenderAPI) : m_pRenderAPI(pRenderAPI) {  }

		~RenderAPIHandle() { delete this->m_pRenderAPI; }

		operator RenderAPI*  () noexcept { return this->m_pRenderAPI; }
		RenderAPI* operator->() noexcept { return this->m_pRenderAPI; }
	};

};