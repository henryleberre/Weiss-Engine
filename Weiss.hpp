﻿#pragma once

/*  
 *   /‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\
 *  / /‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\ \
 *  | |           ██          ██    ██████████████      ██████████      ██████████████    ██████████████           | |
 *  | |           ██          ██    ██                      ██          ██                ██                       | |
 *  | |           ██          ██    ██                      ██          ██                ██                       | |
 *  | |           ██    ██    ██    ██████████████          ██          ██████████████    ██████████████           | |
 *  | |           ██    ██    ██    ██                      ██                      ██                ██           | |
 *  | |           ██  ██  ██  ██    ██                      ██                      ██                ██           | |
 *  | |             ██      ██      ██████████████      ██████████      ██████████████    ██████████████           | |
 *  | |                                                                                                            | |
 *  | |  ██████████████    ██          ██    ██████████████      ██████████      ██          ██    ██████████████  | |
 *  | |  ██                ████        ██    ██                      ██          ████        ██    ██              | |
 *  | |  ██                ██  ██      ██    ██                      ██          ██  ██      ██    ██              | |
 *  | |  ██████████████    ██    ██    ██    ██    ██████            ██          ██    ██    ██    ██████████████  | |
 *  | |  ██                ██      ██  ██    ██          ██          ██          ██      ██  ██    ██              | |
 *  | |  ██                ██        ████    ██          ██          ██          ██        ████    ██              | |
 *  | |  ██████████████    ██          ██    ████████████        ██████████      ██          ██    ██████████████  | |
 *  \ \____________________________________________________________________________________________________________/ /
 *   \______________________________________________________________________________________________________________/
 * 
 * // ////////////////////////////////--\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
 * // ||-----------------------------INFO-----------------------------|| \\
 * // |\______________________________________________________________/| \\
 * // \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\--//////////////////////////////// \\ 
 * 
 * Project    : Weiss Engine
 * Author     : Henry LE BERRE (PolarToCartesian)
 * Repository : https://github.com/PolarToCartesian/Weiss
 */

#ifdef _WIN32

	#define _CRT_SECURE_NO_WARNINGS

	#define __WEISS__OS_WINDOWS

	#ifdef _WIN64

		#define __WEISS__PLATFORM_X64
	
	#else // End Of #ifdef _WIN64
	
		#define __WEISS__PLATFORM_X86
	
	#endif

	#define _WINSOCKAPI_					// Stops Windows.h from including winsock2
	#define _WINSOCK_DEPRECATED_NO_WARNINGS // Lets us use htons()
	#define NOMINMAX						// Stops The Importing Of min() And max() From Windef.h

	// Windows Includes
	#include <wrl.h>
	#include <strsafe.h>
	#include <Windows.h>
	#include <windowsx.h>

	// Windows Networking Includes
	#include <winhttp.h>
	#include <winsock2.h>
	#include <ws2tcpip.h>

	// Windows Image Includes
	#include <wincodec.h>

	// Windows DirectX 11 Includes
	#include <d3d11.h>

	// Windows DirectX 12 Includes
	#include <d3d12.h>
	#include <d3dx12.h> // from https://github.com/Microsoft/DirectX-Graphics-Samples/tree/master/Libraries/D3DX12
	#include <dxgi1_6.h>

	// Windows DirectX 11/12 Includes
	#include <d3dcompiler.h>
	#include <DirectXMath.h>

	// Vulkan
	#define VK_USE_PLATFORM_WIN32_KHR

	// Linking
	#pragma comment(lib, "dxgi.lib")
	#pragma comment(lib, "winmm.lib")
	#pragma comment(lib, "d3d11.lib")
	#pragma comment(lib, "d3d12.lib")
	#pragma comment(lib, "dxguid.lib")
	#pragma comment(lib, "user32.lib")
	#pragma comment(lib, "Ws2_32.lib")
	#pragma comment(lib, "Mswsock.lib")
	#pragma comment(lib, "winhttp.lib")
	#pragma comment(lib, "kernel32.lib")
	#pragma comment(lib, "AdvApi32.lib")
	#pragma comment(lib, "D3DCompiler.lib")
	#pragma comment(lib, "windowscodecs.lib")

	#undef _WINSOCKAPI_
	#undef _WINSOCK_DEPRECATED_NO_WARNINGS
	#undef NOMINMAX

	// Windows Macros
	#define WIN_ENABLE_CONSOLE()                            \
	{                                                       \
		AllocConsole();                                     \
		freopen_s((FILE **)stdout, "CONOUT$", "w", stdout); \
	}

#else
	#error The Weiss Engine Is Not (Yet) Supported On Your Platform
#endif

// Vulkan Includes
#include <vulkan/vulkan.h>

#pragma comment(lib, "vulkan-1.lib")

/*
 * // ////////////////////////////--\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
 * // ||------------------C++17 STL Includes------------------|| \\
 * // |\______________________________________________________/| \\
 * // \\\\\\\\\\\\\\\\\\\\\\\\\\\\--//////////////////////////// \\
 */

#include <map>
#include <list>
#include <array>
#include <queue>
#include <mutex>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <memory>
#include <bitset>
#include <numeric>
#include <codecvt>
#include <variant>
#include <fstream>
#include <sstream>
#include <iostream>
#include <optional>
#include <exception>
#include <algorithm>
#include <functional>

/*
 * // //////////////////--\\\\\\\\\\\\\\\\\\ \\
 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
 * // ||--------------UNDEFS--------------|| \\
 * // |\__________________________________/| \\
 * // \\\\\\\\\\\\\\\\\\--////////////////// \\
 */

#ifdef _CRT_SECURE_NO_WARNINGS

	#undef _CRT_SECURE_NO_WARNINGS

#endif // _CRT_SECURE_NO_WARNINGS

/*
 * // ////////////////////////////--\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
 * // ||--------------RELEASE / DEBUG MODE CHECK--------------|| \\
 * // |\______________________________________________________/| \\
 * // \\\\\\\\\\\\\\\\\\\\\\\\\\\\--//////////////////////////// \\
 */

#if defined(_NDEBUG) || defined(NDEBUG)

	#define __WEISS__RELEASE_MODE

#else // end of #if defined(_NDEBUG) || defined(NDEBUG)

	#define __WEISS__DEBUG_MODE

#endif

/*
 * // //////////////////////-\\\\\\\\\\\\\\\\\\\\\\ \\
 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
 * // ||--------------HELPER MACROS--------------|| \\
 * // |\_________________________________________/| \\
 * // \\\\\\\\\\\\\\\\\\\\\\-////////////////////// \\
 */

#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

#define VK_FAILED(vkResult) ((vkResult) != VK_SUCCESS)

#ifdef __WEISS__OS_WINDOWS

	#define DX_FAILED(hResult)  FAILED(hResult)
	#define WIN_FAILED(hResult) FAILED(hResult)

	#define WS_ERROR_MESSAGE(message) MessageBoxA(NULL, message, "Weiss Engine Error", MB_TOPMOST | MB_ICONERROR);

#endif // __WEISS__OS_WINDOWS

/*
 * // ///////////////////////-\\\\\\\\\\\\\\\\\\\\\\\ \\
 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
 * // ||--------------WEISS NAMESPACE--------------|| \\
 * // |\___________________________________________/| \\
 * // \\\\\\\\\\\\\\\\\\\\\\\-/////////////////////// \\
 *
 * The "WS" namespace contains all of Weiss's classes, functions and variables
 * in order to avoid namespace leaks and conflicts with other libraries
 */
namespace WS
{
	/*
	* // ////////////////////-\\\\\\\\\\\\\\\\\\\\ \\
	* // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
	* // ||--------------CONSTANTS--------------|| \\
	* // |\_____________________________________/| \\
	* // \\\\\\\\\\\\\\\\\\\\-//////////////////// \\
	*/

	constexpr const float PI             = 3.14159265359f;
	constexpr const float TWO_PI         = 2.0f * PI;
	constexpr const float HALF_PI        = PI / 2.0f;
	constexpr const float QUARTER_PI     = PI / 4.0f;
	constexpr const float PI_DIV_180     = PI / 180.0f;
	constexpr const float PI_DIV_180_INV = 180.0f / PI;

	constexpr const float TAU         = TWO_PI;
	constexpr const float HALF_TAU    = PI;
	constexpr const float QUARTER_TAU = HALF_PI;

	constexpr const size_t WEISS__FRAME_BUFFER_COUNT = 2u;

	/*
	* // //////////////////-\\\\\\\\\\\\\\\\\\ \\
	* // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
	* // ||--------------ENUMS--------------|| \\
	* // |\_________________________________/| \\
	* // \\\\\\\\\\\\\\\\\\-////////////////// \\
	*/

	enum class ShaderInputElementType
	{
		FLOAT_32,
		UINT_32,
		VECTOR_2D_FLOAT_32,
		VECTOR_3D_FLOAT_32,
		VECTOR_4D_FLOAT_32
	};

	enum class TextureFilter
	{
		POINT,
		BILINEAR,
		TRILINEAR
	};

	enum class PrimitiveTopology
	{
		TRIANGLES,
		TRIANGLE_STRIP
	};

	enum class RenderAPIName
	{
		DIRECTX11,
		DIRECTX12,
		VULKAN
	};

	/*
	 * We have to prexif the codes with LOG_ because the "ERROR"
	 * Keyword is defined by a windows header "wingdi.h"
	 */
	enum class LOG_TYPE {
		LOG_NORMAL,
		LOG_SUCCESS,
		LOG_WARNING,
		LOG_ERROR
	};

	struct Rect
	{ // basicly Window's RECT
		uint16_t left   = 0u;
		uint16_t top    = 0u;
		uint16_t right  = 0u;
		uint16_t bottom = 0u;

		Rect() {}

#ifdef __WEISS__OS_WINDOWS
		Rect(const RECT &rect);

		inline operator const RECT&() const noexcept { return RECT{ left, top, right, bottom }; }
#endif // __WEISS__OS_WINDOWS
	};

	struct ShaderInputElement
	{
		const char *name;
		ShaderInputElementType type;
	};

	struct Coloru8
	{
		union {
			struct
			{
				uint8_t r;
				uint8_t g;
				uint8_t b;
				uint8_t a;
			};
			struct
			{
				uint8_t red;
				uint8_t green;
				uint8_t blue;
				uint8_t alpha;
			};
		};
	};

	constexpr const Coloru8 COLOR_U8_RED   = Coloru8{ 255u, 0u,   0u,   255u };
	constexpr const Coloru8 COLOR_U8_GREEN = Coloru8{ 0u,   255u, 0u,   255u };
	constexpr const Coloru8 COLOR_U8_BLUE  = Coloru8{ 0u,   0u,   255u, 255u };
	constexpr const Coloru8 COLOR_U8_WHITE = Coloru8{ 255u, 255u, 255u, 255u };
	constexpr const Coloru8 COLOR_U8_BLACK = Coloru8{ 0u,   0u,   0u,   255u };

	struct Colorf32
	{
		/*
		 * The union of the two anonymous structs lets the caller
		 * use either shorter or longer names for the same color values
		 */
		union {
			struct
			{
				float r;
				float g;
				float b;
				float a;
			};

			struct
			{
				float red;
				float green;
				float blue;
				float alpha;
			};
		};
	};

	constexpr const Colorf32 COLOR_F32_RED   = Colorf32{1.f, 0.f, 0.f, 1.f};
	constexpr const Colorf32 COLOR_F32_GREEN = Colorf32{0.f, 1.f, 0.f, 1.f};
	constexpr const Colorf32 COLOR_F32_BLUE  = Colorf32{0.f, 0.f, 1.f, 1.f};
	constexpr const Colorf32 COLOR_F32_WHITE = Colorf32{1.f, 1.f, 1.f, 1.f};
	constexpr const Colorf32 COLOR_F32_BLACK = Colorf32{0.f, 0.f, 0.f, 1.f};

	template <typename T, size_t R, size_t C>
	class Matrix
	{
	private:
		T m[R][C] = { 0 };

	public:
		Matrix() = default;

		template <typename T2>
		Matrix(const std::initializer_list<std::initializer_list<T2>> &data);

		template <typename T2, size_t R2, size_t C2>
		Matrix(const Matrix<T2, R2, C2> &other);

#ifdef __WEISS__OS_WINDOWS

		Matrix(const DirectX::XMMATRIX &other);

#endif // __WEISS__OS_WINDOWS

		[[nodiscard]] inline size_t GetRowCount() const noexcept { return R; }

		[[nodiscard]] inline size_t GetColCount() const noexcept { return C; }

		[[nodiscard]] inline T* operator[](const size_t r) { return this->m[r]; }

		[[nodiscard]] inline T&       Get     (const size_t r, const size_t c) noexcept       { return this->m[r][c]; }
		[[nodiscard]] inline const T& GetValue(const size_t r, const size_t c) const noexcept { return this->m[r][c]; }

		[[nodiscard]] inline Matrix<T, R, C> GetTransposed() const noexcept
		{
			Matrix<T, R, C> transposed(*this);

			for (size_t r = 0u; r < R; r++)
				for (size_t c = 0u; c < C; c++)
					transposed[r][c] = this->m[c][r];

			return transposed;
		}

		template <typename T2, size_t R2, size_t C2>
		[[nodiscard]] inline bool operator==(const Matrix<T2, R2, C2> &other) const noexcept
		{
			if constexpr (R == R2 && C == C2 && std::is_same<T, T2>())
			{
				return std::memcmp(this->m, other.m, sizeof(this->m)) == 0;
			}
			else
			{
				return false;
			}
		}

#ifdef __WEISS__OS_WINDOWS

