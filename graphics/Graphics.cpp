#include "Graphics.h"

namespace WS {

	GraphicsEngine::GraphicsEngine(const RenderAPIName& apiName)
	{
		this->m_renderHandle = RenderAPI::Create(apiName);
	}

	void GraphicsEngine::Init(WindowHandle windowHandle)
	{
		this->m_windowHandle = windowHandle;

		this->m_renderHandle->InitRenderAPI(windowHandle, 144u);
	}

	void GraphicsEngine::Run(const size_t fps)
	{
		while (this->m_windowHandle->IsRunning())
		{
			this->m_windowHandle->Update();

			this->m_renderHandle->BeginDrawing();
			this->m_renderHandle->EndDrawing();

			this->OnFrame();
			this->m_renderHandle->Present(false);

			// Temporary
			std::this_thread::sleep_for(std::chrono::milliseconds((unsigned int)(1 / (float)fps * 1000u)));
		}
	}

};