#pragma once

#include "../window/Include.h"
#include "../../math/Include.h"

namespace WS {

	class Camera {
	protected:
		Mat4x4f m_transform = Mat4x4f::MakeIdentity();

		Vec3f m_position;
		Vec3f m_rotation;

	public:
		Camera();

		Camera(const Vec3f& position, const Vec3f& rotation);

		[[nodiscard]] Mat4x4f GetTransform()           const noexcept;
		[[nodiscard]] Mat4x4f GetTransposedTransform() const noexcept;

		[[nodiscard]] Vec3f& GetPosition() noexcept;
		[[nodiscard]] Vec3f& GetRotation() noexcept;

		void Rotate     (const Vec3f& delta)    noexcept;
		void SetRotation(const Vec3f& rotation) noexcept;

		void Translate  (const Vec3f& delta)    noexcept;
		void SetPosition(const Vec3f& position) noexcept;

		virtual void CalculateTransform() = 0;

		virtual void HandleMouseMovements(Mouse& mouse, const float sensitivity) = 0;
		virtual void HandleKeyboardInputs(Keyboard& keyboard, const float speed, const char forward, const char backward, const char left, const char right, const char up, const char down) = 0;
	};

};