		[[nodiscard]] inline operator DirectX::XMMATRIX() const noexcept
		{
			DirectX::XMFLOAT4X4 float4x4;

			if constexpr (R == 4u && C == 4u && std::is_same<T, float>())
			{
				std::memcpy(&float4x4, this->m, sizeof(this->m));
			}
			else
			{
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
	std::ostream &operator<<(std::ostream &stream, const Matrix<T, R, C> &matrix);

	typedef Matrix<float, 3u, 3u> Mat3x3f;
	typedef Matrix<float, 4u, 4u> Mat4x4f;

	template <typename T>
	struct Vector2D
	{
		T x;
		T y;

		Vector2D() = default;

#ifdef __WEISS__OS_WINDOWS

		Vector2D(const DirectX::XMVECTOR &other);

#endif // __WEISS__OS_WINDOWS

		template <typename K>
		Vector2D(const K &n) : x(static_cast<T>(n)), y(static_cast<T>(n))
		{
		}

		template <typename K, typename L>
		Vector2D(const K &x, const L &y) : x(static_cast<T>(x)), y(static_cast<T>(y)) {}

		template <typename K>
		inline void operator+=(const Vector2D<K> &v)
		{
			this->x += v.x;
			this->y += v.y;
		}

		template <typename K>
		inline void operator-=(const Vector2D<K> &v)
		{
			this->x -= v.x;
			this->y -= v.y;
		}

		template <typename K>
		inline void operator*=(const Vector2D<K> &v)
		{
			this->x *= v.x;
			this->y *= v.y;
		}

		template <typename K>
		inline void operator/=(const Vector2D<K> &v)
		{
			this->x /= v.x;
			this->y /= v.y;
		}

		template <typename K>
		inline void operator+=(const K &n)
		{
			this->x += n;
			this->y += n;
		}

		template <typename K>
		inline void operator-=(const K &n)
		{
			this->x -= n;
			this->y -= n;
		}

		template <typename K>
		inline void operator*=(const K &n)
		{
			this->x *= n;
			this->y *= n;
		}

		template <typename K>
		inline void operator/=(const K &n)
		{
			this->x /= n;
			this->y /= n;
		}

		template <typename K>
		[[nodiscard]] inline bool operator==(const Vector2D<K> &v) { return this->x == v.x && this->y == v.y; }

		template <typename K>
		[[nodiscard]] inline bool operator!=(const Vector2D<K> &v) { return this->x != v.x || this->y != v.y; }

#ifdef __WEISS__OS_WINDOWS

		inline operator DirectX::XMVECTOR() const noexcept
		{
			return DirectX::XMVectorSet(this->x, this->y, 0.0f, 0.0f);
		}

#endif // __WEISS__OS_WINDOWS
	};

	template <typename T>
	inline std::ostream &operator<<(std::ostream &os, const Vector2D<T> &v)
	{
		os << '(' << v.x << ", " << v.y << ")";
		return os;
	}

	template <typename T, typename K>
	[[nodiscard]] inline Vector2D<T> operator+(const Vector2D<T> &a, const Vector2D<K> &b) { return Vector2D<T>{a.x + b.x, a.y + b.y}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector2D<T> operator-(const Vector2D<T> &a, const Vector2D<K> &b) { return Vector2D<T>{a.x - b.x, a.y - b.y}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector2D<T> operator*(const Vector2D<T> &a, const Vector2D<K> &b) { return Vector2D<T>{a.x * b.x, a.y * b.y}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector2D<T> operator/(const Vector2D<T> &a, const Vector2D<K> &b) { return Vector2D<T>{a.x / b.x, a.y / b.y}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector2D<T> operator+(const Vector2D<T> &v, const K &n) { return Vector2D<T>{v.x + n, v.y + n}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector2D<T> operator-(const Vector2D<T> &v, const K &n) { return Vector2D<T>{v.x - n, v.y - n}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector2D<T> operator*(const Vector2D<T> &v, const K &n) { return Vector2D<T>{v.x * n, v.y * n}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector2D<T> operator/(const Vector2D<T> &v, const K &n) { return Vector2D<T>{v.x / n, v.y / n}; }

	template <typename T>
	struct Vector3D : Vector2D<T>
	{
		T z;

		Vector3D() = default;

#ifdef __WEISS__OS_WINDOWS

		Vector3D(const DirectX::XMVECTOR &other);

#endif // __WEISS__OS_WINDOWS

		template <typename K>
		Vector3D(const K &n) : Vector2D<T>(n), z(static_cast<T>(n))
		{
		}

		template <typename K, typename L, typename M>
		Vector3D(const K &x, const L &y, const M &z) : Vector2D<T>(x, y), z(static_cast<T>(z)) {}

		template <typename T2>
		Vector3D(const Vector2D<T2> &v) : Vector2D<T>(v) {}

		template <typename K>
		inline void operator+=(const Vector2D<K> &v)
		{
			this->x += v.x;
			this->y += v.y;
		}

		template <typename K>
		inline void operator-=(const Vector2D<K> &v)
		{
			this->x -= v.x;
			this->y -= v.y;
		}

		template <typename K>
		inline void operator*=(const Vector2D<K> &v)
		{
			this->x *= v.x;
			this->y *= v.y;
		}

		template <typename K>
		inline void operator/=(const Vector2D<K> &v)
		{
			this->x /= v.x;
			this->y /= v.y;
		}

		template <typename K>
		inline void operator+=(const Vector3D<K> &v)
		{
			this->x += v.x;
			this->y += v.y;
			this->z += v.z;
		}

		template <typename K>
		inline void operator-=(const Vector3D<K> &v)
		{
			this->x -= v.x;
			this->y -= v.y;
			this->z -= v.z;
		}

		template <typename K>
		inline void operator*=(const Vector3D<K> &v)
		{
			this->x *= v.x;
			this->y *= v.y;
			this->z *= v.z;
		}

		template <typename K>
		inline void operator/=(const Vector3D<K> &v)
		{
			this->x /= v.x;
			this->y /= v.y;
			this->z /= v.z;
		}

		template <typename K>
		inline void operator+=(const K &n)
		{
			this->x += n;
			this->y += n;
			this->z += n;
		}

		template <typename K>
		inline void operator-=(const K &n)
		{
			this->x -= n;
			this->y -= n;
			this->z -= n;
		}

		template <typename K>
		inline void operator*=(const K &n)
		{
			this->x *= n;
			this->y *= n;
			this->z *= n;
		}

		template <typename K>
		inline void operator/=(const K &n)
		{
			this->x /= n;
			this->y /= n;
			this->z /= n;
		}

		template <typename K>
		[[nodiscard]] inline bool operator==(const Vector3D<K> &v) { return this->x == v.x && this->y == v.y && this->z == v.z; }

		template <typename K>
		[[nodiscard]] inline bool operator!=(const Vector3D<K> &v) { return this->x != v.x || this->y != v.y || this->z != v.z; }

#ifdef __WEISS__OS_WINDOWS

		inline operator DirectX::XMVECTOR() const noexcept
		{
			return DirectX::XMVectorSet(this->x, this->y, this->z, 0.0f);
		}

#endif // __WEISS__OS_WINDOWS
	};

	template <typename T, typename K>
	[[nodiscard]] inline Vector3D<T> operator+(const Vector3D<T> &a, const Vector2D<K> &b) { return Vector3D<T>{a.x + b.x, a.y + b.y, a.z}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector3D<T> operator-(const Vector3D<T> &a, const Vector2D<K> &b) { return Vector3D<T>{a.x - b.x, a.y - b.y, a.z}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector3D<T> operator*(const Vector3D<T> &a, const Vector2D<K> &b) { return Vector3D<T>{a.x * b.x, a.y * b.y, a.z}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector3D<T> operator/(const Vector3D<T> &a, const Vector2D<K> &b) { return Vector3D<T>{a.x / b.x, a.y / b.y, a.z}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector3D<T> operator+(const Vector3D<T> &a, const Vector3D<K> &b) { return Vector3D<T>{a.x + b.x, a.y + b.y, a.z + b.z}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector3D<T> operator-(const Vector3D<T> &a, const Vector3D<K> &b) { return Vector3D<T>{a.x - b.x, a.y - b.y, a.z - b.z}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector3D<T> operator*(const Vector3D<T> &a, const Vector3D<K> &b) { return Vector3D<T>{a.x * b.x, a.y * b.y, a.z * b.z}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector3D<T> operator/(const Vector3D<T> &a, const Vector3D<K> &b) { return Vector3D<T>{a.x / b.x, a.y / b.y, a.z / b.z}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector3D<T> operator+(const Vector3D<T> &v, const K &n) { return Vector3D<T>{v.x + n, v.y + n, v.z + n}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector3D<T> operator-(const Vector3D<T> &v, const K &n) { return Vector3D<T>{v.x - n, v.y - n, v.z - n}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector3D<T> operator*(const Vector3D<T> &v, const K &n) { return Vector3D<T>{v.x * n, v.y * n, v.z * n}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector3D<T> operator/(const Vector3D<T> &v, const K &n) { return Vector3D<T>{v.x / n, v.y / n, v.z / n}; }

	template <typename T>
	inline std::ostream &operator<<(std::ostream &os, const Vector3D<T> &v)
	{
		os << '(' << v.x << ", " << v.y << ", " << v.z << ")";
		return os;
	}

	template <typename T>
	struct Vector4D : Vector3D<T>
	{
		T w;

		Vector4D() = default;

#ifdef __WEISS__OS_WINDOWS

		Vector4D(const DirectX::XMVECTOR &other);

#endif // __WEISS__OS_WINDOWS

		template <typename K>
		Vector4D(const K &n) : Vector3D<T>(n), w(static_cast<T>(w)) {  }

		template <typename K, typename L, typename M, typename N>
		Vector4D(const K &x, const L &y, const M &z, const N &w) : Vector3D<T>(x, y, z), w(static_cast<T>(w)) {}

		template <typename T2>
		Vector4D(const Vector2D<T2> &v) : Vector2D<T>(v) {}

		template <typename T2>
		Vector4D(const Vector3D<T2> &v) : Vector3D<T>(v) {}

		template <typename K>
		inline void operator+=(const Vector4D<K> &v)
		{
			this->x += v.x;
			this->y += v.y;
			this->z += v.z;
			this->w += v.w;
		}

		template <typename K>
		inline void operator-=(const Vector4D<K> &v)
		{
			this->x -= v.x;
			this->y -= v.y;
			this->z -= v.z;
			this->w -= v.w;
		}

		template <typename K>
		inline void operator*=(const Vector4D<K> &v)
		{
			this->x *= v.x;
			this->y *= v.y;
			this->z *= v.z;
			this->w *= v.w;
		}

		template <typename K>
		inline void operator/=(const Vector4D<K> &v)
		{
			this->x /= v.x;
			this->y /= v.y;
			this->z /= v.z;
			this->w /= v.w;
		}

		template <typename K>
		inline void operator+=(const K &n)
		{
			this->x += n;
			this->y += n;
			this->z += n;
			this->w += n;
		}

		template <typename K>
		inline void operator-=(const K &n)
		{
			this->x -= n;
			this->y -= n;
			this->z -= n;
			this->w -= n;
		}

		template <typename K>
		inline void operator*=(const K &n)
		{
			this->x *= n;
			this->y *= n;
			this->z *= n;
			this->w *= n;
		}

		template <typename K>
		inline void operator/=(const K &n)
		{
			this->x /= n;
			this->y /= n;
			this->z /= n;
			this->w /= n;
		}

		template <typename K>
		[[nodiscard]] inline bool operator==(const Vector4D<K> &v)
		{
			return this->x == v.x && this->y == v.y && this->z == v.z && this->w == v.w;
		}

		template <typename K>
		[[nodiscard]] inline bool operator!=(const Vector4D<K> &v)
		{
			return this->x != v.x || this->y != v.y || this->z != v.z || this->w != v.w;
		}

#ifdef __WEISS__OS_WINDOWS

		inline operator DirectX::XMVECTOR() const noexcept
		{
			return DirectX::XMVectorSet(this->x, this->y, this->z, this->w);
		}

#endif // __WEISS__OS_WINDOWS
	};

	template <typename T, typename K>
	[[nodiscard]] inline Vector4D<T> operator+(const Vector4D<T> &a, const Vector4D<K> &b) { return Vector4D<T>{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector4D<T> operator-(const Vector4D<T> &a, const Vector4D<K> &b) { return Vector4D<T>{a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector4D<T> operator*(const Vector4D<T> &a, const Vector4D<K> &b) { return Vector4D<T>{a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector4D<T> operator/(const Vector4D<T> &a, const Vector4D<K> &b) { return Vector4D<T>{a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector4D<T> operator+(const Vector4D<T> &v, const K &n) { return Vector4D<T>{v.x + n, v.y + n, v.z + n, v.w + n}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector4D<T> operator-(const Vector4D<T> &v, const K &n) { return Vector4D<T>{v.x - n, v.y - n, v.z - n, v.w - n}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector4D<T> operator*(const Vector4D<T> &v, const K &n) { return Vector4D<T>{v.x * n, v.y * n, v.z * n, v.w * n}; }

	template <typename T, typename K>
	[[nodiscard]] inline Vector4D<T> operator/(const Vector4D<T> &v, const K &n) { return Vector4D<T>{v.x / n, v.y / n, v.z / n, v.w / n}; }

	template <typename T>
	inline std::ostream &operator<<(std::ostream &os, const Vector4D<T> &v)
	{
		os << '(' << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
		return os;
	}

	typedef Vector2D<float>    Vec2f;
	typedef Vector2D<int8_t>   Vec2i8;
	typedef Vector2D<int16_t>  Vec2i16;
	typedef Vector2D<int32_t>  Vec2i32;
	typedef Vector2D<int64_t>  Vec2i64;
	typedef Vector2D<uint8_t>  Vec2u8;
	typedef Vector2D<uint16_t> Vec2u16;
	typedef Vector2D<uint32_t> Vec2u32;
	typedef Vector2D<uint64_t> Vec2u64;

	typedef Vector3D<float>    Vec3f;
	typedef Vector3D<int8_t>   Vec3i8;
	typedef Vector3D<int16_t>  Vec3i16;
	typedef Vector3D<int32_t>  Vec3i32;
	typedef Vector3D<int64_t>  Vec3i64;
	typedef Vector3D<uint8_t>  Vec3u8;
	typedef Vector3D<uint16_t> Vec3u16;
	typedef Vector3D<uint32_t> Vec3u32;
	typedef Vector3D<uint64_t> Vec3u64;

	typedef Vector4D<float>    Vec4f;
	typedef Vector4D<int8_t>   Vec4i8;
	typedef Vector4D<int16_t>  Vec4i16;
	typedef Vector4D<int32_t>  Vec4i32;
	typedef Vector4D<int64_t>  Vec4i64;
	typedef Vector4D<uint8_t>  Vec4u8;
	typedef Vector4D<uint16_t> Vec4u16;
	typedef Vector4D<uint32_t> Vec4u32;
	typedef Vector4D<uint64_t> Vec4u64;

	struct Transform
	{
	private:
		Vec3f m_rotation;
		Vec3f m_translation;

		Mat4x4f m_transform = Mat4x4f::MakeIdentity();

	public:
		Transform() = default;

		[[nodiscard]] inline Vec3f GetRotation()    const noexcept { return this->m_rotation;    }
		[[nodiscard]] inline Vec3f GetTranslation() const noexcept { return this->m_translation; }

		inline void SetRotation   (const Vec3f &rotation)    noexcept { this->m_rotation    = rotation;    }
		inline void SetTranslation(const Vec3f &translation) noexcept { this->m_translation = translation; }

		inline void Rotate   (const Vec3f &delta) noexcept { this->m_rotation += delta; }
		inline void Translate(const Vec3f &delta) noexcept { this->m_translation += delta; }

		[[nodiscard]] inline Mat4x4f GetTransform()           const noexcept { return this->m_transform;                 }
		[[nodiscard]] inline Mat4x4f GetTransposedTransform() const noexcept { return this->m_transform.GetTransposed(); }

		void CalculateTransform() noexcept;
	};

	[[nodiscard]] inline float DegreesToRadians(const float degrees);
	[[nodiscard]] inline float RadiansToDegrees(const float radians);

	// If a polar point is stored as (θ, r)
	[[nodiscard]] inline Vec2f PolarToCartesian(const Vec2f polar);

	[[nodiscard]] inline Vec2f CartesianToPolar(const Vec2f cartesian);

	[[nodiscard]] inline Vec3f GetTriangleSurfaceNormal(const Vec3f &a, const Vec3f &b, const Vec3f &c);

	/*
	 * The "LOG" static class implements Thread Safe Logging Functions
	 * that can be colored (see LOG_TYPE enum class)
	 */ 

	class LOG
	{
	private:
		static std::mutex m_sPrintMutex;

	private:
		template <typename T>
		static void __Print(const T& message, const LOG_TYPE logType = LOG_TYPE::LOG_NORMAL);

	public:
		template <typename T>
		static inline void Print(const T& message, const LOG_TYPE logType = LOG_TYPE::LOG_NORMAL, const bool bBypassMutex = false);

		template <typename T>
		static inline void Println(const T& message, const LOG_TYPE logType = LOG_TYPE::LOG_NORMAL);

	};

	/*
	 * Any object, function or variable in the "Internal" namespace shall
	 * not be used by a user of the library and only used by the Weiss Engine
	 */

	namespace Internal
	{
		/* 
		 * We use a per platform image loading system to use
		 * their platform's preexisting libraries to improve
		 * performance and use less 3rd party libraries
		 * 
		 * This system uses a few virtual function calls but they aren't a big nuisance
		 * 
		 * Any child class shall have the following constructors :
		 * - Image()
		 * - Image(Image&& other)
		 * - Image(const Image& other)
		 * - Image(const char* filename)
		 * - Image(const uint16_t width, const uint16_t height, const Coloru8& fillColor = { 255u,255u,255u,255u })
		 * 
		 * And the following operators : 
		 * - ImageClassName& operator=(ImageClassName&& other)
		 */

		class ImageBase
		{
		protected:
			std::unique_ptr<Coloru8[]> m_buff;

			uint16_t m_width = 0, m_height = 0;
			uint32_t m_nPixels = 0;

		public:
			[[nodiscard]] inline uint16_t GetWidth()      const noexcept { return this->m_width;      }
			[[nodiscard]] inline uint16_t GetHeight()     const noexcept { return this->m_height;     }
			[[nodiscard]] inline uint32_t GetPixelCount() const noexcept { return this->m_nPixels;    }
			[[nodiscard]] inline Coloru8* GetBuffer()     const noexcept { return this->m_buff.get(); }

			[[nodiscard]] inline Coloru8  Sample(const uint16_t x, const uint16_t y) const noexcept { return this->m_buff[y * this->m_width + x]; }

			inline void Set(const uint16_t x, const uint16_t y, const Coloru8 &color) { this->m_buff[y * this->m_width + x] = color; }

			virtual void Write(const char *filename) const = 0;
		};

#ifdef __WEISS__OS_WINDOWS

		namespace WIN
		{

			class WindowsImage : public ImageBase
			{
			public:
				WindowsImage() = default;

				WindowsImage(WindowsImage &&other);

				WindowsImage(const WindowsImage &other);

				WindowsImage(const char *filename);

				WindowsImage(const uint16_t width, const uint16_t height, const Coloru8 &fillColor = {255u, 255u, 255u, 255u});

				WindowsImage& operator=(const WindowsImage& other) noexcept;

				virtual void Write(const char *filename) const override;
			};

		}; // namespace WIN

#endif // __WEISS__OS_WINDOWS

	}; // namespace Internal

#ifdef __WEISS__OS_WINDOWS

	typedef Internal::WIN::WindowsImage Image;

#endif // __WEISS__OS_WINDOWS

	// ///////////////////////////////////--\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
	// |----------------------------------------------------------------------| \\
	// |--------------------------PERIPHERAL DEVICES--------------------------| \\
	// |----------------------------------------------------------------------| \\
	// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\--/////////////////////////////////// \\

	class PeripheralDevice
	{
	public:
		virtual void __OnWindowUpdateBegin() {}
		virtual void __OnWindowUpdateEnd()   {}
	};

	class MouseEventInterface
	{
	protected:
		std::vector<std::function<void(const Vec2u16)>> m_onLeftButtonUpFunctors;
		std::vector<std::function<void(const Vec2u16)>> m_onLeftButtonDownFunctors;

		std::vector<std::function<void(const Vec2u16)>> m_onRightButtonUpFunctors;
		std::vector<std::function<void(const Vec2u16)>> m_onRightButtonDownFunctors;

		std::vector<std::function<void(const int16_t)>> m_onWheelTurnFunctors;

		std::vector<std::function<void(const Vec2u16, const Vec2i16)>> m_onMouseMoveFunctors;
		std::vector<std::function<void(const Vec2u16, const Vec2i16)>> m_onCursorMoveFunctors;

	public:
		inline void OnLeftButtonUp   (const std::function<void(Vec2u16)>& functor) noexcept { this->m_onLeftButtonUpFunctors.push_back(functor);    }
		inline void OnLeftButtonDown (const std::function<void(Vec2u16)>& functor) noexcept { this->m_onLeftButtonDownFunctors.push_back(functor);  }
		inline void OnRightButtonUp  (const std::function<void(Vec2u16)>& functor) noexcept { this->m_onRightButtonUpFunctors.push_back(functor);   }
		inline void OnRightButtonDown(const std::function<void(Vec2u16)>& functor) noexcept { this->m_onRightButtonDownFunctors.push_back(functor); }

		inline void OnWheelTurn (const std::function<void(const int16_t)> &functor)                noexcept { this->m_onWheelTurnFunctors.push_back(functor); }
		inline void OnMouseMove (const std::function<void(const Vec2u16, const Vec2i16)>& functor) noexcept { this->m_onMouseMoveFunctors.push_back(functor);  }
		inline void OnCursorMove(const std::function<void(const Vec2u16, const Vec2i16)>& functor) noexcept { this->m_onCursorMoveFunctors.push_back(functor); }
	};

	class Mouse : public MouseEventInterface
	{
	protected:
		Vec2u16 m_position      { 0, 0 };
		Vec2i16 m_deltaPosition { 0, 0 };

		int16_t m_wheelDelta = 0;

		bool m_isLeftButtonDown  = false;
		bool m_isRightButtonDown = false;

		bool m_wasMouseMovedDuringUpdate  = false;
		bool m_wasCursorMovedDuringUpdate = false;

		bool m_isCursorInWindow = false;

	public:
		Mouse() = default;

		virtual ~Mouse() = default;

		[[nodiscard]] inline bool IsLeftButtonUp()   const { return !this->m_isLeftButtonDown; }
		[[nodiscard]] inline bool IsLeftButtonDown() const { return this->m_isLeftButtonDown;  }

		[[nodiscard]] inline bool IsRightButtonUp()   const { return !this->m_isRightButtonDown; }
		[[nodiscard]] inline bool IsRightButtonDown() const { return this->m_isRightButtonDown;  }

		[[nodiscard]] inline bool IsCursorInWindow() const { return this->m_isCursorInWindow; }

		virtual inline void Show() const noexcept = 0;
		virtual inline void Hide() const noexcept = 0;

		/*
		 * Limits the mouse movements to a specific "Rect"
		 * This may be used in games to make the cursor stay
		 * inside of the window
		*/
		virtual void Clip(const Rect &rect) const noexcept = 0;
	};

	class KeyboardEventInterface
	{
	protected:
		std::vector<uint8_t> m_downKeys;

		std::vector<std::function<void(const uint8_t)>> m_onKeyUpFunctors;
		std::vector<std::function<void(const uint8_t)>> m_onKeyDownFunctors;

	public:
		inline void OnKeyUp  (const std::function<void(const uint8_t)>& functor) noexcept { this->m_onKeyUpFunctors.push_back(functor);   }
		inline void OnKeyDown(const std::function<void(const uint8_t)>& functor) noexcept { this->m_onKeyDownFunctors.push_back(functor); }
	};

	class Keyboard : public KeyboardEventInterface
	{
	protected:
		std::vector<uint8_t> m_downKeys;

	public:
		Keyboard() = default;

		virtual ~Keyboard() = default;

		[[nodiscard]] inline bool IsKeyDown(const uint8_t key) const noexcept
		{
			return this->m_downKeys.end() != std::find(this->m_downKeys.begin(), this->m_downKeys.end(), key);
		}
	};

	// //////////////////////////////////-\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
	// |-------------------------------------------------------------------| \\
	// |------------------------------WINDOWS------------------------------| \\
	// |-------------------------------------------------------------------| \\
	// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\-////////////////////////////////// \\

	struct WindowDescriptor
	{
		uint16_t width = 500u, height = 500u;
		uint16_t x = 0u;
		uint16_t y = 0u;
		const char *title = "Weiss Engine";
		const char *iconPath = nullptr;
		bool isResizable = true;
	};

	struct WindowHandle;

	class Window
	{
	protected:
		Mouse *m_pMouse = nullptr;
		Keyboard *m_pKeyboard = nullptr;

		bool m_isRunning = false;
		bool m_isMinimized = false;

		std::vector<std::function<void(const Vec2u16)>> m_onResizeFunctors;

	public:
		Window() = default;

		virtual ~Window();

		// <<<<---- Events ---->>>> \\

		inline void OnResize(const std::function<void(const Vec2u16)> &functor) noexcept { this->m_onResizeFunctors.push_back(functor); }

		// <<<<---- Getters ---->>>> \\

		[[nodiscard]] inline bool IsRunning() const noexcept { return this->m_isRunning; }

		[[nodiscard]] inline Mouse&    GetMouse()    noexcept { return *this->m_pMouse;    }
		[[nodiscard]] inline Keyboard& GetKeyboard() noexcept { return *this->m_pKeyboard; }

		[[nodiscard]] inline uint16_t GetWindowPositionX() const noexcept { return static_cast<uint16_t>(this->GetWindowRectangle().left);   }
		[[nodiscard]] inline uint16_t GetWindowPositionY() const noexcept { return static_cast<uint16_t>(this->GetWindowRectangle().top);    }
		[[nodiscard]] inline uint16_t GetClientWidth()     const noexcept { return static_cast<uint16_t>(this->GetClientRectangle().right);  }
		[[nodiscard]] inline uint16_t GetClientHeight()    const noexcept { return static_cast<uint16_t>(this->GetClientRectangle().bottom); }

		[[nodiscard]] inline uint16_t GetWindowWidth() const noexcept
		{
			const Rect rect = this->GetWindowRectangle();

			return static_cast<uint16_t>(rect.right - rect.left);
		}

		[[nodiscard]] inline uint16_t GetWindowHeight() const noexcept
		{
			const Rect rect = this->GetWindowRectangle();

			return static_cast<uint16_t>(rect.bottom - rect.top);
		}

		[[nodiscard]] virtual Rect GetWindowRectangle() const noexcept = 0;
		[[nodiscard]] virtual Rect GetClientRectangle() const noexcept = 0;

		// <<<<---- Setters ---->>>> \\

		virtual void SetWindowSize(const uint16_t width, const uint16_t height) = 0;
		virtual void SetClientSize(const uint16_t width, const uint16_t height) = 0;
		virtual void SetTitle(const char *title) const = 0;
		virtual void SetIcon (const char *pathname) = 0;

		// <<<<---- Msc ---->>>> \\

		virtual void Update() = 0;

	public:
		// To Be Defined Per Platform
		static WindowHandle Create(const WindowDescriptor &descriptor = WindowDescriptor{});
	};

	/*
	 * The "WindowHandle" struct contains a pointer to the "Window" object and handles
	 * its proper destruction in order to "free" the user of needing to avoid memory
	 * leaks when creating windows. The user can access the window's methods by using
	 * the "->" operator like he would do with a generic "Window*".
	 */
	struct WindowHandle
	{
		Window* pWindow;

		~WindowHandle() { delete pWindow; }

		inline Window *operator->() noexcept { return this->pWindow; }
		inline operator Window *()  noexcept { return this->pWindow; }
	};

#ifdef __WEISS__OS_WINDOWS

	namespace WIN
	{

		class WindowsPeripheralDevice : public PeripheralDevice
		{
		public:
			virtual bool __HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam) = 0;
		};

		class WindowsMouse : public Mouse,
							 public WindowsPeripheralDevice
		{
		public:
			WindowsMouse();

			virtual inline void Show() const noexcept override { ShowCursor(true);  }
			virtual inline void Hide() const noexcept override { ShowCursor(false); }

			virtual void Clip(const Rect &rect) const noexcept override;

			virtual void __OnWindowUpdateBegin() override;

			virtual bool __HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam) override;

			virtual void __OnWindowUpdateEnd() override;
		};

		class WindowsKeyboard : public Keyboard,
								public WindowsPeripheralDevice
		{
		public:
			virtual bool __HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam) override;
		};

		LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lparam);

		class WindowsWindow : public Window
		{
			friend LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lparam);

		private:
			HWND m_handle = 0;

		public:
			WindowsWindow(const WindowDescriptor &descriptor);

			// <<<<---- Getters ---->>>> //

			[[nodiscard]] inline HWND GetHandle()              const noexcept { return this->m_handle;        }
			[[nodiscard]] inline HDC  GetDeviceContextHandle() const noexcept { return GetDC(this->m_handle); }

			[[nodiscard]] virtual Rect GetWindowRectangle() const noexcept override;

			[[nodiscard]] virtual Rect GetClientRectangle() const noexcept override;

			// <<<<---- Setters ---->>>> //

			virtual void SetWindowSize(const uint16_t width, const uint16_t height) override;

			virtual void SetClientSize(const uint16_t width, const uint16_t height) override;

			virtual void SetTitle(const char *title) const noexcept override;

			virtual void SetIcon(const char *pathname) override;

			// <<<<---- Misc ---->>>> //

			[[nodiscard]] LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam);

			virtual void Update() override;

			void Destroy() noexcept;

			~WindowsWindow();
		};

		LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	}; // namespace WIN

#endif // __WEISS__OS_WINDOWS

	// //////////////////////////////////-\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
	// |-------------------------------------------------------------------| \\
	// |------------------------------CAMERAS------------------------------| \\
	// |-------------------------------------------------------------------| \\
	// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\-////////////////////////////////// \\

	class Camera
	{
	protected:
		Mat4x4f m_transform = Mat4x4f::MakeIdentity();

		Vec3f m_position;
		Vec3f m_rotation;

	public:
		Camera() = default;

		Camera(const Vec3f& position, const Vec3f& rotation) : m_position(position), m_rotation(rotation) { }

		[[nodiscard]] inline Mat4x4f GetTransform()           const noexcept { return this->m_transform;                 }
		[[nodiscard]] inline Mat4x4f GetTransposedTransform() const noexcept { return this->m_transform.GetTransposed(); }

		[[nodiscard]] inline const Vec3f& GetPosition() const noexcept { return this->m_position; }
		[[nodiscard]] inline const Vec3f& GetRotation() const noexcept { return this->m_rotation; }

		inline void Rotate     (const Vec3f &delta)    noexcept { this->m_rotation += delta;   }
		inline void SetRotation(const Vec3f &rotation) noexcept { this->m_rotation = rotation; }

		inline void Translate  (const Vec3f &delta)    noexcept { this->m_position += delta;   }
		inline void SetPosition(const Vec3f &position) noexcept { this->m_position = position; }

		virtual void CalculateTransform() = 0;

		virtual void HandleMouseMovements(Mouse &mouse, const float sensitivity) = 0;
		virtual void HandleKeyboardInputs(Keyboard &keyboard, const float speed, const char forward, const char backward, const char left, const char right, const char up, const char down) = 0;
	};

	struct PerspectiveCameraDescriptor
	{
		const Vec3f position;
		const Vec3f rotation;

		const float fov = 90.0f;
		const float zNear = 0.1f;
		const float zFar = 1000.0f;
	};

	class PerspectiveCamera : public Camera
	{
	private:
		const Vec3f UP_VECTOR{0.0f, 1.0f, 0.0f};
		const Vec3f FORWARD_VECTOR{0.0f, 0.0f, 1.0f};
		const Vec3f RIGHT_VECTOR{1.0f, 0.0f, 0.0f};

		Vec3f m_forwardVector = FORWARD_VECTOR;
		Vec3f m_rightVector = RIGHT_VECTOR;

		float m_fov = 0.0f, m_aspectRatio = 0.0f, m_zNear = 0.0f, m_zFar = 0.0f;

	public:
		PerspectiveCamera(Window *pWindow, const PerspectiveCameraDescriptor &descriptor);

		virtual void CalculateTransform() override;

		virtual void HandleMouseMovements(Mouse &mouse, const float sensitivity) override;

		virtual void HandleKeyboardInputs(Keyboard &keyboard, const float speed, const char forward, const char backward, const char left, const char right, const char up, const char down) override;
	};

	struct OrthographicCameraDescriptor
	{
		const Vec2f position;
		const float ratation;
	};

	class OrthographicCamera : public Camera
	{
	private:
		float m_InvAspectRatio = 0.0f;

	public:
		OrthographicCamera(Window *pWindow, const OrthographicCameraDescriptor &descriptor);

		virtual void CalculateTransform() override;

		virtual void HandleMouseMovements(Mouse &mouse, const float sensitivity) override;

		virtual void HandleKeyboardInputs(Keyboard &keyboard, const float speed, const char forward, const char backward, const char left, const char right, const char up, const char down) override;
	};

	// //////////////////////////////////////-\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
	// [/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
	// |------------------------------GENERIC BUFFERS------------------------------| \\
	// |\_________________________________________________________________________/| \\
	// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\-////////////////////////////////////// \\

	class VertexBuffer
	{
	protected:
		std::vector<int8_t> m_vertexData;

	public:
		virtual void Update() = 0;

		inline void Set(const void *buff, const size_t bufferSize) noexcept
		{
			std::memcpy(this->m_vertexData.data(), buff, bufferSize);
		}

		template <typename CONTAINER>
		inline void Set(const CONTAINER &container) noexcept
		{
			this->Set(container.data(), container.size() * sizeof(container[0]));
		}

		template <typename T>
		inline T& GetVertex(const size_t vertexIndex) noexcept
		{
			return *(((T *)(this->m_vertexData.data())) + vertexIndex);
		}

		template <typename T>
		inline void SetVertex(const size_t vertexIndex, const T &vertex) noexcept
		{
			this->GetVertex<T>(vertexIndex) = vertex;
		}
	};

	class IndexBuffer
	{
	protected:
		std::vector<uint32_t> m_indexData;

	public:
		virtual void Update() = 0;

		inline void Set(const void *buff, const size_t nIndices) noexcept
		{
			std::memcpy(this->m_indexData.data(), buff, nIndices * sizeof(uint32_t));
		}

		template <typename CONTAINER>
		inline void Set(const CONTAINER &container) noexcept
		{
			this->Set(container.data(), container.size());
		}

		inline uint32_t &GetIndex(const size_t indexIndex) noexcept
		{
			return this->m_indexData[indexIndex];
		}

		inline void SetIndex(const size_t indexIndex, const uint32_t index) noexcept
		{
			this->GetIndex(indexIndex) = index;
		}
	};

	class ConstantBuffer
	{
	protected:
		std::vector<int8_t> m_constantBufferData;

	public:
		virtual void Update() = 0;

		template <typename T>
		inline T &Get()
		{
			return *((T *)this->m_constantBufferData.data());
		}

		template <typename T>
		inline void Set(const T &obj)
		{
			this->Get<T>() = obj;
		}
	};

	// //////////////////////////////////////--\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
	// |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
	// |------------------------------GENERIC TEXTURES------------------------------| \\
	// |\__________________________________________________________________________/| \\
	// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\--////////////////////////////////////// \\

	class Texture
	{
	protected:
		Image m_image;

	public:
		virtual void Update() = 0;

		[[nodiscard]] inline const Image& GetImage() const noexcept { return this->m_image; }

		[[nodiscard]] inline void SetImage(const Image& image) noexcept { this->m_image = image; }
	};

	// ///////////////////////////////////////--\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
	// |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
	// |------------------------------GENERIC RENDER API------------------------------| \\
	// |\____________________________________________________________________________/| \\
	// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\--/////////////////////////////////////// \\

	struct Drawable
	{
		size_t pipelineIndex;
		size_t vertexBufferIndex;

		std::optional<size_t> indexBufferIndex;
	};

	struct RenderPipelineDesc
	{
		const char *vsFilename;
		std::vector<ShaderInputElement> sies;
		const char *psFilename;
		std::vector<uint32_t> constantBufferIndices;
		std::vector<uint32_t> textureIndices;
		std::vector<uint32_t> textureSamplerIndices;
		PrimitiveTopology topology = PrimitiveTopology::TRIANGLES;
	};

	class RenderAPIHandle;

	class RenderAPI
	{
	private:
		RenderAPIName m_apiName;

	protected:
		std::vector<VertexBuffer*>   m_pVertexBuffers;
		std::vector<IndexBuffer*>    m_pIndexBuffers;
		std::vector<ConstantBuffer*> m_pConstantBuffers;
		std::vector<Texture*>        m_pTextures;

	public:
		RenderAPI(const RenderAPIName &apiName) : m_apiName(apiName) {  }

		virtual ~RenderAPI() = default;

		// ----- Virtual Functions ----- //

		virtual void InitRenderAPI(Window *pWindow, const uint16_t maxFps = 144u) = 0;
		virtual void InitPipelines(const std::vector<RenderPipelineDesc> &pipelineDescs) = 0;

		virtual void Draw(const Drawable &drawable, const size_t nVertices) = 0;

		/*
		 * This structure is used to take advantage of recent rendering apis such as directx12 and vulkan.
		 * By submitting draw commands to the GPU asynchronously while other functions can be called on the cpu side
		 * (such as game logic and physics). The present method is then called to swap buffers.
		 * This is why dealing with gpu memory after calling "EndFrame()" is undefined behavior.
		 */
		virtual void BeginDrawing() = 0;
		virtual void EndDrawing()   = 0;

		virtual void Present(const bool vSync) = 0;

		virtual size_t CreateVertexBuffer  (const size_t nVertices,      const size_t vertexSize) = 0;
		virtual size_t CreateIndexBuffer   (const size_t nIndices) = 0;
		virtual size_t CreateConstantBuffer(const size_t objSize,        const size_t slot) = 0;
		virtual size_t CreateTexture       (const size_t width,          const size_t height, const size_t slot, const bool useMipmaps = false) = 0;
		virtual size_t CreateTextureSampler(const TextureFilter& filter, const size_t slot) = 0;

		virtual void Fill(const Colorf32 &color = {1.f, 1.f, 1.f, 1.f}) = 0;

		// ----- Non-Virtual Functions ----- //

		inline VertexBuffer&   GetVertexBuffer  (const size_t vertexBufferIndex)   noexcept { return *this->m_pVertexBuffers[vertexBufferIndex];     }
		inline IndexBuffer&    GetIndexBuffer   (const size_t indexBufferIndex)    noexcept { return *this->m_pIndexBuffers[indexBufferIndex];       }
		inline ConstantBuffer& GetConstantBuffer(const size_t constantBufferIndex) noexcept { return *this->m_pConstantBuffers[constantBufferIndex]; }
		inline Texture&        GetTexture       (const size_t textureIndex)        noexcept { return *this->m_pTextures[textureIndex];               }

		// ----- Non-Virtual Virtual Overloads ----- //

		inline size_t CreateVertexBuffer(const void *buff, const size_t nVertices, const size_t vertexSize)
		{
			const size_t i = this->CreateVertexBuffer(nVertices, vertexSize);

			this->GetVertexBuffer(i).Set(buff, nVertices * vertexSize);
			this->GetVertexBuffer(i).Update();

			return i;
		}

		template <typename CONTAINER>
		inline size_t CreateVertexBuffer(const CONTAINER &container)
		{
			return this->CreateVertexBuffer(container.data(), container.size() * sizeof(container[0]), sizeof(container[0]));
		}

		inline size_t CreateIndexBuffer(const void *buff, const size_t nIndices)
		{
			const size_t i = this->CreateIndexBuffer(nIndices);

			this->GetIndexBuffer(i).Set(buff, nIndices);
			this->GetIndexBuffer(i).Update();

			return i;
		}

		template <typename CONTAINER>
		inline size_t CreateIndexBuffer(const CONTAINER &container)
		{
			return this->CreateIndexBuffer(container.data(), container.size());
		}

		template <typename T>
		inline size_t CreateConstantBuffer(const T &obj, const size_t slotVS, const size_t slotPS)
		{
			const size_t constantBufferIndex = this->CreateConstantBuffer(sizeof(T), slotVS, slotPS);
			this->GetConstantBuffer(constantBufferIndex).Set(obj);
			this->GetConstantBuffer(constantBufferIndex).Update();

			return constantBufferIndex;
		}

		inline size_t CreateTexture(Image &image, const size_t slot, const bool useMipmaps = false)
		{
			const size_t textureIndex = this->CreateTexture(image.GetWidth(), image.GetHeight(), false);
			this->GetTexture(textureIndex).SetImage(image);
			this->GetTexture(textureIndex).Update();

			return textureIndex;
		}

		// ----- Getter Functions ----- //

		[[nodiscard]] RenderAPIName GetRenderAPIName() const noexcept { return this->m_apiName; }

		// ----- Creation ----- //
		static RenderAPIHandle Create(const RenderAPIName &apiName);
	};

	/*
	 * The "RenderAPIHandle" struct contains a pointer to the "RenderAPI" object and handles
	 * its proper destruction in order to "free" the user of needing to avoid memory
	 * leaks when creating a derived class of "RenderAPI". The user can access the api's methods by using
	 * the "->" operator like he would do with a generic "RenderAPI*".
	 */
	class RenderAPIHandle
	{
	private:
		RenderAPI *m_pRenderAPI = nullptr;

	public:
		RenderAPIHandle() = default;
		RenderAPIHandle(RenderAPI* pRenderAPI) : m_pRenderAPI(pRenderAPI) {  }

		~RenderAPIHandle() { delete this->m_pRenderAPI; }

		inline operator RenderAPI*  () noexcept { return this->m_pRenderAPI; }
		inline RenderAPI* operator->() noexcept { return this->m_pRenderAPI; }
	};

	// //////////////////////////////////--\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
	// |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
	// ||------------------------------VULKAN-----------------------------|| \\
	// |\_________________________________________________________________/| \\
	// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\--///////////////////////////////// \\

	namespace Internal {

		namespace VK {

			class VKTextureSampler
			{

			};

			/*
			* To prevent a "use after free" (and many mental breakdowns) please overload
			* the "void operator=" function with an r-value reference (like the one for this class)
			* in any class that inherits from this base class.
			*/
			template <typename T>
			class VKObjectWrapper
			{
			public:
				T m_object = VK_NULL_HANDLE;

			public:
				VKObjectWrapper() = default;

				VKObjectWrapper(T& obj) : m_object(obj) {  }

				~VKObjectWrapper() { this->m_object = VK_NULL_HANDLE; }

				VKObjectWrapper<T> &operator=(VKObjectWrapper<T>&& other) noexcept;

				inline       T* GetPtr()       noexcept { return &this->m_object; }
				inline const T* GetPtr() const noexcept { return &this->m_object; }
				inline T* operator->()   const noexcept { return &this->m_object; }

				inline operator       T&()       noexcept { return this->m_object; }
				inline operator const T&() const noexcept { return this->m_object; }
			};

			typedef VKObjectWrapper<VkInstance> VKInstanceObjectWrapper;

			class VKInstance : public VKInstanceObjectWrapper
			{
			public:
				VKInstance() = default;

				VKInstance(const char *appName);

				VKInstance &operator=(VKInstance &&instance) noexcept;

				~VKInstance();

			private:
				static std::vector<VkExtensionProperties> GetAvailableExtensionsPropreties();

				static std::vector<const char *> GetRequiredExtensions() noexcept;
			};

			typedef VKObjectWrapper<VkSurfaceKHR> VKSurfaceObjectWrapper;

			class VKSurface : public VKSurfaceObjectWrapper
			{
			private:
				VKInstance *m_pInstance = nullptr;

				Vec2u16 m_dimensions{0u, 0u};

			public:
				VKSurface() = default;

				VKSurface(VKInstance *pInstance, Window *pWindow);

				VKSurface &operator=(VKSurface &&other) noexcept;

				[[nodiscard]] inline const Vec2u16& GetDimensions() const noexcept { return this->m_dimensions; }

				~VKSurface();
			};

			typedef VKObjectWrapper<VkSemaphore> VKSemaphoreObjectWrapper;

			class VKDevice;

			class VKSemaphore : public VKSemaphoreObjectWrapper
			{
			private:
				const VKDevice *m_pDevice = nullptr;

			public:
				VKSemaphore() = default;

				VKSemaphore(const VKDevice& device);

				VKSemaphore& operator=(VKSemaphore &&other) noexcept;

				~VKSemaphore();
			};

			class VKSwapChain;

			typedef VKObjectWrapper<VkRenderPass> VKRenderPassObjectWrapper;

			class VKRenderPass
			{
			public:
				static VkRenderPass s_colorRenderPass;

			public:
				static void CreateRenderPasses(const VKDevice &device, const VKSwapChain &swapChain);

				static void DestroyRenderPasses(const VKDevice &device);
			};

			typedef VKObjectWrapper<VkSwapchainKHR> VKSwapChainObjectWrapper;

			class VKDevice;
			class VKQueue;

			class VKSwapChain : public VKSwapChainObjectWrapper
			{
			private:
				uint32_t m_nImages = 0u;

				std::vector<VkImage> m_images;
				std::vector<VkImageView> m_imageViews;

				std::vector<VkFramebuffer> m_colorFrameBuffers;

				VkSurfaceFormatKHR m_surfaceFormat;

				VKDevice *m_pDevice = nullptr;
				VKSurface *m_pSurface = nullptr;

				VkExtent2D m_imageExtent2D;

				uint32_t m_currentImageIndex = 0u;

				const VKQueue* m_pPresentQueue;

			public:
				VKSwapChain() = default;

				VKSwapChain(VKDevice &pDevice, VKSurface &pSurface);

				VKSwapChain &operator=(VKSwapChain &&other) noexcept;

				void CreateFrameBuffers();

				void GetNextImage();

				void Present();

				[[nodiscard]] inline uint32_t           GetCurrentImageIndex()                       const noexcept { return this->m_currentImageIndex;             }
				[[nodiscard]] inline VkExtent2D         GetImageExtent()                             const noexcept { return this->m_imageExtent2D;                 }
				[[nodiscard]] inline VkSurfaceFormatKHR GetFormat()                                  const noexcept { return this->m_surfaceFormat;                 }
				[[nodiscard]] inline VkFramebuffer      GetColorFrameBuffer(const size_t frameIndex) const noexcept { return this->m_colorFrameBuffers[frameIndex]; }

				~VKSwapChain();

			private:
				VkPresentModeKHR PickPresentingMode() const;

				VkSurfaceFormatKHR PickSurfaceFormat() const;

				void CreateSwapChain();

				void CreateImagesAndViews();
			};

			typedef VKObjectWrapper<VkCommandPool> VKCommandPoolObjectWrapper;

			class VKCommandPool : public VKCommandPoolObjectWrapper
			{
			private:
				const VKDevice *m_pDevice = nullptr;

			public:
				VKCommandPool() = default;

				VKCommandPool(const VKDevice &device, const uint32_t queueFamilyIndex);

				VKCommandPool &operator=(VKCommandPool &&other) noexcept;

				~VKCommandPool();
			};

			typedef VKObjectWrapper<VkCommandBuffer> VKCommandBufferObjectWrapper;

			class VKDevice;
			class VKSwapChain;
			class VKCommandPool;

			class VKCommandBuffer : public VKCommandBufferObjectWrapper
			{
			private:
				const VKDevice *m_pDevice = nullptr;

				const VKQueue* m_pGraphicsQueue;

			public:
				VKCommandBuffer() = default;

				VKCommandBuffer(const VKDevice &device, const VKCommandPool &commandPool);

				VKCommandBuffer &operator=(VKCommandBuffer &&other) noexcept;

				void BeginRecording() const;

				void BeginRenderPass(const VKSwapChain &swapChain, const VkFramebuffer &frameBuffer, const VkRenderPass &renderPass) const noexcept;

				void BeginColorRenderPass(const VKSwapChain &swapChain) const noexcept;

				void EndRenderPass();

				void EndRecording() const;

				void Submit(const VKSemaphore& swapChainImageAvailableSemaphore) const;

				~VKCommandBuffer() = default;
			};

			class VKDevice;
			class VKSemaphore;
			class VKCommandBuffer;

			typedef VKObjectWrapper<VkQueue> VKQueueObjectWrapper;

			class VKQueue : public VKQueueObjectWrapper
			{
			public:
				VKSemaphore m_semaphore;

			public:
				VKQueue() = default;

				VKQueue(VKDevice &device, const size_t queueIndex);

				void Submit(const std::vector<VkCommandBuffer> &commandBuffers) const;

				VKQueue& operator=(VKQueue &&other) noexcept;
			};

			struct VKPhysicalDeviceDataWrapper
			{
				VkPhysicalDevice m_physicalDevice;
				VkPhysicalDeviceFeatures m_features;
				VkPhysicalDeviceProperties m_propreties;
				std::vector<VkQueueFamilyProperties> m_queueFamilyPropreties;
				std::vector<VkExtensionProperties> m_extensionPropreties;

				union {
					struct
					{
						std::optional<uint32_t> m_graphicsQueueIndex;
						std::optional<uint32_t> m_presentQueueIndex;
					};
					struct
					{
						std::optional<uint32_t> m_queueIndices[2];
					};
				};

				uint32_t m_rating = 0u;

				VKPhysicalDeviceDataWrapper() { }

				VKPhysicalDeviceDataWrapper(const VkPhysicalDevice &physicalDevice, const VKSurface &surface);
			};

			typedef VKObjectWrapper<VkDevice> VKDeviceObjectWrapper;

			class VKDevice : public VKDeviceObjectWrapper
			{
			private:
				VKPhysicalDeviceDataWrapper m_physicalDeviceData;

				union {
					struct
					{
						VKQueue m_graphicsQueue, m_presentQueue;
					};
					struct
					{
						std::array<VKQueue, 2u> m_queues;
					};
				};

			public:
				VKDevice() {  }

				VKDevice(const VKInstance &instance, const VKSurface &surface);

				VKDevice &operator=(VKDevice &&device) noexcept;

				[[nodiscard]] inline const VKQueue* GetGraphicsQueuePtr() const noexcept { WS::LOG::Println(this->m_graphicsQueue.m_object); return &this->m_graphicsQueue; }
				[[nodiscard]] inline const VKQueue* GetPresentQueuePtr()  const noexcept { WS::LOG::Println(this->m_presentQueue.m_object); return &this->m_presentQueue;  }
				[[nodiscard]] inline const VKPhysicalDeviceDataWrapper& GetPhysicalDeviceData() const noexcept { return this->m_physicalDeviceData; }

				~VKDevice() {}

			private:
				void PickPhysicalDevice(const VKInstance &instance, const VKSurface &surface);

				void CreateLogicalDeviceAndQueues(const VKInstance &instance);

				static std::vector<const char *> GetRequiredExtensions() noexcept;
			};

			class VKRenderPipeline
			{
			private:
				const VKDevice *m_pDevice = nullptr;

				VkPipelineLayout m_layout = VK_NULL_HANDLE;
				VkPipeline m_pipeline = VK_NULL_HANDLE;

			public:
				VKRenderPipeline() = default;

				VKRenderPipeline &operator=(VKRenderPipeline &&other);

				VKRenderPipeline(const VKDevice &device, const VKSwapChain &swapChain, const RenderPipelineDesc &pipelineDesc,
								std::vector<ConstantBuffer *> &pConstantBuffers, std::vector<Texture *> pTextures, std::vector<VKTextureSampler *> pTextureSamplers);
				
				~VKRenderPipeline();

			private:
				static VkShaderModule CreateShaderModule(const VKDevice &device, const char *filename);
			};

			class VKRenderAPI : public RenderAPI
			{
			private:
				VKInstance m_instance;
				VKSurface m_surface;
				VKDevice m_device;
				VKSwapChain m_swapChain;
				VKCommandPool m_commandPool;
				VKCommandBuffer m_commandBuffer;

			public:
				VKRenderAPI() : RenderAPI(RenderAPIName::VULKAN) {  }

				~VKRenderAPI();

				virtual void InitRenderAPI(Window *pWindow, const uint16_t maxFps) override;

				virtual void InitPipelines(const std::vector<RenderPipelineDesc> &pipelineDescs) override;

				virtual void Draw(const Drawable &drawable, const size_t nVertices) override;

				virtual void BeginDrawing() override;
				virtual void EndDrawing()   override;

				virtual void Present(const bool vSync) override;

				virtual size_t CreateVertexBuffer  (const size_t nVertices,      const size_t vertexSize) override;
				virtual size_t CreateIndexBuffer   (const size_t nIndices) override;
				virtual size_t CreateConstantBuffer(const size_t objSize,        const size_t slot) override;
				virtual size_t CreateTexture       (const size_t width,          const size_t height, const size_t slot, const bool useMipmaps = false) override;
				virtual size_t CreateTextureSampler(const TextureFilter& filter, const size_t slot) override;

				virtual void Fill(const Colorf32 &color = {1.f, 1.f, 1.f, 1.f}) override;
			};
		}; // VK

#ifdef __WEISS__OS_WINDOWS

		namespace D3D11
		{
			/*
			* To prevent a "use after free" (and many mental breakdowns) please overload the "void operator=" function with an r-value reference (like the one for this class)
			* in any class that inherits from this base class.
			*/
			template <typename T>
			class D3D11ObjectWrapper
			{
			protected:
				T *m_pObject = nullptr;

			public:
				D3D11ObjectWrapper() = default;

				/* This function overloads the assignement operator with an r-value reference to itself
				* It copies the pointer from the "other" and sets it to nullptr.
				* This is done to ensure that the resource isn't freed while this object is being created.
				* (Preventing a "use after free")
				*/
				D3D11ObjectWrapper<T> &operator=(D3D11ObjectWrapper<T> &&other);

				virtual ~D3D11ObjectWrapper();

				inline T*  Get()    noexcept { return this->m_pObject;  }
				inline T** GetPtr() noexcept { return &this->m_pObject; }

				inline T* operator->() noexcept { return this->m_pObject; }
				inline operator T*  () noexcept { return this->m_pObject; }
			};

			typedef D3D11ObjectWrapper<ID3D11Device> D3D11DeviceObjectWrapper;
			typedef D3D11ObjectWrapper<ID3D11DeviceContext> D3D11DeviceContextObjectWrapper;

			typedef D3D11ObjectWrapper<IDXGISwapChain> D3D11SwapChainObjectWrapper;

			class D3D11SwapChain : public D3D11SwapChainObjectWrapper
			{
			public:
				D3D11SwapChain() = default;

				D3D11SwapChain(D3D11DeviceObjectWrapper &pDevice, Window *pWindow);

				D3D11SwapChain &operator=(D3D11SwapChain &&other) noexcept;

				void Present(const bool vSync);
			};

			typedef D3D11ObjectWrapper<ID3D11RenderTargetView> D3D11RenderTargetbjectWrapper;

			class D3D11RenderTarget : public D3D11RenderTargetbjectWrapper
			{
			public:
				D3D11RenderTarget() = default;

				D3D11RenderTarget(D3D11DeviceObjectWrapper &pDevice, D3D11SwapChainObjectWrapper &pSwapChain);

				D3D11RenderTarget &operator=(D3D11RenderTarget &&other) noexcept;

				void SetCurrent(D3D11DeviceContextObjectWrapper &pDeviceContext) const noexcept;
			};

			class D3D11DepthBuffer
			{
			private:
				Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;
				Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_pDepthStencilState;

			public:
				D3D11DepthBuffer() = default;

				D3D11DepthBuffer(Window *pWindow, D3D11DeviceObjectWrapper &pDevice);

				void Clear(D3D11DeviceContextObjectWrapper &pDeviceContext);

				void Bind(D3D11DeviceContextObjectWrapper &pDeviceContext, D3D11RenderTargetbjectWrapper &pRenderTarget);
			};

			class D3D11VertexShader
			{
			private:
				Microsoft::WRL::ComPtr<ID3D11VertexShader> m_pShader;
				Microsoft::WRL::ComPtr<ID3D11InputLayout>  m_pInputLayout;

				D3D11DeviceContextObjectWrapper *m_pDeviceContext = nullptr;

			public:
				D3D11VertexShader() = default;

				D3D11VertexShader(D3D11DeviceObjectWrapper &pDevice,
								D3D11DeviceContextObjectWrapper *pDeviceContext,
								const char *sourceFilename, const std::vector<ShaderInputElement> &sies);

				void Bind() const noexcept;
			};

			class D3D11PixelShader
			{
			private:
				Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pShader;

				D3D11DeviceContextObjectWrapper *m_pDeviceContext = nullptr;

			public:
				D3D11PixelShader() = default;

				D3D11PixelShader(D3D11DeviceObjectWrapper &pDevice,
								D3D11DeviceContextObjectWrapper *pDeviceContext,
								const char *sourceFilename);

				void Bind() const noexcept;
			};

			typedef D3D11ObjectWrapper<ID3D11Buffer> D3D11VertexBufferObjectWrapper;
			typedef D3D11ObjectWrapper<ID3D11Buffer> D3D11IndexBufferObjectWrapper;
			typedef D3D11ObjectWrapper<ID3D11Buffer> D3D11ConstantBufferObjectWrapper;

			class D3D11VertexBuffer : public D3D11VertexBufferObjectWrapper,
									public VertexBuffer
			{
			private:
				size_t m_vertexSize = 0u;

				D3D11DeviceContextObjectWrapper *m_pDeviceContext = nullptr;

			public:
				D3D11VertexBuffer() = default;

				D3D11VertexBuffer(D3D11DeviceObjectWrapper &pDevice,
								D3D11DeviceContextObjectWrapper *pDeviceContext,
								const size_t nVertices, const size_t vertexSize);

				D3D11VertexBuffer &operator=(D3D11VertexBuffer &&other) noexcept;

				void Bind();

				virtual void Update() override;
			};

			class D3D11IndexBuffer : public D3D11IndexBufferObjectWrapper,
									public IndexBuffer
			{
			private:
				size_t m_nIndices = 0u;

				D3D11DeviceContextObjectWrapper *m_pDeviceContext = nullptr;

			public:
				D3D11IndexBuffer() = default;

				D3D11IndexBuffer(D3D11DeviceObjectWrapper &pDevice,
								D3D11DeviceContextObjectWrapper *pDeviceContext,
								const size_t nIndices);

				D3D11IndexBuffer& operator=(D3D11IndexBuffer &&other) noexcept;

				void Bind();

				virtual void Update() override;
			};

			class D3D11ConstantBuffer : public D3D11ConstantBufferObjectWrapper,
										public ConstantBuffer
			{
			private:
				size_t m_objSize = 0u;

				size_t m_slot = 0u;

				D3D11DeviceContextObjectWrapper *m_pDeviceContext = nullptr;

			public:
				D3D11ConstantBuffer() = default;

				D3D11ConstantBuffer(D3D11DeviceObjectWrapper &pDevice,
									D3D11DeviceContextObjectWrapper *pDeviceContext,
									const size_t objSize, const size_t slot);

				D3D11ConstantBuffer &operator=(D3D11ConstantBuffer &&other) noexcept;

				void Bind();

				virtual void Update() override;
			};

			typedef D3D11ObjectWrapper<ID3D11ShaderResourceView> D3D11TextureObjectWrapper;

			class D3D11Texture : public Texture,
								public D3D11TextureObjectWrapper
			{
			private:
				D3D11DeviceObjectWrapper *m_pDevice = nullptr;
				D3D11DeviceContextObjectWrapper *m_pDeviceContext = nullptr;

				size_t m_slot = 0u;

				Microsoft::WRL::ComPtr<ID3D11Texture2D> m_texture2D;

				bool m_useMipmaps;

			public:
				D3D11Texture() = default;

				D3D11Texture(D3D11DeviceObjectWrapper &pDevice,
							D3D11DeviceContextObjectWrapper *pDeviceContext,
							const size_t width, const size_t height, const size_t slot, const bool useMipmaps);

				void Bind() const noexcept;

				virtual void Update() override;
			};

			typedef D3D11ObjectWrapper<ID3D11SamplerState> D3D11SamplerStateObjectWrapper;

			class D3D11TextureSampler : public D3D11SamplerStateObjectWrapper
			{
			private:
				D3D11DeviceContextObjectWrapper *m_pDeviceContext = nullptr;

				size_t m_slot = 0u;

			public:
				D3D11TextureSampler() = default;

				D3D11TextureSampler(D3D11DeviceObjectWrapper &pDevice,
									D3D11DeviceContextObjectWrapper *pDeviceContext,
									const TextureFilter &filter, const size_t slot);

				void Bind() const noexcept;
			};

			class D3D11RenderPipeline
			{
			private:
				D3D11VertexShader m_pVertexShader;
				D3D11PixelShader m_pPixelShader;
				D3D11_PRIMITIVE_TOPOLOGY m_topology;

				D3D11DeviceContextObjectWrapper *m_pDeviceContext;

				std::vector<uint32_t> m_constantBufferIndices;
				std::vector<uint32_t> m_textureIndices;
				std::vector<uint32_t> m_textureSamplerIndices;

			public:
				D3D11RenderPipeline(D3D11DeviceObjectWrapper &pDevice,
									D3D11DeviceContextObjectWrapper *m_pDeviceContext,
									const RenderPipelineDesc &desc);

				void Bind(std::vector<ConstantBuffer *> &constantBuffers,
						std::vector<Texture *> &textures,
						std::vector<D3D11TextureSampler *> textureSamplers) noexcept;
			};

			class D3D11RenderPipeline;

			class D3D11RenderAPI : public RenderAPI
			{
			private:
				D3D11DeviceObjectWrapper m_pDevice;
				D3D11DeviceContextObjectWrapper m_pDeviceContext;
				D3D11SwapChain m_pSwapChain;
				D3D11RenderTarget m_pRenderTarget;
				D3D11DepthBuffer m_pDepthBuffer;

				std::vector<D3D11RenderPipeline> m_pRenderPipelines;
				std::vector<D3D11TextureSampler *> m_pTextureSamplers;

			public:
				D3D11RenderAPI() : RenderAPI(RenderAPIName::DIRECTX11) {}

				virtual void InitRenderAPI(Window *pWindow, const uint16_t maxFps) override;

				virtual void InitPipelines(const std::vector<RenderPipelineDesc> &pipelineDescs) override;

				virtual void Draw(const Drawable &drawable, const size_t nVertices) override;

				virtual void BeginDrawing() override;
				virtual void EndDrawing()   override;

				virtual void Present(const bool vSync) override;

				virtual size_t CreateVertexBuffer  (const size_t nVertices,      const size_t vertexSize) override;
				virtual size_t CreateIndexBuffer   (const size_t nIndices) override;
				virtual size_t CreateConstantBuffer(const size_t objSize,        const size_t slot) override;
				virtual size_t CreateTexture       (const size_t width,          const size_t height, const size_t slot, const bool useMipmaps = false) override;
				virtual size_t CreateTextureSampler(const TextureFilter& filter, const size_t slot) override;

				virtual void Fill(const Colorf32 &color = {1.f, 1.f, 1.f, 1.f}) override;
			};

		}; // namespace D3D11

		#endif // __WEISS__OS_WINDOWS

		#ifdef __WEISS__OS_WINDOWS

		namespace D3D12
		{

			/*
			* To prevent a "use after free" (and many mental breakdowns) please overload the "void operator=" function with an r-value reference (like the one for this class)
			* in any class that inherits from this base class.
			*/
			template <typename T>
			class D3D12ObjectWrapper
			{
			protected:
				T* m_pObject = nullptr;

			public:
				D3D12ObjectWrapper() = default;

				/* This function overloads the assignement operator with an r-value reference to itself
				* It copies the pointer from the "other" and sets it to nullptr.
				* This is done to ensure that the resource isn't freed while this object is being created.
				* (Preventing a "use after free")
				*/
				D3D12ObjectWrapper& operator=(D3D12ObjectWrapper<T> &&other) noexcept;

				~D3D12ObjectWrapper();

				[[nodiscard]] inline T*  operator->() noexcept { return this->m_pObject;  }
				[[nodiscard]] inline T*  Get()        noexcept { return this->m_pObject;  }
				[[nodiscard]] inline T** GetPtr()     noexcept { return &this->m_pObject; }

				[[nodiscard]] inline operator IUnknown* () const noexcept { return (IUnknown *)this->m_pObject; }
				[[nodiscard]] inline operator T*        () const noexcept { return this->m_pObject;             }
			};

			typedef D3D12ObjectWrapper<IDXGIAdapter1> D3D12AdapterObjectWrapper;

			class D3D12Adapter : public D3D12AdapterObjectWrapper
			{
			public:
				D3D12Adapter();

				D3D12Adapter& operator=(D3D12Adapter&& other) noexcept;
			};

			typedef D3D12ObjectWrapper<ID3D12Device2> D3D12DeviceObjectWrapper;

			class D3D12Device : public D3D12DeviceObjectWrapper
			{
			public:
				D3D12Device() = default;

				D3D12Device(D3D12AdapterObjectWrapper &pAdapter);

				D3D12Device &operator=(D3D12Device &&other) noexcept;
			};

			typedef D3D12ObjectWrapper<ID3D12Fence> D3D12FenceObjectWrapper;

			class D3D12Fence : public D3D12FenceObjectWrapper
			{
			private:
				HANDLE m_fenceEvent = nullptr;

			public:
				D3D12Fence() = default;

				D3D12Fence(D3D12DeviceObjectWrapper &pDevice, const UINT64 initialValue, const D3D12_FENCE_FLAGS flags);

				~D3D12Fence();

				D3D12Fence &operator=(D3D12Fence &&other) noexcept;

				[[nodiscard]] inline HANDLE GetEvent() const noexcept { return this->m_fenceEvent; }
			};

			typedef D3D12ObjectWrapper<ID3D12CommandQueue> D3D12CommandQueueObjectWrapper;

			class D3D12CommandQueue : public D3D12CommandQueueObjectWrapper
			{
			public:
				D3D12CommandQueue() = default;

				D3D12CommandQueue(D3D12DeviceObjectWrapper &pDevice, const D3D12_COMMAND_LIST_TYPE& type);
			};

			typedef D3D12ObjectWrapper<IDXGISwapChain3> D3D12SwapChainObjectWrapper;

			class D3D12SwapChain : public D3D12SwapChainObjectWrapper
			{
			public:
				D3D12SwapChain() = default;

				D3D12SwapChain(D3D12DeviceObjectWrapper &pDevice,
							D3D12CommandQueueObjectWrapper &pCommandQueue,
							const Window *pWindow, const uint16_t maxFps, const UINT bufferCount);

				D3D12SwapChain &operator=(D3D12SwapChain &&other) noexcept;

				void Present(const bool vSync) const;

			private:
				static bool IsTearingSupported();
			};

			typedef D3D12ObjectWrapper<ID3D12DescriptorHeap> D3D12DescriptorHeapObjectWrapper;

			class D3D12DescriptorHeap : public D3D12DescriptorHeapObjectWrapper
			{
			public:
				D3D12DescriptorHeap() = default;

				D3D12DescriptorHeap(D3D12DeviceObjectWrapper &pDevice, const D3D12_DESCRIPTOR_HEAP_TYPE type,
									const uint32_t numDescriptors, const D3D12_DESCRIPTOR_HEAP_FLAGS &flags = D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_NONE);

				D3D12DescriptorHeap &operator=(D3D12DescriptorHeap &&other) noexcept;
			};

			typedef D3D12ObjectWrapper<ID3D12Resource> D3D12RenderTargetObjectWrapper;

			class D3D12RenderTarget : public D3D12RenderTargetObjectWrapper
			{
			public:
				D3D12RenderTarget() = default;

				D3D12RenderTarget(D3D12DeviceObjectWrapper &pDevice,
								D3D12SwapChainObjectWrapper &pSwapChain,
								D3D12DescriptorHeapObjectWrapper &pDescriptorHeap,
								const CD3DX12_CPU_DESCRIPTOR_HANDLE &rtvHandle,
								const uint16_t frameIndex);

				D3D12RenderTarget &operator=(D3D12RenderTarget &&other) noexcept;
			};

			typedef D3D12ObjectWrapper<ID3D12CommandAllocator> D3D12CommandAllocatorObjectWrapper;

			class D3D12CommandAllocator : public D3D12CommandAllocatorObjectWrapper
			{
			public:
				D3D12CommandAllocator() = default;

				D3D12CommandAllocator(D3D12DeviceObjectWrapper &pDevice, const D3D12_COMMAND_LIST_TYPE& type);

				void Reset() const;
			};

			typedef D3D12ObjectWrapper<ID3D12GraphicsCommandList> D3D12CommandListObjectWrapper;

			class D3D12CommandList : public D3D12CommandListObjectWrapper
			{
			public:
				D3D12CommandList() = default;

				D3D12CommandList(D3D12DeviceObjectWrapper& pDevice,
								D3D12CommandAllocatorObjectWrapper& pCommandAllocator,
								const D3D12_COMMAND_LIST_TYPE& type);

				~D3D12CommandList() = default;

				D3D12CommandList &operator=(D3D12CommandList &&other) noexcept;

				void Close();

				void Reset(D3D12CommandAllocatorObjectWrapper &pCommandAllocator) const;
				
				void TransitionResource(ID3D12Resource *pResource, const D3D12_RESOURCE_STATES &before, const D3D12_RESOURCE_STATES &after);
			};

			class D3D12DepthBuffer
			{
			private:
				D3D12ObjectWrapper<ID3D12DescriptorHeap> m_pDescriptorHeap;
				D3D12ObjectWrapper<ID3D12Resource>       m_pDepthStencilBuffer;

				CD3DX12_CPU_DESCRIPTOR_HANDLE m_dsvHandle;

			public:
				D3D12DepthBuffer() = default;

				D3D12DepthBuffer(D3D12Device& pDevice, Window* pWindow);

				void Clear(D3D12CommandListObjectWrapper &pCommandList);

				operator CD3DX12_CPU_DESCRIPTOR_HANDLE *() noexcept;
			};

			typedef D3D12ObjectWrapper<ID3D12RootSignature> D3D12RootSignatureObjectWrapper;

			class D3D12RootSignature : public D3D12RootSignatureObjectWrapper
			{
			public:
				D3D12RootSignature() = default;

				D3D12RootSignature(D3D12DeviceObjectWrapper &pDevice, const D3D12_ROOT_SIGNATURE_FLAGS &flags,
								const std::vector<D3D12_ROOT_PARAMETER1> &rootParameters, const std::vector<D3D12_STATIC_SAMPLER_DESC> &samplers);

				D3D12RootSignature &operator=(D3D12RootSignature &&other) noexcept;
			};

			typedef D3D12ObjectWrapper<ID3D12Resource> D3D12CommittedResourceObjectWrapper;

			class D3D12CommittedResource : public D3D12CommittedResourceObjectWrapper
			{
			private:
				D3D12_RESOURCE_STATES m_originalState = D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_COMMON;
				D3D12_RESOURCE_STATES m_currentState = D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_COMMON;

			public:
				D3D12CommittedResource() = default;

				D3D12CommittedResource(D3D12DeviceObjectWrapper &pDevice, const D3D12_HEAP_TYPE &heapType,
									const D3D12_HEAP_FLAGS &flags, const D3D12_RESOURCE_DESC *descPtr,
									const D3D12_RESOURCE_STATES &states, const char *name = "(PLACEHOLDER NAME)");

				D3D12CommittedResource &operator=(D3D12CommittedResource &&other) noexcept;

				inline void TransitionTo(D3D12CommandListObjectWrapper& pCommandList, const D3D12_RESOURCE_STATES& state) noexcept
				{
					pCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(this->m_pObject, this->m_currentState, state));

					this->m_currentState = state;
				}

				inline void TransitionBack(D3D12CommandListObjectWrapper& pCommandList) noexcept
				{
					this->TransitionTo(pCommandList, this->m_originalState);
				}
			};

			class D3D12VertexBuffer : public VertexBuffer
			{
			private:
				D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

				D3D12CommittedResource m_pVertexBuffer;
				D3D12CommittedResource m_pUploadHeap;

				UINT m_vertexSize = 0u;

				D3D12CommandList *m_pCommandList = nullptr;

			public:
				D3D12VertexBuffer() = default;

				D3D12VertexBuffer(D3D12DeviceObjectWrapper &pDevice,
								D3D12CommandList *pCommandList,
								const size_t nVertices, const size_t vertexSize);

				void Bind();

				virtual void Update() override;
			};

			class D3D12IndexBuffer : public IndexBuffer
			{
			private:
				D3D12_INDEX_BUFFER_VIEW m_indexBufferView;

				D3D12CommittedResource m_pIndexBuffer;
				D3D12CommittedResource m_pUploadHeap;

				size_t m_nIndices = 0u;

				D3D12CommandList *m_pCommandList = nullptr;

			public:
				D3D12IndexBuffer() = default;

				D3D12IndexBuffer(D3D12DeviceObjectWrapper &pDevice,
								D3D12CommandList *pCommandList,
								const size_t nIndices);

				void Bind();

				virtual void Update() override;
			};

			class D3D12ConstantBuffer : public ConstantBuffer
			{
			private:
				size_t m_objSize = 0u;

				size_t m_slot = 0u;

				D3D12CommandList *m_pCommandList;

				std::array<D3D12DescriptorHeap, WEISS__FRAME_BUFFER_COUNT> m_descriptorHeaps;
				std::array<D3D12_CONSTANT_BUFFER_VIEW_DESC, WEISS__FRAME_BUFFER_COUNT> m_constantBufferViews;
				std::array<D3D12CommittedResource, WEISS__FRAME_BUFFER_COUNT> m_pUploadHeaps;

				std::array<bool, WEISS__FRAME_BUFFER_COUNT> m_bNeedsUpdating;

			public:
				D3D12ConstantBuffer() = default;

				D3D12ConstantBuffer(D3D12DeviceObjectWrapper &pDevice,
									D3D12CommandList *pCommandList,
									const size_t objSize, const size_t slot);

				[[nodiscard]] inline D3D12DescriptorHeap& GetDescriptorHeap(const size_t frameIndex) { return this->m_descriptorHeaps[frameIndex]; }

				[[nodiscard]] inline size_t GetSlot() const noexcept { return this->m_slot; }

				void UpdateIfNeeded(const size_t frameIndex);

				virtual void Update() override;

			private:
				void UpdateHeap(const size_t heapIndex);
			};

			class D3D12Texture : public Texture
			{
			private:
				D3D12CommittedResource m_textureResource;
				D3D12CommittedResource m_uploadHeap;

				D3D12DescriptorHeap m_descriptorHeap;

				D3D12_SHADER_RESOURCE_VIEW_DESC m_textureResourceView;

				D3D12CommandList *m_pCommandList = nullptr;

				size_t m_slot = 0u;

			public:
				D3D12Texture() = default;

				D3D12Texture(D3D12DeviceObjectWrapper &pDevice, D3D12CommandList *pCommandList, const size_t width, const size_t height, const size_t slot, const bool useMipmaps);

				[[nodiscard]] inline D3D12DescriptorHeap& GetDescriptorHeap() { return this->m_descriptorHeap; }

				[[nodiscard]] inline size_t GetSlot() const noexcept { return this->m_slot; }

				virtual void Update() override;
			};

			class D3D12TextureSampler
			{
			private:
				D3D12_STATIC_SAMPLER_DESC m_samplerDesc;

			public:
				D3D12TextureSampler() = default;

				D3D12TextureSampler(const TextureFilter &filter);

				[[nodiscard]] inline D3D12_STATIC_SAMPLER_DESC GetSamplerDesc() const noexcept { return this->m_samplerDesc; }
			};

			typedef D3D12ObjectWrapper<ID3D12PipelineState> D3D12RenderPipelineObjectWrapper;

			class D3D12RenderPipeline : public D3D12RenderPipelineObjectWrapper
			{
			private:
				D3D_PRIMITIVE_TOPOLOGY m_topology;

				D3D12RootSignature m_pRootSignature;

				std::vector<uint32_t> m_constantBufferIndices;
				std::vector<uint32_t> m_textureIndices;

				D3D12DescriptorHeap m_gpuDescHeaps[WEISS__FRAME_BUFFER_COUNT];

				D3D12Device *m_pDevice = nullptr;

				std::vector<Texture *> m_pTextures;
				std::vector<ConstantBuffer *> m_pConstantBuffers;
				std::vector<D3D12TextureSampler *> m_pTextureSamplers;

			public:
				D3D12RenderPipeline() = default;

				D3D12RenderPipeline(D3D12RenderPipeline &&other);

				D3D12RenderPipeline(D3D12Device &pDevice, const RenderPipelineDesc &pipelineDesc,
									std::vector<ConstantBuffer *> &pConstantBuffers, std::vector<Texture *> pTextures, std::vector<D3D12TextureSampler *> pTextureSamplers);

				D3D12RenderPipeline &operator=(D3D12RenderPipeline &&other) noexcept;

				void Bind(D3D12CommandList &pCommandList, const size_t frameIndex) noexcept;
			};

			class D3D12CommandSubmitter
			{
			private:
				D3D12CommandList m_pCommandList;

				std::array<UINT64, WEISS__FRAME_BUFFER_COUNT> m_fenceValues;
				std::array<std::unique_ptr<D3D12Fence>, WEISS__FRAME_BUFFER_COUNT> m_pFences;

				std::array<D3D12CommandAllocator, WEISS__FRAME_BUFFER_COUNT> m_pCommandAllocators;

			public:
				D3D12CommandSubmitter() = default;

				D3D12CommandSubmitter(D3D12DeviceObjectWrapper &pDevice);

				void Close();

				void Reset(const size_t frameIndex);

				void Execute(D3D12CommandQueueObjectWrapper &pCommandQueue, const size_t frameIndex);

				void WaitForCompletion(const size_t frameIndex);

				[[nodiscard]] inline D3D12CommandList& GetCommandList()                  noexcept { return this->m_pCommandList;         }
				[[nodiscard]] inline D3D12CommandList* GetCommandListPr()                noexcept { return &this->m_pCommandList;        }
				[[nodiscard]] inline D3D12Fence&       GetFence(const size_t frameIndex) noexcept { return *this->m_pFences[frameIndex]; }
			};

			class D3D12RenderAPI : public RenderAPI
			{
			private:
				D3D12Adapter m_pAdapter;
				D3D12Device m_pDevice;
				D3D12CommandQueue m_pCommandQueue;
				D3D12SwapChain m_pSwapChain;
				D3D12DescriptorHeap m_pDescriptorHeap;
				D3D12DepthBuffer m_pDepthBuffer;

				std::array<D3D12RenderTarget, WEISS__FRAME_BUFFER_COUNT> m_pRenderTargets;

				D3D12CommandSubmitter m_commandSubmitter;

				std::vector<D3D12RenderPipeline> m_renderPipelines;

				size_t currentFrameIndex = 0u;

				CD3DX12_CPU_DESCRIPTOR_HANDLE m_currentRtvHandle;

				D3D12_RECT m_scissors;
				D3D12_VIEWPORT m_viewport;

				std::vector<D3D12TextureSampler *> m_pTextureSamplers;

			private:
				void CreateRenderTargets();

			public:
				D3D12RenderAPI() : RenderAPI(RenderAPIName::DIRECTX12) {  }

				virtual void InitRenderAPI(Window *pWindow, const uint16_t maxFps = 144u) override;

				virtual void InitPipelines(const std::vector<RenderPipelineDesc> &pipelineDescs) override;

				virtual void Draw(const Drawable &drawable, const size_t nVertices) override;

				virtual void BeginDrawing() override;

				virtual void EndDrawing() override;

				virtual void Present(const bool vSync) override;

				virtual size_t CreateVertexBuffer  (const size_t nVertices,      const size_t vertexSize) override;
				virtual size_t CreateIndexBuffer   (const size_t nIndices) override;
				virtual size_t CreateConstantBuffer(const size_t objSize,        const size_t slot) override;
				virtual size_t CreateTexture       (const size_t width,          const size_t height, const size_t slot, const bool useMipmaps = false) override;
				virtual size_t CreateTextureSampler(const TextureFilter& filter, const size_t slot) override;

				virtual void Fill(const Colorf32 &color = {1.f, 1.f, 1.f, 1.f}) override;
			};

		}; // namespace D3D12

#endif // __WEISS__OS_WINDOWS
	}; // Internal

	class SceneObject
	{
	private:
	};

	class SceneNode
	{
	private:
	};

	class Scene
	{
	private:
		std::unique_ptr<SceneNode *> m_pRootNode;

	public:
		Scene() = default;
	};

	class GraphicsEngine
	{
	private:
		RenderAPIHandle m_renderHandle;

		WindowHandle m_windowHandle;

	public:
		GraphicsEngine(const RenderAPIName &apiName);

		void Init(WindowHandle windowHandle);

		void Run(const size_t fps);

		virtual void OnFrame() = 0;

		~GraphicsEngine() = default;
	};

	class ClientSocket
	{
	private:
		SOCKET m_socket = INVALID_SOCKET;

	public:
		ClientSocket();

		~ClientSocket() { this->Disconnect(); }

		void Connect(const char *host, const unsigned int port);

		void Send(const char *data, int length = -1);

		[[nodiscard]] std::pair<std::array<char, 1024u>, size_t> Receive();

		void Disconnect() noexcept;
	};

	class ServerSocket
	{
	private:
		SOCKET m_socket = INVALID_SOCKET;

		std::vector<SOCKET> m_clients;

	public:
		ServerSocket();

		~ServerSocket() { this->Disconnect(); }

		void Bind(const unsigned int port);

		[[nodiscard]] int Accept() noexcept;

		void Send(const int clientID, const char *data, int length = -1);

		[[nodiscard]] std::pair<std::array<char, 1024u>, size_t> Receive(const int clientID);

		void Disconnect() noexcept;
	};

}; // WS

// LOG Static Class
std::mutex   WS::LOG::m_sPrintMutex = std::mutex();

// VKRenderPass Class
VkRenderPass WS::Internal::VK::VKRenderPass::s_colorRenderPass = VK_NULL_HANDLE;

/* 
 * ██████████████████████████████████████████████████████████████████████████████
 * ██                                                                          ██
 * ██                                                                          ██
 * ██  //////////////////////////////////--\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\  ██
 * ██  |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\|  ██
 * ██  ||--------------------------IMPLEMENTATION--------------------------||  ██
 * ██  |\__________________________________________________________________/|  ██
 * ██  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\--//////////////////////////////////  ██
 * ██                                                                          ██
 * ██                                                                          ██
 * ██████████████████████████████████████████████████████████████████████████████
*/

namespace WS {

#ifdef __WEISS__OS_WINDOWS

	template <typename T>
	Vector2D<T>::Vector2D(const DirectX::XMVECTOR& other)
	{
		DirectX::XMFLOAT4 float4;
		DirectX::XMStoreFloat4(&float4, other);

		this->x = float4.x; this->y = float4.y;
	}

#endif // __WEISS__OS_WINDOWS

#ifdef __WEISS__OS_WINDOWS

	template <typename T>
	Vector3D<T>::Vector3D(const DirectX::XMVECTOR& other)
	{
		DirectX::XMFLOAT4 float4;
		DirectX::XMStoreFloat4(&float4, other);

		this->x = float4.x; this->y = float4.y; this->z = float4.z;
	}

#endif // __WEISS__OS_WINDOWS

#ifdef __WEISS__OS_WINDOWS

	template <typename T>
	Vector4D<T>::Vector4D(const DirectX::XMVECTOR& other)
	{
		DirectX::XMFLOAT4 float4;
		DirectX::XMStoreFloat4(&float4, other);

		this->x = float4.x; this->y = float4.y; this->z = float4.z; this->w = float4.w;
	}

#endif // __WEISS__OS_WINDOWS

#ifdef __WEISS__OS_WINDOWS

	Rect::Rect(const RECT& rect)
	{
		this->left   = static_cast<uint16_t>(rect.left);
		this->top    = static_cast<uint16_t>(rect.top);
		this->right  = static_cast<uint16_t>(rect.right);
		this->bottom = static_cast<uint16_t>(rect.bottom);
	}

#endif // __WEISS__OS_WINDOWS

#ifdef __WEISS__OS_WINDOWS

	template <typename T, size_t R, size_t C>
	Matrix<T, R, C>::Matrix(const DirectX::XMMATRIX& other)
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

	/*
	 * // /////////////////////////////-\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
	 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
	 * // ||--------------------------LOG--------------------------|| \\
	 * // |\_______________________________________________________/| \\
	 * // \\\\\\\\\\\\\\\\\\\\\\\\\\\\\-///////////////////////////// \\
	 */

	template <typename T>
	static void LOG::__Print(const T& message, const LOG_TYPE logType)
	{
#ifdef __WEISS__OS_WINDOWS
	
		WORD textAttributes;

		switch (logType)
		{
		case LOG_TYPE::LOG_NORMAL:
			textAttributes = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
			break;
		case LOG_TYPE::LOG_SUCCESS:
			textAttributes = FOREGROUND_INTENSITY | FOREGROUND_GREEN;
			break;
		case LOG_TYPE::LOG_WARNING:
			textAttributes = FOREGROUND_RED | FOREGROUND_GREEN;
			break;
		case LOG_TYPE::LOG_ERROR:
			textAttributes = FOREGROUND_INTENSITY | FOREGROUND_RED;
			break;
		default:
			throw std::runtime_error("[LOG] Your Selected LOG_TYPE Could Not Be Resolved");
		}

		// Set Text Color
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textAttributes);

		std::cout << message;

		// Reset Text Color To White
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

#else // end of #ifdef __WEISS__OS_WINDOWS

		switch (logType)
		{
		case LOG_TYPE::LOG_NORMAL:
			std::cout << "\x1B[1;37m";
			break;
		case LOG_TYPE::LOG_SUCCESS:
			std::cout << "\x1B[1;32m";
			break;
		case LOG_TYPE::LOG_WARNING:
			std::cout << "\x1B[0;33m";
			break;
		case LOG_TYPE::LOG_ERROR:
			std::cout << "\x1B[1;31m";
			break;
		default:
			throw std::runtime_error("[LOG] Your Selected LOG_TYPE Could Not Be Resolved");
		}

		std::cout << message << '\n' << "\x1B[0m";

#endif 
	}

	template <typename T>
	static inline void LOG::Print(const T& message, const LOG_TYPE logType, const bool bBypassMutex)
	{
		if (!bBypassMutex)
		{
			// Lock The Mutex
			std::lock_guard<std::mutex> lock(LOG::m_sPrintMutex);

			__Print(message, logType);
		}
		else
		{
			__Print(message, logType);
		}
	}

	template <typename T>
	static inline void LOG::Println(const T& message, const LOG_TYPE logType)
	{
		// Lock The Mutex
		std::lock_guard<std::mutex> lock(LOG::m_sPrintMutex);

		__Print(message, logType);
		__Print('\n',    logType);
	}

	namespace Internal {

		namespace WIN {

			/*
			* // //////////////////////////////////-\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
			* // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			* // ||--------------------------WINDOWS IMAGE--------------------------|| \\
			* // |\_________________________________________________________________/| \\
			* // \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\-////////////////////////////////// \\
			*/

			WindowsImage::WindowsImage(WindowsImage&& other)
			{
				this->m_width = other.m_width;
				this->m_height = other.m_height;
				this->m_nPixels = other.m_nPixels;

				this->m_buff = std::move(other.m_buff);
			}

			WindowsImage::WindowsImage(const WindowsImage& other)
			{
				this->m_width = other.m_width;
				this->m_height = other.m_height;
				this->m_nPixels = other.m_nPixels;

				const size_t bufferSize = this->m_nPixels * sizeof(Coloru8);
				this->m_buff = std::make_unique<Coloru8[]>(bufferSize);
				std::memcpy(this->m_buff.get(), other.m_buff.get(), bufferSize);
			}

			WindowsImage::WindowsImage(const char* filename)
			{
				Microsoft::WRL::ComPtr<IWICBitmapSource>      decodedConvertedFrame;
				Microsoft::WRL::ComPtr<IWICBitmapDecoder>     bitmapDecoder;
				Microsoft::WRL::ComPtr<IWICImagingFactory>    factory;
				Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frameDecoder;

				if (DX_FAILED(CoInitialize(NULL)))
					throw std::runtime_error("[COM] Failed To Init COM");

				if (DX_FAILED(CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&factory))))
					throw std::runtime_error("[WIC] Could Not Create IWICImagingFactory");

				// Convert from char* to wchar_t*
				const size_t length = mbstowcs(nullptr, filename, 0);
				wchar_t* filenameW = new wchar_t[length];
				mbstowcs(filenameW, filename, length);

				if (DX_FAILED(factory->CreateDecoderFromFilename(filenameW, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &bitmapDecoder)))
					throw std::runtime_error("[WIC] Could Not Read / Open Image");

				if (DX_FAILED(bitmapDecoder->GetFrame(0, &frameDecoder)))
					throw std::runtime_error("[WIC] Could Not Get First Frame Of Image");

				if (DX_FAILED(frameDecoder->GetSize((UINT*)&this->m_width, (UINT*)&this->m_height)))
					throw std::runtime_error("[WIC] Could Not Get Image Width/Height");

				this->m_nPixels = this->m_width * this->m_height;

				if (DX_FAILED(WICConvertBitmapSource(GUID_WICPixelFormat32bppRGBA, frameDecoder.Get(), &decodedConvertedFrame)))
					throw std::runtime_error("[WIC] Could Not Create Bitmap Converter");

				this->m_buff = std::make_unique<Coloru8[]>(this->m_nPixels * sizeof(Coloru8));

				const WICRect sampleRect{ 0, 0, this->m_width, this->m_height };

				if (DX_FAILED(decodedConvertedFrame->CopyPixels(&sampleRect, this->m_width * sizeof(Coloru8), this->m_nPixels * sizeof(Coloru8), (BYTE*)this->m_buff.get())))
					throw std::runtime_error("[WIC] Could Not Copy Pixels From Bitmap");
			}

			WindowsImage& WindowsImage::operator=(const WindowsImage& other) noexcept
			{
				this->m_width   = other.m_width;
				this->m_height  = other.m_height;
				this->m_nPixels = other.m_nPixels;

				const size_t bufferSize = this->m_nPixels * sizeof(Coloru8);
				this->m_buff = std::make_unique<Coloru8[]>(bufferSize);

				std::memcpy(this->m_buff.get(), other.m_buff.get(), bufferSize);

				return *this;
			}

			WindowsImage::WindowsImage(const uint16_t width, const uint16_t height, const Coloru8& fillColor)
			{
				this->m_width = width;
				this->m_height = height;
				this->m_nPixels = this->m_width * this->m_height;

				const size_t bufferSize = this->m_nPixels * sizeof(Coloru8);
				this->m_buff = std::make_unique<Coloru8[]>(bufferSize);

				std::fill_n(this->m_buff.get(), this->m_nPixels, fillColor);
			}

			void WindowsImage::Write(const char* filename) const
			{
				if (DX_FAILED(CoInitialize(NULL)))
					throw std::runtime_error("[COM] Failed To Init COM");

				Microsoft::WRL::ComPtr<IWICImagingFactory>    factory;
				Microsoft::WRL::ComPtr<IWICBitmapEncoder>     bitmapEncoder;
				Microsoft::WRL::ComPtr<IWICBitmapFrameEncode> bitmapFrame;
				Microsoft::WRL::ComPtr<IWICStream>            outputStream;

				if (DX_FAILED(CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&factory))))
					throw std::runtime_error("[WIC] Could Not Create IWICImagingFactory");

				if (DX_FAILED(factory->CreateStream(&outputStream)))
					throw std::runtime_error("[WIC] Failed To Create Output Stream");

				// Convert from char* to wchar_t*
				const size_t length = mbstowcs(nullptr, filename, 0);
				wchar_t* filenameW = new wchar_t[length];
				mbstowcs(filenameW, filename, length);
				if (DX_FAILED(outputStream->InitializeFromFilename(filenameW, GENERIC_WRITE)))
					throw std::runtime_error("[WIC] Failed To Initialize Output Stream From Filename");

				char fileExtension[10u]; // assumes the extension has less than 10-1=9 characters
				std::memset(fileExtension, 0u, 10);
				const size_t offset = std::string_view(filename).find_last_of('.');
				std::memcpy(fileExtension, filename + offset, strlen(filename) - offset + 1);

				// This should be fine thanks to sso (small string optimization)
				const std::unordered_map<std::string, REFGUID> extensionToREFUGUIDMap{
					{ ".bmp", GUID_ContainerFormatBmp  }, { ".png",  GUID_ContainerFormatPng  },
					{ ".ico", GUID_ContainerFormatIco  }, { ".jpeg", GUID_ContainerFormatJpeg },
					{ ".jpg", GUID_ContainerFormatJpeg }, { ".tiff", GUID_ContainerFormatTiff },
					{ ".gif", GUID_ContainerFormatGif  }, { ".wmp",  GUID_ContainerFormatWmp  }
				};

				if (extensionToREFUGUIDMap.find(fileExtension) == std::end(extensionToREFUGUIDMap))
					throw std::runtime_error("[WIC] Your Image Extension Is Not Supported");

				if (DX_FAILED(factory->CreateEncoder(extensionToREFUGUIDMap.at(fileExtension), NULL, &bitmapEncoder)))
					throw std::runtime_error("[WIC] Failed To Create Bitmap Encoder");

				if (DX_FAILED(bitmapEncoder->Initialize(outputStream.Get(), WICBitmapEncoderNoCache)))
					throw std::runtime_error("[WIC] Failed To Initialize Bitmap ");

				if (DX_FAILED(bitmapEncoder->CreateNewFrame(&bitmapFrame, NULL)))
					throw std::runtime_error("[WIC] Failed To Create A New Frame");

				if (DX_FAILED(bitmapFrame->Initialize(NULL)))
					throw std::runtime_error("[WIC] Failed To Initialize A Bitmap's Frame");

				if (DX_FAILED(bitmapFrame->SetSize(this->m_width, this->m_height)))
					throw std::runtime_error("[WIC] Failed To Set A Bitmap's Frame's Size");

				WICPixelFormatGUID pixelFormat = GUID_WICPixelFormat32bppBGRA;
				if (DX_FAILED(bitmapFrame->SetPixelFormat(&pixelFormat)))
					throw std::runtime_error("[WIC] Failed To Set Pixel Format On A Bitmap Frame's");

				if (!IsEqualGUID(pixelFormat, GUID_WICPixelFormat32bppBGRA))
					throw std::runtime_error("[WIC] The Requested Pixel Format Is Not Supported");

				const UINT stride = this->m_width * sizeof(Coloru8);
				const UINT bufferSize = this->m_nPixels * sizeof(Coloru8);
				if (DX_FAILED(bitmapFrame->WritePixels(this->m_height, stride, bufferSize, (BYTE*)this->m_buff.get())))
					throw std::runtime_error("[WIC] Failed To Write Pixels To A Bitmap's Frame");

				if (DX_FAILED(bitmapFrame->Commit()))
					throw std::runtime_error("[WIC] Failed To Commit A Bitmap's Frame");

				if (DX_FAILED(bitmapEncoder->Commit()))
					throw std::runtime_error("[WIC] Failed To Commit Bitmap Encoder");
			}
		}; // namespace WIN
	}; // Internal

	/*
	 * // //////////////////////////////--\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
	 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
	 * // ||--------------------------WINDOW--------------------------|| \\
	 * // |\__________________________________________________________/| \\
	 * // \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\--////////////////////////////// \\
	 */

	Window::~Window()
	{
		if (this->m_pMouse != nullptr)
			delete this->m_pMouse;

		if (this->m_pKeyboard != nullptr)
			delete this->m_pKeyboard;
	}

	namespace WIN {
			/*
			* // //////////////////////////////////-\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
			* // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			* // ||--------------------------WINDOWS MOUSE--------------------------|| \\
			* // |\_________________________________________________________________/| \\
			* // \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\-////////////////////////////////// \\ 
			*/

			WindowsMouse::WindowsMouse()
			{
				RAWINPUTDEVICE mouseInputDevice;
				mouseInputDevice.usUsagePage = 0x01;
				mouseInputDevice.usUsage     = 0x02;
				mouseInputDevice.dwFlags     = 0;
				mouseInputDevice.hwndTarget  = nullptr;

				RegisterRawInputDevices(&mouseInputDevice, 1, sizeof(RAWINPUTDEVICE));
			}

			void WindowsMouse::Clip(const Rect& rect) const noexcept
			{
				RECT winRect{ rect.left, rect.top, rect.right, rect.bottom };
				ClipCursor(&winRect);
			}

			void WindowsMouse::__OnWindowUpdateBegin()
			{
				this->m_wheelDelta = 0;
				this->m_deltaPosition = { 0, 0 };
				this->m_wasMouseMovedDuringUpdate = false;
				this->m_wasCursorMovedDuringUpdate = false;
			}

			bool WindowsMouse::__HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
			{
				switch (msg)
				{
				case WM_INPUT:
				{
					UINT size = 0;

					// WINDOWS API LOGIC
					if (!GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER)))
					{
						std::vector<char> rawBuffer(size);

						if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, rawBuffer.data(), &size, sizeof(RAWINPUTHEADER)) == size)
						{
							const RAWINPUT& ri = reinterpret_cast<const RAWINPUT&>(*rawBuffer.data());

							if (ri.header.dwType == RIM_TYPEMOUSE && (ri.data.mouse.lLastX != 0 || ri.data.mouse.lLastY != 0))
							{
								this->m_deltaPosition += Vec2i16{ static_cast<int16_t>(ri.data.mouse.lLastX), static_cast<int16_t>(ri.data.mouse.lLastY) };

								this->m_wasMouseMovedDuringUpdate = true;
							}
						}
					}

					return true;
				}

				break;
				case WM_MOUSELEAVE:
					this->m_isCursorInWindow = false;

					return true;
				case WM_MOUSEMOVE:
				{
					this->m_position = { static_cast<uint16_t>(GET_X_LPARAM(lParam)), static_cast<uint16_t>(GET_Y_LPARAM(lParam)) };
					this->m_wasCursorMovedDuringUpdate = true;
				}

				this->m_isCursorInWindow = true;

				return true;
				case WM_LBUTTONDOWN:
					this->m_isLeftButtonDown = true;

					for (auto& functor : this->m_onLeftButtonDownFunctors)
						functor(this->m_position);

					return true;
				case WM_LBUTTONUP:
					this->m_isLeftButtonDown = false;

					for (auto& functor : this->m_onLeftButtonUpFunctors)
						functor(this->m_position);

					return true;
				case WM_RBUTTONDOWN:
					this->m_isRightButtonDown = true;

					for (auto& functor : this->m_onRightButtonDownFunctors)
						functor(this->m_position);

					return true;
				case WM_RBUTTONUP:
					this->m_isRightButtonDown = false;

					for (auto& functor : this->m_onRightButtonUpFunctors)
						functor(this->m_position);

					return true;
				case WM_MOUSEWHEEL:
					this->m_wheelDelta += GET_WHEEL_DELTA_WPARAM(wParam);
					return true;
				default:
					return false;
				}
			}

			void WindowsMouse::__OnWindowUpdateEnd()
			{
				if (this->m_wasMouseMovedDuringUpdate)
					for (auto& functor : this->m_onMouseMoveFunctors)
						functor(this->m_position, this->m_deltaPosition);

				if (this->m_wasCursorMovedDuringUpdate)
					for (auto& functor : this->m_onCursorMoveFunctors)
						functor(this->m_position, this->m_deltaPosition);

				if (this->m_wheelDelta != 0)
					for (auto& functor : this->m_onWheelTurnFunctors)
						functor(this->m_wheelDelta);
			}

			/*
			* // //////////////////////////////////--\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
			* // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			* // ||-------------------------WINDOWS KEYBOARD-------------------------|| \\
			* // |\__________________________________________________________________/| \\
			* // \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\--////////////////////////////////// \\ 
			*/

			bool WindowsKeyboard::__HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
			{
				switch (msg)
				{
				case WM_KEYDOWN:
					{
						const uint8_t keyCode = static_cast<uint8_t>(wParam);

						// Verify that the key was not down before the message was sent
						if (!CHECK_BIT(lParam, 30))
						{
							this->m_downKeys.push_back(keyCode);

							for (auto& functor : this->m_onKeyDownFunctors)
								functor(keyCode);
						}

						return true;
					}
				case WM_KEYUP:
					{
						const uint8_t keyCode = static_cast<uint8_t>(wParam);

						this->m_downKeys.erase(std::remove(this->m_downKeys.begin(), this->m_downKeys.end(), keyCode), this->m_downKeys.end());

						for (auto& functor : this->m_onKeyUpFunctors)
							functor(keyCode);

						return true;
					}
				}

				return false;
			}

			/*
			* // //////////////////////////////////-\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
			* // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			* // ||--------------------------WINDOWS WINDOW--------------------------|| \\
			* // |\__________________________________________________________________/| \\
			* // \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\-/////////////////////////////////// \\ 
			*/

			WindowsWindow::WindowsWindow(const WindowDescriptor& descriptor)
			{
				WNDCLASSA wc;
				ZeroMemory(&wc, sizeof(WNDCLASSA));

				wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
				wc.lpfnWndProc   = WindowProcessMessages;
				wc.hInstance     = GetModuleHandle(NULL);
				wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
				wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
				wc.lpszClassName = "WEISS_WNDCLASSA";

				if (!RegisterClassA(&wc))
					throw std::runtime_error("[WINDOW] Could Not Register Window Class");

				// CS_OWNDC For Opengl
				const uint32_t windowStyle = CS_OWNDC | (descriptor.isResizable ? WS_OVERLAPPEDWINDOW : (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX));

				RECT windowRect{ 0, 0, descriptor.width, descriptor.height };
				AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

				this->m_handle = CreateWindowA("WEISS_WNDCLASSA", descriptor.title, windowStyle,
					descriptor.x, descriptor.y,
					windowRect.right - windowRect.left,
					windowRect.bottom - windowRect.top,
					NULL, NULL, wc.hInstance, NULL);

				if (this->m_handle == NULL)
					throw std::runtime_error("[WINDOW] Could Not Create Window");

	#ifdef __WEISS__PLATFORM_X64

				SetWindowLongPtr(this->m_handle, GWLP_USERDATA, (LONG_PTR)this);

	#else

				SetWindowLong(this->m_handle, GWLP_USERDATA, (LONG)this);

	#endif

				this->m_pMouse    = new WindowsMouse();
				this->m_pKeyboard = new WindowsKeyboard();

				ShowWindow(this->m_handle, SW_SHOW);
				UpdateWindow(this->m_handle);

				this->m_isRunning = true;

				if (descriptor.iconPath != nullptr)
					this->SetIcon(descriptor.iconPath);
			}

			[[nodiscard]] Rect WindowsWindow::GetWindowRectangle() const noexcept
			{
				RECT windowRect;
				GetWindowRect(this->m_handle, &windowRect);

				return Rect(windowRect);
			}

			[[nodiscard]] Rect WindowsWindow::GetClientRectangle() const noexcept
			{
				RECT clientRect;
				GetClientRect(this->m_handle, &clientRect);

				return Rect(clientRect);
			}

			[[nodiscard]] LRESULT WindowsWindow::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
			{
				switch (msg)
				{
				case WM_SIZE:
				{
					const Vec2u16 client_area_dimensions = {
						static_cast<uint16_t>(GET_X_LPARAM(lParam)),
						static_cast<uint16_t>(GET_Y_LPARAM(lParam))
					};

					this->m_isMinimized = (client_area_dimensions.x == 0 && client_area_dimensions.y == 0);

					for (auto& functor : this->m_onResizeFunctors)
						functor(client_area_dimensions);
				}

				return 0;
				case WM_DESTROY:
					this->Destroy();

					return 0;
				}

				// Dispatch Message To Peripheral Devices
				if (reinterpret_cast<WindowsMouse*>(this->m_pMouse)->__HandleMessage(msg, wParam, lParam)) return 0;
				if (reinterpret_cast<WindowsKeyboard*>(this->m_pKeyboard)->__HandleMessage(msg, wParam, lParam)) return 0;

				// Otherwise Let Windows Handle The Message
				return DefWindowProc(this->m_handle, msg, wParam, lParam);
			}

			void WindowsWindow::SetWindowSize(const uint16_t width, const uint16_t height)
			{
				SetWindowPos(this->m_handle, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOOWNERZORDER);
			}

			void WindowsWindow::SetClientSize(const uint16_t width, const uint16_t height)
			{
				const uint16_t topBottomWindowPadding = this->GetWindowHeight() - this->GetClientHeight();
				const uint16_t leftRightWindowPadding = this->GetWindowWidth() - this->GetClientWidth();

				this->SetWindowSize(width + leftRightWindowPadding, height + topBottomWindowPadding);
			}

			void WindowsWindow::SetTitle(const char* title) const noexcept
			{
				SetWindowTextA(this->m_handle, title);
			}

			void WindowsWindow::SetIcon(const char* pathname)
			{
				const HICON hIcon = (HICON)LoadImageA(NULL, pathname, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

				if (hIcon == NULL)
					throw std::runtime_error("Could Not Load Icon");

				SendMessage(this->m_handle, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
			}

			void WindowsWindow::Update()
			{
				reinterpret_cast<WindowsMouse*>(this->m_pMouse)->__OnWindowUpdateBegin();
				reinterpret_cast<WindowsKeyboard*>(this->m_pKeyboard)->__OnWindowUpdateBegin();

				MSG msg;
				while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}

				reinterpret_cast<WindowsMouse*>(this->m_pMouse)->__OnWindowUpdateEnd();
				reinterpret_cast<WindowsKeyboard*>(this->m_pKeyboard)->__OnWindowUpdateEnd();
			}

			void WindowsWindow::Destroy() noexcept
			{
				this->m_isRunning = !DestroyWindow(this->m_handle);
			}

			WindowsWindow::~WindowsWindow() { this->Destroy(); }

			LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
			{
#ifdef __WEISS__PLATFORM_X64

				WindowsWindow* window = (WindowsWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

#else

				WindowsWindow* window = (WindowsWindow*)GetWindowLong(hwnd, GWLP_USERDATA);

#endif

				if (window != NULL)
					return window->HandleMessage(msg, wParam, lParam);

				return DefWindowProc(hwnd, msg, wParam, lParam);
			}

	}; // namespace WIN

	/*
	 * // ////////////////////////////////////-\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
	 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
	 * // ||--------------------------PERSPECTIVE CAMERA--------------------------|| \\
	 * // |\______________________________________________________________________/| \\
	 * // \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\-///////////////////////////////////// \\ 
	 */

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

	/*
	 * // /////////////////////////////////////-\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
	 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
	 * // ||--------------------------ORTHOGRAPHIC CAMERA--------------------------|| \\
	 * // |\_______________________________________________________________________/| \\
	 * // \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\-///////////////////////////////////// \\ 
	 */

	OrthographicCamera::OrthographicCamera(Window* pWindow, const OrthographicCameraDescriptor& descriptor)
		: Camera(descriptor.position, Vec3f{ 0.0f, descriptor.ratation, 0.0f })
	{
		auto recalculateInvAspectRatio = [this](const Vec2u16& clientDims)
		{
			this->m_InvAspectRatio = clientDims.y / static_cast<float>(clientDims.x);
		};

		recalculateInvAspectRatio({ pWindow->GetClientWidth(), pWindow->GetClientHeight() });

		pWindow->OnResize(recalculateInvAspectRatio);
	}

	void OrthographicCamera::CalculateTransform()
	{
#ifdef __WEISS__OS_WINDOWS

		this->m_transform = DirectX::XMMatrixScaling(this->m_InvAspectRatio, 1, 1) *
							DirectX::XMMatrixTranslation(-this->m_position.x, -this->m_position.y, 0.0f) *
							DirectX::XMMatrixRotationZ(this->m_rotation.z);

#endif // __WEISS__OS_WINDOWS
	}

	void OrthographicCamera::HandleMouseMovements(Mouse& mouse, const float sensitivity)
	{

	}

	void OrthographicCamera::HandleKeyboardInputs(Keyboard& keyboard, const float speed, const char forward, const char backward, const char left, const char right, const char up, const char down)
	{
#ifdef __WEISS__OS_WINDOWS

		if (keyboard.IsKeyDown(right))
			this->m_position = DirectX::XMVectorSet(this->m_position.x - speed, this->m_position.y, 0.0f, 0.0f);
		if (keyboard.IsKeyDown(left))
			this->m_position = DirectX::XMVectorSet(this->m_position.x + speed, this->m_position.y, 0.0f, 0.0f);

		if (keyboard.IsKeyDown(up))
			this->m_position = DirectX::XMVectorSet(this->m_position.x, this->m_position.y - speed, 0.0f, 0.0f);
		if (keyboard.IsKeyDown(down))
			this->m_position = DirectX::XMVectorSet(this->m_position.x, this->m_position.y + speed, 0.0f, 0.0f);

#endif // __WEISS__OS_WINDOWS
	}

	namespace Internal {

		/*
		 * // //////////////////////////////-\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
		 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
		 * // ||--------------------------VULKAN--------------------------|| \\
		 * // |\__________________________________________________________/| \\
		 * // \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\-/////////////////////////////// \\ 
		 */

		namespace VK {

			static VKAPI_ATTR VkBool32 VKAPI_CALL validationLayerCallback(
				VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
				VkDebugUtilsMessageTypeFlagsEXT messageType,
				const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
				void* pUserData) {

				WS::LOG::Print("validation layer: ", WS::LOG_TYPE::LOG_ERROR);
				WS::LOG::Println(pCallbackData->pMessage, WS::LOG_TYPE::LOG_ERROR);

				return VK_FALSE;
			}

			/*
			 * // ////////////////////////////////////--\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||--------------------------VKObjectWrapper<T>--------------------------|| \\
			 * // |\______________________________________________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\--//////////////////////////////////// \\ 
			 */

			template <typename T>
			VKObjectWrapper<T>& VKObjectWrapper<T>::operator=(VKObjectWrapper<T>&& other) noexcept
			{
				this->m_pObject = other.m_pObject;
				other.m_pObject = VK_NULL_HANDLE;

				return *this;
			}

			/*
			 * // ////////////////////////////////--\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||--------------------------VKInstance--------------------------|| \\
			 * // |\______________________________________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\--//////////////////////////////// \\ 
			 */

			VKInstance::VKInstance(const char* appName)
			{
				const std::vector<VkExtensionProperties> availableExtensionsPropreties = VKInstance::GetAvailableExtensionsPropreties();
				const std::vector<const char*>           requiredExtensions           = VKInstance::GetRequiredExtensions();

				for (const char* requiredExtension : requiredExtensions)
				{
					bool bFound = false;

					for (const VkExtensionProperties& availableExtensionPropreties : availableExtensionsPropreties)
					{
						if (strcmp(requiredExtension, availableExtensionPropreties.extensionName) == 0)
						{
							bFound = true;
							break;
						}
					}

					if (!bFound)
					{
						const std::string errorString = "[VULKAN] Extension \"" + std::string(requiredExtension) + std::string("\" Is Not Supported");
						throw std::runtime_error(errorString.c_str());
					}
				}

				VkApplicationInfo appInfo{};
				appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
				appInfo.pApplicationName = "My Super App Using Weiss Engine";
				appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
				appInfo.pEngineName = "Weiss Engine";
				appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
				appInfo.apiVersion = VK_API_VERSION_1_0;

				VkInstanceCreateInfo createInfo{};
				createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
				createInfo.pApplicationInfo = &appInfo;
				createInfo.enabledExtensionCount   = static_cast<uint32_t>(requiredExtensions.size());
				createInfo.ppEnabledExtensionNames = requiredExtensions.data();

#ifdef __WEISS__DEBUG_MODE

				std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };

				createInfo.enabledLayerCount   = validationLayers.size();
				createInfo.ppEnabledLayerNames = validationLayers.data();

				VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
				debugCreateInfo = {};
				debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
				debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
				debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
				debugCreateInfo.pfnUserCallback = validationLayerCallback;

				createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;

#endif // __WEISS__DEBUG_MODE

				if (VK_FAILED(vkCreateInstance(&createInfo, nullptr, &this->m_object)))
					throw std::runtime_error("[VULKAN] Failed To Create Instance");
			}

			VKInstance& VKInstance::operator=(VKInstance&& other) noexcept
			{
				this->m_object = other.m_object;
				other.m_object = VK_NULL_HANDLE;

				return *this;
			}

			VKInstance::~VKInstance()
			{
				if (this->m_object != VK_NULL_HANDLE)
					vkDestroyInstance(this->m_object, nullptr);
			}

			std::vector<VkExtensionProperties> VKInstance::GetAvailableExtensionsPropreties()
			{
				uint32_t extensionCount = 0;
				if (VK_FAILED(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr)))
					throw std::runtime_error("[VULKAN] Failed To Enumerate Instance Extension Propreties");

				std::vector<VkExtensionProperties> extensions(extensionCount);
				if (VK_FAILED(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data())))
					throw std::runtime_error("[VULKAN] Failed To Enumerate Instance Extension Propreties");

				return extensions;
			}

			std::vector<const char*> VKInstance::GetRequiredExtensions() noexcept
			{
				std::vector<const char*> extensions;

#ifdef __WEISS__DEBUG_MODE

				extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
				
#endif // __WEISS__DEBUG_MODE

#ifdef __WEISS__OS_WINDOWS

				extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
				extensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);

#endif // __WEISS__OS_WINDOWS

				return extensions;
			}
		
			/*
			 * // /////////////////////////////////-\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------------------------VKSurface---------------------------|| \\
			 * // |\_______________________________________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\-///////////////////////////////// \\ 
			 */

			VKSurface::VKSurface(VKInstance* pInstance, Window* pWindow)
				: m_pInstance(pInstance)
			{
		#ifdef __WEISS__OS_WINDOWS

				VkWin32SurfaceCreateInfoKHR createInfo = {};
				createInfo.sType     = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
				createInfo.hwnd      = reinterpret_cast<const WS::WIN::WindowsWindow*>(pWindow)->GetHandle();
				createInfo.hinstance = GetModuleHandle(NULL);

				this->m_dimensions = { pWindow->GetClientWidth(), pWindow->GetClientHeight() };

				if (VK_FAILED(vkCreateWin32SurfaceKHR(*this->m_pInstance, &createInfo, nullptr, &this->m_object)))
					throw std::runtime_error("[VULKAN] Failed To Create Window Surface");

		#endif // __WEISS__OS_WINDOWS
			}

			VKSurface& VKSurface::operator=(VKSurface&& other) noexcept
			{
				this->m_pInstance = other.m_pInstance;
				this->m_object = other.m_object;
				other.m_object = VK_NULL_HANDLE;

				this->m_dimensions = other.m_dimensions;

				return *this;
			}

			VKSurface::~VKSurface()
			{
				if (this->m_object != VK_NULL_HANDLE)
					vkDestroySurfaceKHR(*this->m_pInstance, this->m_object, nullptr);
			}

			/*
			 * // //////////////////////////////////-\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------------------------VKSemaphore---------------------------|| \\
			 * // |\_________________________________________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\-////////////////////////////////// \\ 
			 */

			VKSemaphore::VKSemaphore(const VKDevice& device)
				: m_pDevice(&device)
			{
				VkSemaphoreCreateInfo semaphoreInfo{};
				semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

				if (VK_FAILED(vkCreateSemaphore(device, &semaphoreInfo, nullptr, &this->m_object)))
					throw std::runtime_error("[VULKAN] Failed To Create Sempahore");
			}

			VKSemaphore& VKSemaphore::operator=(VKSemaphore&& other) noexcept
			{
				this->m_object = std::move(other.m_object);
				other.m_object = VK_NULL_HANDLE;

				this->m_pDevice = std::move(other.m_pDevice);

				return *this;
			}

			VKSemaphore::~VKSemaphore()
			{
				if (this->m_object != VK_NULL_HANDLE)
					vkDestroySemaphore(*this->m_pDevice, this->m_object, nullptr);

				this->m_object = VK_NULL_HANDLE;
			}

			/*
			 * // //////////////////////////////////--\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------------------------VKRenderPass---------------------------|| \\
			 * // |\__________________________________________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\--////////////////////////////////// \\ 
			 */

			void VKRenderPass::CreateRenderPasses(const VKDevice& device, const VKSwapChain& swapChain)
			{
				VkAttachmentDescription colorAttachment{};
				colorAttachment.format  = swapChain.GetFormat().format;
				colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
				colorAttachment.loadOp  = VK_ATTACHMENT_LOAD_OP_CLEAR;
				colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
				colorAttachment.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
				colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
				colorAttachment.initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED;
				colorAttachment.finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

				VkAttachmentReference colorAttachmentRef{};
				colorAttachmentRef.attachment = 0;
				colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

				VkSubpassDescription subpass{};
				subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
				subpass.colorAttachmentCount = 1;
				subpass.pColorAttachments = &colorAttachmentRef;

				VkRenderPassCreateInfo renderPassInfo{};
				renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
				renderPassInfo.attachmentCount = 1;
				renderPassInfo.pAttachments = &colorAttachment;
				renderPassInfo.subpassCount = 1;
				renderPassInfo.pSubpasses   = &subpass;

				if (VK_FAILED(vkCreateRenderPass(device, &renderPassInfo, nullptr, &VKRenderPass::s_colorRenderPass)))
					throw std::runtime_error("[VULKAN] Failed To Create Render Pass");
			}

			void VKRenderPass::DestroyRenderPasses(const VKDevice& device)
			{
				vkDestroyRenderPass(device, VKRenderPass::s_colorRenderPass, nullptr);
			}

			/*
			 * // //////////////////////////////////-\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------------------------VKSwapChain---------------------------|| \\
			 * // |\_________________________________________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\-////////////////////////////////// \\ 
			 */

			VKSwapChain::VKSwapChain(VKDevice& pDevice, VKSurface& pSurface)
				: m_pDevice(&pDevice), m_pSurface(&pSurface)
			{
				this->m_pPresentQueue = pDevice.GetPresentQueuePtr();

				this->CreateSwapChain();
				this->CreateImagesAndViews();
			}

			VKSwapChain& VKSwapChain::operator=(VKSwapChain&& other) noexcept
			{
				this->m_nImages = std::move(other.m_nImages);
				this->m_images = std::move(other.m_images);
				this->m_imageViews = std::move(other.m_imageViews);
				this->m_pDevice = std::move(other.m_pDevice);
				this->m_object = std::move(other.m_object);
				this->m_pSurface = std::move(other.m_pSurface);
				this->m_surfaceFormat = std::move(other.m_surfaceFormat);
				this->m_colorFrameBuffers = std::move(other.m_colorFrameBuffers);
				this->m_currentImageIndex = std::move(other.m_currentImageIndex);
				this->m_pPresentQueue = std::move(other.m_pPresentQueue);
				this->m_imageExtent2D = std::move(other.m_imageExtent2D);

				other.m_object = VK_NULL_HANDLE;

				return *this;
			}

			void VKSwapChain::CreateFrameBuffers()
			{
				m_colorFrameBuffers.resize(this->m_images.size());

				VkFramebufferCreateInfo framebufferInfo{};
				framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
				framebufferInfo.attachmentCount = 1;
				framebufferInfo.width  = this->m_imageExtent2D.width;
				framebufferInfo.height = this->m_imageExtent2D.height;
				framebufferInfo.layers = 1;

				this->m_colorFrameBuffers.resize(this->m_imageViews.size());
				for (size_t i = 0; i < this->m_colorFrameBuffers.size(); i++)
				{
					VkImageView attachments[] = {
						this->m_imageViews[i]
					};

					framebufferInfo.pAttachments = attachments;
					framebufferInfo.renderPass   = VKRenderPass::s_colorRenderPass;

					if (VK_FAILED(vkCreateFramebuffer(*this->m_pDevice, &framebufferInfo, nullptr, &this->m_colorFrameBuffers[i])))
						throw std::runtime_error("[VULKAN] Failed To Create A Frame Buffer");
				}
			}

			void VKSwapChain::GetNextImage()
			{
				if (VK_FAILED(vkAcquireNextImageKHR(*this->m_pDevice, this->m_object, UINT64_MAX, this->m_pPresentQueue->m_semaphore, VK_NULL_HANDLE, &this->m_currentImageIndex)))
					throw std::runtime_error("[VULKAN] Failed To Acquire Next Swap Chain Image");
			}

			void VKSwapChain::Present()
			{
				VkPresentInfoKHR presentInfo{};
				presentInfo.waitSemaphoreCount = 1;
				presentInfo.pWaitSemaphores    = this->m_pDevice->GetGraphicsQueuePtr()->m_semaphore.GetPtr();
				presentInfo.swapchainCount     = 1;
				presentInfo.pSwapchains   = &this->m_object;
				presentInfo.pImageIndices = &this->m_currentImageIndex;
				presentInfo.pResults = nullptr;
				presentInfo.sType    = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

				if (VK_FAILED(vkQueuePresentKHR(*this->m_pPresentQueue, &presentInfo)))
					throw std::runtime_error("[VULKAN] Failed To Present Swap Chain Frame Buffer");

				vkQueueWaitIdle(*this->m_pPresentQueue);
			}

			VKSwapChain::~VKSwapChain()
			{
				for (VkImageView& imageView : this->m_imageViews)
					if (imageView != VK_NULL_HANDLE)
						vkDestroyImageView(*this->m_pDevice, imageView, nullptr);

				if (this->m_object != VK_NULL_HANDLE)
					vkDestroySwapchainKHR(*this->m_pDevice, this->m_object, nullptr);

				for (VkFramebuffer& frameBuffer : m_colorFrameBuffers)
					if (frameBuffer != VK_NULL_HANDLE)
						vkDestroyFramebuffer(*this->m_pDevice, frameBuffer, nullptr);
			}

			VkPresentModeKHR VKSwapChain::PickPresentingMode() const
			{
				const VkSurfaceKHR&     surface        = *this->m_pSurface;
				const VkPhysicalDevice& physicalDevice = this->m_pDevice->GetPhysicalDeviceData().m_physicalDevice;

				uint32_t nSupportedPresentingModes;
				vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &nSupportedPresentingModes, nullptr);

				if (nSupportedPresentingModes == 0u)
					throw std::runtime_error("[VULKAN] No Compatible Presenting Mode Could Be Found");

				std::vector<VkPresentModeKHR> supportedPresentingModes(nSupportedPresentingModes);
				vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &nSupportedPresentingModes, supportedPresentingModes.data());

				if (supportedPresentingModes.size() == 0u)
					throw std::runtime_error("[VULKAN] No Compatible Presenting Mode Could Be Found");

				for (const VkPresentModeKHR mode : supportedPresentingModes)
					if (mode == VkPresentModeKHR::VK_PRESENT_MODE_MAILBOX_KHR)
						return mode;

				return supportedPresentingModes[0];
			}

			VkSurfaceFormatKHR VKSwapChain::PickSurfaceFormat() const
			{
				const VkSurfaceKHR&     surface        = *this->m_pSurface;
				const VkPhysicalDevice& physicalDevice = this->m_pDevice->GetPhysicalDeviceData().m_physicalDevice;

				uint32_t nSupportedFormats;
				vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &nSupportedFormats, nullptr);

				if (nSupportedFormats == 0u) return {};

				std::vector<VkSurfaceFormatKHR> supportedFormats(nSupportedFormats);
				vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &nSupportedFormats, supportedFormats.data());

				if (supportedFormats.size() == 0u)
					throw std::runtime_error("[VULKAN] No Supported Surface Format Where Found");

				for (const VkSurfaceFormatKHR& surfaceFormat : supportedFormats)
					if (surfaceFormat.format == VK_FORMAT_B8G8R8A8_SRGB && surfaceFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
						return surfaceFormat;

				return supportedFormats[0];
			}

			void VKSwapChain::CreateSwapChain()
			{
				VKDevice&     device  = *this->m_pDevice;
				VkSurfaceKHR& surface = *this->m_pSurface;

				this->m_surfaceFormat = this->PickSurfaceFormat();
				this->m_imageExtent2D.width  = this->m_pSurface->GetDimensions().x;
				this->m_imageExtent2D.height = this->m_pSurface->GetDimensions().y;

				VkSwapchainCreateInfoKHR createInfo = {};
				createInfo.sType              = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
				createInfo.surface            = surface;
				createInfo.minImageCount      = WEISS__FRAME_BUFFER_COUNT;
				createInfo.imageFormat        = this->m_surfaceFormat.format;
				createInfo.imageColorSpace    = this->m_surfaceFormat.colorSpace;
				createInfo.imageExtent        = this->m_imageExtent2D;
				createInfo.imageArrayLayers   = 1;
				createInfo.imageUsage         = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
				createInfo.preTransform       = VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
				createInfo.compositeAlpha     = VkCompositeAlphaFlagBitsKHR::VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
				createInfo.presentMode        = this->PickPresentingMode();
				createInfo.clipped            = VK_TRUE;
				createInfo.oldSwapchain       = VK_NULL_HANDLE;

				const VKPhysicalDeviceDataWrapper& physicalDeviceData = device.GetPhysicalDeviceData();

				std::array<uint32_t, 2u> sharingQueueFamilyIndices{
					*physicalDeviceData.m_presentQueueIndex,
					*physicalDeviceData.m_graphicsQueueIndex
				};

				if (*physicalDeviceData.m_graphicsQueueIndex == *physicalDeviceData.m_presentQueueIndex)
				{
					createInfo.imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE;
					createInfo.queueFamilyIndexCount = 0u;
					createInfo.pQueueFamilyIndices   = nullptr;
				} else {
					createInfo.imageSharingMode      = VK_SHARING_MODE_CONCURRENT;
					createInfo.queueFamilyIndexCount = 2u;

					createInfo.pQueueFamilyIndices = sharingQueueFamilyIndices.data();
				}
				
				if (VK_FAILED(vkCreateSwapchainKHR(device, &createInfo, nullptr, &this->m_object)))
					throw std::runtime_error("[VULKAN] Failed To Create Swap Chain");
			}

			void VKSwapChain::CreateImagesAndViews()
			{
				vkGetSwapchainImagesKHR(*this->m_pDevice, this->m_object, &this->m_nImages, nullptr);
				this->m_images.resize(this->m_nImages);
				this->m_imageViews.resize(this->m_nImages);
				vkGetSwapchainImagesKHR(*this->m_pDevice, this->m_object, &this->m_nImages, this->m_images.data());

				for (size_t i = 0; i < this->m_nImages; i++)
				{
					VkImageViewCreateInfo createInfo{};
					createInfo.sType    = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
					createInfo.image    = this->m_images[i];
					createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
					createInfo.format   = this->m_surfaceFormat.format;
					createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
					createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
					createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
					createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
					createInfo.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
					createInfo.subresourceRange.baseMipLevel   = 0;
					createInfo.subresourceRange.levelCount     = 1;
					createInfo.subresourceRange.baseArrayLayer = 0;
					createInfo.subresourceRange.layerCount     = 1;

					if (VK_FAILED(vkCreateImageView(*this->m_pDevice, &createInfo, nullptr, &this->m_imageViews[i])))
						throw std::runtime_error("[VULKAN] Failed To Create An Image View");
				}
			}

			/*
			 * // /////////////////////////////////--\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||--------------------------VKCommandPool--------------------------|| \\
			 * // |\_________________________________________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\--////////////////////////////////// \\ 
			 */

			VKCommandPool::VKCommandPool(const VKDevice& device, const uint32_t queueFamilyIndex)
				: m_pDevice(&device)
			{
				VkCommandPoolCreateInfo poolInfo{};
				poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
				poolInfo.queueFamilyIndex = queueFamilyIndex;

				if (VK_FAILED(vkCreateCommandPool(device, &poolInfo, nullptr, &this->m_object)))
					throw std::runtime_error("[VULKAN] Failed To Create Command Pool");
			}

			VKCommandPool& VKCommandPool::operator=(VKCommandPool&& other) noexcept
			{
				this->m_object = other.m_object;
				other.m_object = VK_NULL_HANDLE;

				this->m_pDevice = std::move(other.m_pDevice);

				return *this;
			}

			VKCommandPool::~VKCommandPool()
			{
				vkDestroyCommandPool(*this->m_pDevice, this->m_object, nullptr);
			}

			/*
			 * // //////////////////////////////////-\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||-------------------------VKCommandBuffer-------------------------|| \\
			 * // |\_________________________________________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\-////////////////////////////////// \\ 
			 */

			VKCommandBuffer::VKCommandBuffer(const VKDevice& device, const VKCommandPool& commandPool)
				: m_pDevice(&device)
			{
				VkCommandBufferAllocateInfo allocInfo{};
				allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
				allocInfo.commandPool = commandPool;
				allocInfo.commandBufferCount = 1u;
				allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;

				if (VK_FAILED(vkAllocateCommandBuffers(device, &allocInfo, &this->m_object)))
					throw std::runtime_error("[VULKAN] Failed To Create Command Buffer");

				this->m_pGraphicsQueue = device.GetPresentQueuePtr();
			}

			VKCommandBuffer& VKCommandBuffer::operator=(VKCommandBuffer&& other) noexcept
			{
				this->m_object = other.m_object;
				other.m_object = VK_NULL_HANDLE;
				this->m_pGraphicsQueue = other.m_pGraphicsQueue;

				this->m_pDevice = other.m_pDevice;

				return *this;
			}

			void VKCommandBuffer::BeginRecording() const
			{
				VkCommandBufferBeginInfo beginInfo{};
				beginInfo.flags = 0;
				beginInfo.pInheritanceInfo = nullptr;
				beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

				if (VK_FAILED(vkBeginCommandBuffer(this->m_object, &beginInfo)))
					throw std::runtime_error("[VULKAN] Failed To Begin Command Buffer Recording");
			}

			void VKCommandBuffer::BeginRenderPass(const VKSwapChain& swapChain, const VkFramebuffer& frameBuffer, const VkRenderPass& renderPass) const noexcept
			{
				VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };

				VkRenderPassBeginInfo renderPassInfo{};
				renderPassInfo.renderPass  = renderPass;
				renderPassInfo.framebuffer = frameBuffer;
				renderPassInfo.clearValueCount = 1;
				renderPassInfo.pClearValues    = &clearColor;
				renderPassInfo.renderArea.offset = { 0, 0 };
				renderPassInfo.renderArea.extent = swapChain.GetImageExtent();
				renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;

				vkCmdBeginRenderPass(this->m_object, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
			}

			void VKCommandBuffer::BeginColorRenderPass(const VKSwapChain& swapChain) const noexcept
			{
				this->BeginRenderPass(swapChain, swapChain.GetColorFrameBuffer(swapChain.GetCurrentImageIndex()), VKRenderPass::s_colorRenderPass);
			}

			void VKCommandBuffer::EndRenderPass()
			{
				vkCmdEndRenderPass(this->m_object);
			}

			void VKCommandBuffer::EndRecording() const
			{
				if (VK_FAILED(vkEndCommandBuffer(this->m_object)))
					throw std::runtime_error("[VULKAN] Failed To End Command Buffer Recording");
			}
			
			void VKCommandBuffer::Submit(const VKSemaphore& swapChainImageAvailableSemaphore) const
			{
				VkSubmitInfo submitInfo{};
				submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

				VkSemaphore waitSemaphores[] = { swapChainImageAvailableSemaphore.m_object };
				VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
				submitInfo.waitSemaphoreCount = 1;
				submitInfo.pWaitSemaphores    = waitSemaphores;
				submitInfo.pWaitDstStageMask  = waitStages;
				submitInfo.commandBufferCount = 1;
				submitInfo.pCommandBuffers    = this->GetPtr();

				VkSemaphore signalSemaphores[]  = { this->m_pGraphicsQueue->m_semaphore.m_object };
				submitInfo.signalSemaphoreCount = 1;
				submitInfo.pSignalSemaphores    = signalSemaphores;

				if (VK_FAILED(vkQueueSubmit(*this->m_pGraphicsQueue, 1, &submitInfo, VK_NULL_HANDLE)))
					throw std::runtime_error("[VULKAN] Failed To Submit Draw Command Buffer");
			}

			/*
			 * // //////////////////////////////-\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||-------------------------VKQueue-------------------------|| \\
			 * // |\_________________________________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\-////////////////////////////// \\ 
			 */

			VKQueue::VKQueue(VKDevice& device, const size_t queueIndex)
			{
				this->m_semaphore = VKSemaphore(device);

				vkGetDeviceQueue(device, static_cast<uint32_t>(queueIndex), 0, &this->m_object);
			}

			void VKQueue::Submit(const std::vector<VkCommandBuffer>& commandBuffers) const
			{
				std::cout << this->m_semaphore.m_object << '\n';
				VkSubmitInfo submitInfo{};
				submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
				VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
				submitInfo.waitSemaphoreCount = 1u;
				submitInfo.pWaitSemaphores    = this->m_semaphore.GetPtr();
				submitInfo.pWaitDstStageMask  = waitStages;
				submitInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());
				submitInfo.pCommandBuffers    = commandBuffers.data();
				submitInfo.signalSemaphoreCount = 1;
				submitInfo.pSignalSemaphores = this->m_semaphore.GetPtr();

				if (VK_FAILED(vkQueueSubmit(this->m_object, 1, &submitInfo, VK_NULL_HANDLE)))
					throw std::runtime_error("[VULKAN] Failed To Submit Queue");
			}

			VKQueue& VKQueue::operator=(VKQueue&& other) noexcept
			{
				this->m_object = other.m_object;
				other.m_object = VK_NULL_HANDLE;

				this->m_semaphore = std::move(other.m_semaphore);

				return *this;
			}

			/*
			 * // //////////////////////////////-\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------------VKPhysicalDeviceDataWrapper---------------|| \\
			 * // |\_________________________________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\-////////////////////////////// \\ 
			 */

			VKPhysicalDeviceDataWrapper::VKPhysicalDeviceDataWrapper(const VkPhysicalDevice& physicalDevice, const VKSurface& surface)
				: m_physicalDevice(physicalDevice)
			{
				vkGetPhysicalDeviceFeatures  (physicalDevice, &this->m_features);
				vkGetPhysicalDeviceProperties(physicalDevice, &this->m_propreties);

				uint32_t familyCount;
				vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &familyCount, nullptr);

				this->m_queueFamilyPropreties.resize(familyCount);
				vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &familyCount, this->m_queueFamilyPropreties.data());

				uint32_t i = 0u;
				for (const VkQueueFamilyProperties& queueFamily : this->m_queueFamilyPropreties)
				{
					const VkQueueFlags queueFlags = queueFamily.queueFlags;

					if (queueFlags & VK_QUEUE_GRAPHICS_BIT)
						this->m_graphicsQueueIndex = i;


					VkBool32 presentSupport = false;
					vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &presentSupport);

					if (presentSupport)
						this->m_presentQueueIndex = i;

					i++;
				}
				
				switch (this->m_propreties.deviceType)
				{
				case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
					this->m_rating += 10u;
					break;
				case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
					this->m_rating += 3;
					break;
				}

				uint32_t extensionCount;
				vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

				this->m_extensionPropreties.resize(extensionCount);
				vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, this->m_extensionPropreties.data());
			}

			/*
			 * // ////////////////////--\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------------VKDevice---------------|| \\
			 * // |\______________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\--//////////////////// \\ 
			 */

			VKDevice::VKDevice(const VKInstance& instance, const VKSurface& surface)
			{
				this->PickPhysicalDevice(instance, surface);
				this->CreateLogicalDeviceAndQueues(instance);
			}

			VKDevice& VKDevice::operator=(VKDevice&& device) noexcept
			{
				this->m_graphicsQueue = std::move(device.m_graphicsQueue);
				this->m_physicalDeviceData = device.m_physicalDeviceData;
				this->m_graphicsQueue = std::move(device.m_graphicsQueue);
				this->m_presentQueue = std::move(device.m_presentQueue);
				this->m_object  = device.m_object;
				device.m_object = nullptr;

				return *this;
			}

			void VKDevice::PickPhysicalDevice(const VKInstance& instance, const VKSurface& surface)
			{
				// Get Physical Devices
				uint32_t deviceCount = 0;
				if (VK_FAILED(vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr)))
					throw std::runtime_error("[VULKAN] Failed To Enumerate Physical Devices");

				if (deviceCount == 0u)
					throw std::runtime_error("[VULKAN] No Vulkan Compatible Devices Where Found");

				std::vector<VkPhysicalDevice> devices(deviceCount);
				if (VK_FAILED(vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data())))
					throw std::runtime_error("[VULKAN] Failed To Enumerate Physical Devices");

				// Pick
				std::multimap<uint64_t, VKPhysicalDeviceDataWrapper> candidates;
				for (const VkPhysicalDevice& physicalDevice : devices)
				{
					const VKPhysicalDeviceDataWrapper physicalDeviceDataWrapper(physicalDevice, surface);

					if (physicalDeviceDataWrapper.m_graphicsQueueIndex.has_value() && physicalDeviceDataWrapper.m_presentQueueIndex.has_value())
						candidates.insert({ physicalDeviceDataWrapper.m_rating, physicalDeviceDataWrapper });
				}

				if (candidates.size() == 0u)
					throw std::runtime_error("[VULKAN] No Suitable Vulkan Compatible GPU Was Found");

				this->m_physicalDeviceData = candidates.rbegin()->second;
			}

			void VKDevice::CreateLogicalDeviceAndQueues(const VKInstance& instance)
			{
				/* Check Extension Support */
				const std::vector<const char*> requiredExtensions  = VKDevice::GetRequiredExtensions();

				for (const char* requiredExtension : requiredExtensions)
				{
					bool bFound = false;

					for (VkExtensionProperties& availableExtensionPropreties : this->m_physicalDeviceData.m_extensionPropreties)
					{
						if (strcmp(requiredExtension, availableExtensionPropreties.extensionName) == 0)
						{
							bFound = true;
							break;
						}
					}

					if (!bFound)
					{
						const std::string errorString = "[VULKAN] Extension \"" + std::string(requiredExtension) + std::string("\" Is Not Supported");
						throw std::runtime_error(errorString.c_str());
					}
				}

				/* Create Logical Device */

				std::array<VkDeviceQueueCreateInfo, 2u> queueCreateInfos;

				uint32_t i = 0u;
				for (VkDeviceQueueCreateInfo& queueCreateInfo : queueCreateInfos)
				{
					queueCreateInfo = {};
					queueCreateInfo.sType      = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
					queueCreateInfo.queueCount = 1u;
					queueCreateInfo.queueFamilyIndex = this->m_physicalDeviceData.m_queueIndices[i++].value();

					float queuePriority = 1.0f;
					queueCreateInfo.pQueuePriorities = &queuePriority;
				}

				VkPhysicalDeviceFeatures deviceFeatures = {};

				VkDeviceCreateInfo createInfo = {};
				createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
				createInfo.pQueueCreateInfos       = queueCreateInfos.data();
				createInfo.queueCreateInfoCount    = static_cast<uint32_t>(queueCreateInfos.size());
				createInfo.pEnabledFeatures        = &deviceFeatures;
				createInfo.enabledLayerCount       = 0u;
				createInfo.ppEnabledLayerNames     = nullptr;
				createInfo.enabledExtensionCount   = static_cast<uint32_t>(requiredExtensions.size());
				createInfo.ppEnabledExtensionNames = requiredExtensions.data();

				if (VK_FAILED(vkCreateDevice(this->m_physicalDeviceData.m_physicalDevice, &createInfo, nullptr, &this->m_object)))
					throw std::runtime_error("|VULKAN] Failed To Create Logical Device");

				/* Create The Queues */

				for (size_t i = 0u; i < queueCreateInfos.size(); i++)
					this->m_queues[i] = VKQueue(*this, this->m_physicalDeviceData.m_queueIndices[i].value());
			}

			std::vector<const char*> VKDevice::GetRequiredExtensions()  noexcept
			{
				return { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
			}

			/*
			 * // ////////////////////////--\\\\\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------------VKRenderPipeline---------------|| \\
			 * // |\______________________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\\\\--//////////////////////// \\ 
			 */

			VKRenderPipeline& VKRenderPipeline::operator=(VKRenderPipeline&& other)
			{
				this->m_layout = other.m_layout;
				other.m_layout = VK_NULL_HANDLE;

				this->m_pipeline = other.m_pipeline;
				other.m_pipeline = VK_NULL_HANDLE;

				this->m_pDevice = other.m_pDevice;

				return *this;
			}

			VKRenderPipeline::VKRenderPipeline(const VKDevice& device, const VKSwapChain& swapChain, const RenderPipelineDesc& pipelineDesc,
											std::vector<ConstantBuffer*>& pConstantBuffers, std::vector<Texture*> pTextures, std::vector<VKTextureSampler*> pTextureSamplers)
				: m_pDevice(&device)
			{
				const VkShaderModule vertexShaderModule = VKRenderPipeline::CreateShaderModule(device, pipelineDesc.vsFilename);
				const VkShaderModule pixelShaderModule  = VKRenderPipeline::CreateShaderModule(device, pipelineDesc.psFilename);

				VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
				vertShaderStageInfo.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				vertShaderStageInfo.stage  = VK_SHADER_STAGE_VERTEX_BIT;
				vertShaderStageInfo.module = vertexShaderModule;
				vertShaderStageInfo.pName  = "main";

				VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
				fragShaderStageInfo.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				fragShaderStageInfo.stage  = VK_SHADER_STAGE_FRAGMENT_BIT;
				fragShaderStageInfo.module = pixelShaderModule;
				fragShaderStageInfo.pName  = "main";

				const VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

				VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
				vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
				vertexInputInfo.vertexBindingDescriptionCount = 0;
				vertexInputInfo.pVertexBindingDescriptions    = nullptr;
				vertexInputInfo.vertexAttributeDescriptionCount = 0;
				vertexInputInfo.pVertexAttributeDescriptions    = nullptr;

				VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
				inputAssembly.sType    = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
				inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
				inputAssembly.primitiveRestartEnable = VK_FALSE;

				VkViewport viewport{};
				viewport.x = 0.0f;
				viewport.y = 0.0f;
				viewport.width  = (float)swapChain.GetImageExtent().width;
				viewport.height = (float)swapChain.GetImageExtent().height;
				viewport.minDepth = 0.0f;
				viewport.maxDepth = 1.0f;

				VkRect2D scissor{};
				scissor.offset = { 0, 0 };
				scissor.extent = swapChain.GetImageExtent();

				VkPipelineViewportStateCreateInfo viewportState{};
				viewportState.sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
				viewportState.viewportCount = 1;
				viewportState.pViewports    = &viewport;
				viewportState.scissorCount  = 1;
				viewportState.pScissors     = &scissor;

				VkPipelineRasterizationStateCreateInfo rasterizer{};
				rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
				rasterizer.depthClampEnable = VK_FALSE;
				rasterizer.rasterizerDiscardEnable = VK_FALSE;
				rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
				rasterizer.lineWidth   = 1.0f;
				rasterizer.cullMode  = VK_CULL_MODE_BACK_BIT;
				rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
				rasterizer.depthBiasEnable = VK_FALSE;
				rasterizer.depthBiasConstantFactor = 0.0f;
				rasterizer.depthBiasClamp          = 0.0f;
				rasterizer.depthBiasSlopeFactor    = 0.0f;

				VkPipelineMultisampleStateCreateInfo multisampling{};
				multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
				multisampling.sampleShadingEnable = VK_FALSE;
				multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
				multisampling.minSampleShading = 1.0f;
				multisampling.pSampleMask = nullptr;
				multisampling.alphaToCoverageEnable = VK_FALSE;
				multisampling.alphaToOneEnable = VK_FALSE;

				VkPipelineColorBlendAttachmentState colorBlendAttachment{};
				colorBlendAttachment.blendEnable = VK_TRUE;
				colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
				colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
				colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
				colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
				colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
				colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

				VkPipelineColorBlendStateCreateInfo colorBlending{};
				colorBlending.sType           = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
				colorBlending.logicOpEnable   = VK_FALSE;
				colorBlending.logicOp         = VK_LOGIC_OP_COPY;
				colorBlending.attachmentCount = 1;
				colorBlending.pAttachments    = &colorBlendAttachment;
				colorBlending.blendConstants[0] = 0.0f;
				colorBlending.blendConstants[1] = 0.0f;
				colorBlending.blendConstants[2] = 0.0f;
				colorBlending.blendConstants[3] = 0.0f;

				VkDynamicState dynamicStates[] = {
					VK_DYNAMIC_STATE_VIEWPORT
				};

				VkPipelineDynamicStateCreateInfo dynamicState{};
				dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
				dynamicState.dynamicStateCount = sizeof(dynamicStates) / sizeof(VkDynamicState);
				dynamicState.pDynamicStates    = dynamicStates;

				VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
				pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
				pipelineLayoutInfo.setLayoutCount = 0;
				pipelineLayoutInfo.pSetLayouts = nullptr;
				pipelineLayoutInfo.pushConstantRangeCount = 0;
				pipelineLayoutInfo.pPushConstantRanges = nullptr;

				if (FAILED(vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &this->m_layout)))
					throw std::runtime_error("failed to create pipeline layout!");


				VkGraphicsPipelineCreateInfo pipelineInfo{};
				pipelineInfo.sType      = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
				pipelineInfo.stageCount = sizeof(shaderStages) / sizeof(VkPipelineShaderStageCreateInfo);
				pipelineInfo.pStages    = shaderStages;
				pipelineInfo.pVertexInputState = &vertexInputInfo;
				pipelineInfo.pInputAssemblyState = &inputAssembly;
				pipelineInfo.pViewportState = &viewportState;
				pipelineInfo.pRasterizationState = &rasterizer;
				pipelineInfo.pMultisampleState = &multisampling;
				pipelineInfo.pDepthStencilState = nullptr; // Optional
				pipelineInfo.pColorBlendState = &colorBlending;
				pipelineInfo.pDynamicState = nullptr; // Optional
				pipelineInfo.layout     = this->m_layout;
				pipelineInfo.renderPass = VKRenderPass::s_colorRenderPass;
				pipelineInfo.subpass    = 0;
				pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
				pipelineInfo.basePipelineIndex = -1; // Optional

				if (VK_FAILED(vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &this->m_pipeline)))
					throw std::runtime_error("[VULKAN] Failed To Create Pipeline");

				vkDestroyShaderModule(device, vertexShaderModule, nullptr);
				vkDestroyShaderModule(device, pixelShaderModule,  nullptr);
			}

			VKRenderPipeline::~VKRenderPipeline()
			{
				vkDestroyPipeline(*this->m_pDevice, this->m_pipeline, nullptr);
				vkDestroyPipelineLayout(*this->m_pDevice, this->m_layout, nullptr);
			}

			VkShaderModule VKRenderPipeline::CreateShaderModule(const VKDevice& device, const char* filename)
			{
				std::ifstream file(filename, std::ios::ate | std::ios::binary);

				if (!file.is_open())
					throw std::runtime_error("[VULKAN] Failed To Open Binary Shader File");

				std::vector<char> contents(file.tellg());
				file.seekg(0);
				file.read(contents.data(), contents.size());
				file.close();

				VkShaderModuleCreateInfo createInfo{};
				createInfo.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
				createInfo.codeSize = contents.size();
				createInfo.pCode    = reinterpret_cast<const uint32_t*>(contents.data());

				VkShaderModule shaderModule;
				if (VK_FAILED(vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule)))
					throw std::runtime_error("[VULKAN] Failed To Create Shader Module");

				return shaderModule;
			}

			/*
			 * // ////////////////////////-\\\\\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||-----------------VKRenderAPI-----------------|| \\
			 * // |\_____________________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\\\\-//////////////////////// \\ 
			 */

			VKRenderAPI::~VKRenderAPI()
			{
				VKRenderPass::DestroyRenderPasses(this->m_device);
			}

			void VKRenderAPI::InitRenderAPI(Window* pWindow, const uint16_t maxFps)
			{
				this->m_instance  = VKInstance("App Made With Weiss Engine");
				this->m_surface   = VKSurface(&this->m_instance, pWindow);
				this->m_device    = VKDevice(this->m_instance, this->m_surface);
				this->m_swapChain = VKSwapChain(this->m_device, this->m_surface);
				this->m_commandPool   = VKCommandPool(this->m_device, this->m_device.GetPhysicalDeviceData().m_graphicsQueueIndex.value());
				this->m_commandBuffer = VKCommandBuffer(this->m_device, this->m_commandPool);

				VKRenderPass::CreateRenderPasses(this->m_device, this->m_swapChain);

				this->m_swapChain.CreateFrameBuffers();
			}

			void VKRenderAPI::InitPipelines(const std::vector<RenderPipelineDesc>& pipelineDescs)
			{

			}

			void VKRenderAPI::Draw(const Drawable& drawable, const size_t nVertices)
			{
				this->m_commandBuffer.BeginColorRenderPass(this->m_swapChain);
				//vkCmdDraw(this->m_commandBuffer, 3u, 0u, 0u, 0u);
			}

			void VKRenderAPI::BeginDrawing()
			{
				this->m_swapChain.GetNextImage();
				this->m_commandBuffer.BeginRecording();
			}

			void VKRenderAPI::EndDrawing()
			{
				this->m_commandBuffer.EndRenderPass();
				this->m_commandBuffer.EndRecording();
				this->m_commandBuffer.Submit(this->m_device.GetPresentQueuePtr()->m_semaphore);
			}

			void VKRenderAPI::Present(const bool vSync)
			{
				this->m_swapChain.Present();
			}

			size_t VKRenderAPI::CreateVertexBuffer(const size_t nVertices, const size_t vertexSize)
			{
				return 0u;
			}

			size_t VKRenderAPI::CreateIndexBuffer(const size_t nIndices)
			{
				return 0u;
			}

			size_t VKRenderAPI::CreateConstantBuffer(const size_t objSize, const size_t slot)
			{
				return 0u;
			}

			size_t VKRenderAPI::CreateTexture(const size_t width, const size_t height, const size_t slot, const bool useMipmaps)
			{
				return 0u;
			}

			size_t VKRenderAPI::CreateTextureSampler(const TextureFilter& filter, const size_t slot)
			{
				return 0u;
			}

			void VKRenderAPI::Fill(const Colorf32& color)
			{

			}

		}; // namespace VK

		/*
		 * // /////////////////////-\\\\\\\\\\\\\\\\\\\\\ \\
		 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
		 * // ||-----------------D3D11-----------------|| \\
		 * // |\_______________________________________/| \\
		 * // \\\\\\\\\\\\\\\\\\\\\-///////////////////// \\ 
		 */

		namespace D3D11 {

			/*
			 * // /////////////////////-\\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D11ObjectWrapper<T>---------|| \\
			 * // |\_______________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\-///////////////////// \\ 
			 */

			template <typename T>
			D3D11ObjectWrapper<T>& D3D11ObjectWrapper<T>::operator=(D3D11ObjectWrapper<T>&& other)
			{
				this->m_pObject = other.m_pObject;
				other.m_pObject = nullptr;

				return *this;
			}

			template <typename T>
			D3D11ObjectWrapper<T>::~D3D11ObjectWrapper()
			{
				if (this->m_pObject)
				{
					this->m_pObject->Release();
					this->m_pObject = nullptr;
				}
			}

			/*
			 * // ////////////////////--\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||------------D3D11SwapChain------------|| \\
			 * // |\______________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\--//////////////////// \\ 
			 */

			D3D11SwapChain::D3D11SwapChain(D3D11DeviceObjectWrapper& pDevice, Window* pWindow)
			{
				Microsoft::WRL::ComPtr<IDXGIDevice>  dxgiDevice;
				Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter;
				Microsoft::WRL::ComPtr<IDXGIFactory> dxgiFactory;

				if (DX_FAILED(pDevice->QueryInterface(IID_PPV_ARGS(&dxgiDevice))))
					throw std::runtime_error("Could Not Get IDXGIDevice From D3D11Device");

				if (DX_FAILED(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf())))
					throw std::runtime_error("Could Not Get DXGIAdapter From DXGIDevice");

				if (DX_FAILED(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), &dxgiFactory)))
					throw std::runtime_error("Could Not Get DXGIAdapter's Parent");

