#include "Texture.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	D3D12Texture::D3D12Texture(D3D12DeviceObjectWrapper& pDevice, D3D12CommandList* pCommandList, const Image& image, const size_t slot, const bool useMipmaps)
		: m_pCommandList(pCommandList), m_slot(slot)
	{
		D3D12_RESOURCE_DESC resourceDesc {};
		resourceDesc = {};
		resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		resourceDesc.Alignment = 0; 
		resourceDesc.Width = image.GetWidth();
		resourceDesc.Height = image.GetHeight();
		resourceDesc.DepthOrArraySize = 1;
		resourceDesc.MipLevels = useMipmaps ? 0 : 1;
		resourceDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UINT;
		resourceDesc.SampleDesc.Count   = 1;
		resourceDesc.SampleDesc.Quality = 0;
		resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		resourceDesc.Flags  = D3D12_RESOURCE_FLAG_NONE;

		this->m_textureResource = D3D12CommittedResource(pDevice, D3D12_HEAP_TYPE_DEFAULT, D3D12_HEAP_FLAG_NONE, &resourceDesc,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, "Texture Committed Resource");

		UINT64 textureUploadBufferSize;
		pDevice->GetCopyableFootprints(&resourceDesc, 0, 1, 0, nullptr, nullptr, nullptr, &textureUploadBufferSize);

		this->m_uploadHeap = D3D12CommittedResource(pDevice, D3D12_HEAP_TYPE_UPLOAD, D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(textureUploadBufferSize),
													D3D12_RESOURCE_STATE_GENERIC_READ, "Texture Upload Heap");

		this->m_descriptorHeap = D3D12DescriptorHeap(pDevice, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 1, D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE);

		this->m_textureResourceView.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		this->m_textureResourceView.Format = resourceDesc.Format;
		this->m_textureResourceView.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		this->m_textureResourceView.Texture2D.MipLevels = 1;
		
		pDevice->CreateShaderResourceView(this->m_textureResource, &this->m_textureResourceView, this->m_descriptorHeap->GetCPUDescriptorHandleForHeapStart());

		this->Update(image);
	}

	D3D12DescriptorHeap& D3D12Texture::GetDescriptorHeap()
	{
		return this->m_descriptorHeap;
	}

	void D3D12Texture::Bind()
	{
		(*this->m_pCommandList)->SetGraphicsRootDescriptorTable(1u, this->m_descriptorHeap->GetGPUDescriptorHandleForHeapStart());
	}

	size_t D3D12Texture::GetSlot() const noexcept
	{
		return this->m_slot;
	}

	void D3D12Texture::Update(const Image& image)
	{
		this->m_textureResource.TransitionTo(*this->m_pCommandList, D3D12_RESOURCE_STATE_COPY_DEST);

		D3D12_SUBRESOURCE_DATA textureData{};
		textureData.pData = image.GetBuffer();
		textureData.RowPitch = image.GetWidth() * sizeof(Coloru8);
		textureData.SlicePitch = image.GetPixelCount() * sizeof(Coloru8);
		
		UpdateSubresources(*this->m_pCommandList, this->m_textureResource, this->m_uploadHeap, 0, 0, 1, &textureData);

		this->m_textureResource.TransitionBack(*this->m_pCommandList);
	}

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS