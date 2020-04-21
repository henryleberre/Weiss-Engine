#include "Include.h"

namespace WS {

	RenderAPIHandle RenderAPI::Create(const RenderAPIName& apiName)
	{
		switch (apiName)
		{
#ifdef __WEISS__OS_WINDOWS
		case RenderAPIName::DIRECTX11:
			return new Internal::D3D11::D3D11RenderAPI();
		case RenderAPIName::DIRECTX12:
			return new Internal::D3D12::D3D12RenderAPI();
#endif // __WEISS__OS_WINDOWS
		}

		throw std::runtime_error("[RENDER API] Your Render API Is Not Supported");
	}

}; // WS