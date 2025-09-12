#pragma once
#include <DirectXMath.h>
#include <cmath>


struct Vector2 {
	float x = 0.0f;
	float y = 0.0f;

	static const Vector2 ZERO;
	static const Vector2 UNIT_X;
	static const Vector2 UNIT_Y;
	static const Vector2 UNIT_SCALE;

	constexpr Vector2() noexcept : x(0.0f), y(0.0f) {}
	constexpr Vector2(float X, float Y) noexcept : x(X), y(Y) {}
	explicit Vector2(const DirectX::XMFLOAT2 &xmf2) noexcept : x(xmf2.x), y(xmf2.y) {}
	explicit Vector2(DirectX::FXMVECTOR fxm) noexcept { *this = fxm; }

	operator DirectX::XMFLOAT2() const noexcept {
		return { x, y };
	}
	operator DirectX::XMVECTOR() const noexcept {
		return DirectX::XMVectorSet(x, y, 0.0f, 0.0f);
	}
	Vector2 &operator=(const DirectX::XMFLOAT2 &xmf2) noexcept {
		x = xmf2.x;
		y = xmf2.y;
		return *this;
	} 
	Vector2 &operator=(DirectX::FXMVECTOR fxm) noexcept {
		DirectX::XMFLOAT2 xmFloat2;
		DirectX::XMStoreFloat2(&xmFloat2, fxm);
		x = xmFloat2.x;
		y = xmFloat2.y;
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
		assert(s != 0.0f, "Division by zero in Vector2::operator/=");
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
		assert(s != 0.0f, "Division by zero in Vector2::operator/");
		return Vector2(a.x / s, a.y / s);
	}
	friend Vector2 operator*(const Vector2 &a, float s) noexcept {
		return Vector2(a.x * s, a.y * s);
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
		assert(fabsf(normal.LengthSquared() - 1.0f) > 1e-3f, "Vector2::Reflect recieved non-normalized normal");
		return 2.0f * normal * this->Dot(normal) - *this;
	}

};

inline const Vector2 Vector2::ZERO(0, 0);
inline const Vector2 Vector2::UNIT_X(1, 0);
inline const Vector2 Vector2::UNIT_Y(0, 1);
inline const Vector2 Vector2::UNIT_SCALE(1, 1);

inline Vector2 Lerp(const Vector2 &a, const Vector2 &b, float t) noexcept {
	return (a * (1.0f - t)) + (b * t);
}



struct Vector2i {
	int x = 0;
	int y = 0;

	static const Vector2i ZERO;
	static const Vector2i UNIT_X;
	static const Vector2i UNIT_Y;
	static const Vector2i UNIT_SCALE;

	constexpr Vector2i() noexcept : x(0), y(0) {}
	constexpr Vector2i(int X, int Y) noexcept : x(X), y(Y) {}


	constexpr Vector2i operator-() const noexcept {
		return { -x, -y };
	}
	Vector2i &operator+=(const Vector2i &rhs) noexcept {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	Vector2i &operator-=(const Vector2i &rhs) noexcept {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	Vector2i &operator*=(int s) noexcept {
		x *= s;
		y *= s;
		return *this;
	}
	Vector2i &operator/=(int s) noexcept {
		assert(s != 0 && "Division by zero in Vector2i::operator/=");
		x /= s;
		y /= s;
		return *this;
	}
	friend Vector2i operator+(Vector2i a, const Vector2i &b) noexcept {
		a += b;
		return a;
	}
	friend Vector2i operator-(Vector2i a, const Vector2i &b) noexcept {
		a -= b;
		return a;
	}
	friend Vector2i operator*(Vector2i a, int s) noexcept {
		a *= s;
		return a;
	}
	friend Vector2i operator*(Vector2i a,int s) noexcept {
		return Vector2i(a.x * s, a.y * s);
	}
	friend Vector2i operator/(int s, Vector2i a) noexcept {
		assert(s != 0 && "Division by zero in Vector2i::operator/");
		return Vector2i(a.x / s, a.y / s);
	}
	friend bool operator==(const Vector2i &a, const Vector2i &b) noexcept {
		return a.x == b.x && a.y == b.y;
	}

	friend bool operator!=(const Vector2i &a, const Vector2i &b) noexcept {
		return !(a == b);
	}
	int Dot(const Vector2i &other) const noexcept {
		return x * other.x + y * other.y;
	}
	int ManhattanLength() const noexcept {
		return std::abs(x) + std::abs(y);
	}
	int LengthSquared() const noexcept {
		return x * x + y * y;
	}
};

inline const Vector2i Vector2i::ZERO(0, 0);
inline const Vector2i Vector2i::UNIT_X(1, 0);
inline const Vector2i Vector2i::UNIT_Y(0, 1);
inline const Vector2i Vector2i::UNIT_SCALE(1, 1);