#pragma once
#include <DirectXMath.h>
#include <cmath>
#include "Vector2.h"

class Vector3 {
public:
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    static const Vector3 Zero;
    static const Vector3 UnitX;
    static const Vector3 UnitY;
    static const Vector3 UnitZ;
    static const Vector3 UnitScale;

    // Constructors //

    constexpr Vector3() noexcept : x(0), y(0), z(0) {}
    constexpr Vector3(float X, float Y, float Z) noexcept : x(X), y(Y), z(Z) {}
    constexpr Vector3(const DirectX::XMFLOAT3 &xmf3) noexcept : x(xmf3.x), y(xmf3.y), z(xmf3.z) {}
    explicit constexpr Vector3(const float(&arr)[3]) noexcept : x(arr[0]), y(arr[1]), z(arr[2]) {}

    // DirectX Conversions //

    operator DirectX::XMFLOAT3() const noexcept {
        return DirectX::XMFLOAT3(x, y, z);
    }
    Vector3 &operator=(const DirectX::XMFLOAT3 &xmf3) noexcept {
        x = xmf3.x; y = xmf3.y; z = xmf3.z;
        return *this;
    }
    Vector3 &operator=(DirectX::FXMVECTOR fxm) noexcept {
        DirectX::XMFLOAT3 temp;
        DirectX::XMStoreFloat3(&temp, fxm);
        x = temp.x; y = temp.y; z = temp.z;
        return *this;
    }

    // Explicit conversion(1 for position, 0 for direction)
    [[nodiscard]] DirectX::XMVECTOR ToXMVECTOR(float w) const noexcept {
        return DirectX::XMVectorSet(x, y, z, w);
    }

    // Compound Assignment Operators (modifying *this) //

    Vector3 &operator+=(const Vector3 &rhs) noexcept {
        x += rhs.x; y += rhs.y; z += rhs.z;
        return *this;
    }
    Vector3 &operator-=(const Vector3 &rhs) noexcept {
        x -= rhs.x; y -= rhs.y; z -= rhs.z;
        return *this;
    }
    Vector3 &operator*=(float s) noexcept {
        x *= s; y *= s; z *= s;
        return *this;
    }
    Vector3 &operator/=(float s) noexcept {
        assert(s != 0.0f && "Division by zero in Vector3::operator/=");
        x /= s; y /= s; z /= s;
        return *this;
    }

    // Arithmetic Operators (returning a copy) //

    friend Vector3 operator+(Vector3 a, const Vector3 &b) noexcept {
        a += b;
        return a;
    }
    friend Vector3 operator-(Vector3 a, const Vector3 &b) noexcept {
        a -= b;
        return a;
    }
    friend Vector3 operator/(Vector3 a, float s) noexcept {
        assert(s != 0.0f && "Division by zero in Vector3::operator/");
        a /= s;
        return a;
    }
    friend Vector3 operator*(Vector3 a, float s) noexcept {
        a *= s;
        return a;
    }
    friend Vector3 operator*(float s, Vector3 a) noexcept {
        a *= s;
        return a;
    }

    // Comparison operators //

    bool operator==(const Vector3 &rhs) const noexcept {
        return
            fabs(x - rhs.x) < vecEpsilon &&
            fabs(y - rhs.y) < vecEpsilon &&
            fabs(z - rhs.z) < vecEpsilon;
    }
    bool operator!=(const Vector3 &rhs) const noexcept {
        return !(*this == rhs);
    }


    // Helper Functions //

    constexpr float LengthSquared() const noexcept {
        return x * x + y * y + z * z;
    }
    float Length() const noexcept {
        return sqrt(LengthSquared());
    }
    float Dot(const Vector3 &other) const noexcept {
        return (x * other.x) + (y * other.y) + (z * other.z);
    }
    [[nodiscard]] Vector3 Normalized() const noexcept {
        float lsq = LengthSquared();
        if (lsq <= 1e-8f) { return Vector3::Zero; }
        return (*this) * (1.0f / sqrt(lsq));
    }
    [[nodiscard]] Vector3 Cross(const Vector3 &other) const noexcept {
        return Vector3(
            (y * other.z) - (z * other.y),
            (z * other.x) - (x * other.z),
            (x * other.y) - (y * other.x)
        );
    }
    [[nodiscard]] Vector3 Reflect(const Vector3 &normal) const noexcept {
        assert(fabs(normal.LengthSquared() - 1.0f) < 1e-3f && "Vector3::Reflect received non-normalized normal");

        float dot = this->Dot(normal);
        float factor = 2.0f * dot;

        return *this - factor * normal;
    }
    [[nodiscard]] Vector3 RotateYaw(float yaw) const noexcept {
        float cosy = cosf(yaw);
        float siny = sinf(yaw);
        float xNew = x * cosy + z * siny;
        float zNew = -x * siny + z * cosy;
        return Vector3(xNew, y, zNew);
    }
    [[nodiscard]] Vector3 RotatePitch(float pitch) const noexcept {
        float cosp = cosf(pitch);
        float sinp = sinf(pitch);
        float yNew = y * cosp - z * sinp;
        float zNew = y * sinp + z * cosp;
        return Vector3(x, yNew, zNew);
    }
    [[nodiscard]] Vector3 RotatePitchYaw(float yaw, float pitch) const noexcept {
        return this->RotatePitch(pitch).RotateYaw(yaw);
    }
    [[nodiscard]] Vector2 xy() const noexcept { 
        return Vector2(x, y); 
    }
    [[nodiscard]] Vector2 xz() const noexcept { 
        return Vector2(x, z); 
    }
    [[nodiscard]] Vector2 yz() const noexcept { 
        return Vector2(y, z); 
    }
};

