#pragma once
#include "Debug/DebugHelpers.h" 

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
	explicit V2(const DirectX::XMFLOAT2 &xmf2) noexcept : x(xmf2.x), y(xmf2.y) {}
	explicit V2(DirectX::FXMVECTOR fxm) noexcept { *this = fxm; }

	operator DirectX::XMFLOAT2() const noexcept {
		return { x, y };
	}
	operator DirectX::XMVECTOR() const noexcept {
		return DirectX::XMVectorSet(x, y, 0.0f, 0.0f);
	}
	V2 &operator=(const DirectX::XMFLOAT2 &xmf2) noexcept {
		x = xmf2.x;
		y = xmf2.y;
		return *this;
	} 
	V2 &operator=(DirectX::FXMVECTOR fxm) noexcept {
		DirectX::XMFLOAT2 xmFloat2;
		DirectX::XMStoreFloat2(&xmFloat2, fxm);
		x = xmFloat2.x;
		y = xmFloat2.y;
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
		ASSERT_MSG(s != 0.0f, "Division by zero in V2::operator/=");
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
		ASSERT_MSG(s != 0.0f, "Division by zero in V2::operator/");
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
	float Dot(const V2 &other) const noexcept {
		return (x * other.x) + (y * other.y);
	}
	_NODISCARD V2 Normalized() const noexcept {
		float lsq = LengthSquared();
		if (lsq <= 1e-8f) { return V2::ZERO; }

		return (*this) * (1.0f / sqrt(lsq));
	}
	_NODISCARD V2 Reflect(const V2 &normal) const noexcept {
		ASSERT_MSG(fabsf(normal.LengthSquared() - 1.0f) > 1e-3f, "V2::Reflect recieved non-normalized normal");
		return 2.0f * normal * this->Dot(normal) - *this;
	}

};

inline const V2 V2::ZERO(0, 0);
inline const V2 V2::UNIT_X(1, 0);
inline const V2 V2::UNIT_Y(0, 1);
inline const V2 V2::UNIT_SCALE(1, 1);

typedef V2 V2;

inline V2 Lerp(const V2 &a, const V2 &b, float t) noexcept {
	return (a * (1.0f - t)) + (b * t);
}