#include "Graphics.h"

GraphicsEngine::GraphicsEngine(const RenderAPIName& apiName)
{
	this->m_pRenderAPI = RenderAPI::Create(apiName);
}

GraphicsEngine::~GraphicsEngine()
{
	delete this->m_pRenderAPI;
}