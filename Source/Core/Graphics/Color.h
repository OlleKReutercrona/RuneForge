#pragma once
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Math.h"

#include <array>

namespace RF {	
class Color {
  public:
	float r;
	float g;
	float b;
	float a;

	// Constructors //

	Color() : r(0), g(0), b(0), a(1) {}
	Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
	Color(float r, float g, float b) : Color(r, g, b, 1.0f) {}
	Color(const Color& color) : Color(color.r, color.g, color.b, color.a) { }
	Color(const Vector3& v3) : Color(v3.x, v3.y, v3.z, 1.0f) {}
	Color(const Vector4f& v4) : Color(v4.x, v4.y, v4.z, v4.w) {}
	~Color() = default;

	// Conversions //

	inline Color Linear() const {
		return Color(
			math::GammaToLinearSpace(r),
			math::GammaToLinearSpace(g),
			math::GammaToLinearSpace(b),
			a);
	}

	inline Color Gamma() const {
		return Color(
			math::LinearToGammaSpace(r),
			math::LinearToGammaSpace(g), 
			math::LinearToGammaSpace(b), 
			a);
	}

	inline std::array<float, 3> ToFloat3() const {
		return {r, g, b};
	}

	inline std::array<float, 4> ToFloat4() const {
		return {r, g, b, a};
	}

	// Compound Assignment Operators (modifying *this) //

	Color& operator+=(const Color& rhs) {
		r += rhs.r; g += rhs.g; b += rhs.b; a += rhs.a;
		return *this;
	}

	Color& operator-=(const Color& rhs) {
		r -= rhs.r; g -= rhs.g; b -= rhs.b; a -= rhs.a;
		return *this;
	}

	Color& operator*=(float s) {
		r *= s; g *= s; b *= s; a *= s;
		return *this;
	}

	Color& operator/=(float s) {
		assert(s != 0.0f && "Division by zero in Color::operator/=");
		r /= s; g /= s; b /= s; a /= s;
		return *this;
	}

	// Arithmetic Operators (returning a copy) //

	friend Color operator+(Color a, const Color& b) {
		a += b;
		return a;
	}

	friend Color operator-(Color a, const Color& b) {
		a -= b;
		return a;
	}

	friend Color operator*(Color a, float s) {
		a *= s;
		return a;
	}

	friend Color operator*(float s, Color a) {
		a *= s;
		return a;
	}

	friend Color operator/(Color a, float s) {
		a /= s;
		return a;
	}

	// Comparison operators //

	bool operator==(const Color& rhs) const {
		return
			fabs(r - rhs.r) < 1e-6f &&
			fabs(g - rhs.g) < 1e-6f &&
			fabs(b - rhs.b) < 1e-6f &&
			fabs(a - rhs.a) < 1e-6f;
	}

	bool operator!=(const Color& rhs) const {
		return !(*this == rhs);
	}

	// Indexing operator //

	float operator[](int index) const {
		switch (index) {
			case 0:
				return r;
			case 1:
				return g;
			case 2:
				return b;
			case 3:
				return a;
			default:
				assert(false && "Invalid Color index!");
				return 0.0f; // Return to silence compiler warning
		}
	}

	float& operator[](int index) {
		switch (index) {
			case 0:
				return r;
			case 1:
				return g;
			case 2:
				return b;
			case 3:
				return a;
			default:
				assert(false && "Invalid Color index!");
				static float dummy = 0.0f; // Return reference to dummy to silence compiler warning
				return dummy;
		}
	}

	// Color Presets //

	// Achromatic

	static const Color White;
	static const Color LightGray;
	static const Color Gray;
	static const Color DarkGray;
	static const Color Black;
	static const Color Clear;

	// Reds

	static const Color Red;
	static const Color DarkRed;
	static const Color Crimson;
	static const Color Salmon;

	// Oranges / Yellows

	static const Color Orange;
	static const Color OrangeRed;
	static const Color Yellow;
	static const Color Gold;

	// Greens

	static const Color Green;
	static const Color DarkGreen;
	static const Color Lime;
	static const Color Olive;
	static const Color Teal;
	static const Color Mint;

	// Blues

	static const Color Blue;
	static const Color DarkBlue;
	static const Color SkyBlue;
	static const Color Navy;
	static const Color Cyan;
	static const Color Cornflower;

	// Purples / Pinks

	static const Color Magenta;
	static const Color Purple;
	static const Color Violet;
	static const Color Indigo;
	static const Color Pink;
	static const Color HotPink;

	// Browns

