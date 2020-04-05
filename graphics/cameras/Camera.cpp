#include "Camera.h"

Camera::Camera() { }

[[nodiscard]] DirectX::XMMATRIX Camera::GetTransform()           const noexcept { return this->m_transform; }
[[nodiscard]] DirectX::XMMATRIX Camera::GetTransposedTransform() const noexcept { return DirectX::XMMatrixTranspose(this->m_transform); }

[[nodiscard]] Vec3f Camera::GetPosition() const noexcept { return Vec3f{ this->m_position.m128_f32[0], this->m_position.m128_f32[1], this->m_position.m128_f32[2] }; }
[[nodiscard]] Vec3f Camera::GetRotation() const noexcept { return Vec3f{ this->m_rotation.m128_f32[0], this->m_rotation.m128_f32[1], this->m_rotation.m128_f32[2] }; }