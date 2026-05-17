#include "Graphics/Color.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"

#include <gtest/gtest.h>
#include <cmath>

namespace RF {

// -------------------------------------------------------------------------
// Constructors
// -------------------------------------------------------------------------

TEST(ColorTests, DefaultConstructor_IsTransparentBlack) {
	Color c;
	EXPECT_FLOAT_EQ(c.r, 0.0f);
	EXPECT_FLOAT_EQ(c.g, 0.0f);
	EXPECT_FLOAT_EQ(c.b, 0.0f);
	EXPECT_FLOAT_EQ(c.a, 1.0f);
}

TEST(ColorTests, ConstructorRGBA_SetsAllComponents) {
	Color c(0.1f, 0.2f, 0.3f, 0.4f);
	EXPECT_FLOAT_EQ(c.r, 0.1f);
	EXPECT_FLOAT_EQ(c.g, 0.2f);
	EXPECT_FLOAT_EQ(c.b, 0.3f);
	EXPECT_FLOAT_EQ(c.a, 0.4f);
}

TEST(ColorTests, ConstructorRGB_DefaultsAlphaToOne) {
	Color c(0.5f, 0.6f, 0.7f);
	EXPECT_FLOAT_EQ(c.r, 0.5f);
	EXPECT_FLOAT_EQ(c.g, 0.6f);
	EXPECT_FLOAT_EQ(c.b, 0.7f);
	EXPECT_FLOAT_EQ(c.a, 1.0f);
}

TEST(ColorTests, CopyConstructor_CopiesAllComponents) {
	Color original(0.1f, 0.2f, 0.3f, 0.4f);
	Color copy(original);
	EXPECT_EQ(copy, original);
}

TEST(ColorTests, ConstructorFromVector3_SetsRGBAndAlphaOne) {
	Vector3 v(0.3f, 0.6f, 0.9f);
	Color c(v);
	EXPECT_FLOAT_EQ(c.r, 0.3f);
	EXPECT_FLOAT_EQ(c.g, 0.6f);
	EXPECT_FLOAT_EQ(c.b, 0.9f);
	EXPECT_FLOAT_EQ(c.a, 1.0f);
}

TEST(ColorTests, ConstructorFromVector4_SetsRGBA) {
	Vector4 v(0.2f, 0.4f, 0.6f, 0.8f);
	Color c(v);
	EXPECT_FLOAT_EQ(c.r, 0.2f);
	EXPECT_FLOAT_EQ(c.g, 0.4f);
	EXPECT_FLOAT_EQ(c.b, 0.6f);
	EXPECT_FLOAT_EQ(c.a, 0.8f);
}

// -------------------------------------------------------------------------
// Conversions
// -------------------------------------------------------------------------

TEST(ColorTests, ToFloat3_ReturnsRGB) {
	Color c(0.1f, 0.2f, 0.3f, 0.9f);
	auto f3 = c.ToFloat3();
	EXPECT_FLOAT_EQ(f3[0], 0.1f);
	EXPECT_FLOAT_EQ(f3[1], 0.2f);
	EXPECT_FLOAT_EQ(f3[2], 0.3f);
}

TEST(ColorTests, ToFloat4_ReturnsRGBA) {
	Color c(0.1f, 0.2f, 0.3f, 0.4f);
	auto f4 = c.ToFloat4();
	EXPECT_FLOAT_EQ(f4[0], 0.1f);
	EXPECT_FLOAT_EQ(f4[1], 0.2f);
	EXPECT_FLOAT_EQ(f4[2], 0.3f);
	EXPECT_FLOAT_EQ(f4[3], 0.4f);
}

TEST(ColorTests, Linear_ConvertsGammaToLinearSpace) {
	Color gamma(1.0f, 1.0f, 1.0f, 1.0f);
	Color linear = gamma.Linear();
	// GammaToLinearSpace(1.0f) = pow((1.0f + 0.055f) / 1.055f, 2.4f) = 1.0f
	EXPECT_NEAR(linear.r, 1.0f, 1e-5f);
	EXPECT_NEAR(linear.g, 1.0f, 1e-5f);
	EXPECT_NEAR(linear.b, 1.0f, 1e-5f);
	EXPECT_FLOAT_EQ(linear.a, 1.0f); // Alpha is unchanged
}

TEST(ColorTests, Linear_LowValueUsesLinearBranch) {
	// Values <= 0.04045 use the linear branch: value / 12.92
	Color c(0.04f, 0.04f, 0.04f, 0.5f);
	Color linear = c.Linear();
	EXPECT_NEAR(linear.r, 0.04f / 12.92f, 1e-5f);
	EXPECT_NEAR(linear.g, 0.04f / 12.92f, 1e-5f);
	EXPECT_NEAR(linear.b, 0.04f / 12.92f, 1e-5f);
	EXPECT_FLOAT_EQ(linear.a, 0.5f);
}

// -------------------------------------------------------------------------
// Arithmetic Operators
// -------------------------------------------------------------------------

TEST(ColorTests, AdditionOperator_AddsComponents) {
	Color a(0.1f, 0.2f, 0.3f, 0.4f);
	Color b(0.4f, 0.3f, 0.2f, 0.1f);
	Color result = a + b;
	EXPECT_NEAR(result.r, 0.5f, 1e-6f);
	EXPECT_NEAR(result.g, 0.5f, 1e-6f);
	EXPECT_NEAR(result.b, 0.5f, 1e-6f);
	EXPECT_NEAR(result.a, 0.5f, 1e-6f);
}

TEST(ColorTests, SubtractionOperator_SubtractsComponents) {
	Color a(0.5f, 0.5f, 0.5f, 0.5f);
	Color b(0.1f, 0.2f, 0.3f, 0.4f);
	Color result = a - b;
	EXPECT_NEAR(result.r, 0.4f, 1e-6f);
	EXPECT_NEAR(result.g, 0.3f, 1e-6f);
	EXPECT_NEAR(result.b, 0.2f, 1e-6f);
	EXPECT_NEAR(result.a, 0.1f, 1e-6f);
}

TEST(ColorTests, MultiplicationByScalar_ScalesComponents) {
	Color c(0.5f, 0.4f, 0.3f, 1.0f);
	Color result = c * 2.0f;
	EXPECT_NEAR(result.r, 1.0f, 1e-6f);
	EXPECT_NEAR(result.g, 0.8f, 1e-6f);
	EXPECT_NEAR(result.b, 0.6f, 1e-6f);
	EXPECT_NEAR(result.a, 2.0f, 1e-6f);
}

TEST(ColorTests, ScalarMultiplication_IsCommutative) {
	Color c(0.2f, 0.4f, 0.6f, 0.8f);
	EXPECT_EQ(c * 3.0f, 3.0f * c);
}

TEST(ColorTests, DivisionByScalar_DividesComponents) {
	Color c(0.8f, 0.6f, 0.4f, 0.2f);
	Color result = c / 2.0f;
	EXPECT_NEAR(result.r, 0.4f, 1e-6f);
	EXPECT_NEAR(result.g, 0.3f, 1e-6f);
	EXPECT_NEAR(result.b, 0.2f, 1e-6f);
	EXPECT_NEAR(result.a, 0.1f, 1e-6f);
}

// -------------------------------------------------------------------------
// Compound Assignment Operators
// -------------------------------------------------------------------------

TEST(ColorTests, AddAssign_ModifiesInPlace) {
	Color c(0.1f, 0.1f, 0.1f, 0.1f);
	c += Color(0.2f, 0.3f, 0.4f, 0.5f);
	EXPECT_NEAR(c.r, 0.3f, 1e-6f);
	EXPECT_NEAR(c.g, 0.4f, 1e-6f);
	EXPECT_NEAR(c.b, 0.5f, 1e-6f);
	EXPECT_NEAR(c.a, 0.6f, 1e-6f);
}

TEST(ColorTests, SubtractAssign_ModifiesInPlace) {
	Color c(0.9f, 0.8f, 0.7f, 0.6f);
	c -= Color(0.1f, 0.2f, 0.3f, 0.4f);
	EXPECT_NEAR(c.r, 0.8f, 1e-6f);
	EXPECT_NEAR(c.g, 0.6f, 1e-6f);
	EXPECT_NEAR(c.b, 0.4f, 1e-6f);
	EXPECT_NEAR(c.a, 0.2f, 1e-6f);
}

TEST(ColorTests, MultiplyAssign_ModifiesInPlace) {
	Color c(0.5f, 0.5f, 0.5f, 0.5f);
	c *= 2.0f;
	EXPECT_NEAR(c.r, 1.0f, 1e-6f);
	EXPECT_NEAR(c.g, 1.0f, 1e-6f);
	EXPECT_NEAR(c.b, 1.0f, 1e-6f);
	EXPECT_NEAR(c.a, 1.0f, 1e-6f);
}

TEST(ColorTests, DivideAssign_ModifiesInPlace) {
	Color c(1.0f, 0.8f, 0.6f, 0.4f);
	c /= 2.0f;
	EXPECT_NEAR(c.r, 0.5f, 1e-6f);
	EXPECT_NEAR(c.g, 0.4f, 1e-6f);
	EXPECT_NEAR(c.b, 0.3f, 1e-6f);
	EXPECT_NEAR(c.a, 0.2f, 1e-6f);
}

// -------------------------------------------------------------------------
// Comparison Operators
// -------------------------------------------------------------------------

TEST(ColorTests, EqualityOperator_ReturnsTrueForIdenticalColors) {
	Color a(0.2f, 0.4f, 0.6f, 0.8f);
	Color b(0.2f, 0.4f, 0.6f, 0.8f);
	EXPECT_TRUE(a == b);
}

TEST(ColorTests, EqualityOperator_ReturnsFalseForDifferentColors) {
	Color a(0.1f, 0.2f, 0.3f, 0.4f);
	Color b(0.9f, 0.8f, 0.7f, 0.6f);
	EXPECT_FALSE(a == b);
}

TEST(ColorTests, InequalityOperator_ReturnsTrueForDifferentColors) {
	EXPECT_TRUE(Color::Red != Color::Blue);
}

TEST(ColorTests, InequalityOperator_ReturnsFalseForIdenticalColors) {
	EXPECT_FALSE(Color::White != Color::White);
}

// -------------------------------------------------------------------------
// Indexing Operator
// -------------------------------------------------------------------------

TEST(ColorTests, IndexOperator_ReturnsCorrectComponents) {
	Color c(0.1f, 0.2f, 0.3f, 0.4f);
	EXPECT_FLOAT_EQ(c[0], 0.1f);
	EXPECT_FLOAT_EQ(c[1], 0.2f);
	EXPECT_FLOAT_EQ(c[2], 0.3f);
	EXPECT_FLOAT_EQ(c[3], 0.4f);
}

TEST(ColorTests, IndexOperator_MutatesCorrectComponent) {
	Color c(0.0f, 0.0f, 0.0f, 0.0f);
	c[0] = 1.0f;
	c[1] = 0.5f;
	c[2] = 0.25f;
	c[3] = 0.75f;
	EXPECT_FLOAT_EQ(c.r, 1.0f);
	EXPECT_FLOAT_EQ(c.g, 0.5f);
	EXPECT_FLOAT_EQ(c.b, 0.25f);
	EXPECT_FLOAT_EQ(c.a, 0.75f);
}

// -------------------------------------------------------------------------
// Color Presets
// -------------------------------------------------------------------------

TEST(ColorTests, Preset_White) {
	EXPECT_EQ(Color::White, Color(1.0f, 1.0f, 1.0f, 1.0f));
}

TEST(ColorTests, Preset_Black) {
	EXPECT_EQ(Color::Black, Color(0.0f, 0.0f, 0.0f, 1.0f));
}

TEST(ColorTests, Preset_Clear_HasZeroAlpha) {
	EXPECT_FLOAT_EQ(Color::Clear.a, 0.0f);
}

TEST(ColorTests, Preset_Red) {
	EXPECT_EQ(Color::Red, Color(1.0f, 0.0f, 0.0f, 1.0f));
}

TEST(ColorTests, Preset_Green) {
	EXPECT_EQ(Color::Green, Color(0.0f, 1.0f, 0.0f, 1.0f));
}

TEST(ColorTests, Preset_Blue) {
	EXPECT_EQ(Color::Blue, Color(0.0f, 0.0f, 1.0f, 1.0f));
}

} // namespace RF