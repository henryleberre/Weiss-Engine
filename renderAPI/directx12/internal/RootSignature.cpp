#include "RootSignature.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12RootSignature::DirectX12RootSignature(DirectX12DeviceObjectWrapper& pDevice, const D3D12_ROOT_SIGNATURE_FLAGS& flags)
{
	CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init(0, nullptr, 0, nullptr, flags);

	Microsoft::WRL::ComPtr<ID3DBlob> pSignature;
	if (D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &pSignature, nullptr) != S_OK)
		throw std::runtime_error("[DIRECTX 12] Failed To Serialize Root Signature");

	if (pDevice->CreateRootSignature(0, pSignature->GetBufferPointer(), pSignature->GetBufferSize(), IID_PPV_ARGS(&this->m_pObject)) != S_OK)
		throw std::runtime_error("[DIRECTX 12] Failed To Create Root Signature");
}

#endif // __WEISS__OS_WINDOWS