				DXGI_SWAP_CHAIN_DESC scd{};
				scd.BufferDesc.Width  = 0;
				scd.BufferDesc.Height = 0;
				scd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
				scd.BufferDesc.RefreshRate.Numerator   = 0;
				scd.BufferDesc.RefreshRate.Denominator = 0;
				scd.BufferDesc.Scaling          = DXGI_MODE_SCALING_UNSPECIFIED;
				scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
				scd.SampleDesc.Count   = 1;
				scd.SampleDesc.Quality = 0;
				scd.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
				scd.BufferCount  = WEISS__FRAME_BUFFER_COUNT;
				scd.OutputWindow = reinterpret_cast<WS::WIN::WindowsWindow*>(pWindow)->GetHandle();
				scd.Windowed     = TRUE;
				scd.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
				scd.Flags = 0;

				if (DX_FAILED(dxgiFactory->CreateSwapChain(pDevice, &scd, &this->m_pObject)))
					throw std::runtime_error("[DIRECTX 11] Failed To Create Swap Chain");
			}

			D3D11SwapChain& D3D11SwapChain::operator=(D3D11SwapChain&& other) noexcept
			{
				this->m_pObject = other.m_pObject;
				other.m_pObject = nullptr;

				return *this;
			}

			void D3D11SwapChain::Present(const bool vSync)
			{
				if (DX_FAILED(this->m_pObject->Present(vSync ? 1u : 0u, 0u)))
					throw std::runtime_error("Failed To Swap Buffers");
			}

