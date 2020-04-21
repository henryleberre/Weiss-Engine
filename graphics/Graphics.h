#pragma once

#include "cameras/Include.h"
#include "../math/Include.h"
#include "../common/Include.h"
#include "../window/Include.h"
#include "../renderAPI/Include.h"

namespace WS {

	class GraphicsEngine {
	private:
		RenderAPIHandle m_apiHandle;

	public:
		GraphicsEngine(const RenderAPIName& apiName);

		void Init();

		void Run(const size_t fps);

		virtual void OnDraw() = 0;
		virtual void OnUpdate() = 0;

		~GraphicsEngine() = default;
	};

};