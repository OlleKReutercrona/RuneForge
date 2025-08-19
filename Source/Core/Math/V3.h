#pragma once
#include <DirectXMath.h>
#include <cmath>
#include "V2.h"

struct V3 {
	float x, y, z;

	static const V3 ZERO;
	static const V3 UNIT_X;
	static const V3 UNIT_Y;
	static const V3 UNIT_Z;
	static const V3 UNIT_SCALE;

	constexpr V3() noexcept : x(0), y(0), z(0) {}
	constexpr V3(float X, float Y, float Z) noexcept : x(X), y(Y), z(Z) {}
	explicit V3(const DirectX::XMFLOAT3 &f) noexcept : x(f.x), y(f.y), z(f.z) {}
	explicit V3(DirectX::FXMVECTOR v) noexcept { *this = v; }

	operator DirectX::XMFLOAT3() const noexcept {
		return { x, y, z };
	}
	operator DirectX::XMVECTOR() const noexcept {
		return DirectX::XMVectorSet(x, y, z, 0.0f);
	}
	V3 &operator=(const DirectX::XMFLOAT3 &f) noexcept {
		x = f.x; y = f.y; z = f.z;
		return *this;
	}
	V3 &operator=(DirectX::FXMVECTOR v) noexcept {
		DirectX::XMFLOAT3 f;
		DirectX::XMStoreFloat3(&f, v);
		x = f.x; y = f.y; z = f.z;
		return *this;
	}
	constexpr V3 operator-() const noexcept {
		return { -x, -y, -z };
	}
	V3 &operator+=(const V3 &rhs) noexcept {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}
	V3 &operator-=(const V3 &rhs) noexcept {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}
	V3 &operator*=(float s) noexcept {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	V3 &operator/=(float s) noexcept {
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}
	friend V3 operator+(V3 a, const V3 &b) noexcept {
		a += b;
		return a;
	}
	friend V3 operator-(V3 a, const V3 &b) noexcept {
		a -= b;
		return a;
	}
	friend V3 operator/(V3 a, float s) noexcept {
		a /= s;
		return a;
	}
	friend V3 operator*(const V3 &a, float s) noexcept {
		V3 result = a;
		result *= s;
		return result;
	}
	friend V3 operator*(float s, const V3 &a) noexcept {
		V3 result = a;
		result *= s;
		return result;
	}

	float LengthSquared() const noexcept {
		return (x * x + y * y + z * z);
	}
	float Length() const noexcept {
		return sqrt(LengthSquared());
	}
	V3 Normalized() const noexcept {
		float lengthSquared = LengthSquared();
		if (lengthSquared <= 1e-8f) return V3::ZERO;

		return (*this) * (1.0f / sqrt(lengthSquared));
	}
	float Dot(const V3 &other) const noexcept {
		return (x * other.x) + (y * other.y) + (z * other.z);
	}
	V3 Cross(const V3 &other) const noexcept {
		return V3(
			(y * other.z) - (z * other.y),
			(z * other.x) - (x * other.z),
			(x * other.y) - (y * other.x)
		);
	}

	V2 xy() const noexcept { return V2(x, y); }
	V2 xz() const noexcept { return V2(x, z); }
	V2 yz() const noexcept { return V2(y, z); }
};

inline const V3 V3::ZERO(0, 0, 0);
inline const V3 V3::UNIT_X(1, 0, 0);
inline const V3 V3::UNIT_Y(0, 1, 0);
inline const V3 V3::UNIT_Z(0, 0, 1);
inline const V3 V3::UNIT_SCALE(1, 1, 1);

inline float Dot(const V3 &a, const V3 &b) noexcept {
	return a.Dot(b);
}
inline V3 Cross(const V3 &a, const V3 &b) noexcept {
	return a.Cross(b);
}
inline V3 Lerp(const V3 &a, const V3 &b, float t) noexcept {
	return (a * (1.0f - t)) + (b * t);
}
