#pragma once

#include "Device.h"
#include "../../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D12    {

	typedef D3D12ObjectWrapper<ID3D12RootSignature> D3D12RootSignatureObjectWrapper;

	class D3D12RootSignature : public D3D12RootSignatureObjectWrapper {
	public:
		D3D12RootSignature() {  }

		D3D12RootSignature(D3D12DeviceObjectWrapper& pDevice, const D3D12_ROOT_SIGNATURE_FLAGS& flags,
							   const std::vector<D3D12_ROOT_PARAMETER1>& rootParameters = {});

		void operator=(D3D12RootSignature&& other) noexcept;
	};

}; // D3D12
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS