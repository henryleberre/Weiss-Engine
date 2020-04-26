#pragma once

#include "internal/Include.h"
#include "../common/Include.h"
#include "../../common/Include.h"

#ifdef __WEISS__OS_WINDOWS

namespace WS       {
namespace Internal {
namespace D3D11    {

	typedef D3D11ObjectWrapper<ID3D11ShaderResourceView> D3D11TextureObjectWrapper;

	class D3D11Texture : public Texture,
						 public D3D11TextureObjectWrapper {
	private:
		D3D11DeviceContextObjectWrapper* m_pDeviceContext = nullptr;

		size_t m_slot = 0u;

	public:
		D3D11Texture() = default;
		D3D11Texture(D3D11DeviceObjectWrapper& pDevice,
					 D3D11DeviceContextObjectWrapper* pDeviceContext,
					 const Image& image, const size_t slot, const bool useMipmaps);

		void Bind() const noexcept;

		virtual void Update(const Image& image) override;
	};

}; // D3D11
}; // Internal
}; // WS

#endif // __WEISS__OS_WINDOWS