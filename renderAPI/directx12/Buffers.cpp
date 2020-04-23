#include "Buffers.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	D3D12VertexBuffer::D3D12VertexBuffer(D3D12VertexBuffer&& other) noexcept
		: m_vertexSize(other.m_vertexSize), m_pCommandList(other.m_pCommandList)
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = nullptr;

		this->m_pUploadHeap = std::move(other.m_pUploadHeap);
		this->m_vertexData  = other.m_vertexData;
		this->m_vertexBufferView = other.m_vertexBufferView;
	}

	D3D12VertexBuffer::D3D12VertexBuffer(D3D12DeviceObjectWrapper& pDevice,
										 D3D12CommandList* pCommandList,
										 const size_t nVertices, const size_t vertexSize)
		: m_vertexSize((UINT)vertexSize), m_pCommandList(pCommandList)
	{
		const UINT bufferSize = static_cast<UINT>(vertexSize * nVertices);

		if (FAILED(pDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(bufferSize), D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER,
			nullptr, IID_PPV_ARGS(&this->m_pObject))))
			throw std::runtime_error("[DIRECTX 12] Failed To Create Vertex Buffer Resource");

		this->m_pObject->SetName(L"Vertex Buffer Resource Heap");

		if (FAILED(pDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(bufferSize), D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr, IID_PPV_ARGS(this->m_pUploadHeap.GetPtr()))))
			throw std::runtime_error("[DIRECTX 12] Failed To Create Vertex Buffer Upload Heap");

		m_pUploadHeap->SetName(L"Vertex Buffer Upload Resource Heap");

		this->m_vertexData.resize(bufferSize);
		std::memset(this->m_vertexData.data(), 0u, bufferSize);

		this->m_vertexBufferView.StrideInBytes  = this->m_vertexSize;
		this->m_vertexBufferView.SizeInBytes    = static_cast<UINT>(this->m_vertexData.size());
		this->m_vertexBufferView.BufferLocation = this->m_pObject->GetGPUVirtualAddress();
	}

	void D3D12VertexBuffer::operator=(D3D12VertexBuffer&& other) noexcept
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = nullptr;

		this->m_pUploadHeap  = std::move(other.m_pUploadHeap);
		this->m_pCommandList = other.m_pCommandList;
		this->m_vertexSize   = other.m_vertexSize;
		this->m_vertexData   = other.m_vertexData;
		this->m_vertexBufferView = other.m_vertexBufferView;
	}

	void D3D12VertexBuffer::Bind()
	{
		(*this->m_pCommandList)->IASetVertexBuffers(0u, 1u, &this->m_vertexBufferView);
	}

	void D3D12VertexBuffer::Update()
	{
		(*this->m_pCommandList).TransitionResource(this->m_pObject, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, D3D12_RESOURCE_STATE_COPY_DEST);

		D3D12_SUBRESOURCE_DATA vertexData = {};
		vertexData.pData      = this->m_vertexData.data();
		vertexData.RowPitch   = this->m_vertexData.size();
		vertexData.SlicePitch = this->m_vertexData.size();

		UpdateSubresources(*this->m_pCommandList, this->m_pObject, this->m_pUploadHeap, 0, 0, 1, &vertexData);

		(*this->m_pCommandList).TransitionResource(this->m_pObject, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
	}


	D3D12IndexBuffer::D3D12IndexBuffer(D3D12IndexBuffer&& other) noexcept
		: m_nIndices(other.m_nIndices), m_pCommandList(m_pCommandList)
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = nullptr;

		this->m_pUploadHeap = std::move(other.m_pUploadHeap);
		other.m_pUploadHeap.SetObjNullptr();
		this->m_indexBufferView = other.m_indexBufferView;
	}

	D3D12IndexBuffer::D3D12IndexBuffer(D3D12DeviceObjectWrapper& pDevice,
									   D3D12CommandList* pCommandList,
									   const size_t nIndices)
		: m_nIndices(nIndices), m_pCommandList(pCommandList)
	{
		const UINT bufferSize = static_cast<UINT>(nIndices * sizeof(uint32_t));

		if (FAILED(pDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(bufferSize), D3D12_RESOURCE_STATE_INDEX_BUFFER,
			nullptr, IID_PPV_ARGS(&this->m_pObject))))
			throw std::runtime_error("[DIRECTX 12] Failed To Create Index Buffer Resource");

		this->m_pObject->SetName(L"Index Buffer Resource Heap");

		if (FAILED(pDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(bufferSize), D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr, IID_PPV_ARGS(this->m_pUploadHeap.GetPtr()))))
			throw std::runtime_error("[DIRECTX 12] Failed To Create Index Buffer Upload Heap");

		this->m_pUploadHeap->SetName(L"Index Buffer Upload Resource Heap");

		this->m_indexData.resize(bufferSize);
		std::memset(this->m_indexData.data(), 0u, bufferSize);

		this->m_indexBufferView.Format         = DXGI_FORMAT_R32_UINT;
		this->m_indexBufferView.SizeInBytes    = static_cast<UINT>(this->m_indexData.size());
		this->m_indexBufferView.BufferLocation = this->m_pObject->GetGPUVirtualAddress();
	}

	void D3D12IndexBuffer::operator=(D3D12IndexBuffer&& other) noexcept
	{
		this->m_pObject = other.m_pObject;
		other.m_pObject = nullptr;

		this->m_nIndices        = other.m_nIndices;
		this->m_pUploadHeap     = std::move(other.m_pUploadHeap);
		this->m_pCommandList    = other.m_pCommandList;
		this->m_indexBufferView = other.m_indexBufferView;
	}

	void D3D12IndexBuffer::Bind()
	{
		(*this->m_pCommandList)->IASetIndexBuffer(&this->m_indexBufferView);
	}

	void D3D12IndexBuffer::Update()
	{
		(*this->m_pCommandList).TransitionResource(this->m_pObject, D3D12_RESOURCE_STATE_INDEX_BUFFER, D3D12_RESOURCE_STATE_COPY_DEST);

		D3D12_SUBRESOURCE_DATA indexData = {};
		indexData.pData      = this->m_indexData.data();
		indexData.RowPitch   = this->m_indexData.size();
		indexData.SlicePitch = indexData.RowPitch;

		UpdateSubresources(*this->m_pCommandList, this->m_pObject, this->m_pUploadHeap, 0, 0, 1, &indexData);

		(*this->m_pCommandList).TransitionResource(this->m_pObject, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_INDEX_BUFFER);
	}

	D3D12ConstantBuffer::D3D12ConstantBuffer()
	{

	}

	D3D12ConstantBuffer::D3D12ConstantBuffer(D3D12ConstantBuffer&& other) noexcept
		: m_slot(other.m_slot), m_objSize(other.m_objSize), m_pCommandList(other.m_pCommandList)
	{
		this->m_constantBufferData  = other.m_constantBufferData;
		this->m_constantBufferViews = other.m_constantBufferViews;
		this->m_descriptorHeaps = std::move(other.m_descriptorHeaps);
		this->m_pUploadHeaps = std::move(other.m_pUploadHeaps);
	}

	D3D12ConstantBuffer::D3D12ConstantBuffer(D3D12DeviceObjectWrapper& pDevice,
											 D3D12CommandList* pCommandList,
											 const size_t objSize, const size_t slot)
		: m_objSize(objSize), m_slot(slot), m_pCommandList(pCommandList)
	{
		this->m_constantBufferData.resize(objSize);
		std::memset(this->m_constantBufferData.data(), 0u, objSize);

		for (int i = 0; i < WEISS__FRAME_BUFFER_COUNT; i++)
			this->m_descriptorHeaps[i] = D3D12DescriptorHeap(pDevice, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 1u, D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE);

		for (int i = 0; i < WEISS__FRAME_BUFFER_COUNT; i++)
		{
			if (FAILED(pDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Buffer(1024 * 64), D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr, IID_PPV_ARGS(this->m_pUploadHeaps[i].GetPtr()))))
				throw std::runtime_error("[DIRECTX 12] Failed To Create A Commited Resource For A Constant Buffer");

			this->m_pUploadHeaps[i]->SetName(L"Constant Buffer Upload Resource Heap");

			this->m_constantBufferViews[i].BufferLocation = this->m_pUploadHeaps[i]->GetGPUVirtualAddress();
			this->m_constantBufferViews[i].SizeInBytes = (objSize + 255) & ~255;

			pDevice->CreateConstantBufferView(&this->m_constantBufferViews[i], this->m_descriptorHeaps[i]->GetCPUDescriptorHandleForHeapStart());
		}
	}

	void D3D12ConstantBuffer::Bind(const size_t frameIndex)
	{
		D3D12DescriptorHeap& descriptorHeap = this->m_descriptorHeaps[frameIndex];

		this->m_pCommandList->Get()->SetDescriptorHeaps(1u, descriptorHeap.GetPtr());
		this->m_pCommandList->Get()->SetGraphicsRootDescriptorTable(0u, descriptorHeap->GetGPUDescriptorHandleForHeapStart());
	}

	size_t D3D12ConstantBuffer::GetSlot() const noexcept { return this->m_slot; }

	void D3D12ConstantBuffer::Update()
	{
		CD3DX12_RANGE readRange(0, 0);
		CD3DX12_RANGE writtenRange(0, this->m_objSize);

		for (size_t i = 0; i < WEISS__FRAME_BUFFER_COUNT; i++)
		{
			uint8_t* gpuDestAddr;
			if (FAILED(this->m_pUploadHeaps[i]->Map(0, &readRange, reinterpret_cast<void**>(&gpuDestAddr))))
				throw std::runtime_error("[DIRECTX 12] Failed To Map Constant Buffer Memory");

			memcpy((void*)gpuDestAddr, this->m_constantBufferData.data(), this->m_objSize);

			this->m_pUploadHeaps[i]->Unmap(0, &writtenRange);
		}
	}

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS