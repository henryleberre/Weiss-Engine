#pragma once

#include "../math/Include.h"
#include "../common/Include.h"
#include "../window/Include.h"
#include "../renderAPI/Include.h"

class GraphicsEngine {
private:
	RenderAPI* m_pRenderAPI = nullptr;

public:
	GraphicsEngine(const RenderAPIName& apiName);

	~GraphicsEngine();
};