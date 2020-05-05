#include "Transform.h"

namespace WS {

	Vec3f Transform::GetRotation()    const noexcept { return this->m_rotation;    }
	Vec3f Transform::GetTranslation() const noexcept { return this->m_translation; }

	void Transform::SetRotation   (const Vec3f& rotation)    noexcept { this->m_rotation    = rotation;    }
	void Transform::SetTranslation(const Vec3f& translation) noexcept { this->m_translation = translation; }

	void Transform::Rotate   (const Vec3f& delta) noexcept { this->m_rotation    += delta; }
	void Transform::Translate(const Vec3f& delta) noexcept { this->m_translation += delta; }

	Mat4x4f Transform::GetTransform()           const noexcept { return this->m_transform;                 }
	Mat4x4f Transform::GetTransposedTransform() const noexcept { return this->m_transform.GetTransposed(); }

	void Transform::CalculateTransform() noexcept
	{
#ifdef __WEISS__OS_WINDOWS

		this->m_transform = DirectX::XMMatrixTranslationFromVector(this->m_translation)
						  * DirectX::XMMatrixRotationX(this->m_rotation.x)
						  * DirectX::XMMatrixRotationY(this->m_rotation.y)
						  * DirectX::XMMatrixRotationZ(this->m_rotation.z);

#endif // __WEISS__OS_WINDOWS
	}

}; // WS