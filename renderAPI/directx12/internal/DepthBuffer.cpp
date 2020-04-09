#include "DepthBuffer.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12DepthBuffer::DirectX12DepthBuffer(DirectX12Device& pDevice, Window* pWindow)
{
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type  = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	if (FAILED(pDevice->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(this->m_pDescriptorHeap.GetPtr()))))
		throw std::runtime_error("[DIRECTX 12] Failed To Create Descriptor Heap For Depth Buffer");

	D3D12_DEPTH_STENCIL_VIEW_DESC depthStencilDesc = {};
	depthStencilDesc.Format        = DXGI_FORMAT_D32_FLOAT;
	depthStencilDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	depthStencilDesc.Flags         = D3D12_DSV_FLAG_NONE;

	D3D12_CLEAR_VALUE depthOptimizedClearValue = {};
	depthOptimizedClearValue.Format               = DXGI_FORMAT_D32_FLOAT;
	depthOptimizedClearValue.DepthStencil.Depth   = 1.0f;
	depthOptimizedClearValue.DepthStencil.Stencil = 0;

	if (FAILED(pDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE,
												&CD3DX12_RESOURCE_DESC::Tex2D(DXGI_FORMAT_D32_FLOAT, pWindow->GetClientWidth(), pWindow->GetClientHeight(), 1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL),
												D3D12_RESOURCE_STATE_DEPTH_WRITE, &depthOptimizedClearValue,
												IID_PPV_ARGS(this->m_pDepthStencilBuffer.GetPtr()))))
		throw std::runtime_error("[DIRECTX 12] Failed To Create Depth Stencil Heap");
	
	this->m_pDepthStencilBuffer->SetName(L"Depth/Stencil Resource Heap");

	pDevice->CreateDepthStencilView(this->m_pDepthStencilBuffer, &depthStencilDesc, this->m_pDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

	this->m_dsvHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(this->m_pDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
}

void DirectX12DepthBuffer::Clear(DirectX12CommandListObjectWrapper& pCommandList)
{
	pCommandList->ClearDepthStencilView(this->m_pDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

DirectX12DepthBuffer::operator CD3DX12_CPU_DESCRIPTOR_HANDLE* () noexcept
{
	return &this->m_dsvHandle;
}

#endif // __WEISS__OS_WINDOWS