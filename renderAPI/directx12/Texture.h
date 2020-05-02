#pragma once

#include "internal/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	class D3D12Texture : public Texture {
	private:
		D3D12CommittedResource m_textureResource;
		D3D12CommittedResource m_uploadHeap;

		D3D12DescriptorHeap m_descriptorHeap;

		D3D12_SHADER_RESOURCE_VIEW_DESC m_textureResourceView;

		D3D12CommandList* m_pCommandList = nullptr;

		size_t m_slot = 0u;

	public:
		D3D12Texture() = default;
		D3D12Texture(D3D12DeviceObjectWrapper& pDevice, D3D12CommandList* pCommandList, const size_t width, const size_t height, const size_t slot, const bool useMipmaps);

		D3D12DescriptorHeap& GetDescriptorHeap();

		size_t GetSlot() const noexcept;

		virtual void Update(const Image& image) override;
	};

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS