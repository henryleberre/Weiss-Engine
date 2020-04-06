#pragma once

#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

class DirectX12VertexBuffer : public VertexBuffer {
private:
	Microsoft::WRL::ComPtr<ID3D12Resource> m_pVertexBuffer;

	D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

public:
	DirectX12VertexBuffer(const std::shared_ptr<DirectX12Device>& pDevice, const size_t vertexSize, const size_t nVertices, const void* buff = nullptr);

	void Bind(const std::shared_ptr<DirectX12CommandList>& pCommandList);
	virtual size_t GetCount() override;
	virtual void   SetData(const void* buff, const size_t nVertices) override;
};

#endif // __WEISS__OS_WINDOWS