inline const Vector3 Vector3::Zero(0, 0, 0);
inline const Vector3 Vector3::UnitX(1, 0, 0);
inline const Vector3 Vector3::UnitY(0, 1, 0);
inline const Vector3 Vector3::UnitZ(0, 0, 1);
inline const Vector3 Vector3::UnitScale(1, 1, 1);


class Vector3i {
public:
    int x = 0;
    int y = 0;
    int z = 0;

    static const Vector3i Zero;
    static const Vector3i UnitX;
    static const Vector3i UnitY;
    static const Vector3i UnitZ;
    static const Vector3i UnitScale;

    // Constructors //

    constexpr Vector3i() noexcept : x(0), y(0), z(0) {}
    constexpr Vector3i(int X, int Y, int Z) noexcept : x(X), y(Y), z(Z) {}
    explicit constexpr Vector3i(const int(&arr)[3]) noexcept : x(arr[0]), y(arr[1]), z(arr[2]) {}
    Vector3i(const DirectX::XMINT3 &xi) noexcept : x(xi.x), y(xi.y), z(xi.z) {}

    // DirectX Conversions //

    operator DirectX::XMINT3() const noexcept { 
        return DirectX::XMINT3(x, y, z); 
    }
    operator DirectX::XMFLOAT3() const noexcept { 
        return DirectX::XMFLOAT3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)); 
    }
    Vector3i &operator=(const DirectX::XMINT3 &xi) noexcept {
        x = xi.x; y = xi.y; z = xi.z;
        return *this;
    }
    Vector3i &operator=(DirectX::FXMVECTOR fxm) noexcept {
        DirectX::XMFLOAT3 temp;
        DirectX::XMStoreFloat3(&temp, fxm);
        x = static_cast<int>(temp.x);
        y = static_cast<int>(temp.y);
        z = static_cast<int>(temp.z);
        return *this;
    }

    // Explicit conversion(1 for position, 0 for direction) 
    [[nodiscard]] DirectX::XMVECTOR ToXMVECTOR(float w) const noexcept {
        return DirectX::XMVectorSet(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), w);
    }

    // Compound Assignment Operators (modifying *this) //

    Vector3i &operator+=(const Vector3i &rhs) noexcept { 
        x += rhs.x; y += rhs.y; z += rhs.z; return *this; 
    }
    Vector3i &operator-=(const Vector3i &rhs) noexcept { 
        x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; 
    }
    Vector3i &operator*=(int s) noexcept { 
        x *= s; y *= s; z *= s; return *this; 
    }
    Vector3i &operator/=(int s) noexcept { 
        assert(s != 0 && "Division by zero in Vector3i::operator/=");
        x /= s; 
        y /= s; 
        z /= s; 
        return *this; 
    }

    // Arithmetic Operators (returning a copy) //

    friend Vector3i operator+(Vector3i a, const Vector3i &b) noexcept { 
        a += b; return a; 
    }
    friend Vector3i operator-(Vector3i a, const Vector3i &b) noexcept { 
        a -= b; return a; 
    }
    friend Vector3i operator*(Vector3i a, int s) noexcept { 
        a *= s; return a; 
    }
    friend Vector3i operator*(int s, Vector3i a) noexcept { 
        a *= s; return a; 
    }
    friend Vector3i operator/(Vector3i a, int s) noexcept { 
        assert(s != 0 && "Division by zero in Vector3i::operator/");
        a /= s; return a; 
    }

    // Comparison operators //

    bool operator==(const Vector3i &rhs) const noexcept {
        constexpr float eps = vecEpsilon;
        return 
            abs(x - rhs.x) < eps && 
            abs(y - rhs.y) < eps && 
            abs(z - rhs.z) < eps;
    }
    bool operator!=(const Vector3i &rhs) const noexcept {
        return !(*this == rhs);
    }

    // Helper functions //

    constexpr int LengthSquared() const noexcept { 
        return x * x + y * y + z * z; 
    }
    constexpr int Dot(const Vector3i &other) const noexcept { 
        return x * other.x + y * other.y + z * other.z; 
    }

    [[nodiscard]] Vector2i xy() const noexcept {
        return Vector2i(x, y);
    }
    [[nodiscard]] Vector2i xz() const noexcept {
        return Vector2i(x, z);
    }
    [[nodiscard]] Vector2i yz() const noexcept {
        return Vector2i(y, z);
    }

    enum class RotateAxis { X, Y, Z, };
    // Steps can be -/+ for left/right rotation.
    [[nodiscard]] Vector3i Rotate90(RotateAxis axis, int steps) const noexcept {

        steps = ((steps % 4) + 4) % 4; // normalize steps to 0..3

        if (steps == 0) { return *this; }

        switch (axis) {
            case RotateAxis::X:
                switch (steps) {
                    case 1: return Vector3i(x, -z, y);
                    case 2: return Vector3i(x, -y, -z);
                    case 3: return Vector3i(x, z, -y);
                }
                break;
            case RotateAxis::Y:
                switch (steps) {
                    case 1: return Vector3i(z, y, -x);
                    case 2: return Vector3i(-x, y, -z);
                    case 3: return Vector3i(-z, y, x);
                }
                break;
            case RotateAxis::Z:
                switch (steps) {
                    case 1: return Vector3i(-y, x, z);
                    case 2: return Vector3i(-x, -y, z);
                    case 3: return Vector3i(y, -x, z);
                }
                break;
        }

        return *this;
    }

};

inline const Vector3i Vector3i::Zero(0, 0, 0);
inline const Vector3i Vector3i::UnitX(1, 0, 0);
inline const Vector3i Vector3i::UnitY(0, 1, 0);
inline const Vector3i Vector3i::UnitZ(0, 0, 1);
inline const Vector3i Vector3i::UnitScale(1, 1, 1);
