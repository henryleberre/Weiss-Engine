#pragma once

#include "Vector.h"
#include "Constants.h"

namespace WS {

	[[nodiscard]] inline float DegreesToRadians(const float degrees);
	[[nodiscard]] inline float RadiansToDegrees(const float radians);

	// If a polar point is stored as (θ, r)
	[[nodiscard]] inline Vec2f PolarToCartesian(const Vec2f polar);

	[[nodiscard]] inline Vec2f CartesianToPolar(const Vec2f cartesian);

	[[nodiscard]] inline Vec3f GetTriangleSurfaceNormal(const Vec3f& a, const Vec3f& b, const Vec3f& c);

}; // WS