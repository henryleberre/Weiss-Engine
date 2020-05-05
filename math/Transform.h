#pragma once

#include "Vector.h"
#include "Matrix.h"

namespace WS {

	struct Transform {
	private:
		Vec3f m_rotation;
		Vec3f m_translation;

		Mat4x4f m_transform = Mat4x4f::MakeIdentity();

	public:
		Transform() = default;

		Vec3f GetRotation()    const noexcept;
		Vec3f GetTranslation() const noexcept;

		void SetRotation   (const Vec3f& rotation)    noexcept;
		void SetTranslation(const Vec3f& translation) noexcept;

		void Rotate   (const Vec3f& delta) noexcept;
		void Translate(const Vec3f& delta) noexcept;

		Mat4x4f GetTransform()           const noexcept;
		Mat4x4f GetTransposedTransform() const noexcept;

		void CalculateTransform() noexcept;
	};

}; // WS