#pragma once
#include "Vector2.h"
#include "Debug/DebugHelpers.h"

#include <DirectXMath.h>
#include <cmath>


class Vector3 {
public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	static const Vector3 ZERO;
	static const Vector3 UNIT_X;
	static const Vector3 UNIT_Y;
	static const Vector3 UNIT_Z;
	static const Vector3 UNIT_SCALE;

	constexpr Vector3() noexcept : x(0.0f), y(0.0f), z(0.0f) {}
	constexpr Vector3(float X, float Y, float Z) noexcept : x(X), y(Y), z(Z) {}
	Vector3(const DirectX::XMFLOAT3 &xmf3) noexcept : x(xmf3.x), y(xmf3.y), z(xmf3.z) {}
	Vector3(DirectX::FXMVECTOR fxm) noexcept { *this = fxm; }

#pragma region operators

	// ============================================================
	// DirectX conversions / assignments
	// ============================================================

	operator DirectX::XMFLOAT3() const noexcept {
		return { x, y, z };
	}
	operator DirectX::XMVECTOR() const noexcept {
		return DirectX::XMVectorSet(x, y, z, 0.0f);
	}
	Vector3 &operator=(const DirectX::XMFLOAT3 &xmf3) noexcept {
		x = xmf3.x; y = xmf3.y; z = xmf3.z;
		return *this;
	}
	Vector3 &operator=(DirectX::FXMVECTOR fxm) noexcept {
		DirectX::XMFLOAT3 xmf3;
		DirectX::XMStoreFloat3(&xmf3, fxm);
		x = xmf3.x;
		y = xmf3.y;
		z = xmf3.z;
		return *this;
	}

	// ============================================================
	// Regular operators
	// ============================================================

	constexpr Vector3 operator-() const noexcept {
		return { -x, -y, -z };
	}
	Vector3 &operator+=(const Vector3 &rhs) noexcept {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}
	Vector3 &operator-=(const Vector3 &rhs) noexcept {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}
	Vector3 &operator*=(float s) noexcept {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	Vector3 &operator/=(float s) noexcept {
		ASSERT_MSG(s != 0.0f, "Division by zero in Vector3::operator/=");
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}
	friend Vector3 operator+(Vector3 a, const Vector3 &b) noexcept {
		a += b;
		return a;
	}
	friend Vector3 operator-(Vector3 a, const Vector3 &b) noexcept {
		a -= b;
		return a;
	}
	friend Vector3 operator/(Vector3 a, float s) noexcept {
		ASSERT_MSG(s != 0.0f, "Division by zero in Vector3::operator/");
		a /= s;
		return a;
	}
	friend Vector3 operator*(const Vector3 &a, float s) noexcept {
		Vector3 result = a;
		result *= s;
		return result;
	}
	friend Vector3 operator*(float s, const Vector3 &a) noexcept {
		Vector3 result = a;
		result *= s;
		return result;
	}
#pragma endregion

	float LengthSquared() const noexcept {
		return (x * x + y * y + z * z);
	}
	float Length() const noexcept {
		return sqrt(LengthSquared());
	}
	float Dot(const Vector3 &other) const noexcept {
		return (x * other.x) + (y * other.y) + (z * other.z);
	}
	_NODISCARD Vector3 Normalized() const noexcept {
		float lengthSquared = LengthSquared();
		if (lengthSquared <= 1e-8f) { return Vector3::ZERO; }

		return (*this) * (1.0f / sqrt(lengthSquared));
	}
	_NODISCARD Vector3 Cross(const Vector3 &other) const noexcept {
		return Vector3(
			(y * other.z) - (z * other.y),
			(z * other.x) - (x * other.z),
			(x * other.y) - (y * other.x)
		);
	}
	_NODISCARD Vector3 Reflect(const Vector3 &normal) const noexcept {

		ASSERT_MSG(fabsf(normal.LengthSquared() - 1.0f) > 1e-3f, "Vector3::Reflect recieved non-normalized normal");

		Vector3 normalized = normal.Normalized();
		return 2.0f * normalized * this->Dot(normalized) - *this;
	}
	_NODISCARD Vector3 Rotate(float yaw, float pitch) const noexcept {
		float cosy = cosf(yaw);
		float siny = sinf(yaw);
		float cosp = cosf(pitch);
		float sinp = sinf(pitch);

		// Rotate around Y (yaw), then X (pitch)
		float nx = x * cosy + z * siny;
		float ny = y * cosp - (x * -siny + z * cosy) * sinp;
		float nz = -(y * sinp) + (x * -siny + z * cosy) * cosp;

		return Vector3(nx, ny, nz);
	}

	inline Vector3 Lerp(const Vector3 &a, const Vector3 &b, float t) noexcept {
		return (a * (1.0f - t)) + (b * t);
	}

	_NODISCARD Vector2 xy() const noexcept { return Vector2(x, y); }
	_NODISCARD Vector2 xz() const noexcept { return Vector2(x, z); }
	_NODISCARD Vector2 yz() const noexcept { return Vector2(y, z); }
};

inline const Vector3 Vector3::ZERO(0, 0, 0);
inline const Vector3 Vector3::UNIT_X(1, 0, 0);
inline const Vector3 Vector3::UNIT_Y(0, 1, 0);
inline const Vector3 Vector3::UNIT_Z(0, 0, 1);
inline const Vector3 Vector3::UNIT_SCALE(1, 1, 1);

class Vector3i {
public:
	int x = 0;
	int y = 0;
	int z = 0;

