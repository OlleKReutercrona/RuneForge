#pragma once
#include <DirectXMath.h>
#include <cmath>

#include "../Debug/DebugHelpers.h" // FIXME : need to update premake to get rid of ../

struct Vector2 {
	float x, y;

	static const Vector2 ZERO;
	static const Vector2 UNIT_X;
	static const Vector2 UNIT_Y;
	static const Vector2 UNIT_SCALE;

	constexpr Vector2() noexcept : x(0), y(0) {}
	constexpr Vector2(float X, float Y) noexcept : x(X), y(Y) {}
	explicit Vector2(const DirectX::XMFLOAT2 &f) noexcept : x(f.x), y(f.y) {}
	explicit Vector2(DirectX::FXMVECTOR v) noexcept { *this = v; }

	operator DirectX::XMFLOAT2() const noexcept {
		return { x, y };
	}
	operator DirectX::XMVECTOR() const noexcept {
		return DirectX::XMVectorSet(x, y, 0.0f, 0.0f);
	}
	Vector2 &operator=(const DirectX::XMFLOAT2 &f) noexcept {
		x = f.x;
		y = f.y;
		return *this;
	}
	Vector2 &operator=(DirectX::FXMVECTOR v) noexcept {
		DirectX::XMFLOAT2 f;
		DirectX::XMStoreFloat2(&f, v);
		x = f.x;
		y = f.y;
		return *this;
	}
	constexpr Vector2 operator-() const noexcept {
		return { -x, -y };
	}
	Vector2 &operator+=(const Vector2 &rhs) noexcept {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	Vector2 &operator-=(const Vector2 &rhs) noexcept {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	Vector2 &operator*=(float s) noexcept {
		x *= s;
		y *= s;
		return *this;
	}
	Vector2 &operator/=(float s) noexcept {
		ASSERT_MSG(s != 0.0f, "Division by zero in Vector2::operator/=");
		x /= s;
		y /= s;
		return *this;
	}
	friend Vector2 operator+(Vector2 a, const Vector2 &b) noexcept {
		a += b;
		return a;
	}
	friend Vector2 operator-(Vector2 a, const Vector2 &b) noexcept {
		a -= b;
		return a;
	}
	friend Vector2 operator/(Vector2 a, float s) noexcept {
		ASSERT_MSG(s != 0.0f, "Division by zero in Vector2::operator/");
		a /= s;
		return a;
	}
	friend Vector2 operator*(const Vector2 &a, float s) noexcept {
		Vector2 result = a;
		result *= s;
		return result;
	}
	friend Vector2 operator*(float s, const Vector2 &a) noexcept {
		Vector2 result = a;
		result *= s;
		return result;
	}

	float LengthSquared() const noexcept {
		return (x * x + y * y);
	}
	float Length() const noexcept {
		return sqrt(LengthSquared());
	}
	float Dot(const Vector2 &other) const noexcept {
		return (x * other.x) + (y * other.y);
	}
	_NODISCARD Vector2 Normalized() const noexcept {
		float lsq = LengthSquared();
		if (lsq <= 1e-8f) { return Vector2::ZERO; }

		return (*this) * (1.0f / sqrt(lsq));
	}
	_NODISCARD Vector2 Reflect(const Vector2 &normal) const noexcept {
		ASSERT_MSG(fabsf(normal.LengthSquared() - 1.0f) > 1e-3f, "Vector2::Reflect recieved non-normalized normal");
		return 2.0f * normal * this->Dot(normal) - *this;
	}

};

inline const Vector2 Vector2::ZERO(0, 0);
inline const Vector2 Vector2::UNIT_X(1, 0);
inline const Vector2 Vector2::UNIT_Y(0, 1);
inline const Vector2 Vector2::UNIT_SCALE(1, 1);

typedef Vector2 V2;

inline Vector2 Lerp(const Vector2 &a, const Vector2 &b, float t) noexcept {
	return (a * (1.0f - t)) + (b * t);
}