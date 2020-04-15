#include "RootSignature.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12RootSignature::DirectX12RootSignature(DirectX12DeviceObjectWrapper& pDevice, const D3D12_ROOT_SIGNATURE_FLAGS& flags,
											   const std::vector<CD3DX12_ROOT_PARAMETER>& rootParameters)
{
	CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init(rootParameters.size(), rootParameters.data(), 0, nullptr, flags);

	Microsoft::WRL::ComPtr<ID3DBlob> pSignature;
	Microsoft::WRL::ComPtr<ID3DBlob> pError;
	if (FAILED(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &pSignature, pError.GetAddressOf())))
		throw std::runtime_error("[DIRECTX 12] Failed To Serialize Root Signature");

	if (FAILED(pDevice->CreateRootSignature(0, pSignature->GetBufferPointer(), pSignature->GetBufferSize(), IID_PPV_ARGS(&this->m_pObject))))
		throw std::runtime_error("[DIRECTX 12] Failed To Create Root Signature");
}

void DirectX12RootSignature::operator=(DirectX12RootSignature&& other) noexcept
{
	this->m_pObject = other.m_pObject;
	other.m_pObject = nullptr;
}

#endif // __WEISS__OS_WINDOWS