			/*
			 * // //////////////////////-\\\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||------------D3D11RenderTarget------------|| \\
			 * // |\_________________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\\-////////////////////// \\ 
			 */

			D3D11RenderTarget::D3D11RenderTarget(D3D11DeviceObjectWrapper& pDevice, D3D11SwapChainObjectWrapper& pSwapChain)
			{
				Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;

				if (DX_FAILED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer)))
					throw std::runtime_error("[DIRECTX 11] Could Not Get BackBuffer");

				if (DX_FAILED(pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &this->m_pObject)))
					throw std::runtime_error("[DIRECTX 11] Could Not Create RenderTargetView");
			}

			D3D11RenderTarget& D3D11RenderTarget::operator=(D3D11RenderTarget&& other) noexcept
			{
				this->m_pObject = other.m_pObject;
				other.m_pObject = nullptr;

				return *this;
			}

			void D3D11RenderTarget::SetCurrent(D3D11DeviceContextObjectWrapper& pDeviceContext) const noexcept
			{
				pDeviceContext->OMSetRenderTargets(1u, &this->m_pObject, NULL);
			}

			/*
			 * // /////////////////////--\\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||------------D3D11DepthBuffer------------|| \\
			 * // |\________________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\--///////////////////// \\ 
			 */

			D3D11DepthBuffer::D3D11DepthBuffer(Window* pWindow, D3D11DeviceObjectWrapper& pDevice)
			{
				D3D11_DEPTH_STENCIL_DESC dsDesc = {};
				dsDesc.DepthEnable      = TRUE;
				dsDesc.DepthWriteMask   = D3D11_DEPTH_WRITE_MASK_ALL;
				dsDesc.DepthFunc        = D3D11_COMPARISON_LESS;
				dsDesc.StencilReadMask  = 0xFF;
				dsDesc.StencilWriteMask = 0xFF;
				dsDesc.FrontFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;
				dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
				dsDesc.FrontFace.StencilPassOp      = D3D11_STENCIL_OP_KEEP;
				dsDesc.FrontFace.StencilFunc        = D3D11_COMPARISON_ALWAYS;
				dsDesc.BackFace.StencilFailOp       = D3D11_STENCIL_OP_KEEP;
				dsDesc.BackFace.StencilDepthFailOp  = D3D11_STENCIL_OP_DECR;
				dsDesc.BackFace.StencilPassOp       = D3D11_STENCIL_OP_KEEP;
				dsDesc.BackFace.StencilFunc         = D3D11_COMPARISON_ALWAYS;

				if (DX_FAILED(pDevice->CreateDepthStencilState(&dsDesc, &this->m_pDepthStencilState)))
					throw std::runtime_error("Could Not Create DepthStencilState");

				Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthStencil;
				D3D11_TEXTURE2D_DESC descDepth = {};
				descDepth.Width  = pWindow->GetClientWidth();
				descDepth.Height = pWindow->GetClientHeight();
				descDepth.MipLevels = 1u;
				descDepth.ArraySize = 1u;
				descDepth.Format    = DXGI_FORMAT_D32_FLOAT;
				descDepth.SampleDesc.Count   = 1u;
				descDepth.SampleDesc.Quality = 0u;
				descDepth.Usage     = D3D11_USAGE_DEFAULT;
				descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;

				if (DX_FAILED(pDevice->CreateTexture2D(&descDepth, nullptr, &pDepthStencil)))
					throw std::runtime_error("Could Not Create Texture2D");

				D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
				descDSV.Format             = DXGI_FORMAT_D32_FLOAT;
				descDSV.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
				descDSV.Texture2D.MipSlice = 0u;

				if (DX_FAILED(pDevice->CreateDepthStencilView(pDepthStencil.Get(), &descDSV, &this->m_pDepthStencilView)))
					throw std::runtime_error("Could Not Create DepthStencilView");
			}

			void D3D11DepthBuffer::Clear(D3D11DeviceContextObjectWrapper& pDeviceContext)
			{
				pDeviceContext->ClearDepthStencilView(this->m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
			}

			void D3D11DepthBuffer::Bind(D3D11DeviceContextObjectWrapper& pDeviceContext, D3D11RenderTargetbjectWrapper& pRenderTarget)
			{
				pDeviceContext->OMSetRenderTargets(1u, pRenderTarget.GetPtr(), this->m_pDepthStencilView.Get());
				pDeviceContext->OMSetDepthStencilState(this->m_pDepthStencilState.Get(), 1u);
			}

			/*
			 * // //////////////////////-\\\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||------------D3D11VertexShader------------|| \\
			 * // |\_________________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\\-////////////////////// \\ 
			 */

			D3D11VertexShader::D3D11VertexShader(D3D11DeviceObjectWrapper& pDevice,
										 D3D11DeviceContextObjectWrapper* pDeviceContext,
										 const char* sourceFilename, const std::vector<ShaderInputElement>& sies)
				: m_pDeviceContext(pDeviceContext)
			{
				Microsoft::WRL::ComPtr<ID3DBlob> pBlob;

				// Create Shader
				std::ifstream fileStream(sourceFilename);
				std::string   sourceCode((std::istreambuf_iterator<char>(fileStream)), (std::istreambuf_iterator<char>()));

				if (D3DCompile(sourceCode.c_str(), sourceCode.size(), NULL, NULL, NULL, "main", "vs_5_0", 0, 0, &pBlob, NULL) != S_OK)
					throw std::runtime_error("Could Not Compile Vertex Shader");

				if (pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &this->m_pShader) != S_OK)
					throw std::runtime_error("Could Not Create Vertex Shader");

				// Create Input Layout
				std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDescriptors(sies.size());
				for (uint32_t i = 0; i < inputElementDescriptors.size(); i++)
				{
					inputElementDescriptors[i] = D3D11_INPUT_ELEMENT_DESC{};
					inputElementDescriptors[i].SemanticName = sies[i].name;

					switch (sies[i].type)
					{
					case ShaderInputElementType::FLOAT_32:
						inputElementDescriptors[i].Format = DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
						break;
					case ShaderInputElementType::UINT_32:
						inputElementDescriptors[i].Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
						break;
					case ShaderInputElementType::VECTOR_2D_FLOAT_32:
						inputElementDescriptors[i].Format = DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
						break;
					case ShaderInputElementType::VECTOR_3D_FLOAT_32:
						inputElementDescriptors[i].Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
						break;
					case ShaderInputElementType::VECTOR_4D_FLOAT_32:
						inputElementDescriptors[i].Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
						break;
					default:
						throw std::runtime_error("Input Element Type Not Supported");
					}

					inputElementDescriptors[i].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
					inputElementDescriptors[i].InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
				}

				if (pDevice->CreateInputLayout(inputElementDescriptors.data(), (UINT)inputElementDescriptors.size(), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &this->m_pInputLayout) != S_OK)
					throw std::runtime_error("Could Not Create Input Layout");
			}

			void D3D11VertexShader::Bind() const noexcept
			{
				(*this->m_pDeviceContext)->IASetInputLayout(this->m_pInputLayout.Get());
				(*this->m_pDeviceContext)->VSSetShader(this->m_pShader.Get(), nullptr, 0u);
			}

			/*
			 * // /////////////////////--\\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||------------D3D11PixelShader------------|| \\
			 * // |\________________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\--///////////////////// \\ 
			 */

			D3D11PixelShader::D3D11PixelShader(D3D11DeviceObjectWrapper& pDevice,
									   D3D11DeviceContextObjectWrapper* pDeviceContext,
									   const char* sourceFilename)
				: m_pDeviceContext(pDeviceContext)
			{
				Microsoft::WRL::ComPtr<ID3DBlob> pBlob;

				std::ifstream fileStream(sourceFilename);
				std::string sourceCode((std::istreambuf_iterator<char>(fileStream)), (std::istreambuf_iterator<char>()));

				if (D3DCompile(sourceCode.c_str(), sourceCode.size(), NULL, NULL, NULL, "main", "ps_5_0", 0, 0, &pBlob, NULL) != S_OK)
					throw std::runtime_error("Could Not Compile Pixel Shader");

				if (pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &this->m_pShader) != S_OK)
					throw std::runtime_error("Could Not Create Pixel Shader");
				}

			void D3D11PixelShader::Bind() const noexcept
			{
				(*this->m_pDeviceContext)->PSSetShader(this->m_pShader.Get(), nullptr, 0u);
			}

			/*
			 * // //////////////////////-\\\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||------------D3D11VertexBuffer------------|| \\
			 * // |\_________________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\\-////////////////////// \\ 
			 */

			D3D11VertexBuffer::D3D11VertexBuffer(D3D11DeviceObjectWrapper& pDevice,
										 D3D11DeviceContextObjectWrapper* pDeviceContext,
										 const size_t nVertices, const size_t vertexSize)
				: m_vertexSize(vertexSize), m_pDeviceContext(pDeviceContext)
			{
				D3D11_BUFFER_DESC bd = {};
				bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				bd.Usage = D3D11_USAGE_DYNAMIC;
				bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				bd.MiscFlags = 0u;
				bd.ByteWidth = static_cast<UINT>(nVertices * this->m_vertexSize);
				bd.StructureByteStride = static_cast<UINT>(this->m_vertexSize);

				this->m_vertexData.resize(bd.ByteWidth);
				std::memset(this->m_vertexData.data(), 0, bd.ByteWidth);

				if (DX_FAILED(pDevice->CreateBuffer(&bd, nullptr, &this->m_pObject)))
					throw std::runtime_error("Unable To Create Vertex Buffer");
			}

			D3D11VertexBuffer& D3D11VertexBuffer::operator=(D3D11VertexBuffer&& other) noexcept
			{
				this->m_pObject = other.m_pObject;
				other.m_pObject = nullptr;
				this->m_vertexData = std::move(other.m_vertexData);
				this->m_vertexSize = std::move(other.m_vertexSize);

				return *this;
			}

			void D3D11VertexBuffer::Bind()
			{
				const UINT stride = static_cast<UINT>(this->m_vertexSize);
				const UINT offset = 0u;

				(*this->m_pDeviceContext)->IASetVertexBuffers(0u, 1u, &this->m_pObject, &stride, &offset);
			}

			void D3D11VertexBuffer::Update()
			{
				D3D11_MAPPED_SUBRESOURCE resource;
				if (DX_FAILED((*this->m_pDeviceContext)->Map(this->m_pObject, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource)))
					throw std::runtime_error("Could Not Map Vertex Buffer Memory");

				std::memcpy(resource.pData, this->m_vertexData.data(), this->m_vertexData.size());
				(*this->m_pDeviceContext)->Unmap(this->m_pObject, 0);
			}

			/*
			 * // /////////////////////--\\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||------------D3D11IndexBuffer------------|| \\
			 * // |\________________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\--///////////////////// \\ 
			 */

			D3D11IndexBuffer::D3D11IndexBuffer(D3D11DeviceObjectWrapper& pDevice,
									   D3D11DeviceContextObjectWrapper* pDeviceContext,
									   const size_t nIndices)
				: m_nIndices(nIndices), m_pDeviceContext(pDeviceContext)
			{
				D3D11_BUFFER_DESC bd = {};
				bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
				bd.Usage = D3D11_USAGE_DYNAMIC;
				bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				bd.MiscFlags = 0u;
				bd.ByteWidth = static_cast<UINT>(this->m_nIndices * sizeof(uint32_t));
				bd.StructureByteStride = static_cast<UINT>(sizeof(uint32_t));

				this->m_indexData.resize(bd.ByteWidth);
				std::memset(this->m_indexData.data(), 0, bd.ByteWidth);

				if (DX_FAILED(pDevice->CreateBuffer(&bd, nullptr, &this->m_pObject)))
					throw std::runtime_error("Unable To Create Index Buffer");
			}

			D3D11IndexBuffer& D3D11IndexBuffer::operator=(D3D11IndexBuffer&& other) noexcept
			{
				this->m_pObject = other.m_pObject;
				other.m_pObject = nullptr;
			
				other.m_nIndices  = other.m_nIndices;
				other.m_indexData = std::move(other.m_indexData);

				return *this;
			}

			void D3D11IndexBuffer::Bind()
			{
				(*this->m_pDeviceContext)->IASetIndexBuffer(this->m_pObject, DXGI_FORMAT_R32_UINT, 0u);
			}

			void D3D11IndexBuffer::Update()
			{
				D3D11_MAPPED_SUBRESOURCE resource;
				if (DX_FAILED((*this->m_pDeviceContext)->Map(this->m_pObject, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource)))
					throw std::runtime_error("Could Not Map Index Buffer Memory");

				std::memcpy(resource.pData, this->m_indexData.data(), this->m_indexData.size());
				(*this->m_pDeviceContext)->Unmap(this->m_pObject, 0);
			}

			/*
			 * // ///////////////////////-\\\\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||------------D3D11ConstantBuffer------------|| \\
			 * // |\___________________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\\\-/////////////////////// \\ 
			 */

			D3D11ConstantBuffer::D3D11ConstantBuffer(D3D11DeviceObjectWrapper& pDevice,
											 D3D11DeviceContextObjectWrapper* pDeviceContext,
											 const size_t objSize, const size_t slot)
				: m_objSize(objSize), m_slot(slot), m_pDeviceContext(pDeviceContext)
			{
				D3D11_BUFFER_DESC bd = {};
				bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				bd.Usage = D3D11_USAGE_DYNAMIC;
				bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				bd.MiscFlags = 0u;
				bd.ByteWidth = static_cast<UINT>(this->m_objSize);

				this->m_constantBufferData.resize(bd.ByteWidth);
				std::memset(this->m_constantBufferData.data(), 0, bd.ByteWidth);

				if (DX_FAILED(pDevice->CreateBuffer(&bd, nullptr, &this->m_pObject)))
					throw std::runtime_error("[DIRECTX 11] Unable To Create Constant Buffer");
			}

			D3D11ConstantBuffer& D3D11ConstantBuffer::operator=(D3D11ConstantBuffer&& other) noexcept
			{
				this->m_pObject = other.m_pObject;
				other.m_pObject = nullptr;

				this->m_slot    = other.m_slot;
				this->m_objSize = other.m_objSize;
				this->m_constantBufferData = std::move(other.m_constantBufferData);
				
				return *this;
			}

			void D3D11ConstantBuffer::Bind()
			{
				(*this->m_pDeviceContext)->VSSetConstantBuffers((UINT)this->m_slot, 1u, &this->m_pObject);
			}

			void D3D11ConstantBuffer::Update()
			{
				D3D11_MAPPED_SUBRESOURCE resource;
				if (DX_FAILED((*this->m_pDeviceContext)->Map(this->m_pObject, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &resource)))
					throw std::runtime_error("[DIRECTX 11] Failed To Map Constant Buffer Memory");

				std::memcpy(resource.pData, this->m_constantBufferData.data(), this->m_objSize);
				(*this->m_pDeviceContext)->Unmap(this->m_pObject, 0u);
			}

			/*
			 * // ///////////////////--\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||------------D3D11Texture------------|| \\
			 * // |\____________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\--/////////////////// \\ 
			 */

			D3D11Texture::D3D11Texture(D3D11DeviceObjectWrapper& pDevice,
                               D3D11DeviceContextObjectWrapper* pDeviceContext,
                               const size_t width, const size_t height, const size_t slot, const bool useMipmaps)
				: m_pDeviceContext(pDeviceContext), m_pDevice(&pDevice), m_slot(slot)
			{
				D3D11_TEXTURE2D_DESC texture2DDescriptor = {};
				texture2DDescriptor.Width     = static_cast<UINT>(width);
				texture2DDescriptor.Height    = static_cast<UINT>(height);
				texture2DDescriptor.MipLevels = useMipmaps ? 0 : 1;
				texture2DDescriptor.ArraySize = 1u;
				texture2DDescriptor.Format    = DXGI_FORMAT_R8G8B8A8_UNORM;
				texture2DDescriptor.SampleDesc.Count   = 1u;
				texture2DDescriptor.SampleDesc.Quality = 0;
				texture2DDescriptor.Usage     = D3D11_USAGE_DEFAULT;
				texture2DDescriptor.BindFlags = useMipmaps ? D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET : D3D11_BIND_SHADER_RESOURCE;
				texture2DDescriptor.MiscFlags = useMipmaps ? D3D11_RESOURCE_MISC_GENERATE_MIPS : 0;

				if (DX_FAILED(pDevice->CreateTexture2D(&texture2DDescriptor, nullptr, &this->m_texture2D)))
					throw std::runtime_error("[DIRECTX 11] Failed To Create Texture");

				D3D11_SHADER_RESOURCE_VIEW_DESC SRVDescriptor = {};
				SRVDescriptor.Format                    = DXGI_FORMAT_R8G8B8A8_UNORM;
				SRVDescriptor.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
				SRVDescriptor.Texture2D.MostDetailedMip = 0;
				SRVDescriptor.Texture2D.MipLevels       = useMipmaps ? -1 : 1;

				if (DX_FAILED(pDevice->CreateShaderResourceView(this->m_texture2D.Get(), &SRVDescriptor, &this->m_pObject)))
					throw std::runtime_error("[DIRECTX 11] Failed To Create Shader Resource View");
			}

			void D3D11Texture::Bind() const noexcept
			{
				(*this->m_pDeviceContext)->VSSetShaderResources(static_cast<UINT>(this->m_slot), 1u, &this->m_pObject);
				(*this->m_pDeviceContext)->PSSetShaderResources(static_cast<UINT>(this->m_slot), 1u, &this->m_pObject);
			}

			void D3D11Texture::Update()
			{
				D3D11_SUBRESOURCE_DATA* subResourceData = new D3D11_SUBRESOURCE_DATA();
				subResourceData->pSysMem          = static_cast<void*>(this->m_image.GetBuffer());
				subResourceData->SysMemPitch      = this->m_image.GetWidth() * sizeof(Coloru8);
				subResourceData->SysMemSlicePitch = 0;

				this->m_pDeviceContext->Get()->UpdateSubresource(this->m_texture2D.Get(), 0u, nullptr, subResourceData->pSysMem, subResourceData->SysMemPitch, 0u);

				if (this->m_useMipmaps)
					this->m_pDeviceContext->Get()->GenerateMips(this->m_pObject);
			}

			/*
			 * // ////////////////////-\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D11TextureSampler---------|| \\
			 * // |\_____________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\-//////////////////// \\ 
			 */

			D3D11TextureSampler::D3D11TextureSampler(D3D11DeviceObjectWrapper& pDevice,
                                             D3D11DeviceContextObjectWrapper* pDeviceContext,
                                             const TextureFilter& filter, const size_t slot)
				: m_pDeviceContext(pDeviceContext), m_slot(slot)
			{
				D3D11_SAMPLER_DESC samplerDescriptor;

				switch (filter)
				{
				case TextureFilter::POINT:
					samplerDescriptor.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
					break;
				case TextureFilter::BILINEAR:
					samplerDescriptor.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
					break;
				case TextureFilter::TRILINEAR:
					samplerDescriptor.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
					break;
				default:
					throw std::runtime_error("[DIRECTX 11] Your Filtering Method Is Not Supported");
				}

				samplerDescriptor.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
				samplerDescriptor.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
				samplerDescriptor.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
				samplerDescriptor.MaxAnisotropy = D3D11_MAX_MAXANISOTROPY;
				samplerDescriptor.ComparisonFunc = D3D11_COMPARISON_NEVER;
				samplerDescriptor.MipLODBias = 0.0f;
				samplerDescriptor.MinLOD = 0.0f;
				samplerDescriptor.MaxLOD = D3D11_FLOAT32_MAX;

				if (DX_FAILED(pDevice->CreateSamplerState(&samplerDescriptor, &this->m_pObject)))
					throw std::runtime_error("[DIRECTX 11] Failed To Create Sampler State");
			}

			void D3D11TextureSampler::Bind() const noexcept
			{
				(*this->m_pDeviceContext)->VSSetSamplers(static_cast<UINT>(this->m_slot), 1u, &this->m_pObject);
				(*this->m_pDeviceContext)->PSSetSamplers(static_cast<UINT>(this->m_slot), 1u, &this->m_pObject);
			}

			/*
			 * // ////////////////////-\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D11RenderPipeline---------|| \\
			 * // |\_____________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\-//////////////////// \\ 
			 */

			D3D11RenderPipeline::D3D11RenderPipeline(D3D11DeviceObjectWrapper& pDevice,
											 D3D11DeviceContextObjectWrapper* pDeviceContext,
											 const RenderPipelineDesc& desc)
				: m_pDeviceContext(pDeviceContext),      m_constantBufferIndices(desc.constantBufferIndices),
				m_textureIndices(desc.textureIndices), m_textureSamplerIndices(desc.textureSamplerIndices)
			{
				switch (desc.topology)
				{
				case PrimitiveTopology::TRIANGLES:
					this->m_topology = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
					break;
				case PrimitiveTopology::TRIANGLE_STRIP:
					this->m_topology = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
					break;
				default:
					throw std::runtime_error("[DIRECTX 11] Requested Primitive Topology Is Not Supported");
					break;
				}

				this->m_pVertexShader = D3D11VertexShader(pDevice, pDeviceContext, desc.vsFilename, desc.sies);
				this->m_pPixelShader  = D3D11PixelShader(pDevice, pDeviceContext, desc.psFilename);
			}

			void D3D11RenderPipeline::Bind(std::vector<ConstantBuffer*>& constantBuffers,
										std::vector<Texture*>& textures,
										std::vector<D3D11TextureSampler*> textureSamplers) noexcept
			{
				this->m_pVertexShader.Bind();
				this->m_pPixelShader.Bind();

				for (uint32_t cbIndex : this->m_constantBufferIndices)
					dynamic_cast<D3D11ConstantBuffer*>(constantBuffers[cbIndex])->Bind();

				for (uint32_t texIndex : this->m_textureIndices)
					dynamic_cast<D3D11Texture*>(textures[texIndex])->Bind();

				for (uint32_t texSamplerIndex : this->m_textureSamplerIndices)
					textureSamplers[texSamplerIndex]->Bind();

				(*this->m_pDeviceContext)->IASetPrimitiveTopology(this->m_topology);
			}

			/*
			 * // /////////////////--\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D11RenderAPI---------|| \\
			 * // |\________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\--///////////////// \\ 
			 */

			void D3D11RenderAPI::InitRenderAPI(Window* pWindow, const uint16_t maxFps)
			{
				if (D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, this->m_pDevice.GetPtr(), nullptr, this->m_pDeviceContext.GetPtr()) != S_OK)
					throw std::runtime_error("Could Not Create Device");

				this->m_pSwapChain    = D3D11SwapChain(this->m_pDevice, pWindow);
				this->m_pRenderTarget = D3D11RenderTarget(this->m_pDevice, this->m_pSwapChain);
				this->m_pDepthBuffer  = D3D11DepthBuffer(pWindow, this->m_pDevice);

				this->m_pRenderTarget.SetCurrent(this->m_pDeviceContext);

				// Create Viewport
				D3D11_VIEWPORT vp;
				vp.Width    = static_cast<FLOAT>(pWindow->GetClientWidth());
				vp.Height   = static_cast<FLOAT>(pWindow->GetClientHeight());
				vp.MinDepth = 0;
				vp.MaxDepth = 1;
				vp.TopLeftX = 0;
				vp.TopLeftY = 0;

				this->m_pDeviceContext->RSSetViewports(1u, &vp);

				this->m_pDepthBuffer.Bind(this->m_pDeviceContext, this->m_pRenderTarget);
			}

			void D3D11RenderAPI::InitPipelines(const std::vector<RenderPipelineDesc>& pipelineDescs)
			{
				this->m_pRenderPipelines.reserve(pipelineDescs.size());
				for (const RenderPipelineDesc& pipelineDesc : pipelineDescs)
					this->m_pRenderPipelines.emplace_back(this->m_pDevice, &this->m_pDeviceContext, pipelineDesc);
			}

			void D3D11RenderAPI::Draw(const Drawable& drawable, const size_t nVertices)
			{
				this->m_pRenderPipelines[drawable.pipelineIndex].Bind(this->m_pConstantBuffers, this->m_pTextures, this->m_pTextureSamplers);
				dynamic_cast<D3D11VertexBuffer*>(this->m_pVertexBuffers[drawable.vertexBufferIndex])->Bind();

				if (drawable.indexBufferIndex.has_value()) {
					dynamic_cast<D3D11IndexBuffer*>(this->m_pIndexBuffers[drawable.indexBufferIndex.value()])->Bind();

					this->m_pDeviceContext->DrawIndexed(static_cast<UINT>(nVertices), 0u, 0u);
				} else {
					this->m_pDeviceContext->Draw(static_cast<UINT>(nVertices), 0u);
				}
			}

			void D3D11RenderAPI::BeginDrawing()
			{
				this->Fill();
			}

			void D3D11RenderAPI::EndDrawing()
			{
				this->m_pDepthBuffer.Clear(this->m_pDeviceContext);
			}

			void D3D11RenderAPI::Present(const bool vSync)
			{
				this->m_pSwapChain.Present(vSync);
			}

			size_t D3D11RenderAPI::CreateVertexBuffer(const size_t nVertices, const size_t vertexSize)
			{
				this->m_pVertexBuffers.push_back(new D3D11VertexBuffer(this->m_pDevice, &this->m_pDeviceContext, nVertices, vertexSize));

				return this->m_pVertexBuffers.size() - 1u;
			}

			size_t D3D11RenderAPI::CreateIndexBuffer(const size_t nIndices)
			{
				this->m_pIndexBuffers.push_back(new D3D11IndexBuffer(this->m_pDevice, &this->m_pDeviceContext, nIndices));

				return this->m_pIndexBuffers.size() - 1u;
			}

			size_t D3D11RenderAPI::CreateConstantBuffer(const size_t objSize, const size_t slot)
			{
				this->m_pConstantBuffers.push_back(new D3D11ConstantBuffer(this->m_pDevice, &this->m_pDeviceContext, objSize, slot));

				return this->m_pConstantBuffers.size() - 1u;
			}

			size_t D3D11RenderAPI::CreateTexture(const size_t width, const size_t height, const size_t slot, const bool useMipmaps)
			{
				this->m_pTextures.push_back(new D3D11Texture(this->m_pDevice, &this->m_pDeviceContext, width, height, slot, useMipmaps));

				return this->m_pTextures.size() - 1u;
			}

			size_t D3D11RenderAPI::CreateTextureSampler(const TextureFilter& filter, const size_t slot)
			{
				this->m_pTextureSamplers.push_back(new D3D11TextureSampler(this->m_pDevice, &this->m_pDeviceContext, filter, slot));

				return this->m_pTextureSamplers.size() - 1u;
			}

			void D3D11RenderAPI::Fill(const Colorf32& color)
			{
				this->m_pDeviceContext->ClearRenderTargetView(this->m_pRenderTarget, (float*)&color);
			}

		}; // namespace D3D11

		/*
		 * // /////////////////////-\\\\\\\\\\\\\\\\\\\\\ \\
		 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
		 * // ||-----------------D3D12-----------------|| \\
		 * // |\_______________________________________/| \\
		 * // \\\\\\\\\\\\\\\\\\\\\-///////////////////// \\ 
		 */

		namespace D3D12 {

			/*
			 * // /////////////////////-\\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D12ObjectWrapper<T>---------|| \\
			 * // |\_______________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\-///////////////////// \\ 
			 */

			template <typename T>
			D3D12ObjectWrapper<T>& D3D12ObjectWrapper<T>::operator=(D3D12ObjectWrapper<T>&& other) noexcept
			{
				this->m_pObject = other.m_pObject;
				other.m_pObject = nullptr;

				return *this;
			}

			template <typename T>
			D3D12ObjectWrapper<T>::~D3D12ObjectWrapper()
			{
				if (this->m_pObject)
				{
					this->m_pObject->Release();
					this->m_pObject = nullptr;
				}
			}

			/*
			 * // ////////////////--\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D12Adapter---------|| \\
			 * // |\______________________________/| \\
			 * // \\\\\\\\\\\\\\\\--//////////////// \\ 
			 */

			D3D12Adapter::D3D12Adapter()
			{
				IDXGIFactory4* dxgiFactory;
				if (DX_FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory))))
					throw std::runtime_error("[DIRECTX 12] Failed To Create DXGIFactory1");

				int adapterIndex = 0;

				while (dxgiFactory->EnumAdapters1(adapterIndex, &this->m_pObject) != DXGI_ERROR_NOT_FOUND)
				{
					DXGI_ADAPTER_DESC1 desc;
					this->m_pObject->GetDesc1(&desc);

					if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
						continue;
					
					if (SUCCEEDED(D3D12CreateDevice(this->m_pObject, D3D_FEATURE_LEVEL_12_1, _uuidof(ID3D12Device2), nullptr)))
						return;

					adapterIndex++;
				}

				throw std::runtime_error("[DIRECTX 12] Failed To Create Adapter");
			}

			D3D12Adapter& D3D12Adapter::operator=(D3D12Adapter&& other) noexcept
			{
				this->m_pObject = other.m_pObject;
				other.m_pObject = nullptr;

				return *this;
			}

			/*
			 * // ////////////////-\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D12Device---------|| \\
			 * // |\_____________________________/| \\
			 * // \\\\\\\\\\\\\\\\-//////////////// \\ 
			 */

			D3D12Device::D3D12Device(D3D12AdapterObjectWrapper& pAdapter)
			{
				if (DX_FAILED(D3D12CreateDevice(pAdapter, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&this->m_pObject))))
					throw std::runtime_error("[D3D12] Failed To Create Device");

