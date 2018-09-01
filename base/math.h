#pragma once
namespace math
{
	constexpr float pi = 3.14159265358979323846f;  // M_PI
	constexpr float pi_2 = pi * 2.f;                 // M_PI * 2.f
	
	constexpr float deg_to_rad(float val) {
		return val * (pi / 180.f);
	}
	constexpr float rad_to_deg(float val) {
		return val * (180.f / pi);
	}
	constexpr float angle_mod(float angle) {
		return (360.f / 65536) * (int(angle * (65536.f / 360.0f)) & 65535);
	}

}