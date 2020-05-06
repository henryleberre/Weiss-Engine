#pragma once

#include "CommandPool.h"

namespace WS       {
namespace Internal {
namespace VK       {

	typedef VKObjectWrapper<VkCommandBuffer> VKCommandBufferObjectWrapper;

	class VKCommandBuffer : public VKCommandBufferObjectWrapper
	{
	private:
		const VKDevice* m_pDevice = nullptr;

	public:
		VKCommandBuffer() = default;

		VKCommandBuffer(const VKDevice& device, const VKCommandPool& commandPool);

		VKCommandBuffer& operator=(VKCommandBuffer&& other) noexcept;

		void BeginRecording() const;
		void EndRecording()   const;

		~VKCommandBuffer() = default;
	};

}; // VK
}; // Internal
}; // WS