#ifdef __WEISS__DEBUG_MODE

				Microsoft::WRL::ComPtr<ID3D12InfoQueue> pInfoQueue;
				if (SUCCEEDED(this->m_pObject->QueryInterface(IID_PPV_ARGS(&pInfoQueue))))
				{
					pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, TRUE);
					pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, TRUE);
					pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, TRUE);

					//D3D12_MESSAGE_CATEGORY Categories[] = {};

					D3D12_MESSAGE_SEVERITY Severities[] =
					{
						D3D12_MESSAGE_SEVERITY_INFO
					};

					D3D12_MESSAGE_ID DenyIds[] = {
						D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_MISMATCHINGCLEARVALUE,   
						D3D12_MESSAGE_ID_MAP_INVALID_NULLRANGE,                         
						D3D12_MESSAGE_ID_UNMAP_INVALID_NULLRANGE,                      
					};

					D3D12_INFO_QUEUE_FILTER NewFilter = {};
					NewFilter.DenyList.NumSeverities = _countof(Severities);
					NewFilter.DenyList.pSeverityList = Severities;
					NewFilter.DenyList.NumIDs        = _countof(DenyIds);
					NewFilter.DenyList.pIDList       = DenyIds;

					if (pInfoQueue->PushStorageFilter(&NewFilter) != S_OK)
						throw std::runtime_error("[D3D12] Could Not Push Storage FIlter");
				}

