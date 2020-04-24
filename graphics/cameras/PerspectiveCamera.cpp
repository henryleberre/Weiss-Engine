#include "PerspectiveCamera.h"

namespace WS {

	PerspectiveCamera::PerspectiveCamera(Window* pWindow, const PerspectiveCameraDescriptor& descriptor)
		: Camera(descriptor.position, descriptor.rotation), m_fov(descriptor.fov), m_zNear(descriptor.zNear), m_zFar(descriptor.zFar)
	{
		auto recalculateAspectRatio = [this](const Vec2u16& clientDims)
		{
			this->m_aspectRatio = clientDims.x / static_cast<float>(clientDims.y);
		};

		recalculateAspectRatio({ pWindow->GetClientWidth(), pWindow->GetClientHeight() });

		pWindow->OnResize(recalculateAspectRatio);
	}

	void PerspectiveCamera::CalculateTransform()
	{
#ifdef __WEISS__OS_WINDOWS
		DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYawFromVector(this->m_rotation);
		DirectX::XMVECTOR focusPosition  = DirectX::XMVectorAdd(DirectX::XMVector3TransformCoord(FORWARD_VECTOR, rotationMatrix), this->m_position);
		DirectX::XMVECTOR upDirection    = DirectX::XMVector3TransformCoord(UP_VECTOR, rotationMatrix);

		this->m_forwardVector = DirectX::XMVector3TransformCoord(FORWARD_VECTOR, rotationMatrix);
		this->m_rightVector   = DirectX::XMVector3TransformCoord(RIGHT_VECTOR, rotationMatrix);

		this->m_transform = DirectX::XMMatrixLookAtLH(this->m_position, focusPosition, upDirection) *
							DirectX::XMMatrixPerspectiveFovLH(this->m_fov, this->m_aspectRatio, this->m_zNear, this->m_zFar);
#endif // __WEISS__OS_WINDOWS
	}

	void PerspectiveCamera::HandleMouseMovements(Mouse& mouse, const float sensitivity)
	{
		mouse.OnMouseMove([sensitivity, this, &mouse](const Vec2u16 position, const Vec2i16 delta)
			{
				if (mouse.IsCursorInWindow()) {
					this->Rotate({ sensitivity * delta.y, sensitivity * delta.x, 0.0f });
				}
			});
	}

	void PerspectiveCamera::HandleKeyboardInputs(Keyboard& keyboard, const float speed, const char forward, const char backward, const char left, const char right, const char up, const char down)
	{
#ifdef __WEISS__OS_WINDOWS

		if (keyboard.IsKeyDown(forward))
			this->m_position = DirectX::XMVectorAdd(this->m_position, DirectX::XMVectorMultiply(this->m_forwardVector, DirectX::XMVectorSet(speed, speed, speed, 0.0f)));
		if (keyboard.IsKeyDown(backward))
			this->m_position = DirectX::XMVectorSubtract(this->m_position, DirectX::XMVectorMultiply(this->m_forwardVector, DirectX::XMVectorSet(speed, speed, speed, 0.0f)));

		if (keyboard.IsKeyDown(right))
			this->m_position = DirectX::XMVectorAdd(this->m_position, DirectX::XMVectorMultiply(this->m_rightVector, DirectX::XMVectorSet(speed, speed, speed, 0.0f)));
		if (keyboard.IsKeyDown(left))
			this->m_position = DirectX::XMVectorSubtract(this->m_position, DirectX::XMVectorMultiply(this->m_rightVector, DirectX::XMVectorSet(speed, speed, speed, 0.0f)));

		if (keyboard.IsKeyDown(up))
			this->m_position = DirectX::XMVectorAdd(this->m_position, DirectX::XMVectorMultiply(UP_VECTOR, DirectX::XMVectorSet(speed, speed, speed, 0.0f)));
		if (keyboard.IsKeyDown(down))
			this->m_position = DirectX::XMVectorSubtract(this->m_position, DirectX::XMVectorMultiply(UP_VECTOR, DirectX::XMVectorSet(speed, speed, speed, 0.0f)));

#endif // __WEISS__OS_WINDOWS
	}

};