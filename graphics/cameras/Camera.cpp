#include "Camera.h"

namespace WS {

	Camera::Camera() { }

	Camera::Camera(const Vec3f& position, const Vec3f& rotation)
		: m_position(position), m_rotation(rotation)
	{

	}

	[[nodiscard]] Mat4x4f Camera::GetTransform()           const noexcept { return this->m_transform;                             }
	[[nodiscard]] Mat4x4f Camera::GetTransposedTransform() const noexcept { return DirectX::XMMatrixTranspose(this->m_transform); }

	[[nodiscard]] Vec3f& Camera::GetPosition() noexcept { return this->m_position; }
	[[nodiscard]] Vec3f& Camera::GetRotation() noexcept { return this->m_rotation; }

	void Camera::Rotate     (const Vec3f& delta)    noexcept { this->m_rotation += delta;   }
	void Camera::SetRotation(const Vec3f& rotation) noexcept { this->m_rotation = rotation; }

	void Camera::Translate  (const Vec3f& delta)    noexcept { this->m_position += delta;   }
	void Camera::SetPosition(const Vec3f& position) noexcept { this->m_position = position; }

};