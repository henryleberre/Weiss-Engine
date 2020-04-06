#include "RootSignature.h"

#ifdef __WEISS__OS_WINDOWS

DirectX12RootSignature::DirectX12RootSignature(const std::shared_ptr<DirectX12Device>& pDevice, const D3D12_ROOT_SIGNATURE_FLAGS& flags)
{
	CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	Microsoft::WRL::ComPtr<ID3DBlob> pSignature;
	if (D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &pSignature, nullptr) != S_OK)
		throw std::runtime_error("[DIRECTX 12] Failed To Serialize Root Signature");

	if (pDevice->Get()->CreateRootSignature(0, pSignature->GetBufferPointer(), pSignature->GetBufferSize(), IID_PPV_ARGS(&this->m_pRootSignature)) != S_OK)
		throw std::runtime_error("[DIRECTX 12] Failed To Create Root Signature");
}

Microsoft::WRL::ComPtr<ID3D12RootSignature> DirectX12RootSignature::Get() const noexcept
{
	return this->m_pRootSignature;
}

DirectX12RootSignature::operator Microsoft::WRL::ComPtr<ID3D12RootSignature>() const noexcept
{
	return this->m_pRootSignature;
}

#endif // __WEISS__OS_WINDOWS