	static const Color Brown;
	static const Color Sienna;
	static const Color Tan;
	static const Color Beige;
};

// Achromatic
inline const Color Color::White = Color(1.0f, 1.0f, 1.0f, 1.0f);			  // #FFFFFF
inline const Color Color::LightGray = Color(0.8275f, 0.8275f, 0.8275f, 1.0f); // #D3D3D3
inline const Color Color::Gray = Color(0.5020f, 0.5020f, 0.5020f, 1.0f);	  // #808080
inline const Color Color::DarkGray = Color(0.6627f, 0.6627f, 0.6627f, 1.0f);  // #A9A9A9
inline const Color Color::Black = Color(0.0f, 0.0f, 0.0f, 1.0f);			  // #000000
inline const Color Color::Clear = Color(0.0f, 0.0f, 0.0f, 0.0f);			  // #00000000

// Reds
inline const Color Color::Red = Color(1.0f, 0.0f, 0.0f, 1.0f);				// #FF0000
inline const Color Color::DarkRed = Color(0.5451f, 0.0f, 0.0f, 1.0f);		// #8B0000
inline const Color Color::Crimson = Color(0.8627f, 0.0784f, 0.2353f, 1.0f); // #DC143C
inline const Color Color::Salmon = Color(0.9804f, 0.5020f, 0.4471f, 1.0f);	// #FA8072

// Oranges / Yellows
inline const Color Color::Orange = Color(1.0f, 0.6471f, 0.0f, 1.0f);	// #FFA500
inline const Color Color::OrangeRed = Color(1.0f, 0.2706f, 0.0f, 1.0f); // #FF4500
inline const Color Color::Yellow = Color(1.0f, 1.0f, 0.0f, 1.0f);		// #FFFF00
inline const Color Color::Gold = Color(1.0f, 0.8431f, 0.0f, 1.0f);		// #FFD700

// Greens
inline const Color Color::Green = Color(0.0f, 0.5020f, 0.0f, 1.0f);		// #008000
inline const Color Color::Lime = Color(0.0f, 1.0f, 0.0f, 1.0f);			// #00FF00
inline const Color Color::DarkGreen = Color(0.0f, 0.3922f, 0.0f, 1.0f); // #006400
inline const Color Color::Olive = Color(0.5020f, 0.5020f, 0.0f, 1.0f);	// #808000
inline const Color Color::Teal = Color(0.0f, 0.5020f, 0.5020f, 1.0f);	// #008080
inline const Color Color::Mint = Color(0.9608f, 1.0f, 0.9804f, 1.0f);	// #F5FFFA

// Blues
inline const Color Color::Blue = Color(0.0f, 0.0f, 1.0f, 1.0f);				   // #0000FF
inline const Color Color::DarkBlue = Color(0.0f, 0.0f, 0.5451f, 1.0f);		   // #00008B
inline const Color Color::SkyBlue = Color(0.5294f, 0.8078f, 0.9216f, 1.0f);	   // #87CEEB
inline const Color Color::Navy = Color(0.0f, 0.0f, 0.5020f, 1.0f);			   // #000080
inline const Color Color::Cyan = Color(0.0f, 1.0f, 1.0f, 1.0f);				   // #00FFFF
inline const Color Color::Cornflower = Color(0.3922f, 0.5843f, 0.9294f, 1.0f); // #6495ED

// Purples / Pinks
inline const Color Color::Magenta = Color(1.0f, 0.0f, 1.0f, 1.0f);		   // #FF00FF
inline const Color Color::Purple = Color(0.5020f, 0.0f, 0.5020f, 1.0f);	   // #800080
inline const Color Color::Violet = Color(0.9333f, 0.5098f, 0.9333f, 1.0f); // #EE82EE
inline const Color Color::Indigo = Color(0.2941f, 0.0f, 0.5098f, 1.0f);	   // #4B0082
inline const Color Color::Pink = Color(1.0f, 0.7529f, 0.7961f, 1.0f);	   // #FFC0CB
inline const Color Color::HotPink = Color(1.0f, 0.4118f, 0.7059f, 1.0f);   // #FF69B4

// Browns
inline const Color Color::Brown = Color(0.5451f, 0.2706f, 0.0745f, 1.0f);  // #8B4513
inline const Color Color::Sienna = Color(0.6275f, 0.3216f, 0.1765f, 1.0f); // #A0522D
inline const Color Color::Tan = Color(0.8235f, 0.7059f, 0.5490f, 1.0f);	   // #D2B48C
inline const Color Color::Beige = Color(0.9608f, 0.9608f, 0.8627f, 1.0f);  // #F5F5DC
} // namespace RF