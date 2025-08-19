#pragma once
#include <DirectXMath.h>
#include <cmath>

struct V2 {
	float x, y;

	static const V2 ZERO;
	static const V2 UNIT_X;
	static const V2 UNIT_Y;
	static const V2 UNIT_SCALE;

	constexpr V2() noexcept : x(0), y(0) {}
	constexpr V2(float X, float Y) noexcept : x(X), y(Y) {}
	explicit V2(const DirectX::XMFLOAT2 &f) noexcept : x(f.x), y(f.y) {}
	explicit V2(DirectX::FXMVECTOR v) noexcept { *this = v; }

	operator DirectX::XMFLOAT2() const noexcept {
		return { x, y };
	}
	operator DirectX::XMVECTOR() const noexcept {
		return DirectX::XMVectorSet(x, y, 0.0f, 0.0f);
	}
	V2 &operator=(const DirectX::XMFLOAT2 &f) noexcept {
		x = f.x;
		y = f.y;
		return *this;
	}
	V2 &operator=(DirectX::FXMVECTOR v) noexcept {
		DirectX::XMFLOAT2 f;
		DirectX::XMStoreFloat2(&f, v);
		x = f.x;
		y = f.y;
		return *this;
	}
	constexpr V2 operator-() const noexcept {
		return { -x, -y };
	}
	V2 &operator+=(const V2 &rhs) noexcept {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	V2 &operator-=(const V2 &rhs) noexcept {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	V2 &operator*=(float s) noexcept {
		x *= s;
		y *= s;
		return *this;
	}
	V2 &operator/=(float s) noexcept {
		x /= s;
		y /= s;
		return *this;
	}
	friend V2 operator+(V2 a, const V2 &b) noexcept {
		a += b;
		return a;
	}
	friend V2 operator-(V2 a, const V2 &b) noexcept {
		a -= b;
		return a;
	}
	friend V2 operator/(V2 a, float s) noexcept {
		a /= s;
		return a;
	}
	friend V2 operator*(const V2 &a, float s) noexcept {
		V2 result = a;
		result *= s;
		return result;
	}
	friend V2 operator*(float s, const V2 &a) noexcept {
		V2 result = a;
		result *= s;
		return result;
	}


	float LengthSquared() const noexcept {
		return (x * x + y * y);
	}
	float Length() const noexcept {
		return sqrt(LengthSquared());
	}
	V2 Normalized() const noexcept {
		float lsq = LengthSquared();
		if (lsq <= 1e-8f) return V2::ZERO;

		return (*this) * (1.0f / sqrt(lsq));
	}
	float Dot(const V2 &other) const noexcept {
		return (x * other.x) + (y * other.y);
	}

};

inline const V2 V2::ZERO(0, 0);
inline const V2 V2::UNIT_X(1, 0);
inline const V2 V2::UNIT_Y(0, 1);
inline const V2 V2::UNIT_SCALE(1, 1);

inline float Dot(const V2 &a, const V2 &b) noexcept {
	return (a.x * b.x) + (a.y * b.y);
}
inline V2 Lerp(const V2 &a, const V2 &b, float t) noexcept {
	return (a * (1.0f - t)) + (b * t);
}