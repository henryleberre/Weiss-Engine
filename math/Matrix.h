#pragma once

#include "../common/Include.h"

template <typename T, size_t R, size_t C>
class Matrix
{
private:
	T m[R][C] = { 0 };

public:
	Matrix() = default;

	[[nodiscard]] size_t GetRowCount() const noexcept { return R; }
	[[nodiscard]] size_t GetColCount() const noexcept { return C; }

	T* operator[](const size_t r) { return this->m[r]; }

	T& Get(const size_t r, const size_t c) noexcept { return this->m[r][c]; }
	const T& GetValue(const size_t r, const size_t c) const noexcept { return this->m[r][c]; }

	Matrix<T, R, C> GetTransposed() const noexcept {
		Matrix<T, R, C> transposed(*this);
		for (size_t r = 0u; r < R; r++)
			for (size_t c = 0u; c < C; c++)
				transposed[r][c] = this->m[c][r];

		return transposed;
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

typedef Matrix<float, 4u, 4u> Mat4x4f;