#endif // __WEISS__DEBUG_MODE
			}

			D3D12Device& D3D12Device::operator=(D3D12Device&& other) noexcept
			{
				this->m_pObject = other.m_pObject;
				other.m_pObject = nullptr;

				return *this;
			}

			/*
			 * // ///////////////--\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D12Fence---------|| \\
			 * // |\____________________________/| \\
			 * // \\\\\\\\\\\\\\\--/////////////// \\ 
			 */

			D3D12Fence::D3D12Fence(D3D12DeviceObjectWrapper& pDevice, const UINT64 initialValue, const D3D12_FENCE_FLAGS flags)
			{
				if (pDevice->CreateFence(initialValue, flags, IID_PPV_ARGS(&this->m_pObject)) != S_OK)
					throw std::runtime_error("[DIRECTX 12] Failed To Create Fence");

				this->m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
				if (this->m_fenceEvent == nullptr)
					throw std::runtime_error("[DIRECTX 12] Failed To Create Fence Event");
			}

			D3D12Fence::~D3D12Fence()
			{
				CloseHandle(this->m_fenceEvent);
			}

			D3D12Fence& D3D12Fence::operator=(D3D12Fence&& other) noexcept
			{
				this->m_pObject = other.m_pObject;
				other.m_pObject = nullptr;

				return *this;
			}

			/*
			 * // ///////////////////-\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D12CommandQueue---------|| \\
			 * // |\___________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\-/////////////////// \\ 
			 */

			D3D12CommandQueue::D3D12CommandQueue(D3D12DeviceObjectWrapper& pDevice, const D3D12_COMMAND_LIST_TYPE& type)
			{
				D3D12_COMMAND_QUEUE_DESC desc = {};
				desc.Type     = type;
				desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
				desc.Flags    = D3D12_COMMAND_QUEUE_FLAG_NONE;
				desc.NodeMask = 0;

				if (DX_FAILED(pDevice->CreateCommandQueue(&desc, IID_PPV_ARGS(&this->m_pObject))))
					throw std::runtime_error("[D3D12] Could Not Create Command Queue");
			}

			/*
			 * // /////////////////--\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D12SwapChain---------|| \\
			 * // |\________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\--///////////////// \\ 
			 */

			D3D12SwapChain::D3D12SwapChain(D3D12DeviceObjectWrapper&       pDevice,
								   D3D12CommandQueueObjectWrapper& pCommandQueue,
								   const Window* pWindow, const uint16_t maxFps, const UINT bufferCount)
			{
				Microsoft::WRL::ComPtr<IDXGIFactory4> dxgiFactory4;

				UINT createFactoryFlags = 0;

		#ifdef __WEISS__DEBUG_MODE

				createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;

		#endif // __WEISS__DEBUG_MODE

				if (DX_FAILED(CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&dxgiFactory4))))
					throw std::runtime_error("[D3D12] Could Not Create DXGIFactory2");
			
				DXGI_MODE_DESC backBufferDesc = {};
				backBufferDesc.Width  = pWindow->GetClientWidth();
				backBufferDesc.Height = pWindow->GetClientHeight();
				backBufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

				DXGI_SAMPLE_DESC sampleDesc = {};
				sampleDesc.Count = 1;

				DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
				swapChainDesc.BufferCount  = WEISS__FRAME_BUFFER_COUNT;
				swapChainDesc.BufferDesc   = backBufferDesc;
				swapChainDesc.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
				swapChainDesc.SwapEffect   = DXGI_SWAP_EFFECT_FLIP_DISCARD;
				swapChainDesc.OutputWindow = reinterpret_cast<const WS::WIN::WindowsWindow*>(pWindow)->GetHandle();
				swapChainDesc.SampleDesc   = sampleDesc;
				swapChainDesc.Windowed     = true; 
				swapChainDesc.Flags        = D3D12SwapChain::IsTearingSupported() ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0;

				if (DX_FAILED(dxgiFactory4->CreateSwapChain(pCommandQueue, &swapChainDesc, (IDXGISwapChain**) &this->m_pObject)))
					throw std::runtime_error("[DIRECTX 12] Failed To Create Swap Chain");
			}

			D3D12SwapChain& D3D12SwapChain::operator=(D3D12SwapChain&& other) noexcept
			{
				this->m_pObject = other.m_pObject;
				other.m_pObject = nullptr;

				return *this;
			}

			void D3D12SwapChain::Present(const bool vSync) const
			{
				if (DX_FAILED(this->m_pObject->Present(vSync ? 1u : 0u, 0u)))
					throw std::runtime_error("[DIRECTX 12] Presentation Failed");
			}

			bool D3D12SwapChain::IsTearingSupported()
			{
				BOOL isTearingSupported = FALSE;

				Microsoft::WRL::ComPtr<IDXGIFactory4> factory4;
				Microsoft::WRL::ComPtr<IDXGIFactory5> factory5;

				if (DX_FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory4))))
					throw std::runtime_error("[DIRECTX 12] Failed To Check Tearing (While Running CreateDXGIFactory1)");

				if (DX_FAILED(factory4.As(&factory5)))
					throw std::runtime_error("[DIRECTX 12] Failed To Check Tearing (While Running CreateDXGIFactory1)");

				if (DX_FAILED(factory5->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &isTearingSupported, sizeof(isTearingSupported))))
					return false;

				return true;
			}

			/*
			 * // ////////////////////-\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D12DescriptorHeap---------|| \\
			 * // |\_____________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\-//////////////////// \\ 
			 */

			D3D12DescriptorHeap::D3D12DescriptorHeap(D3D12DeviceObjectWrapper& pDevice, const D3D12_DESCRIPTOR_HEAP_TYPE type, const uint32_t numDescriptors, const D3D12_DESCRIPTOR_HEAP_FLAGS& flags)
			{
				D3D12_DESCRIPTOR_HEAP_DESC desc = {};
				desc.NumDescriptors = numDescriptors;
				desc.Type  = type;
				desc.Flags = flags;

				if (DX_FAILED(pDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&this->m_pObject))))
					throw std::runtime_error("[D3D12] Could Not Create Descriptor Heap");
			}

			D3D12DescriptorHeap& D3D12DescriptorHeap::operator=(D3D12DescriptorHeap&& other) noexcept
			{
				this->m_pObject = other.m_pObject;
				other.m_pObject = nullptr;

				return *this;
			}

			/*
			 * // ///////////////////-\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D12RenderTarget---------|| \\
			 * // |\___________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\-/////////////////// \\ 
			 */

			D3D12RenderTarget::D3D12RenderTarget(D3D12DeviceObjectWrapper& pDevice,
										 D3D12SwapChainObjectWrapper& pSwapChain,
										 D3D12DescriptorHeapObjectWrapper& pDescriptorHeap,
										 const CD3DX12_CPU_DESCRIPTOR_HANDLE& rtvHandle,
										 const uint16_t frameIndex)
			{
				if (pSwapChain->GetBuffer(frameIndex, IID_PPV_ARGS(&this->m_pObject)) != S_OK)
					throw std::runtime_error("[DIRECTX 12] Failed To Get Back Buffer");

				pDevice->CreateRenderTargetView(this->m_pObject, nullptr, rtvHandle);
			}

			D3D12RenderTarget& D3D12RenderTarget::operator=(D3D12RenderTarget&& other) noexcept
			{
				this->m_pObject = other.m_pObject;
				other.m_pObject = nullptr;

				return *this;
			}

			/*
			 * // /////////////////////-\\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D12CommandAllocator---------|| \\
			 * // |\_______________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\-///////////////////// \\ 
			 */

			D3D12CommandAllocator::D3D12CommandAllocator(D3D12DeviceObjectWrapper& pDevice, const D3D12_COMMAND_LIST_TYPE& type)
			{
				if (pDevice->CreateCommandAllocator(type, IID_PPV_ARGS(&this->m_pObject)) != S_OK)
					throw std::runtime_error("[DIRECTX 12] Could Not Create Command Allocator");
			}

			void D3D12CommandAllocator::Reset() const
			{
				if (DX_FAILED(this->m_pObject->Reset()))
					throw std::runtime_error("[DIRECTX 12] Could Not Reset Command Allocator");
			}

			/*
			 * // ////////////////////-\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D12CommandList---------|| \\
			 * // |\__________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\-///////////////// \\ 
			 */

			D3D12CommandList::D3D12CommandList(D3D12DeviceObjectWrapper& pDevice,
									   D3D12CommandAllocatorObjectWrapper& pCommandAllocator,
									   const D3D12_COMMAND_LIST_TYPE& type)
			{
				if (DX_FAILED(pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, pCommandAllocator, NULL, IID_PPV_ARGS(&this->m_pObject))))
					throw std::runtime_error("[DIRECTX 12] Failed To Create Command List");
			}

			D3D12CommandList& D3D12CommandList::operator=(D3D12CommandList&& other) noexcept
			{
				this->m_pObject = other.m_pObject;
				other.m_pObject = nullptr;

				return *this;
			}

			void D3D12CommandList::Close()
			{
				if (DX_FAILED(this->m_pObject->Close()))
					throw std::runtime_error("[DIRECTX 12] Failed To Close Command List");
			}

			void D3D12CommandList::Reset(D3D12CommandAllocatorObjectWrapper& pCommandAllocator) const
			{
				if (DX_FAILED(this->m_pObject->Reset(pCommandAllocator, NULL)))
					throw std::runtime_error("[DIRECTX 12] Failed To Reset Command List");
			}

			void D3D12CommandList::TransitionResource(ID3D12Resource* pResource, const D3D12_RESOURCE_STATES& before, const D3D12_RESOURCE_STATES& after)
			{
				this->m_pObject->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pResource, before, after));
			}

			/*
			 * // ////////////////////-\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D12DepthBuffer---------|| \\
			 * // |\__________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\-///////////////// \\ 
			 */

			D3D12DepthBuffer::D3D12DepthBuffer(D3D12Device& pDevice, Window* pWindow)
			{
				D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
				dsvHeapDesc.NumDescriptors = 1;
				dsvHeapDesc.Type  = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
				dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

				if (DX_FAILED(pDevice->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(this->m_pDescriptorHeap.GetPtr()))))
					throw std::runtime_error("[DIRECTX 12] Failed To Create Descriptor Heap For Depth Buffer");

				D3D12_DEPTH_STENCIL_VIEW_DESC depthStencilDesc = {};
				depthStencilDesc.Format        = DXGI_FORMAT_D32_FLOAT;
				depthStencilDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
				depthStencilDesc.Flags         = D3D12_DSV_FLAG_NONE;

				D3D12_CLEAR_VALUE depthOptimizedClearValue = {};
				depthOptimizedClearValue.Format               = DXGI_FORMAT_D32_FLOAT;
				depthOptimizedClearValue.DepthStencil.Depth   = 1.0f;
				depthOptimizedClearValue.DepthStencil.Stencil = 0;

				if (DX_FAILED(pDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE,
															&CD3DX12_RESOURCE_DESC::Tex2D(DXGI_FORMAT_D32_FLOAT, pWindow->GetClientWidth(), pWindow->GetClientHeight(), 1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL),
															D3D12_RESOURCE_STATE_DEPTH_WRITE, &depthOptimizedClearValue,
															IID_PPV_ARGS(this->m_pDepthStencilBuffer.GetPtr()))))
					throw std::runtime_error("[DIRECTX 12] Failed To Create Depth Stencil Heap");
			
				this->m_pDepthStencilBuffer->SetName(L"Depth/Stencil Resource Heap");

				pDevice->CreateDepthStencilView(this->m_pDepthStencilBuffer, &depthStencilDesc, this->m_pDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

				this->m_dsvHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(this->m_pDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
			}

			void D3D12DepthBuffer::Clear(D3D12CommandListObjectWrapper& pCommandList)
			{
				pCommandList->ClearDepthStencilView(this->m_pDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
			}

			D3D12DepthBuffer::operator CD3DX12_CPU_DESCRIPTOR_HANDLE* () noexcept
			{
				return &this->m_dsvHandle;
			}

			/*
			 * // /////////////////////-\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D12RootSignature---------|| \\
			 * // |\____________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\-////////////////// \\ 
			 */

			D3D12RootSignature::D3D12RootSignature(D3D12DeviceObjectWrapper& pDevice, const D3D12_ROOT_SIGNATURE_FLAGS& flags,
										   const std::vector<D3D12_ROOT_PARAMETER1>& rootParameters, const std::vector<D3D12_STATIC_SAMPLER_DESC>& samplers)
			{
				Microsoft::WRL::ComPtr<ID3DBlob> pSignature;
				Microsoft::WRL::ComPtr<ID3DBlob> pError;

				D3D12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
				rootSignatureDesc.Version                    = D3D_ROOT_SIGNATURE_VERSION_1_1;
				rootSignatureDesc.Desc_1_1.NumParameters     = static_cast<UINT>(rootParameters.size());
				rootSignatureDesc.Desc_1_1.Flags             = flags;
				rootSignatureDesc.Desc_1_1.pParameters       = (rootParameters.size() > 0) ? rootParameters.data() : nullptr;
				rootSignatureDesc.Desc_1_1.pStaticSamplers   = samplers.data();
				rootSignatureDesc.Desc_1_1.NumStaticSamplers = static_cast<UINT>(samplers.size());

				if (DX_FAILED(D3D12SerializeVersionedRootSignature(&rootSignatureDesc, &pSignature, &pError)))
					throw std::runtime_error("[DIRECTX 12] Failed To Serialize Root Signature");

				if (DX_FAILED(pDevice->CreateRootSignature(0, pSignature->GetBufferPointer(), pSignature->GetBufferSize(), IID_PPV_ARGS(&this->m_pObject))))
					throw std::runtime_error("[DIRECTX 12] Failed To Create Root Signature");
			}

			D3D12RootSignature& D3D12RootSignature::operator=(D3D12RootSignature&& other) noexcept
			{
				this->m_pObject = other.m_pObject;
				other.m_pObject = nullptr;

				return *this;
			}

			/*
			 * // ///////////////////////-\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D12CommittedResource---------|| \\
			 * // |\________________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\\\-//////////////////// \\ 
			 */

			D3D12CommittedResource::D3D12CommittedResource(D3D12DeviceObjectWrapper& pDevice,   const D3D12_HEAP_TYPE& heapType,
												   const D3D12_HEAP_FLAGS& flags,       const D3D12_RESOURCE_DESC* descPtr,
												   const D3D12_RESOURCE_STATES& states, const char* name)
				: m_originalState(states), m_currentState(states)
			{
				
				if (DX_FAILED(pDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(heapType), flags, descPtr, states,
															nullptr, IID_PPV_ARGS(&this->m_pObject))))
				{
					const std::string errorString = "[DIRECTX 12] Failed To Create A Committed Resource Named " + std::string(name);

					throw std::runtime_error(errorString.c_str());
				}
			
				const std::wstring nameW(&name[0], &name[strlen(name) + 1u]);
				this->m_pObject->SetName(nameW.c_str());
			}
			
			D3D12CommittedResource& D3D12CommittedResource::operator=(D3D12CommittedResource&& other) noexcept
			{
				this->m_pObject = other.m_pObject;
				other.m_pObject = nullptr;

				this->m_currentState  = other.m_currentState;
				this->m_originalState = other.m_originalState;

				return *this;
			}				

			/*
			 * // ///////////////////-\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D12VertexBuffer---------|| \\
			 * // |\___________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\-/////////////////// \\ 
			 */

			D3D12VertexBuffer::D3D12VertexBuffer(D3D12DeviceObjectWrapper& pDevice,
										 D3D12CommandList* pCommandList,
										 const size_t nVertices, const size_t vertexSize)
				: m_vertexSize((UINT)vertexSize), m_pCommandList(pCommandList)
			{
				const UINT bufferSize = static_cast<UINT>(vertexSize * nVertices);

				this->m_pVertexBuffer = D3D12CommittedResource(pDevice, D3D12_HEAP_TYPE_DEFAULT, D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(bufferSize),
															D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, "Vertex Buffer");

				this->m_pUploadHeap = D3D12CommittedResource(pDevice, D3D12_HEAP_TYPE_UPLOAD,  D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(bufferSize),
															D3D12_RESOURCE_STATE_GENERIC_READ, "Vertex Buffer Upload Heap");

				this->m_vertexData.resize(bufferSize);
				std::memset(this->m_vertexData.data(), 0u, bufferSize);

				this->m_vertexBufferView.StrideInBytes  = this->m_vertexSize;
				this->m_vertexBufferView.SizeInBytes    = static_cast<UINT>(this->m_vertexData.size());
				this->m_vertexBufferView.BufferLocation = this->m_pVertexBuffer->GetGPUVirtualAddress();
			}

			void D3D12VertexBuffer::Bind()
			{
				(*this->m_pCommandList)->IASetVertexBuffers(0u, 1u, &this->m_vertexBufferView);
			}

			void D3D12VertexBuffer::Update()
			{
				this->m_pVertexBuffer.TransitionTo(*this->m_pCommandList, D3D12_RESOURCE_STATE_COPY_DEST);

				D3D12_SUBRESOURCE_DATA vertexData = {};
				vertexData.pData      = this->m_vertexData.data();
				vertexData.RowPitch   = this->m_vertexData.size();
				vertexData.SlicePitch = this->m_vertexData.size();

				UpdateSubresources(*this->m_pCommandList, this->m_pVertexBuffer, this->m_pUploadHeap, 0, 0, 1, &vertexData);

				this->m_pVertexBuffer.TransitionBack(*this->m_pCommandList);
			}

			/*
			 * // //////////////////--\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D12IndexBuffer---------|| \\
			 * // |\__________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\--////////////////// \\ 
			 */

			D3D12IndexBuffer::D3D12IndexBuffer(D3D12DeviceObjectWrapper& pDevice,
											D3D12CommandList* pCommandList,
											const size_t nIndices)
				: m_nIndices(nIndices), m_pCommandList(pCommandList)
			{
				const UINT bufferSize = static_cast<UINT>(nIndices * sizeof(uint32_t));

				this->m_pIndexBuffer = D3D12CommittedResource(pDevice, D3D12_HEAP_TYPE_DEFAULT, D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(bufferSize),
															D3D12_RESOURCE_STATE_INDEX_BUFFER, "Index Buffer");

				this->m_pUploadHeap = D3D12CommittedResource(pDevice, D3D12_HEAP_TYPE_UPLOAD,  D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(bufferSize),
															D3D12_RESOURCE_STATE_GENERIC_READ, "Index Buffer Upload Heap");

				this->m_indexData.resize(bufferSize);
				std::memset(this->m_indexData.data(), 0u, bufferSize);

				this->m_indexBufferView.Format         = DXGI_FORMAT_R32_UINT;
				this->m_indexBufferView.SizeInBytes    = static_cast<UINT>(this->m_indexData.size());
				this->m_indexBufferView.BufferLocation = this->m_pIndexBuffer->GetGPUVirtualAddress();
			}

			void D3D12IndexBuffer::Bind()
			{
				(*this->m_pCommandList)->IASetIndexBuffer(&this->m_indexBufferView);
			}

			void D3D12IndexBuffer::Update()
			{
				this->m_pIndexBuffer.TransitionTo(*this->m_pCommandList, D3D12_RESOURCE_STATE_COPY_DEST);

				D3D12_SUBRESOURCE_DATA indexData = {};
				indexData.pData      = this->m_indexData.data();
				indexData.RowPitch   = this->m_indexData.size();
				indexData.SlicePitch = indexData.RowPitch;

				UpdateSubresources(*this->m_pCommandList, this->m_pIndexBuffer, this->m_pUploadHeap, 0, 0, 1, &indexData);

				this->m_pIndexBuffer.TransitionBack(*this->m_pCommandList);
			}

			/*
			 * // ////////////////////-\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D12ConstantBuffer---------|| \\
			 * // |\_____________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\-//////////////////// \\ 
			 */

			D3D12ConstantBuffer::D3D12ConstantBuffer(D3D12DeviceObjectWrapper& pDevice,
													D3D12CommandList* pCommandList,
													const size_t objSize, const size_t slot)
				: m_objSize(objSize), m_slot(slot), m_pCommandList(pCommandList)
			{
				this->m_constantBufferData.resize(objSize);
				std::memset(this->m_constantBufferData.data(), 0u, objSize);

				for (int i = 0; i < WEISS__FRAME_BUFFER_COUNT; i++)
					this->m_descriptorHeaps[i] = D3D12DescriptorHeap(pDevice, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 1u, D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_NONE);

				for (int i = 0; i < WEISS__FRAME_BUFFER_COUNT; i++)
				{
					this->m_pUploadHeaps[i] = D3D12CommittedResource(pDevice, D3D12_HEAP_TYPE_UPLOAD, D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(1024 * 64),
																	D3D12_RESOURCE_STATE_GENERIC_READ, "Constant Buffer Upload Heap");

					this->m_constantBufferViews[i].BufferLocation = this->m_pUploadHeaps[i]->GetGPUVirtualAddress();
					this->m_constantBufferViews[i].SizeInBytes = (objSize + 255) & ~255;

					pDevice->CreateConstantBufferView(&this->m_constantBufferViews[i], this->m_descriptorHeaps[i]->GetCPUDescriptorHandleForHeapStart());
				}
			}

			void D3D12ConstantBuffer::UpdateIfNeeded(const size_t frameIndex)
			{
				if (this->m_bNeedsUpdating[frameIndex])
					this->UpdateHeap(frameIndex);
			}

			void D3D12ConstantBuffer::Update()
			{
				std::fill(this->m_bNeedsUpdating.begin(), this->m_bNeedsUpdating.end(), true);
			}

			void D3D12ConstantBuffer::UpdateHeap(const size_t heapIndex)
			{
				this->m_bNeedsUpdating[heapIndex] = false;

				CD3DX12_RANGE readRange(0, 0);
				CD3DX12_RANGE writtenRange(0, this->m_objSize);

				D3D12CommittedResource& uploadHeap = this->m_pUploadHeaps[heapIndex];

				uint8_t* gpuDestAddr;
				if (DX_FAILED(uploadHeap->Map(0, &readRange, reinterpret_cast<void**>(&gpuDestAddr))))
					throw std::runtime_error("[DIRECTX 12] Failed To Map Constant Buffer Memory");

				memcpy((void*)gpuDestAddr, this->m_constantBufferData.data(), this->m_objSize);

				uploadHeap->Unmap(0, &writtenRange);
			}

			/*
			 * // ////////////////--\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D12Texture---------|| \\
			 * // |\______________________________/| \\
			 * // \\\\\\\\\\\\\\\\--//////////////// \\ 
			 */

			D3D12Texture::D3D12Texture(D3D12DeviceObjectWrapper& pDevice, D3D12CommandList* pCommandList, const size_t width, const size_t height, const size_t slot, const bool useMipmaps)
				: m_pCommandList(pCommandList), m_slot(slot)
			{
				D3D12_RESOURCE_DESC resourceDesc {};
				resourceDesc = {};
				resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
				resourceDesc.Alignment = 0; 
				resourceDesc.Width  = static_cast<UINT>(width);
				resourceDesc.Height = static_cast<UINT>(height);
				resourceDesc.DepthOrArraySize = 1;
				resourceDesc.MipLevels = useMipmaps ? 0 : 1;
				resourceDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
				resourceDesc.SampleDesc.Count   = 1;
				resourceDesc.SampleDesc.Quality = 0;
				resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
				resourceDesc.Flags  = D3D12_RESOURCE_FLAG_NONE;

				this->m_textureResource = D3D12CommittedResource(pDevice, D3D12_HEAP_TYPE_DEFAULT, D3D12_HEAP_FLAG_NONE, &resourceDesc,
																D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, "Texture Committed Resource");

				UINT64 textureUploadBufferSize;
				pDevice->GetCopyableFootprints(&resourceDesc, 0, 1, 0, nullptr, nullptr, nullptr, &textureUploadBufferSize);

				this->m_uploadHeap = D3D12CommittedResource(pDevice, D3D12_HEAP_TYPE_UPLOAD, D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(textureUploadBufferSize),
															D3D12_RESOURCE_STATE_GENERIC_READ, "Texture Upload Heap");

				this->m_descriptorHeap = D3D12DescriptorHeap(pDevice, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 1, D3D12_DESCRIPTOR_HEAP_FLAG_NONE);

				this->m_textureResourceView.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
				this->m_textureResourceView.Format = resourceDesc.Format;
				this->m_textureResourceView.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
				this->m_textureResourceView.Texture2D.MipLevels = useMipmaps ? 0 : 1;
				
				pDevice->CreateShaderResourceView(this->m_textureResource, &this->m_textureResourceView, this->m_descriptorHeap->GetCPUDescriptorHandleForHeapStart());
			}
			
			void D3D12Texture::Update()
			{
				this->m_textureResource.TransitionTo(*this->m_pCommandList, D3D12_RESOURCE_STATE_COPY_DEST);

				D3D12_SUBRESOURCE_DATA textureData{};
				textureData.pData      = this->m_image.GetBuffer();
				textureData.RowPitch   = this->m_image.GetWidth()      * sizeof(Coloru8);
				textureData.SlicePitch = this->m_image.GetPixelCount() * sizeof(Coloru8);
		
				UpdateSubresources(*this->m_pCommandList, this->m_textureResource, this->m_uploadHeap, 0, 0, 1, &textureData);

				this->m_textureResource.TransitionBack(*this->m_pCommandList);
			}

			/*
			 * // ////////////////////-\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D12TextureSampler---------|| \\
			 * // |\_____________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\-//////////////////// \\ 
			 */

			D3D12TextureSampler::D3D12TextureSampler(const TextureFilter& filter)
			{
				switch (filter)
				{
				case TextureFilter::POINT:
					this->m_samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
					break;
				case TextureFilter::BILINEAR:
					this->m_samplerDesc.Filter = D3D12_FILTER_MIN_MAG_LINEAR_MIP_POINT;
					break;
				case TextureFilter::TRILINEAR:
					this->m_samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
					break;
				default:
					throw std::runtime_error("[DIRECTX 12] Your Filtering Method Is Not Supported");
				}
				
				this->m_samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
				this->m_samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
				this->m_samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
				this->m_samplerDesc.MipLODBias = 0;
				this->m_samplerDesc.MaxAnisotropy  = D3D12_MAX_MAXANISOTROPY;
				this->m_samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
				this->m_samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
				this->m_samplerDesc.MinLOD = 0.0f;
				this->m_samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
				this->m_samplerDesc.ShaderRegister = 0;
				this->m_samplerDesc.RegisterSpace  = 0;
				this->m_samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
			}

			/*
			 * // ////////////////////-\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D12RenderPipeline---------|| \\
			 * // |\_____________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\-//////////////////// \\ 
			 */

			D3D12RenderPipeline::D3D12RenderPipeline(D3D12RenderPipeline&& other)
			{
				this->m_pObject = other.m_pObject;
				other.m_pObject = nullptr;

				this->m_topology = other.m_topology;
				this->m_pRootSignature = std::move(other.m_pRootSignature);
				this->m_constantBufferIndices = other.m_constantBufferIndices;
				this->m_textureIndices = other.m_textureIndices;
			}

			D3D12RenderPipeline::D3D12RenderPipeline(D3D12Device& pDevice, const RenderPipelineDesc& pipelineDesc,
													std::vector<ConstantBuffer*>& pConstantBuffers, std::vector<Texture*> pTextures, std::vector<D3D12TextureSampler*> pTextureSamplers)
				: m_pDevice(&pDevice), m_constantBufferIndices(pipelineDesc.constantBufferIndices), m_textureIndices(pipelineDesc.textureIndices),
				m_pConstantBuffers(pConstantBuffers), m_pTextures(pTextures), m_pTextureSamplers(pTextureSamplers)
			{
				// Specify Compilation Flags
				UINT compileFlags = 0u;

		#ifdef __WEISS__DEBUG_MODE

				compileFlags |= D3DCOMPILE_DEBUG;

		#endif // __WEISS__DEBUG_MODE

				// Vertex Shader
				Microsoft::WRL::ComPtr<ID3DBlob> pVertexShaderByteCode;
				Microsoft::WRL::ComPtr<ID3DBlob> pErrorBuff;

				wchar_t vsFilenameW[FILENAME_MAX];
				{
					size_t convertedCharP = 0;
					mbstowcs_s(&convertedCharP, vsFilenameW, strlen(pipelineDesc.vsFilename) + 1u, pipelineDesc.vsFilename, _TRUNCATE);
				}

				if (DX_FAILED(D3DCompileFromFile(vsFilenameW, nullptr, nullptr, "main", "vs_5_0", compileFlags,
						0, &pVertexShaderByteCode, &pErrorBuff)))
				{
		#ifdef __WEISS__DEBUG_MODE
					OutputDebugStringA((char*)pErrorBuff->GetBufferPointer());
		#endif // __WEISS__DEBUG_MODE

					throw std::runtime_error("[DIRECTX 12] Failed To Compile Vertex Shader");
				}

				D3D12_SHADER_BYTECODE vertexShaderBytecode = {};
				vertexShaderBytecode.BytecodeLength  = pVertexShaderByteCode->GetBufferSize();
				vertexShaderBytecode.pShaderBytecode = pVertexShaderByteCode->GetBufferPointer();

				// Pixel Shader
				Microsoft::WRL::ComPtr<ID3DBlob> pPixelShaderByteCode;

				wchar_t psFilenameW[FILENAME_MAX];
				{
					size_t convertedCharP = 0;
					mbstowcs_s(&convertedCharP, psFilenameW, strlen(pipelineDesc.psFilename) + 1u, pipelineDesc.psFilename, _TRUNCATE);
				}

				if (DX_FAILED(D3DCompileFromFile(psFilenameW, nullptr, nullptr, "main", "ps_5_0", compileFlags,
					0, &pPixelShaderByteCode, &pErrorBuff)))
				{
		#ifdef __WEISS__DEBUG_MODE

					OutputDebugStringA((char*)pErrorBuff->GetBufferPointer());

		#endif // __WEISS__DEBUG_MODE

					throw std::runtime_error("[DIRECTX 12] Failed To Compile Pixel Shader");
				}

				D3D12_SHADER_BYTECODE pixelShaderBytecode = {};
				pixelShaderBytecode.BytecodeLength  = pPixelShaderByteCode->GetBufferSize();
				pixelShaderBytecode.pShaderBytecode = pPixelShaderByteCode->GetBufferPointer();

				// Input Layout
				std::vector<D3D12_INPUT_ELEMENT_DESC> inputElementDescriptors(pipelineDesc.sies.size());
				for (uint32_t i = 0; i < inputElementDescriptors.size(); i++)
				{
					inputElementDescriptors[i] = D3D12_INPUT_ELEMENT_DESC{};
					inputElementDescriptors[i].SemanticName = pipelineDesc.sies[i].name;

					switch (pipelineDesc.sies[i].type)
					{
					case ShaderInputElementType::FLOAT_32:
						inputElementDescriptors[i].Format = DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
						break;
					case ShaderInputElementType::UINT_32:
						inputElementDescriptors[i].Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
						break;
					case ShaderInputElementType::VECTOR_2D_FLOAT_32:
						inputElementDescriptors[i].Format = DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
						break;
					case ShaderInputElementType::VECTOR_3D_FLOAT_32:
						inputElementDescriptors[i].Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
						break;
					case ShaderInputElementType::VECTOR_4D_FLOAT_32:
						inputElementDescriptors[i].Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
						break;
					default:
						throw std::runtime_error("[DIRECTX 12] Input Element Type Not Supported");
					}

					inputElementDescriptors[i].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
					inputElementDescriptors[i].InputSlotClass    = D3D12_INPUT_CLASSIFICATION::D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
				}

				D3D12_INPUT_LAYOUT_DESC inputLayoutDesc = {};
				inputLayoutDesc.NumElements        = static_cast<UINT>(pipelineDesc.sies.size());
				inputLayoutDesc.pInputElementDescs = inputElementDescriptors.data();

				// Pipeline
				D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
				psoDesc.InputLayout    = inputLayoutDesc;
				psoDesc.VS = vertexShaderBytecode;
				psoDesc.PS = pixelShaderBytecode;

				switch (pipelineDesc.topology)
				{
				case PrimitiveTopology::TRIANGLES:
					psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
					this->m_topology = D3D_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
					break;
				case PrimitiveTopology::TRIANGLE_STRIP:
					psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
					this->m_topology = D3D_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
					break;
				default:
					throw std::runtime_error("[DIRECTX 12] The Primitive Topology Type You Resquested Is Not Supported");
					break;
				}

				psoDesc.RTVFormats[0]    = DXGI_FORMAT_R8G8B8A8_UNORM;
				psoDesc.SampleDesc.Count = 1;
				psoDesc.SampleMask       = 0xffffffff;
				psoDesc.RasterizerState  = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
				psoDesc.BlendState       = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
				psoDesc.DepthStencilState.DepthEnable   = FALSE;
				psoDesc.DepthStencilState.StencilEnable = FALSE;
				psoDesc.NumRenderTargets = 1;

				// Root Signature
				std::vector<D3D12_DESCRIPTOR_RANGE1> descriptorRanges(pipelineDesc.constantBufferIndices.size() + pipelineDesc.textureIndices.size());

				std::vector<D3D12_ROOT_PARAMETER1> rootParameters;

				{
					size_t j = 0u;
					for (size_t i = 0; i < pipelineDesc.constantBufferIndices.size(); i++)
					{
						D3D12ConstantBuffer*     pConstantBufferX12 = dynamic_cast<D3D12ConstantBuffer*>(pConstantBuffers[pipelineDesc.constantBufferIndices[i]]);
						D3D12_DESCRIPTOR_RANGE1& cbvDescriptorRange = descriptorRanges[j++];

						cbvDescriptorRange.RangeType      = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
						cbvDescriptorRange.NumDescriptors = 1u;
						cbvDescriptorRange.RegisterSpace  = 0u;
						cbvDescriptorRange.BaseShaderRegister = (UINT)pConstantBufferX12->GetSlot();
						cbvDescriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
					}

					for (size_t i = 0; i < pipelineDesc.textureIndices.size(); i++)
					{
						D3D12_DESCRIPTOR_RANGE1& texDescriptorRange = descriptorRanges[j++];
						texDescriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
						texDescriptorRange.NumDescriptors = 1u;
						texDescriptorRange.BaseShaderRegister = (UINT)dynamic_cast<D3D12Texture*>(pTextures[pipelineDesc.textureIndices[i]])->GetSlot();
						texDescriptorRange.RegisterSpace = 0;
						texDescriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
					}

					D3D12_ROOT_PARAMETER1 constantBufferRootParam;
					constantBufferRootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
					constantBufferRootParam.DescriptorTable.NumDescriptorRanges = (UINT)descriptorRanges.size();
					constantBufferRootParam.DescriptorTable.pDescriptorRanges   = descriptorRanges.data();
					constantBufferRootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY::D3D12_SHADER_VISIBILITY_ALL;

					rootParameters.push_back(constantBufferRootParam);
				}

				std::vector<D3D12_STATIC_SAMPLER_DESC> samplers(pipelineDesc.textureSamplerIndices.size());
				for (size_t i = 0u; i < samplers.size(); i++)
					samplers[i] = pTextureSamplers[pipelineDesc.textureSamplerIndices[i]]->GetSamplerDesc();

				this->m_pRootSignature = D3D12RootSignature(pDevice, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT, rootParameters, samplers);

				psoDesc.pRootSignature = this->m_pRootSignature;

				// create the pso
				if (DX_FAILED(pDevice->CreateGraphicsPipelineState(&psoDesc, __uuidof(ID3D12PipelineState), (void**)&this->m_pObject)))
					throw std::runtime_error("[DIRECTX 12] Failed To Create Graphics Pipeline State");

				for (size_t frameIndex = 0u; frameIndex < WEISS__FRAME_BUFFER_COUNT; frameIndex++)
				{
					D3D12DescriptorHeap& gpuDescHeap = this->m_gpuDescHeaps[frameIndex];

					gpuDescHeap = D3D12DescriptorHeap(pDevice, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, this->m_constantBufferIndices.size() + this->m_textureIndices.size(),
													D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE);

					CD3DX12_CPU_DESCRIPTOR_HANDLE gpuDescHeapHandleEnd(gpuDescHeap->GetCPUDescriptorHandleForHeapStart());
					const UINT incrementSize = pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

					for (const size_t cbIndex : this->m_constantBufferIndices) {
						D3D12ConstantBuffer& cbBuffer = *dynamic_cast<D3D12ConstantBuffer*>(pConstantBuffers[cbIndex]);

						pDevice->CopyDescriptorsSimple(1u, gpuDescHeapHandleEnd, cbBuffer.GetDescriptorHeap(frameIndex)->GetCPUDescriptorHandleForHeapStart(), D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

						gpuDescHeapHandleEnd.Offset(1u, incrementSize);
					}

					for (const size_t texIndex : this->m_textureIndices) {
						D3D12Texture& texture = *dynamic_cast<D3D12Texture*>(pTextures[texIndex]);

						pDevice->CopyDescriptorsSimple(1u, gpuDescHeapHandleEnd, texture.GetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart(), D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

						gpuDescHeapHandleEnd.Offset(1u, incrementSize);
					}
				}
			}

			D3D12RenderPipeline& D3D12RenderPipeline::operator=(D3D12RenderPipeline&& other) noexcept
			{
				this->m_pObject = std::move(other.m_pObject);

				this->m_topology = other.m_topology;
				this->m_pRootSignature = std::move(other.m_pRootSignature);
				this->m_constantBufferIndices = other.m_constantBufferIndices;
				this->m_textureIndices = other.m_textureIndices;

				size_t i = 0u;
				for (D3D12DescriptorHeap& gpuHeap : this->m_gpuDescHeaps)
					gpuHeap = std::move(other.m_gpuDescHeaps[i++]);

				return *this;
			}

			void D3D12RenderPipeline::Bind(D3D12CommandList& pCommandList, const size_t frameIndex) noexcept
			{
				for (uint32_t cbIndex : this->m_constantBufferIndices)
					dynamic_cast<D3D12ConstantBuffer*>(this->m_pConstantBuffers[cbIndex])->UpdateIfNeeded(frameIndex);

				pCommandList->SetGraphicsRootSignature(this->m_pRootSignature);
				pCommandList->SetPipelineState(this->m_pObject);
				pCommandList->SetDescriptorHeaps(1u, this->m_gpuDescHeaps[frameIndex].GetPtr());
				pCommandList->SetGraphicsRootDescriptorTable(0u, this->m_gpuDescHeaps[frameIndex]->GetGPUDescriptorHandleForHeapStart());
				pCommandList->IASetPrimitiveTopology(this->m_topology);
			}

			/*
			 * // /////////////////////-\\\\\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D12CommandSubmitter---------|| \\
			 * // |\_______________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\\\\\-///////////////////// \\ 
			 */

			D3D12CommandSubmitter::D3D12CommandSubmitter(D3D12DeviceObjectWrapper& pDevice)
			{
				for (uint16_t i = 0; i < WEISS__FRAME_BUFFER_COUNT; i++)
					this->m_pCommandAllocators[i] = D3D12CommandAllocator(pDevice, D3D12_COMMAND_LIST_TYPE_DIRECT);

				this->m_pCommandList = D3D12CommandList(pDevice, this->m_pCommandAllocators[0], D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);

				for (uint16_t i = 0; i < WEISS__FRAME_BUFFER_COUNT; i++) {
					this->m_pFences[i]     = std::make_unique<D3D12Fence>(pDevice, 0u, D3D12_FENCE_FLAGS::D3D12_FENCE_FLAG_NONE);
					this->m_fenceValues[i] = 0u;
				}
			}

			void D3D12CommandSubmitter::Close()
			{
				this->m_pCommandList.Close();
			}

			void D3D12CommandSubmitter::Reset(const size_t frameIndex)
			{
				this->m_pCommandAllocators[frameIndex].Reset();
				this->m_pCommandList.Reset(this->m_pCommandAllocators[frameIndex]);
			}

			void D3D12CommandSubmitter::Execute(D3D12CommandQueueObjectWrapper& pCommandQueue, const size_t frameIndex)
			{
				ID3D12CommandList* ppCommandLists[] = { this->m_pCommandList };
				pCommandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

				D3D12Fence& pFence     = *this->m_pFences[frameIndex];
				UINT64&     fenceValue = this->m_fenceValues[frameIndex];

				if (DX_FAILED(pCommandQueue->Signal(pFence, fenceValue)))
					throw std::runtime_error("[DIRECTX 12] Failed To Signal The Fence");
			}

			void D3D12CommandSubmitter::WaitForCompletion(const size_t frameIndex)
			{
				D3D12Fence& pFence     = *this->m_pFences[frameIndex];
				UINT64&     fenceValue = this->m_fenceValues[frameIndex];

				if (pFence->GetCompletedValue() < fenceValue) {
					if (DX_FAILED(pFence->SetEventOnCompletion(fenceValue, pFence.GetEvent())))
						throw std::runtime_error("[DIRECTX 12] Failed To Set Event On Completion For Fence");

					WaitForSingleObject(pFence.GetEvent(), INFINITE);

				}

				fenceValue++;
			}

			/*
			 * // /////////////////--\\\\\\\\\\\\\\\\\ \\
			 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
			 * // ||---------D3D12RenderAPI---------|| \\
			 * // |\________________________________/| \\
			 * // \\\\\\\\\\\\\\\\\--///////////////// \\ 
			 */

			void D3D12RenderAPI::CreateRenderTargets()
			{
				CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(this->m_pDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

				UINT rtvDescriptorSize = this->m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

				for (uint16_t i = 0; i < WEISS__FRAME_BUFFER_COUNT; i++)
				{
					this->m_pRenderTargets[i] = D3D12RenderTarget(this->m_pDevice, this->m_pSwapChain, this->m_pDescriptorHeap, rtvHandle, i);
					rtvHandle.Offset(1, rtvDescriptorSize);
				}
			}

			void D3D12RenderAPI::InitRenderAPI(Window* pWindow, const uint16_t maxFps)
			{
				this->m_pDevice         = D3D12Device(this->m_pAdapter);
				this->m_pDepthBuffer    = D3D12DepthBuffer(this->m_pDevice, pWindow);
				this->m_pCommandQueue   = D3D12CommandQueue(this->m_pDevice, D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);
				this->m_pSwapChain      = D3D12SwapChain(this->m_pDevice, this->m_pCommandQueue, pWindow, maxFps, static_cast<UINT>(WEISS__FRAME_BUFFER_COUNT));
				this->m_pDescriptorHeap = D3D12DescriptorHeap(this->m_pDevice, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, static_cast<UINT>(WEISS__FRAME_BUFFER_COUNT));

				this->CreateRenderTargets();

				this->m_commandSubmitter = D3D12CommandSubmitter(this->m_pDevice);

				this->currentFrameIndex = this->m_pSwapChain->GetCurrentBackBufferIndex();

				this->m_viewport.TopLeftX = 0;
				this->m_viewport.TopLeftY = 0;
				this->m_viewport.Width    = pWindow->GetClientWidth();
				this->m_viewport.Height   = pWindow->GetClientHeight();
				this->m_viewport.MinDepth = 0.0f;
				this->m_viewport.MaxDepth = 1.0f;

				this->m_scissors.left   = 0;
				this->m_scissors.top    = 0;
				this->m_scissors.right  = pWindow->GetClientWidth();
				this->m_scissors.bottom = pWindow->GetClientHeight();
			}

			void D3D12RenderAPI::InitPipelines(const std::vector<RenderPipelineDesc>& pipelineDescs)
			{
				// Create Pipelines
				for (const RenderPipelineDesc& pipelineDesc : pipelineDescs)
					this->m_renderPipelines.emplace_back(this->m_pDevice, pipelineDesc, this->m_pConstantBuffers, this->m_pTextures, this->m_pTextureSamplers);
			}

			void D3D12RenderAPI::Draw(const Drawable& drawable, const size_t nVertices)
			{
				D3D12CommandList& pGfxCommandList = this->m_commandSubmitter.GetCommandList();

				this->m_renderPipelines[drawable.pipelineIndex].Bind(pGfxCommandList, this->currentFrameIndex);
				dynamic_cast<D3D12VertexBuffer*>(this->m_pVertexBuffers[drawable.vertexBufferIndex])->Bind();

				if (drawable.indexBufferIndex.has_value()) {
					dynamic_cast<D3D12IndexBuffer*>(this->m_pIndexBuffers[drawable.indexBufferIndex.value()])->Bind();

					pGfxCommandList->DrawIndexedInstanced(static_cast<UINT>(nVertices), 1, 0, 0, 0);
				} else {
					pGfxCommandList->DrawInstanced(static_cast<UINT>(nVertices), 1u, 0, 0);
				}
			}

			void D3D12RenderAPI::BeginDrawing()
			{
				// Wait For Next Frame
				this->currentFrameIndex = this->m_pSwapChain->GetCurrentBackBufferIndex();

				D3D12RenderTarget& renderTarget    = this->m_pRenderTargets[this->currentFrameIndex];
				D3D12CommandList&  pGfxCommandList = this->m_commandSubmitter.GetCommandList();

				pGfxCommandList.TransitionResource(renderTarget, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

				this->m_currentRtvHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(this->m_pDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), static_cast<INT>(this->currentFrameIndex), this->m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));

				this->m_pDepthBuffer.Clear(pGfxCommandList);
				pGfxCommandList->RSSetViewports(1u, &this->m_viewport);
				pGfxCommandList->RSSetScissorRects(1u, &this->m_scissors);
				pGfxCommandList->OMSetRenderTargets(1u, &m_currentRtvHandle, FALSE, this->m_pDepthBuffer);

				this->Fill();
			}

			void D3D12RenderAPI::EndDrawing()
			{
				D3D12RenderTarget& renderTarget    = this->m_pRenderTargets[this->currentFrameIndex];
				D3D12CommandList&  pGfxCommandList = this->m_commandSubmitter.GetCommandList();
				D3D12Fence& pFence = this->m_commandSubmitter.GetFence(this->currentFrameIndex);

				pGfxCommandList.TransitionResource(renderTarget, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);

				this->m_commandSubmitter.Close();
				this->m_commandSubmitter.Execute(this->m_pCommandQueue, this->currentFrameIndex);
			}

			void D3D12RenderAPI::Present(const bool vSync)
			{
				this->m_pSwapChain.Present(vSync);

				this->m_commandSubmitter.WaitForCompletion(currentFrameIndex);
				this->m_commandSubmitter.Reset(this->currentFrameIndex);
			}

			size_t D3D12RenderAPI::CreateVertexBuffer(const size_t nVertices, const size_t vertexSize)
			{
				const size_t vertexBufferIndex = this->m_pVertexBuffers.size();

				this->m_pVertexBuffers.push_back(new D3D12VertexBuffer(this->m_pDevice, this->m_commandSubmitter.GetCommandListPr(), nVertices, vertexSize));

				return vertexBufferIndex;
			}

			size_t D3D12RenderAPI::CreateIndexBuffer(const size_t nIndices)
			{
				const size_t indexBufferIndex = this->m_pIndexBuffers.size();

				this->m_pIndexBuffers.push_back(new D3D12IndexBuffer(this->m_pDevice, this->m_commandSubmitter.GetCommandListPr(), nIndices));

				return indexBufferIndex;
			}

			size_t D3D12RenderAPI::CreateConstantBuffer(const size_t objSize, const size_t slot)
			{
				this->m_pConstantBuffers.push_back(new D3D12ConstantBuffer(this->m_pDevice, this->m_commandSubmitter.GetCommandListPr(), objSize, slot));

				return this->m_pConstantBuffers.size() - 1u;
			}

			size_t D3D12RenderAPI::CreateTexture(const size_t width, const size_t height, const size_t slot, const bool useMipmaps)
			{
				this->m_pTextures.push_back(new D3D12Texture(this->m_pDevice, this->m_commandSubmitter.GetCommandListPr(), width, height, slot, useMipmaps));

				return this->m_pTextures.size() - 1u;
			}

			size_t D3D12RenderAPI::CreateTextureSampler(const TextureFilter& filter, const size_t slot)
			{
				this->m_pTextureSamplers.push_back(new D3D12TextureSampler(filter));

				return this->m_pTextureSamplers.size() - 1u;
			}

			void D3D12RenderAPI::Fill(const Colorf32& color)
			{
				D3D12CommandList& pGfxCommandList = this->m_commandSubmitter.GetCommandList();

				pGfxCommandList->ClearRenderTargetView(this->m_currentRtvHandle, (float*)&color, 0, nullptr);
			}

		}; // namespace D3D12

	}; // namespace Internal

	/*
	 * // /////////////////--\\\\\\\\\\\\\\\\\ \\
	 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
	 * // ||---------GraphicsEngine---------|| \\
	 * // |\________________________________/| \\
	 * // \\\\\\\\\\\\\\\\\--///////////////// \\ 
	 */

	GraphicsEngine::GraphicsEngine(const RenderAPIName& apiName)
	{
		this->m_renderHandle = RenderAPI::Create(apiName);
	}

	void GraphicsEngine::Init(WindowHandle windowHandle)
	{
		this->m_windowHandle = windowHandle;

		this->m_renderHandle->InitRenderAPI(windowHandle, 144u);
	}

	void GraphicsEngine::Run(const size_t fps)
	{
	while (this->m_windowHandle->IsRunning())
		{
			this->m_windowHandle->Update();

			this->m_renderHandle->BeginDrawing();
			this->m_renderHandle->EndDrawing();

			this->OnFrame();
			this->m_renderHandle->Present(false);

			// Temporary
			std::this_thread::sleep_for(std::chrono::milliseconds((unsigned int)(1 / (float)fps * 1000u)));
		}
	}

	/*
	 * // ////////////////--\\\\\\\\\\\\\\\\ \\
	 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
	 * // ||---------ClientSocket---------|| \\
	 * // |\______________________________/| \\
	 * // \\\\\\\\\\\\\\\\--//////////////// \\ 
	 */

	ClientSocket::ClientSocket()
	{
#ifdef __WEISS__OS_WINDOWS
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 0), &wsaData);
#endif // __WEISS__OS_WINDOWS
	}

	void ClientSocket::Connect(const char* host, const unsigned int port)
	{
		sockaddr_in sockAddr;
		sockAddr.sin_addr.s_addr = inet_addr(host);
		sockAddr.sin_family      = AF_INET;
		sockAddr.sin_port        = htons(port);

		this->m_socket = socket(AF_INET, SOCK_STREAM, 0);

		if (this->m_socket == INVALID_SOCKET)
			throw std::runtime_error("[CLIENT SOCKET] Creation Failed");

		if (connect(this->m_socket, (sockaddr*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR)
			throw std::runtime_error("[CLIENT SOCKET] Failed To Connect");
	}

	void ClientSocket::Send(const char* data, int length)
	{
		if (length < 0)
			length = static_cast<int>(strlen(data) + 1u);

		if (send(this->m_socket, data, length, 0) == SOCKET_ERROR)
			throw std::runtime_error("[CLIENT SOCKET] Error While Sending Data");
	}

	[[nodiscard]] std::pair<std::array<char, 1024u>, size_t> ClientSocket::Receive()
	{
		std::array<char, 1024u> buffer;

		const int iResult = recv(this->m_socket, buffer.data(), 1024u, 0);

		if (iResult == 0 || iResult == SOCKET_ERROR)
			throw std::runtime_error("[CLIENT SOCKET] Error While Receiving Data");

		return { buffer, (size_t)iResult };
	}

	void ClientSocket::Disconnect() noexcept
	{
		this->m_socket = INVALID_SOCKET;

		closesocket(this->m_socket);

#ifdef __WEISS__OS_WINDOWS
		WSACleanup();
#endif // __WEISS__OS_WINDOWS
	}

	/*
	 * // ////////////////--\\\\\\\\\\\\\\\\ \\
	 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
	 * // ||---------ServerSocket---------|| \\
	 * // |\______________________________/| \\
	 * // \\\\\\\\\\\\\\\\--//////////////// \\ 
	 */

	ServerSocket::ServerSocket()
	{
#ifdef __WEISS__OS_WINDOWS
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 0), &wsaData);
#endif // __WEISS__OS_WINDOWS
	}

	void ServerSocket::Bind(const unsigned int port)
	{
		this->m_socket = socket(AF_INET, SOCK_STREAM, 0);

		if (this->m_socket == INVALID_SOCKET)
			throw std::runtime_error("[SERVER SOCKET] Creation Failed");

		sockaddr_in sockAddr;
		sockAddr.sin_addr.s_addr = INADDR_ANY;
		sockAddr.sin_family      = AF_INET;
		sockAddr.sin_port        = htons(5555);

		if (bind(this->m_socket, (sockaddr*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR)
			throw std::runtime_error("[SERVER SOCKET] Binding Failed");

		if (listen(this->m_socket, 0) == SOCKET_ERROR)
			throw std::runtime_error("[SERVER SOCKET] Listening Failed");
	}

	[[nodiscard]] int ServerSocket::Accept() noexcept
	{
		sockaddr_in clientAddr;
		int clientAddrSize = 0;

		const SOCKET client = accept(this->m_socket, (SOCKADDR*)&clientAddr, &clientAddrSize);

		if (client != INVALID_SOCKET)
		{
			this->m_clients.push_back(client);

			return static_cast<int>(this->m_clients.size() - 1u);
		}

		return -1;
	}

	void ServerSocket::Send(const int clientID, const char* data, int length)
	{
		if (length < 0)
			length = static_cast<int>(strlen(data) + 1);

		if (send(this->m_clients[clientID], data, length, 0) == SOCKET_ERROR)
			throw std::runtime_error("[SERVER SOCKET] Could Not Send Data To Client");
	}

	[[nodiscard]] std::pair<std::array<char, 1024u>, size_t> ServerSocket::Receive(const int clientID)
	{
		std::array<char, 1024u> buffer;

		const int iResult = recv(this->m_clients[clientID], buffer.data(), 1024u, 0);

		if (iResult == 0 || iResult == SOCKET_ERROR)
			throw std::runtime_error("[SERVER SOCKET] Error While Receiving Data From Client");

		return { buffer, (size_t)iResult };
	}

	void ServerSocket::Disconnect() noexcept
	{
		this->m_socket = INVALID_SOCKET;

		closesocket(this->m_socket);

#ifdef __WEISS__OS_WINDOWS
		WSACleanup();
#endif // __WEISS__OS_WINDOWS
	} 

	/*
	 * // ////////////////////////////////-\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
	 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
	 * // ||--------------------------::Create()--------------------------|| \\
	 * // |\______________________________________________________________/| \\
	 * // \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\-///////////////////////////////// \\ 
	 */

	WindowHandle Window::Create(const WindowDescriptor &descriptor)
	{
#ifdef __WEISS__OS_WINDOWS

		return {new WIN::WindowsWindow(descriptor)};

#endif // __WEISS__OS_WINDOWS

		throw std::runtime_error("Could Not Create A Window For Your Operating System");
	}

	RenderAPIHandle RenderAPI::Create(const RenderAPIName &apiName)
	{
		switch (apiName)
		{
		case RenderAPIName::VULKAN:
			return new WS::Internal::VK::VKRenderAPI();

#ifdef __WEISS__OS_WINDOWS

		case RenderAPIName::DIRECTX11:
			return new WS::Internal::D3D11::D3D11RenderAPI();
		case RenderAPIName::DIRECTX12:
			return new WS::Internal::D3D12::D3D12RenderAPI();

#endif // __WEISS__OS_WINDOWS
		}

		throw std::runtime_error("[RENDER API] Your Render API Is Not Supported");
	}

}; // WS

/*
 * // /////////////////////////////////--\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
 * // ||-----------------------------UNDEFS-----------------------------|| \\
 * // |\________________________________________________________________/| \\
 * // \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\--///////////////////////////////// \\ 
 */

#ifdef __WEISS__OS_WINDOWS

	#undef DX_FAILED
	#undef WIN_FAILED

#endif // __WEISS__OS_WINDOWS

#undef VK_FAILED

/*
 * // //////////////////////////////////-\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \\
 * // |/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\| \\
 * // ||-------------------------------EOF-------------------------------|| \\
 * // |\_________________________________________________________________/| \\
 * // \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\-////////////////////////////////// \\ 
 * 
 *   /‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\
 *  / /‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\ \
 *  | |           ██          ██    ██████████████      ██████████      ██████████████    ██████████████           | |
 *  | |           ██          ██    ██                      ██          ██                ██                       | |
 *  | |           ██          ██    ██                      ██          ██                ██                       | |
 *  | |           ██    ██    ██    ██████████████          ██          ██████████████    ██████████████           | |
 *  | |           ██    ██    ██    ██                      ██                      ██                ██           | |
 *  | |           ██  ██  ██  ██    ██                      ██                      ██                ██           | |
 *  | |             ██      ██      ██████████████      ██████████      ██████████████    ██████████████           | |
 *  | |                                                                                                            | |
 *  | |  ██████████████    ██          ██    ██████████████      ██████████      ██          ██    ██████████████  | |
 *  | |  ██                ████        ██    ██                      ██          ████        ██    ██              | |
 *  | |  ██                ██  ██      ██    ██                      ██          ██  ██      ██    ██              | |
 *  | |  ██████████████    ██    ██    ██    ██    ██████            ██          ██    ██    ██    ██████████████  | |
 *  | |  ██                ██      ██  ██    ██          ██          ██          ██      ██  ██    ██              | |
 *  | |  ██                ██        ████    ██          ██          ██          ██        ████    ██              | |
 *  | |  ██████████████    ██          ██    ████████████        ██████████      ██          ██    ██████████████  | |
 *  \ \____________________________________________________________________________________________________________/ /
 *   \______________________________________________________________________________________________________________/
 */