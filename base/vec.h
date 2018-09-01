#pragma once
#include "includes.h"

class vec_t {
public:
	float x, y, z;

	vec_t& operator+=(const vec_t& v) {
		x += v.x; y += v.y; z += v.z; return *this;
	}

	vec_t& operator-=(const vec_t& v) {
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}

	vec_t& operator*=(float v) {
		x *= v; y *= v; z *= v; return *this;
	}

	vec_t operator-(const vec_t& v) {
		return vec_t{ x - v.x, y - v.y, z - v.z };
	}

	vec_t operator*(float v) const {
		return vec_t{ x * v, y * v, z * v };
	}

	vec_t& clamp() {
		x = std::clamp(std::remainderf(x, 180.f), -89.f, 89.f);
		y = std::clamp(std::remainderf(y, 360.f), -180.f, 180.f);
		z = 0.f;

		return *this;
	}
};