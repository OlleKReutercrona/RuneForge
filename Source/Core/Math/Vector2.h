#pragma once
#include <DirectXMath.h>
#include <cmath>

constexpr float vecEpsilon = 1e-6f;

class Vector2 {
public:
    float x = 0.0f;
    float y = 0.0f;

    static const Vector2 Zero;
    static const Vector2 UnitX;
    static const Vector2 UnitY;
    static const Vector2 UnitScale;

    // Constructors //

    constexpr Vector2() noexcept : x(0), y(0) {}
    constexpr Vector2(float X, float Y) noexcept : x(X), y(Y) {}
    explicit constexpr Vector2(const float(&arr)[2]) noexcept : x(arr[0]), y(arr[1]) {}
    Vector2(const DirectX::XMFLOAT2 &xmf2) noexcept : x(xmf2.x), y(xmf2.y) {}
    Vector2(DirectX::FXMVECTOR fxm) noexcept { *this = fxm; }

    // DirectX Conversions //

    operator DirectX::XMFLOAT2() const noexcept {
        return DirectX::XMFLOAT2(x, y);
    }
    Vector2 &operator=(const DirectX::XMFLOAT2 &xmf2) noexcept {
        x = xmf2.x;
        y = xmf2.y;
        return *this;
    }
    Vector2 &operator=(DirectX::FXMVECTOR fxm) noexcept {
        DirectX::XMFLOAT2 temp;
        DirectX::XMStoreFloat2(&temp, fxm);
        x = temp.x;
        y = temp.y;
        return *this;
    }

    // Explicit conversion(1 for position, 0 for direction)
    [[nodiscard]] DirectX::XMVECTOR ToXMVECTOR(float w) const noexcept {
        return DirectX::XMVectorSet(x, y, 0.0f, w);
    }

    // Compound Assignment Operators (modifying *this) //

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
        //assert(s != 0.0f && "Division by zero in Vector2::operator/=");
        x /= s;
        y /= s;
        return *this;
    }

    // Arithmetic Operators (returning a copy) //

    friend Vector2 operator+(Vector2 a, const Vector2 &b) noexcept { 
        a += b; 
        return a; 
    }
    friend Vector2 operator-(Vector2 a, const Vector2 &b) noexcept { 
        a -= b; 
        return a; 
    }
    friend Vector2 operator/(Vector2 a, float s) noexcept { 
        //assert(s != 0.0f && "Division by zero in Vector2::operator/"); 
        a /= s; 
        return a; 
    }
    friend Vector2 operator*(Vector2 a, float s) noexcept { 
        a *= s;
        return a; 
    }
    friend Vector2 operator*(float s, Vector2 a) noexcept {
        a *= s; 
        return a; 
    }

    // Comparison operators //

    bool operator==(const Vector2 &rhs) const noexcept {
        return fabs(x - rhs.x) < vecEpsilon && fabs(y - rhs.y) < vecEpsilon;
    }
    bool operator!=(const Vector2 &rhs) const noexcept {
        return !(*this == rhs);
    }

    // Helper functions //

    constexpr float LengthSquared() const noexcept { 
        return x * x + y * y; 
    }
    float Length() const noexcept { 
        return sqrtf(LengthSquared()); 
    }
    float Dot(const Vector2 &other) const noexcept { 
        return x * other.x + y * other.y; 
    }
    [[nodiscard]] Vector2 Normalized() const noexcept {
        float lsq = LengthSquared();
        if (lsq <= 1e-8f) { return Vector2::Zero; }
        return (*this) * (1.0f / sqrtf(lsq));
    }
    [[nodiscard]] Vector2 Reflect(const Vector2 &normal) const noexcept {
        //assert(fabs(normal.LengthSquared() - 1.0f) < 1e-3f && "Vector3::Reflect received non-normalized normal");

        float dot = this->Dot(normal);
        float factor = 2.0f * dot;

        return *this - factor * normal;
    }

};

inline const Vector2 Vector2::Zero(0, 0);
inline const Vector2 Vector2::UnitX(1, 0);
inline const Vector2 Vector2::UnitY(0, 1);
inline const Vector2 Vector2::UnitScale(1, 1);


class Vector2i {
public:
    int x = 0;
    int y = 0;

    static const Vector2i Zero;
    static const Vector2i UnitX;
    static const Vector2i UnitY;
    static const Vector2i UnitScale;

    // Constructors //

    constexpr Vector2i() noexcept : x(0), y(0) {}
    constexpr Vector2i(int X, int Y) noexcept : x(X), y(Y) {}
    explicit constexpr Vector2i(const int(&arr)[2]) noexcept : x(arr[0]), y(arr[1]) {}
    Vector2i(const DirectX::XMINT2 &xi) noexcept : x(xi.x), y(xi.y) {}

    // DirectX Conversions //

    operator DirectX::XMINT2() const noexcept {
        return DirectX::XMINT2(x, y);
    }
    operator DirectX::XMFLOAT2() const noexcept {
        return DirectX::XMFLOAT2(static_cast<float>(x), static_cast<float>(y));
    }
    Vector2i &operator=(const DirectX::XMINT2 &xi) noexcept {
        x = xi.x;
        y = xi.y;
        return *this;
    }
    Vector2i &operator=(DirectX::FXMVECTOR fxm) noexcept {
        DirectX::XMFLOAT2 temp;
        DirectX::XMStoreFloat2(&temp, fxm);
        x = static_cast<int>(temp.x);
        y = static_cast<int>(temp.y);
        return *this;
    }

    // Explicit conversion(1 for position, 0 for direction)
    [[nodiscard]] DirectX::XMVECTOR ToXMVECTOR(float w) const noexcept {
        return DirectX::XMVectorSet(static_cast<float>(x), static_cast<float>(y), 0.0f, w);
    }

    // Compound Assignment Operators (modifying *this) //

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
        //assert(s != 0 && "Division by zero in Vector2i::operator/=");
        x /= s;
        y /= s;
        return *this;
    }

    // Arithmetic Operators (returning a copy) //

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
    friend Vector2i operator*(int s, Vector2i a) noexcept {
        a *= s;
        return a;
    }
    friend Vector2i operator/(Vector2i a, int s) noexcept {
        //assert(s != 0 && "Division by zero in Vector2i::operator/");
        a /= s;
        return a;
    }

    // Comparison operators //

    bool operator==(const Vector2i &other) const noexcept { 
        return x == other.x && y == other.y; 
    }
    bool operator!=(const Vector2i &other) const noexcept { 
        return !(*this == other); 
    }

    // Helper Functions //

    constexpr int LengthSquared() const noexcept {
        return x * x + y * y;
    }
    int Dot(const Vector2i &other) const noexcept { return x * other.x + y * other.y; }
};

inline const Vector2i Vector2i::Zero(0, 0);
inline const Vector2i Vector2i::UnitX(1, 0);
inline const Vector2i Vector2i::UnitY(0, 1);
inline const Vector2i Vector2i::UnitScale(1, 1);