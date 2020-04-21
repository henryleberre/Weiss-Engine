#pragma once

#include "../common/Include.h"

template <typename T, size_t R, size_t C>
class Matrix
{
private:
	T m[R][C] = { 0 };

public:
	Matrix() = default;

	template <typename T2>
	Matrix(const std::initializer_list<std::initializer_list<T2>>& data)
	{
		size_t r = 0, c = 0;
		for (const std::initializer_list<T2>& row : data) {
			for (const T2& cell : row)
				this->m[r][c++] = static_cast<T>(cell);
			r++;
		}
	}

	template <typename T2, size_t R2, size_t C2>
	Matrix(const Matrix<T2, R2, C2>& other)
	{
		if constexpr (R == R2 && C == C2 && std::is_same<T, T2>()) {
			std::memcpy(this->m, other.m, sizeof(this->m));
		} else {
			const size_t _R = std::min(R, R2);
			const size_t _C = std::min(C, C2);

			for (size_t r = 0u; r < _R; r++)
				for (size_t c = 0u; c < _C; c++)
					this->m[r][c] = static_cast<T>(other.m[r][c]);
		}
	}

#ifdef __WEISS__OS_WINDOWS

	Matrix(const DirectX::XMMATRIX& other)
	{
		DirectX::XMFLOAT4X4 float4x4;
		DirectX::XMStoreFloat4x4(&float4x4, other);

		if constexpr (R == 4u && C == 4u && std::is_same<T, float>()) {
			std::memcpy(this->m, float4x4.m, sizeof(this->m));
		} else {
			const size_t _R = std::min(R, 4u);
			const size_t _C = std::min(C, 4u);

			for (size_t r = 0u; r < _R; r++)
				for (size_t c = 0u; c < _C; c++)
					this->m[r][c] = static_cast<T>(float4x4.m[r][c]);
		}
	}

#endif // __WEISS__OS_WINDOWS

	[[nodiscard]] inline size_t GetRowCount() const noexcept { return R; }
	[[nodiscard]] inline size_t GetColCount() const noexcept { return C; }

	[[nodiscard]] inline T* operator[](const size_t r) { return this->m[r]; }

	[[nodiscard]] inline T& Get(const size_t r, const size_t c) noexcept { return this->m[r][c]; }
	[[nodiscard]] inline const T& GetValue(const size_t r, const size_t c) const noexcept { return this->m[r][c]; }

	[[nodiscard]] inline Matrix<T, R, C> GetTransposed() const noexcept {
		Matrix<T, R, C> transposed(*this);
		for (size_t r = 0u; r < R; r++)
			for (size_t c = 0u; c < C; c++)
				transposed[r][c] = this->m[c][r];

		return transposed;
	}

	template <typename T2, size_t R2, size_t C2>
	[[nodiscard]] inline bool operator==(const Matrix<T2, R2, C2>& other) const noexcept
	{
		if constexpr (R == R2 && C == C2 && std::is_same<T, T2>()) {
			return std::memcmp(this->m, other.m, sizeof(this->m)) == 0;
		} else {
			return false;
		}
	}

#ifdef __WEISS__OS_WINDOWS

	[[nodiscard]] inline operator DirectX::XMMATRIX() const noexcept
	{
		DirectX::XMFLOAT4X4 float4x4;

		if constexpr (R == 4u && C == 4u && std::is_same<T, float>()) {
			std::memcpy(&float4x4, this->m, sizeof(this->m));
		} else {
			const size_t _R = std::min(R, 4u);
			const size_t _C = std::min(C, 4u);

			for (size_t r = 0u; r < _R; r++)
				for (size_t c = 0u; c < _C; c++)
					float4x4[r][c] = static_cast<T>(this->m[r][c]);
		}
		
		return DirectX::XMLoadFloat4x4(&float4x4);
	}

#endif // __WEISS__OS_WINDOWS

public:
	[[nodiscard]] static inline constexpr Matrix<T, R, C> MakeIdentity()
	{
		Matrix<T, R, C> mat;
		if constexpr (R == C)
			for (size_t i = 0; i < R; i++)
				mat[i][i] = 1.0f;

		return mat;
	}
};

template <typename T, size_t R, size_t C>
std::ostream& operator<<(std::ostream& stream, const Matrix<T, R, C>& matrix)
{
	for (size_t r = 0u; r < R; r++)
	{
		stream << '|';
		for (size_t c = 0u; c < C - 1u; c++)
			stream << matrix.GetValue(r, c) << ", ";

		stream << matrix.GetValue(r, C-1u) << "|\n";
	}

	return stream;
}

typedef Matrix<float, 3u, 3u> Mat3x3f;
typedef Matrix<float, 4u, 4u> Mat4x4f;