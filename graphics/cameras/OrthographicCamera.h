#pragma once

#include "Camera.h"
#include "../../window/Include.h"
#include "../../common/Include.h"

namespace WS {

	struct OrthographicCameraDescriptor
	{
		const Vec2f position;
		const float ratation;
	};

	class OrthographicCamera : public Camera {
	private:
		float m_InvAspectRatio = 0.0f;

	public:
		OrthographicCamera(Window* pWindow, const OrthographicCameraDescriptor& descriptor);

		virtual void CalculateTransform() override;

		virtual void HandleMouseMovements(Mouse& mouse, const float sensitivity) override;
		virtual void HandleKeyboardInputs(Keyboard& keyboard, const float speed, const char forward, const char backward, const char left, const char right, const char up, const char down) override;
	};

};