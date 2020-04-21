#include "Graphics.h"

namespace WS {

	GraphicsEngine::GraphicsEngine(const RenderAPIName& apiName)
	{
		this->m_apiHandle = RenderAPI::Create(apiName);
	}

};