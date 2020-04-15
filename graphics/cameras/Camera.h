#pragma once

#include "../../math/Include.h"

class Camera {
protected:
	DirectX::XMMATRIX m_transform = DirectX::XMMatrixIdentity();

	DirectX::XMVECTOR m_position = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR m_rotation = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

public:
	Camera();

	[[nodiscard]] DirectX::XMMATRIX GetTransform()           const noexcept;
	[[nodiscard]] DirectX::XMMATRIX GetTransposedTransform() const noexcept;

	[[nodiscard]] Vec3f GetPosition() const noexcept;
	[[nodiscard]] Vec3f GetRotation() const noexcept;

	virtual void CalculateTransform() = 0;
};