#include "Camera.h"
#include "../../window/Include.h"

namespace WS {

	struct PerspectiveCameraDescriptor
	{
		const Vec3f position;
		const Vec3f rotation;

		const float fov;
		const float zNear;
		const float zFar;
	};

	class PerspectiveCamera : public Camera
	{
	private:
		const DirectX::XMVECTOR UP_VECTOR      = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		const DirectX::XMVECTOR FORWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		const DirectX::XMVECTOR RIGHT_VECTOR   = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

		DirectX::XMVECTOR m_forwardVector = FORWARD_VECTOR;
		DirectX::XMVECTOR m_rightVector = RIGHT_VECTOR;

		float m_fov = 0.0f, m_aspectRatio = 0.0f, m_zNear = 0.0f, m_zFar = 0.0f;

	private:
		[[nodiscard]] DirectX::XMMATRIX GetViewMatrix();

		[[nodiscard]] DirectX::XMMATRIX GetProjectionMatrix();

	public:
		PerspectiveCamera(Window* pWindow, const PerspectiveCameraDescriptor& descriptor);

		virtual void CalculateTransform() override;

		virtual void HandleMouseMovements(Mouse& mouse, const float sensitivity) override;
		virtual void HandleKeyboardInputs(Keyboard& keyboard, const float speed, const char forward, const char backward, const char left, const char right, const char up, const char down) override;
	};

};