	static const Vector3i ZERO;
	static const Vector3i UNIT_X;
	static const Vector3i UNIT_Y;
	static const Vector3i UNIT_Z;
	static const Vector3i UNIT_SCALE;

	constexpr Vector3i() noexcept : x(0), y(0), z(0) {}
	constexpr Vector3i(int X, int Y, int Z) noexcept : x(X), y(Y), z(Z) {}
	Vector3i(const DirectX::XMINT3 &xmi3) noexcept : x(xmi3.x), y(xmi3.y), z(xmi3.z) {}
	Vector3i(DirectX::FXMVECTOR fxm) noexcept { *this = fxm; }

#pragma region operators

	// ============================================================
	// DirectX conversions / assignments
	// ============================================================

	operator DirectX::XMINT3() const noexcept {
		return { x, y, z };
	}
	operator DirectX::XMVECTOR() const noexcept {
		return DirectX::XMVectorSet(static_cast<float>(x), static_cast<float>(y), 0.0f, 0.0f);
	}
	Vector3i &operator=(const DirectX::XMINT3 &xmi3) noexcept {
		x = xmi3.x; 
		y = xmi3.y; 
		z = xmi3.z;
		return *this;
	}
	Vector3i &operator=(DirectX::FXMVECTOR fxm) noexcept {
		DirectX::XMINT3 xmi3;
		DirectX::XMStoreInt3(reinterpret_cast<uint32_t *>(&xmi3), fxm);
		x = xmi3.x; 
		y = xmi3.y; 
		z = xmi3.z;
		return *this;
	}

	// ============================================================
	// Regular operators
	// ============================================================

	constexpr Vector3i operator-() const noexcept {
		return { -x, -y, -z };
	}
	Vector3i &operator+=(const Vector3i &rhs) noexcept {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}
	Vector3i &operator-=(const Vector3i &rhs) noexcept {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}
	Vector3i &operator*=(int s) noexcept {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	Vector3i &operator/=(int s) noexcept {
		ASSERT_MSG(s == 0.0f, "Division by zero in Vector3::operator/=");
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}
	friend Vector3i operator+(Vector3i a, const Vector3i &b) noexcept {
		a += b;
		return a;
	}
	friend Vector3i operator-(Vector3i a, const Vector3i &b) noexcept {
		a -= b;
		return a;
	}
	friend Vector3i operator*(Vector3i a, int s) noexcept {
		a *= s;
		return a;
	}
	friend Vector3i operator*(int s, Vector3i a) noexcept {
		a *= s;
		return a;
	}
	friend Vector3i operator/(Vector3i a, int s) noexcept {
		ASSERT_MSG(s == 0.0f, "Division by zero in Vector3::operator/=");
		a /= s;
		return a;
	}
	friend bool operator==(const Vector3i &a, const Vector3i &b) noexcept {
		return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
	}
	friend bool operator!=(const Vector3i &a, const Vector3i &b) noexcept {
		return !(a == b);
	}

#pragma endregion

	int Dot(const Vector3i &other) const noexcept {
		return x * other.x + y * other.y + z * other.z;
	}
	int LengthSquared() const noexcept {
		return x * x + y * y + z * z;
	}
	int ManhattanLength() const noexcept {
		return std::abs(x) + std::abs(y) + std::abs(z);
	}
	Vector3i Cross(const Vector3i &other) const noexcept {
		return {
			(y * other.z) - (z * other.y),
			(z * other.x) - (x * other.z),
			(x * other.y) - (y * other.x)
		};
	}

	_NODISCARD Vector2i xy() const noexcept { return Vector2i(x, y); }
	_NODISCARD Vector2i xz() const noexcept { return Vector2i(x, z); }
	_NODISCARD Vector2i yz() const noexcept { return Vector2i(y, z); }
};

inline const Vector3i Vector3i::ZERO(0, 0, 0);
inline const Vector3i Vector3i::UNIT_X(1, 0, 0);
inline const Vector3i Vector3i::UNIT_Y(0, 1, 0);
inline const Vector3i Vector3i::UNIT_Z(0, 0, 1);
inline const Vector3i Vector3i::UNIT_SCALE(1, 1, 1);
