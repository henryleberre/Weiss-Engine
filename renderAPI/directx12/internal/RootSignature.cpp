#include "RootSignature.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12RootSignature::DirectX12RootSignature(DirectX12DeviceObjectWrapper& pDevice, const D3D12_ROOT_SIGNATURE_FLAGS& flags,
											   const std::vector<D3D12_ROOT_PARAMETER1>& rootParameters)
{
	Microsoft::WRL::ComPtr<ID3DBlob> pSignature;
	Microsoft::WRL::ComPtr<ID3DBlob> pError;

	D3D12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Version = D3D_ROOT_SIGNATURE_VERSION_1_1;
	rootSignatureDesc.Desc_1_1.NumParameters = static_cast<UINT>(rootParameters.size());
	rootSignatureDesc.Desc_1_1.Flags = flags;
	rootSignatureDesc.Desc_1_1.pParameters = (rootParameters.size() > 0) ? rootParameters.data() : nullptr;
	rootSignatureDesc.Desc_1_1.pStaticSamplers = nullptr;
	rootSignatureDesc.Desc_1_1.NumStaticSamplers = 0u;

	if (FAILED(D3D12SerializeVersionedRootSignature(&rootSignatureDesc, &pSignature, &pError))) {
		throw std::runtime_error("[DIRECTX 12] Failed To Serialize Root Signature");
	}

	if (FAILED(pDevice->CreateRootSignature(0, pSignature->GetBufferPointer(), pSignature->GetBufferSize(), IID_PPV_ARGS(&this->m_pObject))))
		throw std::runtime_error("[DIRECTX 12] Failed To Create Root Signature");
}

void DirectX12RootSignature::operator=(DirectX12RootSignature&& other) noexcept
{
	this->m_pObject = other.m_pObject;
	other.m_pObject = nullptr;
}

#endif // __WEISS__OS_WINDOWS