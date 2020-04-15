#pragma once

#include "Camera.h"
#include "../../window/Include.h"

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

	void Rotate(const float angle);

	void SetPosition(const Vec2f& v);

	void SetRotation(const Vec2f& v);

	void Translate(const Vec2f& v);

	virtual void CalculateTransform() override;

	void HandleKeyboardInputs(Keyboard& keyboard, const float speed, const char left, const char right, const char up, const char down);
};
