#pragma once

#include "../math/Include.h"
#include "../common/Include.h"
#include "../window/Include.h"
#include "../renderAPI/Include.h"

class GraphicsEngine {
private:
	RenderAPIHandle m_pRenderAPI;

public:
	GraphicsEngine(const RenderAPIName& apiName);

	~GraphicsEngine();
};