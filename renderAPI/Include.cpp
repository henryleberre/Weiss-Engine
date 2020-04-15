#include "Include.h"

RenderAPIHandle RenderAPI::Create(const RenderAPIName& apiName)
{
	switch (apiName)
	{
#ifdef __WEISS__OS_WINDOWS
	case RenderAPIName::DIRECTX11:
		return new DirectX11RenderAPI();
	case RenderAPIName::DIRECTX12:
		return new DirectX12RenderAPI();
#endif // __WEISS__OS_WINDOWS
	}

	throw std::runtime_error("[RENDER API] Your Render API Is Not Supported");
}