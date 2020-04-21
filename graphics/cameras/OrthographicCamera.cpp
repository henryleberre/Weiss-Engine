#include "OrthographicCamera.h"

namespace WS {

	OrthographicCamera::OrthographicCamera(Window* pWindow, const OrthographicCameraDescriptor& descriptor)
		: Camera(descriptor.position, Vec3f{ 0.0f, descriptor.ratation, 0.0f })
	{
		auto recalculateInvAspectRatio = [this](const Vec2u16& clientDims)
		{
			this->m_InvAspectRatio = clientDims.y / static_cast<float>(clientDims.x);
		};

		recalculateInvAspectRatio({ pWindow->GetClientWidth(), pWindow->GetClientHeight() });

		pWindow->OnResize(recalculateInvAspectRatio);
	}

	void OrthographicCamera::CalculateTransform()
	{
#ifdef __WEISS__OS_WINDOWS

		this->m_transform = DirectX::XMMatrixScaling(this->m_InvAspectRatio, 1, 1) *
							DirectX::XMMatrixTranslation(-this->m_position.x, -this->m_position.y, 0.0f) *
							DirectX::XMMatrixRotationZ(this->m_rotation.z);

#endif // __WEISS__OS_WINDOWS
	}

	void OrthographicCamera::HandleMouseMovements(Mouse& mouse, const float sensitivity)
	{

	}

	void OrthographicCamera::HandleKeyboardInputs(Keyboard& keyboard, const float speed, const char forward, const char backward, const char left, const char right, const char up, const char down)
	{
#ifdef __WEISS__OS_WINDOWS

		if (keyboard.IsKeyDown(right))
			this->m_position = DirectX::XMVectorSet(this->m_position.x - speed, this->m_position.y, 0.0f, 0.0f);
		if (keyboard.IsKeyDown(left))
			this->m_position = DirectX::XMVectorSet(this->m_position.x + speed, this->m_position.y, 0.0f, 0.0f);

		if (keyboard.IsKeyDown(up))
			this->m_position = DirectX::XMVectorSet(this->m_position.x, this->m_position.y - speed, 0.0f, 0.0f);
		if (keyboard.IsKeyDown(down))
			this->m_position = DirectX::XMVectorSet(this->m_position.x, this->m_position.y + speed, 0.0f, 0.0f);

#endif // __WEISS__OS_WINDOWS
	}

};