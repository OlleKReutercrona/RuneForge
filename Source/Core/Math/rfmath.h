#pragma once
#include <cmath>

#ifndef PI
#define PI 3.14159265358979323846f
#endif

namespace rfmath {

    static inline constexpr float TWO_PI = 2.0f * PI;
    static inline constexpr float HALF_PI = 0.5f * PI;

    static inline constexpr float Deg2Rad(float deg) noexcept { return deg * (PI / 180.0f); }
    static inline constexpr float Rad2Deg(float rad) noexcept { return rad * (180.0f / PI); }

    template<typename T> static inline constexpr T Square(const T &x) noexcept { return x * x; }
    template<typename T> static inline constexpr T Cube(const T &x) noexcept { return x * x * x; }

    template<typename T> static inline constexpr const T &Min(const T &a, const T &b) noexcept { return (a < b) ? a : b; }
    template<typename T> static inline constexpr const T &Max(const T &a, const T &b) noexcept { return (a > b) ? a : b; }
    template<typename T> static inline constexpr const T &Clamp(const T &x, const T &lo, const T &hi) noexcept { return (x < lo) ? lo : (x > hi ? hi : x); }

    static inline float WrapDeg(float d) noexcept {
        float result = std::fmod(d, 360.0f);
        return (result < 0.0f) ? result + 360.0f : result;
    }

    static inline float WrapRad(float r) noexcept {
        float result = std::fmod(r, TWO_PI);
        return (result < 0.0f) ? result + TWO_PI : result;
    }

}