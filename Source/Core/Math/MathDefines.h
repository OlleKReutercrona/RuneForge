#pragma once
#include <cmath>

#ifndef PI
#define PI 3.14159265358979323846f
#endif

#define TWO_PI   (2.0f * PI)
#define HALF_PI  (0.5f * PI)

#define DEG2RAD(deg)	((deg) * (PI / 180.0f))
#define RAD2DEG(rad)	((rad) * (180.0f / PI))

#define SQUARE(x)	((x) * (x))
#define CUBE(x)		((x) * (x) * (x))

#define MIN(a, b)   (((a) < (b)) ? (a) : (b))
#define MAX(a, b)   (((a) > (b)) ? (a) : (b))
#define CLAMP(x, lo, hi)	(((x) < (lo)) ? (lo) : (((x) > (hi)) ? (hi) : (x)))

#define WRAP_DEG(d)   (fmodf((d), 360.0f) < 0 ? fmodf((d), 360.0f) + 360.0f : fmodf((d), 360.0f))
#define WRAP_RAD(r)   (fmodf((r), TWO_PI) < 0 ? fmodf((r), TWO_PI) + TWO_PI : fmodf((r), TWO_PI))

