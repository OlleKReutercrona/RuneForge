#include <gtest/gtest.h>

#include "Math/Vector4.h"
#include "Utility/TestUtility.h"
#include <DirectXMath.h>

using namespace DirectX;

namespace RFMath {
TestUtility testUtility;

//*********************************************************************************
// FLOAT
//*********************************************************************************
TEST(Vector4_Float_Tests, DefaultConstructor) {
	Vector4f vector;
	EXPECT_EQ(vector.x, 0.0f);
	EXPECT_EQ(vector.y, 0.0f);
	EXPECT_EQ(vector.z, 0.0f);
	EXPECT_EQ(vector.w, 0.0f);
}

TEST(Vector4_Float_Tests, ParameterizedConstructor) {
	float randomX = testUtility.GetRandomFloat();
	float randomY = testUtility.GetRandomFloat();
	float randomZ = testUtility.GetRandomFloat();
	float randomW = testUtility.GetRandomFloat();
	Vector4f vector(randomX, randomY, randomZ, randomW);
	EXPECT_EQ(vector.x, randomX);
	EXPECT_EQ(vector.y, randomY);
	EXPECT_EQ(vector.z, randomZ);
	EXPECT_EQ(vector.w, randomW);
}

TEST(Vector4_Float_Tests, CopyConstructor) {
	float randomX = testUtility.GetRandomFloat();
	float randomY = testUtility.GetRandomFloat();
	float randomZ = testUtility.GetRandomFloat();
	float randomW = testUtility.GetRandomFloat();
	Vector4f vector1(randomX, randomY, randomZ, randomW);
	Vector4f vector2(vector1);
	EXPECT_EQ(vector2, vector1);
}

TEST(Vector4_Float_Tests, AssignmentOperator) {
	float randomX = testUtility.GetRandomFloat();
	float randomY = testUtility.GetRandomFloat();
	float randomZ = testUtility.GetRandomFloat();
	float randomW = testUtility.GetRandomFloat();
	Vector4f vector1(randomX, randomY, randomZ, randomW);
	Vector4f vector2 = vector1;
	EXPECT_EQ(vector2, vector1);
}

TEST(Vector4_Float_Tests, MultiplicationOperator) {
	const float randomX1 = testUtility.GetRandomFloat();
	const float randomY1 = testUtility.GetRandomFloat();
	const float randomZ1 = testUtility.GetRandomFloat();
	const float randomW1 = testUtility.GetRandomFloat();
	Vector4f vector1(randomX1, randomY1, randomZ1, randomW1);

	const float randomX2 = testUtility.GetRandomFloat();
	const float randomY2 = testUtility.GetRandomFloat();
	const float randomZ2 = testUtility.GetRandomFloat();
	const float randomW2 = testUtility.GetRandomFloat();
	Vector4f vector2(randomX2, randomY2, randomZ2, randomW2);

	auto result = vector1 * vector2;
	EXPECT_EQ(result.x, randomX1 * randomX2);
	EXPECT_EQ(result.y, randomY1 * randomY2);
	EXPECT_EQ(result.z, randomZ1 * randomZ2);
	EXPECT_EQ(result.w, randomW1 * randomW2);
}

TEST(Vector4_Float_Tests, MultiplicationAssignmentOperator) {
	const float randomX1 = testUtility.GetRandomFloat();
	const float randomY1 = testUtility.GetRandomFloat();
	const float randomZ1 = testUtility.GetRandomFloat();
	const float randomW1 = testUtility.GetRandomFloat();
	Vector4f vector1(randomX1, randomY1, randomZ1, randomW1);

	const float randomX2 = testUtility.GetRandomFloat();
	const float randomY2 = testUtility.GetRandomFloat();
	const float randomZ2 = testUtility.GetRandomFloat();
	const float randomW2 = testUtility.GetRandomFloat();
	Vector4f vector2(randomX2, randomY2, randomZ2, randomW2);

	vector1 *= vector2;
	EXPECT_EQ(vector1.x, randomX1 * randomX2);
	EXPECT_EQ(vector1.y, randomY1 * randomY2);
	EXPECT_EQ(vector1.z, randomZ1 * randomZ2);
	EXPECT_EQ(vector1.w, randomW1 * randomW2);
}

TEST(Vector4_Float_Tests, AdditionOperator) {
	const float randomX1 = testUtility.GetRandomFloat();
	const float randomY1 = testUtility.GetRandomFloat();
	const float randomZ1 = testUtility.GetRandomFloat();
	const float randomW1 = testUtility.GetRandomFloat();
	Vector4f vector1(randomX1, randomY1, randomZ1, randomW1);

	const float randomX2 = testUtility.GetRandomFloat();
	const float randomY2 = testUtility.GetRandomFloat();
	const float randomZ2 = testUtility.GetRandomFloat();
	const float randomW2 = testUtility.GetRandomFloat();
	Vector4f vector2(randomX2, randomY2, randomZ2, randomW2);

	auto result = vector1 + vector2;
	EXPECT_EQ(result.x, randomX1 + randomX2);
	EXPECT_EQ(result.y, randomY1 + randomY2);
	EXPECT_EQ(result.z, randomZ1 + randomZ2);
	EXPECT_EQ(result.w, randomW1 + randomW2);
}

TEST(Vector4_Float_Tests, AdditionAssignmentOperator) {
	const float randomX1 = testUtility.GetRandomFloat();
	const float randomY1 = testUtility.GetRandomFloat();
	const float randomZ1 = testUtility.GetRandomFloat();
	const float randomW1 = testUtility.GetRandomFloat();
	Vector4f vector1(randomX1, randomY1, randomZ1, randomW1);

	const float randomX2 = testUtility.GetRandomFloat();
	const float randomY2 = testUtility.GetRandomFloat();
	const float randomZ2 = testUtility.GetRandomFloat();
	const float randomW2 = testUtility.GetRandomFloat();
	Vector4f vector2(randomX2, randomY2, randomZ2, randomW2);

	vector1 += vector2;
	EXPECT_EQ(vector1.x, randomX1 + randomX2);
	EXPECT_EQ(vector1.y, randomY1 + randomY2);
	EXPECT_EQ(vector1.z, randomZ1 + randomZ2);
	EXPECT_EQ(vector1.w, randomW1 + randomW2);
}

TEST(Vector4_Float_Tests, LengthSqrd) {
	const float randomX = testUtility.GetRandomFloat();
	const float randomY = testUtility.GetRandomFloat();
	const float randomZ = testUtility.GetRandomFloat();
	const float randomW = testUtility.GetRandomFloat();
	Vector4f vector(randomX, randomY, randomZ, randomW);

	const float expectedLengthSqrd = randomX * randomX + randomY * randomY + randomZ * randomZ + randomW * randomW;
	EXPECT_EQ(vector.LengthSqrd(), expectedLengthSqrd);
}

TEST(Vector4_Float_Tests, Length) {
	const float randomX = testUtility.GetRandomFloat();
	const float randomY = testUtility.GetRandomFloat();
	const float randomZ = testUtility.GetRandomFloat();
	const float randomW = testUtility.GetRandomFloat();
	Vector4f vector(randomX, randomY, randomZ, randomW);
	const float expectedLength = sqrt(randomX * randomX + randomY * randomY + randomZ * randomZ + randomW * randomW);

	EXPECT_EQ(vector.Length(), expectedLength);
}

TEST(Vector4_Float_Tests, GetNormalized) {
	const float randomX = testUtility.GetRandomFloat();
	const float randomY = testUtility.GetRandomFloat();
	const float randomZ = testUtility.GetRandomFloat();
	const float randomW = testUtility.GetRandomFloat();
	Vector4f vector(randomX, randomY, randomZ, randomW);

	const float length = vector.Length();
	Vector4f expectedNormalized(randomX / length, randomY / length, randomZ / length, randomW / length);

	EXPECT_EQ(vector.GetNormalized(), expectedNormalized);
}

TEST(Vector4_Float_Tests, Normalize) {
	const float randomX = testUtility.GetRandomFloat();
	const float randomY = testUtility.GetRandomFloat();
	const float randomZ = testUtility.GetRandomFloat();
	const float randomW = testUtility.GetRandomFloat();
	Vector4f vector(randomX, randomY, randomZ, randomW);

	const float length = vector.Length();
	vector.Normalize();

	EXPECT_EQ(vector.x, randomX / length);
	EXPECT_EQ(vector.y, randomY / length);
	EXPECT_EQ(vector.z, randomZ / length);
	EXPECT_EQ(vector.w, randomW / length);
}

TEST(Vector4_Float_Tests, Dot) {
	const float randomX1 = testUtility.GetRandomFloat();
	const float randomY1 = testUtility.GetRandomFloat();
	const float randomZ1 = testUtility.GetRandomFloat();
	const float randomW1 = testUtility.GetRandomFloat();
	Vector4f vector1(randomX1, randomY1, randomZ1, randomW1);

	const float randomX2 = testUtility.GetRandomFloat();
	const float randomY2 = testUtility.GetRandomFloat();
	const float randomZ2 = testUtility.GetRandomFloat();
	const float randomW2 = testUtility.GetRandomFloat();
	Vector4f vector2(randomX2, randomY2, randomZ2, randomW2);

	const float expectedDot = randomX1 * randomX2 + randomY1 * randomY2 + randomZ1 * randomZ2 + randomW1 * randomW2;

	EXPECT_EQ(vector1.Dot(vector2), expectedDot);
}

// DX Stuff

TEST(Vector4_Float_Tests, XMFLOAT4_Constructor) {
	const float randomX = testUtility.GetRandomFloat();
	const float randomY = testUtility.GetRandomFloat();
	const float randomZ = testUtility.GetRandomFloat();
	const float randomW = testUtility.GetRandomFloat();
	DirectX::XMFLOAT4 xmFloat4(randomX, randomY, randomZ, randomW);
	Vector4f vector(xmFloat4);
	EXPECT_EQ(vector.x, randomX);
	EXPECT_EQ(vector.y, randomY);
	EXPECT_EQ(vector.z, randomZ);
	EXPECT_EQ(vector.w, randomW);
}

TEST(Vector4_Float_Tests, XMINT4_Constructor) {
	const int randomX = testUtility.GetRandomInt();
	const int randomY = testUtility.GetRandomInt();
	const int randomZ = testUtility.GetRandomInt();
	const int randomW = testUtility.GetRandomInt();
	DirectX::XMINT4 xmInt4(randomX, randomY, randomZ, randomW);
	Vector4f vector(xmInt4);
	EXPECT_EQ(vector.x, static_cast<float>(randomX));
	EXPECT_EQ(vector.y, static_cast<float>(randomY));
	EXPECT_EQ(vector.z, static_cast<float>(randomZ));
	EXPECT_EQ(vector.w, static_cast<float>(randomW));
}

TEST(Vector4_Float_Tests, XMUINT4_Constructor) {
	const unsigned int randomX = testUtility.GetRandomInt(0);
	const unsigned int randomY = testUtility.GetRandomInt(0);
	const unsigned int randomZ = testUtility.GetRandomInt(0);
	const unsigned int randomW = testUtility.GetRandomInt(0);
	DirectX::XMUINT4 xmUInt4(randomX, randomY, randomZ, randomW);
	Vector4f vector(xmUInt4);
	EXPECT_EQ(vector.x, static_cast<float>(randomX));
	EXPECT_EQ(vector.y, static_cast<float>(randomY));
	EXPECT_EQ(vector.z, static_cast<float>(randomZ));
	EXPECT_EQ(vector.w, static_cast<float>(randomW));
}

TEST(Vector4_Float_Tests, ToXMFLOAT4) {
	const float randomX = testUtility.GetRandomFloat();
	const float randomY = testUtility.GetRandomFloat();
	const float randomZ = testUtility.GetRandomFloat();
	const float randomW = testUtility.GetRandomFloat();
	Vector4f vector(randomX, randomY, randomZ, randomW);

	DirectX::XMFLOAT4 xmFloat4 = vector.ToXMFLOAT4();
	EXPECT_EQ(xmFloat4.x, randomX);
	EXPECT_EQ(xmFloat4.y, randomY);
	EXPECT_EQ(xmFloat4.z, randomZ);
	EXPECT_EQ(xmFloat4.w, randomW);
}

TEST(Vector4_Float_Tests, XMFLOAT4_Operator) {
	const float randomX = testUtility.GetRandomFloat();
	const float randomY = testUtility.GetRandomFloat();
	const float randomZ = testUtility.GetRandomFloat();
	const float randomW = testUtility.GetRandomFloat();
	Vector4f vector(randomX, randomY, randomZ, randomW);

	DirectX::XMFLOAT4 xmFloat4(vector);
	EXPECT_EQ(xmFloat4.x, randomX);
	EXPECT_EQ(xmFloat4.y, randomY);
	EXPECT_EQ(xmFloat4.z, randomZ);
	EXPECT_EQ(xmFloat4.w, randomW);
}

TEST(Vector4_Float_Tests, toXMINT4) {
	const float randomX = testUtility.GetRandomFloat();
	const float randomY = testUtility.GetRandomFloat();
	const float randomZ = testUtility.GetRandomFloat();
	const float randomW = testUtility.GetRandomFloat();
	Vector4f vector(randomX, randomY, randomZ, randomW);

	DirectX::XMINT4 xmInt4 = vector.ToXMINT4();
	EXPECT_EQ(xmInt4.x, static_cast<int>(randomX));
	EXPECT_EQ(xmInt4.y, static_cast<int>(randomY));
	EXPECT_EQ(xmInt4.z, static_cast<int>(randomZ));
	EXPECT_EQ(xmInt4.w, static_cast<int>(randomW));
}

TEST(Vector4_Float_Tests, ToXMINT4) {
	const float randomX = testUtility.GetRandomFloat();
	const float randomY = testUtility.GetRandomFloat();
	const float randomZ = testUtility.GetRandomFloat();
	const float randomW = testUtility.GetRandomFloat();
	Vector4f vector(randomX, randomY, randomZ, randomW);
	DirectX::XMINT4 xmInt4(vector);
	EXPECT_EQ(xmInt4.x, static_cast<int>(randomX));
	EXPECT_EQ(xmInt4.y, static_cast<int>(randomY));
	EXPECT_EQ(xmInt4.z, static_cast<int>(randomZ));
	EXPECT_EQ(xmInt4.w, static_cast<int>(randomW));
}

TEST(Vector4_Float_Tests, ToXMUINT4) {
	const float randomX = testUtility.GetRandomFloat();
	const float randomY = testUtility.GetRandomFloat();
	const float randomZ = testUtility.GetRandomFloat();
	const float randomW = testUtility.GetRandomFloat();
	Vector4f vector(randomX, randomY, randomZ, randomW);

	DirectX::XMUINT4 xmUInt4 = vector.ToXMUINT4();
	EXPECT_EQ(xmUInt4.x, static_cast<unsigned int>(randomX));
	EXPECT_EQ(xmUInt4.y, static_cast<unsigned int>(randomY));
	EXPECT_EQ(xmUInt4.z, static_cast<unsigned int>(randomZ));
	EXPECT_EQ(xmUInt4.w, static_cast<unsigned int>(randomW));
}

TEST(Vector4_Float_Tests, XMUINT4_Operator) {
	const float randomX = testUtility.GetRandomFloat();
	const float randomY = testUtility.GetRandomFloat();
	const float randomZ = testUtility.GetRandomFloat();
	const float randomW = testUtility.GetRandomFloat();
	Vector4f vector(randomX, randomY, randomZ, randomW);
	DirectX::XMUINT4 xmUInt4(vector);
	EXPECT_EQ(xmUInt4.x, static_cast<unsigned int>(randomX));
	EXPECT_EQ(xmUInt4.y, static_cast<unsigned int>(randomY));
	EXPECT_EQ(xmUInt4.z, static_cast<unsigned int>(randomZ));
	EXPECT_EQ(xmUInt4.w, static_cast<unsigned int>(randomW));
}

//*********************************************************************************
// DOUBLE (Vector4d) - same tests as float but with double alias
//*********************************************************************************
TEST(Vector4_Double_Tests, DefaultConstructor) {
	Vector4d vector;
	EXPECT_EQ(vector.x, 0.0);
	EXPECT_EQ(vector.y, 0.0);
	EXPECT_EQ(vector.z, 0.0);
	EXPECT_EQ(vector.w, 0.0);
}

TEST(Vector4_Double_Tests, ParameterizedConstructor) {
	double randomX = static_cast<double>(testUtility.GetRandomFloat());
	double randomY = static_cast<double>(testUtility.GetRandomFloat());
	double randomZ = static_cast<double>(testUtility.GetRandomFloat());
	double randomW = static_cast<double>(testUtility.GetRandomFloat());
	Vector4d vector(randomX, randomY, randomZ, randomW);
	EXPECT_EQ(vector.x, randomX);
	EXPECT_EQ(vector.y, randomY);
	EXPECT_EQ(vector.z, randomZ);
	EXPECT_EQ(vector.w, randomW);
}

TEST(Vector4_Double_Tests, CopyConstructor) {
	double randomX = static_cast<double>(testUtility.GetRandomFloat());
	double randomY = static_cast<double>(testUtility.GetRandomFloat());
	double randomZ = static_cast<double>(testUtility.GetRandomFloat());
	double randomW = static_cast<double>(testUtility.GetRandomFloat());
	Vector4d vector1(randomX, randomY, randomZ, randomW);
	Vector4d vector2(vector1);
	EXPECT_EQ(vector2, vector1);
}

TEST(Vector4_Double_Tests, AssignmentOperator) {
	double randomX = static_cast<double>(testUtility.GetRandomFloat());
	double randomY = static_cast<double>(testUtility.GetRandomFloat());
	double randomZ = static_cast<double>(testUtility.GetRandomFloat());
	double randomW = static_cast<double>(testUtility.GetRandomFloat());
	Vector4d vector1(randomX, randomY, randomZ, randomW);
	Vector4d vector2 = vector1;
	EXPECT_EQ(vector2, vector1);
}

TEST(Vector4_Double_Tests, MultiplicationOperator) {
	const double randomX1 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomY1 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomZ1 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomW1 = static_cast<double>(testUtility.GetRandomFloat());
	Vector4d vector1(randomX1, randomY1, randomZ1, randomW1);

	const double randomX2 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomY2 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomZ2 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomW2 = static_cast<double>(testUtility.GetRandomFloat());
	Vector4d vector2(randomX2, randomY2, randomZ2, randomW2);

	auto result = vector1 * vector2;
	EXPECT_EQ(result.x, randomX1 * randomX2);
	EXPECT_EQ(result.y, randomY1 * randomY2);
	EXPECT_EQ(result.z, randomZ1 * randomZ2);
	EXPECT_EQ(result.w, randomW1 * randomW2);
}

TEST(Vector4_Double_Tests, MultiplicationAssignmentOperator) {
	const double randomX1 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomY1 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomZ1 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomW1 = static_cast<double>(testUtility.GetRandomFloat());
	Vector4d vector1(randomX1, randomY1, randomZ1, randomW1);

	const double randomX2 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomY2 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomZ2 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomW2 = static_cast<double>(testUtility.GetRandomFloat());
	Vector4d vector2(randomX2, randomY2, randomZ2, randomW2);

	vector1 *= vector2;
	EXPECT_EQ(vector1.x, randomX1 * randomX2);
	EXPECT_EQ(vector1.y, randomY1 * randomY2);
	EXPECT_EQ(vector1.z, randomZ1 * randomZ2);
	EXPECT_EQ(vector1.w, randomW1 * randomW2);
}

TEST(Vector4_Double_Tests, AdditionOperator) {
	const double randomX1 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomY1 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomZ1 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomW1 = static_cast<double>(testUtility.GetRandomFloat());
	Vector4d vector1(randomX1, randomY1, randomZ1, randomW1);

	const double randomX2 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomY2 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomZ2 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomW2 = static_cast<double>(testUtility.GetRandomFloat());
	Vector4d vector2(randomX2, randomY2, randomZ2, randomW2);

	auto result = vector1 + vector2;
	EXPECT_EQ(result.x, randomX1 + randomX2);
	EXPECT_EQ(result.y, randomY1 + randomY2);
	EXPECT_EQ(result.z, randomZ1 + randomZ2);
	EXPECT_EQ(result.w, randomW1 + randomW2);
}

TEST(Vector4_Double_Tests, AdditionAssignmentOperator) {
	const double randomX1 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomY1 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomZ1 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomW1 = static_cast<double>(testUtility.GetRandomFloat());
	Vector4d vector1(randomX1, randomY1, randomZ1, randomW1);

	const double randomX2 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomY2 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomZ2 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomW2 = static_cast<double>(testUtility.GetRandomFloat());
	Vector4d vector2(randomX2, randomY2, randomZ2, randomW2);

	vector1 += vector2;
	EXPECT_EQ(vector1.x, randomX1 + randomX2);
	EXPECT_EQ(vector1.y, randomY1 + randomY2);
	EXPECT_EQ(vector1.z, randomZ1 + randomZ2);
	EXPECT_EQ(vector1.w, randomW1 + randomW2);
}

TEST(Vector4_Double_Tests, LengthSqrd) {
	const double randomX = static_cast<double>(testUtility.GetRandomFloat());
	const double randomY = static_cast<double>(testUtility.GetRandomFloat());
	const double randomZ = static_cast<double>(testUtility.GetRandomFloat());
	const double randomW = static_cast<double>(testUtility.GetRandomFloat());
	Vector4d vector(randomX, randomY, randomZ, randomW);

	const double expectedLengthSqrd = randomX * randomX + randomY * randomY + randomZ * randomZ + randomW * randomW;
	EXPECT_EQ(vector.LengthSqrd(), expectedLengthSqrd);
}

TEST(Vector4_Double_Tests, Length) {
	const double randomX = static_cast<double>(testUtility.GetRandomFloat());
	const double randomY = static_cast<double>(testUtility.GetRandomFloat());
	const double randomZ = static_cast<double>(testUtility.GetRandomFloat());
	const double randomW = static_cast<double>(testUtility.GetRandomFloat());
	Vector4d vector(randomX, randomY, randomZ, randomW);
	const double expectedLength = sqrt(randomX * randomX + randomY * randomY + randomZ * randomZ + randomW * randomW);

	EXPECT_EQ(vector.Length(), expectedLength);
}

TEST(Vector4_Double_Tests, GetNormalized) {
	const double randomX = static_cast<double>(testUtility.GetRandomFloat(1));
	const double randomY = static_cast<double>(testUtility.GetRandomFloat(1));
	const double randomZ = static_cast<double>(testUtility.GetRandomFloat(1));
	const double randomW = static_cast<double>(testUtility.GetRandomFloat(1));
	Vector4d vector(randomX, randomY, randomZ, randomW);

	const double length = vector.Length();
	Vector4d expectedNormalized(randomX / length, randomY / length, randomZ / length, randomW / length);

	EXPECT_EQ(vector.GetNormalized(), expectedNormalized);
}

TEST(Vector4_Double_Tests, Normalize) {
	const double randomX = static_cast<double>(testUtility.GetRandomFloat(1));
	const double randomY = static_cast<double>(testUtility.GetRandomFloat(1));
	const double randomZ = static_cast<double>(testUtility.GetRandomFloat(1));
	const double randomW = static_cast<double>(testUtility.GetRandomFloat(1));
	Vector4d vector(randomX, randomY, randomZ, randomW);

	const double length = vector.Length();
	vector.Normalize();

	EXPECT_EQ(vector.x, randomX / length);
	EXPECT_EQ(vector.y, randomY / length);
	EXPECT_EQ(vector.z, randomZ / length);
	EXPECT_EQ(vector.w, randomW / length);
}

TEST(Vector4_Double_Tests, Dot) {
	const double randomX1 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomY1 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomZ1 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomW1 = static_cast<double>(testUtility.GetRandomFloat());
	Vector4d vector1(randomX1, randomY1, randomZ1, randomW1);

	const double randomX2 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomY2 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomZ2 = static_cast<double>(testUtility.GetRandomFloat());
	const double randomW2 = static_cast<double>(testUtility.GetRandomFloat());
	Vector4d vector2(randomX2, randomY2, randomZ2, randomW2);

	const double expectedDot = randomX1 * randomX2 + randomY1 * randomY2 + randomZ1 * randomZ2 + randomW1 * randomW2;

	EXPECT_EQ(vector1.Dot(vector2), expectedDot);
}

// DX Stuff for Vector4d

TEST(Vector4_Double_Tests, XMFLOAT4_Constructor) {
	const float randomX = testUtility.GetRandomFloat();
	const float randomY = testUtility.GetRandomFloat();
	const float randomZ = testUtility.GetRandomFloat();
	const float randomW = testUtility.GetRandomFloat();
	DirectX::XMFLOAT4 xmFloat4(randomX, randomY, randomZ, randomW);
	Vector4d vector(xmFloat4);
	EXPECT_EQ(vector.x, static_cast<double>(randomX));
	EXPECT_EQ(vector.y, static_cast<double>(randomY));
	EXPECT_EQ(vector.z, static_cast<double>(randomZ));
	EXPECT_EQ(vector.w, static_cast<double>(randomW));
}

TEST(Vector4_Double_Tests, XMINT4_Constructor) {
	const int randomX = testUtility.GetRandomInt();
	const int randomY = testUtility.GetRandomInt();
	const int randomZ = testUtility.GetRandomInt();
	const int randomW = testUtility.GetRandomInt();
	DirectX::XMINT4 xmInt4(randomX, randomY, randomZ, randomW);
	Vector4d vector(xmInt4);
	EXPECT_EQ(vector.x, static_cast<double>(randomX));
	EXPECT_EQ(vector.y, static_cast<double>(randomY));
	EXPECT_EQ(vector.z, static_cast<double>(randomZ));
	EXPECT_EQ(vector.w, static_cast<double>(randomW));
}

TEST(Vector4_Double_Tests, XMUINT4_Constructor) {
	const unsigned int randomX = testUtility.GetRandomInt(0);
	const unsigned int randomY = testUtility.GetRandomInt(0);
	const unsigned int randomZ = testUtility.GetRandomInt(0);
	const unsigned int randomW = testUtility.GetRandomInt(0);
	DirectX::XMUINT4 xmUInt4(randomX, randomY, randomZ, randomW);
	Vector4d vector(xmUInt4);
	EXPECT_EQ(vector.x, static_cast<double>(randomX));
	EXPECT_EQ(vector.y, static_cast<double>(randomY));
	EXPECT_EQ(vector.z, static_cast<double>(randomZ));
	EXPECT_EQ(vector.w, static_cast<double>(randomW));
}

TEST(Vector4_Double_Tests, ToXMFLOAT4) {
	const double randomX = static_cast<double>(testUtility.GetRandomFloat());
	const double randomY = static_cast<double>(testUtility.GetRandomFloat());
	const double randomZ = static_cast<double>(testUtility.GetRandomFloat());
	const double randomW = static_cast<double>(testUtility.GetRandomFloat());
	Vector4d vector(randomX, randomY, randomZ, randomW);

	DirectX::XMFLOAT4 xmFloat4 = vector.ToXMFLOAT4();
	EXPECT_EQ(xmFloat4.x, static_cast<float>(randomX));
	EXPECT_EQ(xmFloat4.y, static_cast<float>(randomY));
	EXPECT_EQ(xmFloat4.z, static_cast<float>(randomZ));
	EXPECT_EQ(xmFloat4.w, static_cast<float>(randomW));
}

TEST(Vector4_Double_Tests, XMFLOAT4_Operator) {
	const double randomX = static_cast<double>(testUtility.GetRandomFloat());
	const double randomY = static_cast<double>(testUtility.GetRandomFloat());
	const double randomZ = static_cast<double>(testUtility.GetRandomFloat());
	const double randomW = static_cast<double>(testUtility.GetRandomFloat());
	Vector4d vector(randomX, randomY, randomZ, randomW);

	DirectX::XMFLOAT4 xmFloat4(vector);
	EXPECT_EQ(xmFloat4.x, static_cast<float>(randomX));
	EXPECT_EQ(xmFloat4.y, static_cast<float>(randomY));
	EXPECT_EQ(xmFloat4.z, static_cast<float>(randomZ));
	EXPECT_EQ(xmFloat4.w, static_cast<float>(randomW));
}

TEST(Vector4_Double_Tests, toXMINT4) {
	const double randomX = static_cast<double>(testUtility.GetRandomFloat());
	const double randomY = static_cast<double>(testUtility.GetRandomFloat());
	const double randomZ = static_cast<double>(testUtility.GetRandomFloat());
	const double randomW = static_cast<double>(testUtility.GetRandomFloat());
	Vector4d vector(randomX, randomY, randomZ, randomW);

	DirectX::XMINT4 xmInt4 = vector.ToXMINT4();
	EXPECT_EQ(xmInt4.x, static_cast<int>(randomX));
	EXPECT_EQ(xmInt4.y, static_cast<int>(randomY));
	EXPECT_EQ(xmInt4.z, static_cast<int>(randomZ));
	EXPECT_EQ(xmInt4.w, static_cast<int>(randomW));
}

TEST(Vector4_Double_Tests, ToXMINT4) {
	const double randomX = static_cast<double>(testUtility.GetRandomFloat());
	const double randomY = static_cast<double>(testUtility.GetRandomFloat());
	const double randomZ = static_cast<double>(testUtility.GetRandomFloat());
	const double randomW = static_cast<double>(testUtility.GetRandomFloat());
	Vector4d vector(randomX, randomY, randomZ, randomW);
	DirectX::XMINT4 xmInt4(vector);
	EXPECT_EQ(xmInt4.x, static_cast<int>(randomX));
	EXPECT_EQ(xmInt4.y, static_cast<int>(randomY));
	EXPECT_EQ(xmInt4.z, static_cast<int>(randomZ));
	EXPECT_EQ(xmInt4.w, static_cast<int>(randomW));
}

TEST(Vector4_Double_Tests, ToXMUINT4) {
	const double randomX = static_cast<double>(testUtility.GetRandomFloat());
	const double randomY = static_cast<double>(testUtility.GetRandomFloat());
	const double randomZ = static_cast<double>(testUtility.GetRandomFloat());
	const double randomW = static_cast<double>(testUtility.GetRandomFloat());
	Vector4d vector(randomX, randomY, randomZ, randomW);

	DirectX::XMUINT4 xmUInt4 = vector.ToXMUINT4();
	EXPECT_EQ(xmUInt4.x, static_cast<unsigned int>(randomX));
	EXPECT_EQ(xmUInt4.y, static_cast<unsigned int>(randomY));
	EXPECT_EQ(xmUInt4.z, static_cast<unsigned int>(randomZ));
	EXPECT_EQ(xmUInt4.w, static_cast<unsigned int>(randomW));
}

TEST(Vector4_Double_Tests, XMUINT4_Operator) {
	const double randomX = static_cast<double>(testUtility.GetRandomFloat());
	const double randomY = static_cast<double>(testUtility.GetRandomFloat());
	const double randomZ = static_cast<double>(testUtility.GetRandomFloat());
	const double randomW = static_cast<double>(testUtility.GetRandomFloat());
	Vector4d vector(randomX, randomY, randomZ, randomW);
	DirectX::XMUINT4 xmUInt4(vector);
	EXPECT_EQ(xmUInt4.x, static_cast<unsigned int>(randomX));
	EXPECT_EQ(xmUInt4.y, static_cast<unsigned int>(randomY));
	EXPECT_EQ(xmUInt4.z, static_cast<unsigned int>(randomZ));
	EXPECT_EQ(xmUInt4.w, static_cast<unsigned int>(randomW));
}

//*********************************************************************************
// INT (Vector4i) - same tests as float but adapted to int alias
//*********************************************************************************
TEST(Vector4_Int_Tests, DefaultConstructor) {
	Vector4i vector;
	EXPECT_EQ(vector.x, 0);
	EXPECT_EQ(vector.y, 0);
	EXPECT_EQ(vector.z, 0);
	EXPECT_EQ(vector.w, 0);
}

TEST(Vector4_Int_Tests, ParameterizedConstructor) {
	int randomX = testUtility.GetRandomInt();
	int randomY = testUtility.GetRandomInt();
	int randomZ = testUtility.GetRandomInt();
	int randomW = testUtility.GetRandomInt();
	Vector4i vector(randomX, randomY, randomZ, randomW);
	EXPECT_EQ(vector.x, randomX);
	EXPECT_EQ(vector.y, randomY);
	EXPECT_EQ(vector.z, randomZ);
	EXPECT_EQ(vector.w, randomW);
}

TEST(Vector4_Int_Tests, CopyConstructor) {
	int randomX = testUtility.GetRandomInt();
	int randomY = testUtility.GetRandomInt();
	int randomZ = testUtility.GetRandomInt();
	int randomW = testUtility.GetRandomInt();
	Vector4i vector1(randomX, randomY, randomZ, randomW);
	Vector4i vector2(vector1);
	EXPECT_EQ(vector2, vector1);
}

TEST(Vector4_Int_Tests, AssignmentOperator) {
	int randomX = testUtility.GetRandomInt();
	int randomY = testUtility.GetRandomInt();
	int randomZ = testUtility.GetRandomInt();
	int randomW = testUtility.GetRandomInt();
	Vector4i vector1(randomX, randomY, randomZ, randomW);
	Vector4i vector2 = vector1;
	EXPECT_EQ(vector2, vector1);
}

TEST(Vector4_Int_Tests, MultiplicationOperator) {
	const int randomX1 = testUtility.GetRandomInt();
	const int randomY1 = testUtility.GetRandomInt();
	const int randomZ1 = testUtility.GetRandomInt();
	const int randomW1 = testUtility.GetRandomInt();
	Vector4i vector1(randomX1, randomY1, randomZ1, randomW1);

	const int randomX2 = testUtility.GetRandomInt();
	const int randomY2 = testUtility.GetRandomInt();
	const int randomZ2 = testUtility.GetRandomInt();
	const int randomW2 = testUtility.GetRandomInt();
	Vector4i vector2(randomX2, randomY2, randomZ2, randomW2);

	auto result = vector1 * vector2;
	EXPECT_EQ(result.x, randomX1 * randomX2);
	EXPECT_EQ(result.y, randomY1 * randomY2);
	EXPECT_EQ(result.z, randomZ1 * randomZ2);
	EXPECT_EQ(result.w, randomW1 * randomW2);
}

TEST(Vector4_Int_Tests, MultiplicationAssignmentOperator) {
	const int randomX1 = testUtility.GetRandomInt();
	const int randomY1 = testUtility.GetRandomInt();
	const int randomZ1 = testUtility.GetRandomInt();
	const int randomW1 = testUtility.GetRandomInt();
	Vector4i vector1(randomX1, randomY1, randomZ1, randomW1);

	const int randomX2 = testUtility.GetRandomInt();
	const int randomY2 = testUtility.GetRandomInt();
	const int randomZ2 = testUtility.GetRandomInt();
	const int randomW2 = testUtility.GetRandomInt();
	Vector4i vector2(randomX2, randomY2, randomZ2, randomW2);

	vector1 *= vector2;
	EXPECT_EQ(vector1.x, randomX1 * randomX2);
	EXPECT_EQ(vector1.y, randomY1 * randomY2);
	EXPECT_EQ(vector1.z, randomZ1 * randomZ2);
	EXPECT_EQ(vector1.w, randomW1 * randomW2);
}

TEST(Vector4_Int_Tests, AdditionOperator) {
	const int randomX1 = testUtility.GetRandomInt();
	const int randomY1 = testUtility.GetRandomInt();
	const int randomZ1 = testUtility.GetRandomInt();
	const int randomW1 = testUtility.GetRandomInt();
	Vector4i vector1(randomX1, randomY1, randomZ1, randomW1);

	const int randomX2 = testUtility.GetRandomInt();
	const int randomY2 = testUtility.GetRandomInt();
	const int randomZ2 = testUtility.GetRandomInt();
	const int randomW2 = testUtility.GetRandomInt();
	Vector4i vector2(randomX2, randomY2, randomZ2, randomW2);

	auto result = vector1 + vector2;
	EXPECT_EQ(result.x, randomX1 + randomX2);
	EXPECT_EQ(result.y, randomY1 + randomY2);
	EXPECT_EQ(result.z, randomZ1 + randomZ2);
	EXPECT_EQ(result.w, randomW1 + randomW2);
}

TEST(Vector4_Int_Tests, AdditionAssignmentOperator) {
	const int randomX1 = testUtility.GetRandomInt();
	const int randomY1 = testUtility.GetRandomInt();
	const int randomZ1 = testUtility.GetRandomInt();
	const int randomW1 = testUtility.GetRandomInt();
	Vector4i vector1(randomX1, randomY1, randomZ1, randomW1);

	const int randomX2 = testUtility.GetRandomInt();
	const int randomY2 = testUtility.GetRandomInt();
	const int randomZ2 = testUtility.GetRandomInt();
	const int randomW2 = testUtility.GetRandomInt();
	Vector4i vector2(randomX2, randomY2, randomZ2, randomW2);

	vector1 += vector2;
	EXPECT_EQ(vector1.x, randomX1 + randomX2);
	EXPECT_EQ(vector1.y, randomY1 + randomY2);
	EXPECT_EQ(vector1.z, randomZ1 + randomZ2);
	EXPECT_EQ(vector1.w, randomW1 + randomW2);
}

TEST(Vector4_Int_Tests, LengthSqrd) {
	const int randomX = testUtility.GetRandomInt();
	const int randomY = testUtility.GetRandomInt();
	const int randomZ = testUtility.GetRandomInt();
	const int randomW = testUtility.GetRandomInt();
	Vector4i vector(randomX, randomY, randomZ, randomW);

	const long long expectedLengthSqrd =
		static_cast<long long>(randomX) * randomX + static_cast<long long>(randomY) * randomY +
		static_cast<long long>(randomZ) * randomZ + static_cast<long long>(randomW) * randomW;
	// LengthSqrd returns T (int), but to avoid overflow in expected, compute in long long then cast
	EXPECT_EQ(vector.LengthSqrd(), static_cast<int>(expectedLengthSqrd));
}

TEST(Vector4_Int_Tests, Length) {
	const int randomX = testUtility.GetRandomInt();
	const int randomY = testUtility.GetRandomInt();
	const int randomZ = testUtility.GetRandomInt();
	const int randomW = testUtility.GetRandomInt();
	Vector4i vector(randomX, randomY, randomZ, randomW);
	const int expectedLength =
		static_cast<int>(sqrt(static_cast<double>(randomX) * randomX + static_cast<double>(randomY) * randomY +
							  static_cast<double>(randomZ) * randomZ + static_cast<double>(randomW) * randomW));

	EXPECT_EQ(vector.Length(), expectedLength);
}

TEST(Vector4_Int_Tests, GetNormalized) {
	const int randomX = testUtility.GetRandomInt(1);
	const int randomY = testUtility.GetRandomInt(1);
	const int randomZ = testUtility.GetRandomInt(1);
	const int randomW = testUtility.GetRandomInt(1);
	Vector4i vector(randomX, randomY, randomZ, randomW);

	const int length = vector.Length();
	// Integer division semantics
	Vector4i expectedNormalized(randomX / length, randomY / length,
								randomZ / length, randomW / length);

	EXPECT_EQ(vector.GetNormalized(), expectedNormalized);
}

TEST(Vector4_Int_Tests, Normalize) {
	const int randomX = testUtility.GetRandomInt(1);
	const int randomY = testUtility.GetRandomInt(1);
	const int randomZ = testUtility.GetRandomInt(1);
	const int randomW = testUtility.GetRandomInt(1);
	Vector4i vector(randomX, randomY, randomZ, randomW);

	const int length = vector.Length();
	vector.Normalize();

	EXPECT_EQ(vector.x, randomX / length);
	EXPECT_EQ(vector.y, randomY / length);
	EXPECT_EQ(vector.z, randomZ / length);
	EXPECT_EQ(vector.w, randomW / length);
}

TEST(Vector4_Int_Tests, Dot) {
	const int randomX1 = testUtility.GetRandomInt();
	const int randomY1 = testUtility.GetRandomInt();
	const int randomZ1 = testUtility.GetRandomInt();
	const int randomW1 = testUtility.GetRandomInt();
	Vector4i vector1(randomX1, randomY1, randomZ1, randomW1);

	const int randomX2 = testUtility.GetRandomInt();
	const int randomY2 = testUtility.GetRandomInt();
	const int randomZ2 = testUtility.GetRandomInt();
	const int randomW2 = testUtility.GetRandomInt();
	Vector4i vector2(randomX2, randomY2, randomZ2, randomW2);

	const long long expectedDot =
		static_cast<long long>(randomX1) * randomX2 + static_cast<long long>(randomY1) * randomY2 +
		static_cast<long long>(randomZ1) * randomZ2 + static_cast<long long>(randomW1) * randomW2;

	EXPECT_EQ(vector1.Dot(vector2), static_cast<int>(expectedDot));
}

// DX Stuff for Vector4i

TEST(Vector4_Int_Tests, XMFLOAT4_Constructor) {
	const float randomX = testUtility.GetRandomFloat();
	const float randomY = testUtility.GetRandomFloat();
	const float randomZ = testUtility.GetRandomFloat();
	const float randomW = testUtility.GetRandomFloat();
	DirectX::XMFLOAT4 xmFloat4(randomX, randomY, randomZ, randomW);
	Vector4i vector(xmFloat4);
	EXPECT_EQ(vector.x, static_cast<int>(randomX));
	EXPECT_EQ(vector.y, static_cast<int>(randomY));
	EXPECT_EQ(vector.z, static_cast<int>(randomZ));
	EXPECT_EQ(vector.w, static_cast<int>(randomW));
}

TEST(Vector4_Int_Tests, XMINT4_Constructor) {
	const int randomX = testUtility.GetRandomInt();
	const int randomY = testUtility.GetRandomInt();
	const int randomZ = testUtility.GetRandomInt();
	const int randomW = testUtility.GetRandomInt();
	DirectX::XMINT4 xmInt4(randomX, randomY, randomZ, randomW);
	Vector4i vector(xmInt4);
	EXPECT_EQ(vector.x, randomX);
	EXPECT_EQ(vector.y, randomY);
	EXPECT_EQ(vector.z, randomZ);
	EXPECT_EQ(vector.w, randomW);
}

TEST(Vector4_Int_Tests, XMUINT4_Constructor) {
	const unsigned int randomX = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomY = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomZ = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomW = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	DirectX::XMUINT4 xmUInt4(randomX, randomY, randomZ, randomW);
	Vector4i vector(xmUInt4);
	EXPECT_EQ(vector.x, static_cast<int>(randomX));
	EXPECT_EQ(vector.y, static_cast<int>(randomY));
	EXPECT_EQ(vector.z, static_cast<int>(randomZ));
	EXPECT_EQ(vector.w, static_cast<int>(randomW));
}

TEST(Vector4_Int_Tests, ToXMFLOAT4) {
	const int randomX = testUtility.GetRandomInt();
	const int randomY = testUtility.GetRandomInt();
	const int randomZ = testUtility.GetRandomInt();
	const int randomW = testUtility.GetRandomInt();
	Vector4i vector(randomX, randomY, randomZ, randomW);

	DirectX::XMFLOAT4 xmFloat4 = vector.ToXMFLOAT4();
	EXPECT_EQ(xmFloat4.x, static_cast<float>(randomX));
	EXPECT_EQ(xmFloat4.y, static_cast<float>(randomY));
	EXPECT_EQ(xmFloat4.z, static_cast<float>(randomZ));
	EXPECT_EQ(xmFloat4.w, static_cast<float>(randomW));
}

TEST(Vector4_Int_Tests, XMFLOAT4_Operator) {
	const int randomX = testUtility.GetRandomInt();
	const int randomY = testUtility.GetRandomInt();
	const int randomZ = testUtility.GetRandomInt();
	const int randomW = testUtility.GetRandomInt();
	Vector4i vector(randomX, randomY, randomZ, randomW);

	DirectX::XMFLOAT4 xmFloat4(vector);
	EXPECT_EQ(xmFloat4.x, static_cast<float>(randomX));
	EXPECT_EQ(xmFloat4.y, static_cast<float>(randomY));
	EXPECT_EQ(xmFloat4.z, static_cast<float>(randomZ));
	EXPECT_EQ(xmFloat4.w, static_cast<float>(randomW));
}

TEST(Vector4_Int_Tests, toXMINT4) {
	const int randomX = testUtility.GetRandomInt();
	const int randomY = testUtility.GetRandomInt();
	const int randomZ = testUtility.GetRandomInt();
	const int randomW = testUtility.GetRandomInt();
	Vector4i vector(randomX, randomY, randomZ, randomW);

	DirectX::XMINT4 xmInt4 = vector.ToXMINT4();
	EXPECT_EQ(xmInt4.x, randomX);
	EXPECT_EQ(xmInt4.y, randomY);
	EXPECT_EQ(xmInt4.z, randomZ);
	EXPECT_EQ(xmInt4.w, randomW);
}

TEST(Vector4_Int_Tests, ToXMINT4) {
	const int randomX = testUtility.GetRandomInt();
	const int randomY = testUtility.GetRandomInt();
	const int randomZ = testUtility.GetRandomInt();
	const int randomW = testUtility.GetRandomInt();
	Vector4i vector(randomX, randomY, randomZ, randomW);
	DirectX::XMINT4 xmInt4(vector);
	EXPECT_EQ(xmInt4.x, randomX);
	EXPECT_EQ(xmInt4.y, randomY);
	EXPECT_EQ(xmInt4.z, randomZ);
	EXPECT_EQ(xmInt4.w, randomW);
}

TEST(Vector4_Int_Tests, ToXMUINT4) {
	const int randomX = testUtility.GetRandomInt();
	const int randomY = testUtility.GetRandomInt();
	const int randomZ = testUtility.GetRandomInt();
	const int randomW = testUtility.GetRandomInt();
	Vector4i vector(randomX, randomY, randomZ, randomW);

	DirectX::XMUINT4 xmUInt4 = vector.ToXMUINT4();
	EXPECT_EQ(xmUInt4.x, static_cast<unsigned int>(randomX));
	EXPECT_EQ(xmUInt4.y, static_cast<unsigned int>(randomY));
	EXPECT_EQ(xmUInt4.z, static_cast<unsigned int>(randomZ));
	EXPECT_EQ(xmUInt4.w, static_cast<unsigned int>(randomW));
}

TEST(Vector4_Int_Tests, XMUINT4_Operator) {
	const int randomX = testUtility.GetRandomInt();
	const int randomY = testUtility.GetRandomInt();
	const int randomZ = testUtility.GetRandomInt();
	const int randomW = testUtility.GetRandomInt();
	Vector4i vector(randomX, randomY, randomZ, randomW);
	DirectX::XMUINT4 xmUInt4(vector);
	EXPECT_EQ(xmUInt4.x, static_cast<unsigned int>(randomX));
	EXPECT_EQ(xmUInt4.y, static_cast<unsigned int>(randomY));
	EXPECT_EQ(xmUInt4.z, static_cast<unsigned int>(randomZ));
	EXPECT_EQ(xmUInt4.w, static_cast<unsigned int>(randomW));
}

//*********************************************************************************
// UNSIGNED INT (Vector4ui) - same tests as float but adapted to unsigned int alias
//*********************************************************************************
TEST(Vector4_UInt_Tests, DefaultConstructor) {
	Vector4ui vector;
	EXPECT_EQ(vector.x, 0u);
	EXPECT_EQ(vector.y, 0u);
	EXPECT_EQ(vector.z, 0u);
	EXPECT_EQ(vector.w, 0u);
}

TEST(Vector4_UInt_Tests, ParameterizedConstructor) {
	unsigned int randomX = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	unsigned int randomY = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	unsigned int randomZ = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	unsigned int randomW = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	Vector4ui vector(randomX, randomY, randomZ, randomW);
	EXPECT_EQ(vector.x, randomX);
	EXPECT_EQ(vector.y, randomY);
	EXPECT_EQ(vector.z, randomZ);
	EXPECT_EQ(vector.w, randomW);
}

TEST(Vector4_UInt_Tests, CopyConstructor) {
	unsigned int randomX = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	unsigned int randomY = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	unsigned int randomZ = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	unsigned int randomW = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	Vector4ui vector1(randomX, randomY, randomZ, randomW);
	Vector4ui vector2(vector1);
	EXPECT_EQ(vector2, vector1);
}

TEST(Vector4_UInt_Tests, AssignmentOperator) {
	unsigned int randomX = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	unsigned int randomY = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	unsigned int randomZ = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	unsigned int randomW = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	Vector4ui vector1(randomX, randomY, randomZ, randomW);
	Vector4ui vector2 = vector1;
	EXPECT_EQ(vector2, vector1);
}

TEST(Vector4_UInt_Tests, MultiplicationOperator) {
	const unsigned int randomX1 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomY1 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomZ1 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomW1 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	Vector4ui vector1(randomX1, randomY1, randomZ1, randomW1);

	const unsigned int randomX2 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomY2 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomZ2 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomW2 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	Vector4ui vector2(randomX2, randomY2, randomZ2, randomW2);

	auto result = vector1 * vector2;
	EXPECT_EQ(result.x, randomX1 * randomX2);
	EXPECT_EQ(result.y, randomY1 * randomY2);
	EXPECT_EQ(result.z, randomZ1 * randomZ2);
	EXPECT_EQ(result.w, randomW1 * randomW2);
}

TEST(Vector4_UInt_Tests, MultiplicationAssignmentOperator) {
	const unsigned int randomX1 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomY1 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomZ1 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomW1 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	Vector4ui vector1(randomX1, randomY1, randomZ1, randomW1);

	const unsigned int randomX2 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomY2 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomZ2 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomW2 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	Vector4ui vector2(randomX2, randomY2, randomZ2, randomW2);

	vector1 *= vector2;
	EXPECT_EQ(vector1.x, randomX1 * randomX2);
	EXPECT_EQ(vector1.y, randomY1 * randomY2);
	EXPECT_EQ(vector1.z, randomZ1 * randomZ2);
	EXPECT_EQ(vector1.w, randomW1 * randomW2);
}

TEST(Vector4_UInt_Tests, AdditionOperator) {
	const unsigned int randomX1 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomY1 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomZ1 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomW1 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	Vector4ui vector1(randomX1, randomY1, randomZ1, randomW1);

	const unsigned int randomX2 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomY2 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomZ2 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomW2 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	Vector4ui vector2(randomX2, randomY2, randomZ2, randomW2);

	auto result = vector1 + vector2;
	EXPECT_EQ(result.x, randomX1 + randomX2);
	EXPECT_EQ(result.y, randomY1 + randomY2);
	EXPECT_EQ(result.z, randomZ1 + randomZ2);
	EXPECT_EQ(result.w, randomW1 + randomW2);
}

TEST(Vector4_UInt_Tests, AdditionAssignmentOperator) {
	const unsigned int randomX1 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomY1 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomZ1 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomW1 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	Vector4ui vector1(randomX1, randomY1, randomZ1, randomW1);

	const unsigned int randomX2 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomY2 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomZ2 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomW2 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	Vector4ui vector2(randomX2, randomY2, randomZ2, randomW2);

	vector1 += vector2;
	EXPECT_EQ(vector1.x, randomX1 + randomX2);
	EXPECT_EQ(vector1.y, randomY1 + randomY2);
	EXPECT_EQ(vector1.z, randomZ1 + randomZ2);
	EXPECT_EQ(vector1.w, randomW1 + randomW2);
}

TEST(Vector4_UInt_Tests, LengthSqrd) {
	const unsigned int randomX = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomY = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomZ = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomW = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	Vector4ui vector(randomX, randomY, randomZ, randomW);

	const unsigned long long expectedLengthSqrd =
		static_cast<unsigned long long>(randomX) * randomX + static_cast<unsigned long long>(randomY) * randomY +
		static_cast<unsigned long long>(randomZ) * randomZ + static_cast<unsigned long long>(randomW) * randomW;
	EXPECT_EQ(vector.LengthSqrd(), static_cast<unsigned int>(expectedLengthSqrd));
}

TEST(Vector4_UInt_Tests, Length) {
	const unsigned int randomX = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomY = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomZ = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomW = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	Vector4ui vector(randomX, randomY, randomZ, randomW);
	const unsigned int expectedLength = static_cast<unsigned int>(
		sqrt(static_cast<double>(randomX) * randomX + static_cast<double>(randomY) * randomY +
			 static_cast<double>(randomZ) * randomZ + static_cast<double>(randomW) * randomW));

	EXPECT_EQ(vector.Length(), expectedLength);
}

TEST(Vector4_UInt_Tests, GetNormalized) {
	const unsigned int randomX = static_cast<unsigned int>(testUtility.GetRandomInt(1));
	const unsigned int randomY = static_cast<unsigned int>(testUtility.GetRandomInt(1));
	const unsigned int randomZ = static_cast<unsigned int>(testUtility.GetRandomInt(1));
	const unsigned int randomW = static_cast<unsigned int>(testUtility.GetRandomInt(1));
	Vector4ui vector(randomX, randomY, randomZ, randomW);

	const unsigned int length = vector.Length();
	// Unsigned integer division semantics; avoid divide by zero by using 1 when length==0
	Vector4ui expectedNormalized(randomX / length, randomY / length,
								 randomZ / length, randomW / length);

	EXPECT_EQ(vector.GetNormalized(), expectedNormalized);
}

TEST(Vector4_UInt_Tests, Normalize) {
	const unsigned int randomX = static_cast<unsigned int>(testUtility.GetRandomInt(1));
	const unsigned int randomY = static_cast<unsigned int>(testUtility.GetRandomInt(1));
	const unsigned int randomZ = static_cast<unsigned int>(testUtility.GetRandomInt(1));
	const unsigned int randomW = static_cast<unsigned int>(testUtility.GetRandomInt(1));
	Vector4ui vector(randomX, randomY, randomZ, randomW);

	const unsigned int length = vector.Length();
	vector.Normalize();

	if (length == 0) {
		EXPECT_EQ(vector.x, randomX);
		EXPECT_EQ(vector.y, randomY);
		EXPECT_EQ(vector.z, randomZ);
		EXPECT_EQ(vector.w, randomW);
	} else {
		EXPECT_EQ(vector.x, randomX / length);
		EXPECT_EQ(vector.y, randomY / length);
		EXPECT_EQ(vector.z, randomZ / length);
		EXPECT_EQ(vector.w, randomW / length);
	}
}

TEST(Vector4_UInt_Tests, Dot) {
	const unsigned int randomX1 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomY1 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomZ1 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomW1 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	Vector4ui vector1(randomX1, randomY1, randomZ1, randomW1);

	const unsigned int randomX2 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomY2 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomZ2 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomW2 = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	Vector4ui vector2(randomX2, randomY2, randomZ2, randomW2);

	const unsigned long long expectedDot =
		static_cast<unsigned long long>(randomX1) * randomX2 + static_cast<unsigned long long>(randomY1) * randomY2 +
		static_cast<unsigned long long>(randomZ1) * randomZ2 + static_cast<unsigned long long>(randomW1) * randomW2;

	EXPECT_EQ(vector1.Dot(vector2), static_cast<unsigned int>(expectedDot));
}

// DX Stuff for Vector4ui

TEST(Vector4_UInt_Tests, XMFLOAT4_Constructor) {
	const float randomX = testUtility.GetRandomFloat();
	const float randomY = testUtility.GetRandomFloat();
	const float randomZ = testUtility.GetRandomFloat();
	const float randomW = testUtility.GetRandomFloat();
	DirectX::XMFLOAT4 xmFloat4(randomX, randomY, randomZ, randomW);
	Vector4ui vector(xmFloat4);
	EXPECT_EQ(vector.x, static_cast<unsigned int>(randomX));
	EXPECT_EQ(vector.y, static_cast<unsigned int>(randomY));
	EXPECT_EQ(vector.z, static_cast<unsigned int>(randomZ));
	EXPECT_EQ(vector.w, static_cast<unsigned int>(randomW));
}

TEST(Vector4_UInt_Tests, XMINT4_Constructor) {
	const int randomX = testUtility.GetRandomInt();
	const int randomY = testUtility.GetRandomInt();
	const int randomZ = testUtility.GetRandomInt();
	const int randomW = testUtility.GetRandomInt();
	DirectX::XMINT4 xmInt4(randomX, randomY, randomZ, randomW);
	Vector4ui vector(xmInt4);
	EXPECT_EQ(vector.x, static_cast<unsigned int>(randomX));
	EXPECT_EQ(vector.y, static_cast<unsigned int>(randomY));
	EXPECT_EQ(vector.z, static_cast<unsigned int>(randomZ));
	EXPECT_EQ(vector.w, static_cast<unsigned int>(randomW));
}

TEST(Vector4_UInt_Tests, XMUINT4_Constructor) {
	const unsigned int randomX = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomY = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomZ = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomW = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	DirectX::XMUINT4 xmUInt4(randomX, randomY, randomZ, randomW);
	Vector4ui vector(xmUInt4);
	EXPECT_EQ(vector.x, randomX);
	EXPECT_EQ(vector.y, randomY);
	EXPECT_EQ(vector.z, randomZ);
	EXPECT_EQ(vector.w, randomW);
}

TEST(Vector4_UInt_Tests, ToXMFLOAT4) {
	const unsigned int randomX = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomY = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomZ = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomW = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	Vector4ui vector(randomX, randomY, randomZ, randomW);

	DirectX::XMFLOAT4 xmFloat4 = vector.ToXMFLOAT4();
	EXPECT_EQ(xmFloat4.x, static_cast<float>(randomX));
	EXPECT_EQ(xmFloat4.y, static_cast<float>(randomY));
	EXPECT_EQ(xmFloat4.z, static_cast<float>(randomZ));
	EXPECT_EQ(xmFloat4.w, static_cast<float>(randomW));
}

TEST(Vector4_UInt_Tests, XMFLOAT4_Operator) {
	const unsigned int randomX = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomY = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomZ = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomW = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	Vector4ui vector(randomX, randomY, randomZ, randomW);

	DirectX::XMFLOAT4 xmFloat4(vector);
	EXPECT_EQ(xmFloat4.x, static_cast<float>(randomX));
	EXPECT_EQ(xmFloat4.y, static_cast<float>(randomY));
	EXPECT_EQ(xmFloat4.z, static_cast<float>(randomZ));
	EXPECT_EQ(xmFloat4.w, static_cast<float>(randomW));
}

TEST(Vector4_UInt_Tests, toXMINT4) {
	const unsigned int randomX = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomY = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomZ = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomW = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	Vector4ui vector(randomX, randomY, randomZ, randomW);

	DirectX::XMINT4 xmInt4 = vector.ToXMINT4();
	EXPECT_EQ(xmInt4.x, static_cast<int>(randomX));
	EXPECT_EQ(xmInt4.y, static_cast<int>(randomY));
	EXPECT_EQ(xmInt4.z, static_cast<int>(randomZ));
	EXPECT_EQ(xmInt4.w, static_cast<int>(randomW));
}

TEST(Vector4_UInt_Tests, ToXMINT4) {
	const unsigned int randomX = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomY = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomZ = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomW = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	Vector4ui vector(randomX, randomY, randomZ, randomW);
	DirectX::XMINT4 xmInt4(vector);
	EXPECT_EQ(xmInt4.x, static_cast<int>(randomX));
	EXPECT_EQ(xmInt4.y, static_cast<int>(randomY));
	EXPECT_EQ(xmInt4.z, static_cast<int>(randomZ));
	EXPECT_EQ(xmInt4.w, static_cast<int>(randomW));
}

TEST(Vector4_UInt_Tests, ToXMUINT4) {
	const unsigned int randomX = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomY = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomZ = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomW = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	Vector4ui vector(randomX, randomY, randomZ, randomW);

	DirectX::XMUINT4 xmUInt4 = vector.ToXMUINT4();
	EXPECT_EQ(xmUInt4.x, randomX);
	EXPECT_EQ(xmUInt4.y, randomY);
	EXPECT_EQ(xmUInt4.z, randomZ);
	EXPECT_EQ(xmUInt4.w, randomW);
}

TEST(Vector4_UInt_Tests, XMUINT4_Operator) {
	const unsigned int randomX = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomY = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomZ = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	const unsigned int randomW = static_cast<unsigned int>(testUtility.GetRandomInt(0));
	Vector4ui vector(randomX, randomY, randomZ, randomW);
	DirectX::XMUINT4 xmUInt4(vector);
	EXPECT_EQ(xmUInt4.x, randomX);
	EXPECT_EQ(xmUInt4.y, randomY);
	EXPECT_EQ(xmUInt4.z, randomZ);
	EXPECT_EQ(xmUInt4.w, randomW);
}
} // namespace RFMATH