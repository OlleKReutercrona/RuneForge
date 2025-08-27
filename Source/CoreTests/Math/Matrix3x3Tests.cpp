#include <gtest/gtest.h>

#include <DirectXMath.h>
#include "Matrix3x3.h"
#include "Utility/TestUtility.h"

using namespace DirectX;

TestUtility testUtility;


namespace DirectX {
	inline bool XMMatrixEqual(const DirectX::XMMATRIX& lhs, const DirectX::XMMATRIX& rhs) noexcept {
		static const DirectX::XMVECTOR epsilon = DirectX::XMVectorReplicate(0.00001f);
		return	DirectX::XMVector4NearEqual(lhs.r[0], rhs.r[0], epsilon) &&
			DirectX::XMVector4NearEqual(lhs.r[1], rhs.r[1], epsilon) &&
			DirectX::XMVector4NearEqual(lhs.r[2], rhs.r[2], epsilon) &&
			DirectX::XMVector4NearEqual(lhs.r[3], rhs.r[3], epsilon);
	}

	inline bool operator==(const DirectX::XMMATRIX& lhs, const DirectX::XMMATRIX& rhs) noexcept {
		return XMMatrixEqual(lhs, rhs);
	}

	inline bool operator!=(const DirectX::XMMATRIX& lhs, const DirectX::XMMATRIX& rhs) noexcept {
		return !(lhs == rhs);
	}
}

inline bool operator==(const Matrix3x3& lhs, const Matrix3x3& rhs) noexcept {
	return DirectX::XMMatrixEqual(lhs, rhs);
}

inline bool operator==(const Matrix3x3& lhs, const DirectX::XMMATRIX& rhs) noexcept {
	return DirectX::XMMatrixEqual(lhs, rhs);
}

inline bool operator==(const DirectX::XMMATRIX& lhs, const Matrix3x3& rhs) noexcept {
	return DirectX::XMMatrixEqual(lhs, rhs);
}


//***********************************************************************
TEST(Matrix3x3Tests, DefaultContructor) {
	Matrix3x3 matrix;

	EXPECT_EQ(matrix, XMMatrixIdentity());
}

//***********************************************************************
TEST(Matrix3x3Tests, CopyContructor) {
	for(int i = 0; i < 50; ++i) {
		float randomValue = testUtility.GetRandomFloat();

		Matrix3x3 matrix1;
		matrix1(0, 0) = randomValue;
		matrix1(1, 1) = randomValue;
		matrix1(2, 2) = randomValue;

		Matrix3x3 matrix2(matrix1);
		EXPECT_EQ(matrix1, matrix2);

		XMMATRIX dxMatrix(matrix1);
		EXPECT_EQ(matrix1, dxMatrix);
	}
}

//***********************************************************************
TEST(Matrix3x3Tests, AssignmentOperator) {
	Matrix3x3 matrix1;
	Matrix3x3 matrix2;
	matrix2 = matrix1;
	EXPECT_EQ(matrix2.mMatrix, matrix1.mMatrix);

	Matrix3x3 matrix3;
	matrix3 = XMMatrixIdentity();
	EXPECT_EQ(matrix3, XMMatrixIdentity());
}

//***********************************************************************
TEST(Matrix3x3Tests, MultiplicationOperator) {
	Matrix3x3 matrix1;
	Matrix3x3 matrix2;
	Matrix3x3 result = matrix1 * matrix2;
	EXPECT_EQ(result.mMatrix, matrix1.mMatrix * matrix2.mMatrix);
}

//***********************************************************************
TEST(Matrix3x3Tests, MultiplicationAssignmentOperator) {
	Matrix3x3 matrix1;
	Matrix3x3 matrix2;
	matrix1 *= matrix2;
	EXPECT_EQ(matrix1.mMatrix, XMMatrixIdentity());
}

//***********************************************************************
TEST(Matrix3x3Tests, AdditionOperator) {
	for(int i = 0; i < 50; ++i) {
		float randomValue = testUtility.GetRandomFloat();
		Matrix3x3 matrix1;
		matrix1(0, 0) = randomValue;
		matrix1(1, 1) = randomValue;
		matrix1(2, 2) = randomValue;
		Matrix3x3 matrix2;
		matrix2(0, 0) = randomValue;
		matrix2(1, 1) = randomValue;
		matrix2(2, 2) = randomValue;
		Matrix3x3 result = matrix1 + matrix2;
		EXPECT_EQ(result(0, 0), randomValue + randomValue);
		EXPECT_EQ(result(1, 1), randomValue + randomValue);
		EXPECT_EQ(result(2, 2), randomValue + randomValue);
	}
}

//***********************************************************************
TEST(Matrix3x3Tests, AdditionAssignmentOperator) {
	for(int i = 0; i < 50; ++i) {
		float randomValue = testUtility.GetRandomFloat();
		Matrix3x3 matrix1;
		matrix1(0, 0) = randomValue;
		matrix1(1, 1) = randomValue;
		matrix1(2, 2) = randomValue;
		Matrix3x3 matrix2;
		matrix2(0, 0) = randomValue;
		matrix2(1, 1) = randomValue;
		matrix2(2, 2) = randomValue;
		matrix1 += matrix2;
		EXPECT_EQ(matrix1(0, 0), randomValue + randomValue);
		EXPECT_EQ(matrix1(1, 1), randomValue + randomValue);
		EXPECT_EQ(matrix1(2, 2), randomValue + randomValue);
	}
}

//***********************************************************************
TEST(Matrix3x3Tests, SubtractionOperator) {
	for(int i = 0; i < 50; ++i) {
		float randomValue = testUtility.GetRandomFloat();
		Matrix3x3 matrix1;
		matrix1(0, 0) = randomValue;
		matrix1(1, 1) = randomValue;
		matrix1(2, 2) = randomValue;
		Matrix3x3 matrix2;
		matrix2(0, 0) = randomValue;
		matrix2(1, 1) = randomValue;
		matrix2(2, 2) = randomValue;
		Matrix3x3 result = matrix1 - matrix2;
		EXPECT_EQ(result(0, 0), 0.0f);
		EXPECT_EQ(result(1, 1), 0.0f);
		EXPECT_EQ(result(2, 2), 0.0f);
	}
}

//***********************************************************************
TEST(Matrix3x3Tests, SubtractionAssignmentOperator) {
	for(int i = 0; i < 50; ++i) {
		float randomValue = testUtility.GetRandomFloat();
		Matrix3x3 matrix1;
		matrix1(0, 0) = randomValue;
		matrix1(1, 1) = randomValue;
		matrix1(2, 2) = randomValue;
		Matrix3x3 matrix2;
		matrix2(0, 0) = randomValue;
		matrix2(1, 1) = randomValue;
		matrix2(2, 2) = randomValue;
		matrix1 -= matrix2;
		EXPECT_EQ(matrix1(0, 0), 0.0f);
		EXPECT_EQ(matrix1(1, 1), 0.0f);
		EXPECT_EQ(matrix1(2, 2), 0.0f);
	}
}

//***********************************************************************
TEST(Matrix3x3Tests, ScalarMultiplicationOperator) {
	for(int i = 0; i < 50; ++i) {
		float randomValue = testUtility.GetRandomFloat();
		Matrix3x3 matrix1;
		matrix1(0, 0) = randomValue;
		matrix1(1, 1) = randomValue;
		matrix1(2, 2) = randomValue;
		float scalar = testUtility.GetRandomFloat();
		Matrix3x3 result = matrix1 * scalar;
		EXPECT_EQ(result(0, 0), randomValue * scalar);
		EXPECT_EQ(result(1, 1), randomValue * scalar);
		EXPECT_EQ(result(2, 2), randomValue * scalar);
	}
}

//***********************************************************************
TEST(Matrix3x3Tests, ScalarMultiplicationAssignmentOperator) {
	for(int i = 0; i < 50; ++i) {
		float randomValue = testUtility.GetRandomFloat();
		Matrix3x3 matrix1;
		matrix1(0, 0) = randomValue;
		matrix1(1, 1) = randomValue;
		matrix1(2, 2) = randomValue;
		float scalar = testUtility.GetRandomFloat();
		matrix1 *= scalar;
		EXPECT_EQ(matrix1(0, 0), randomValue * scalar);
		EXPECT_EQ(matrix1(1, 1), randomValue * scalar);
		EXPECT_EQ(matrix1(2, 2), randomValue * scalar);
	}
}

//***********************************************************************
TEST(Matrix3x3Tests, ScalarDivisionOperator) {
	for(int i = 0; i < 50; ++i) {
		float randomValue = testUtility.GetRandomFloat(1.0f, 10000.0f);
		Matrix3x3 matrix1;
		matrix1(0, 0) = randomValue;
		matrix1(1, 1) = randomValue;
		matrix1(2, 2) = randomValue;
		float scalar = testUtility.GetRandomFloat(1.0f, 10000.0f);
		Matrix3x3 result = matrix1 / scalar;
		EXPECT_EQ(result(0, 0), randomValue / scalar);
		EXPECT_EQ(result(1, 1), randomValue / scalar);
		EXPECT_EQ(result(2, 2), randomValue / scalar);
	}
}

//***********************************************************************
TEST(Matrix3x3Tests, ScalarDivisionAssignmentOperator) {
	for(int i = 0; i < 50; ++i) {
		float randomValue = testUtility.GetRandomFloat(1.0f, 10000.0f);
		Matrix3x3 matrix1;
		matrix1(0, 0) = randomValue;
		matrix1(1, 1) = randomValue;
		matrix1(2, 2) = randomValue;
		float scalar = testUtility.GetRandomFloat(1.0f, 10000.0f);
		matrix1 /= scalar;
		EXPECT_EQ(matrix1(0, 0), randomValue / scalar);
		EXPECT_EQ(matrix1(1, 1), randomValue / scalar);
		EXPECT_EQ(matrix1(2, 2), randomValue / scalar);
	}
}

//***********************************************************************
TEST(Matrix3x3Tests, Transpose) {
	for(int i = 0; i < 50; ++i) {
		float randomValue = testUtility.GetRandomFloat();
		Matrix3x3 matrix1;
		matrix1(0, 1) = randomValue;
		matrix1(1, 2) = randomValue;
		matrix1(2, 0) = randomValue;
		Matrix3x3 result = matrix1.Transpose();
		EXPECT_EQ(result(1, 0), randomValue);
		EXPECT_EQ(result(2, 1), randomValue);
		EXPECT_EQ(result(0, 2), randomValue);
	}
}

//***********************************************************************
TEST(Matrix3x3Tests, Inverse) {
	for(int i = 0; i < 50; ++i) {
		float randomValue = testUtility.GetRandomFloat(1.0f, 10000.0f);
		Matrix3x3 matrix1;
		matrix1(0, 0) = randomValue;
		matrix1(1, 1) = randomValue;
		matrix1(2, 2) = randomValue;
		Matrix3x3 result = matrix1.Inverse();
		EXPECT_NEAR(result(0, 0), 1.0f / randomValue, gFloatMargin);
		EXPECT_NEAR(result(1, 1), 1.0f / randomValue, gFloatMargin);
		EXPECT_NEAR(result(2, 2), 1.0f / randomValue, gFloatMargin);
	}
}

//***********************************************************************
TEST(Matrix3x3Tests, CreateRotationAroundX) {
	for(int i = 0; i < 50; ++i) {
		float randomValue = testUtility.GetRandomFloat(-3.14f, 3.14f);
		Matrix3x3 matrix1;
		Matrix3x3 result = matrix1.CreateRotationAroundX(randomValue);
		XMMATRIX dxResult = XMMatrixRotationX(randomValue);
		EXPECT_EQ(result, dxResult);
	}
}

//***********************************************************************
TEST(Matrix3x3Tests, CreateRotationAroundY) {
	for(int i = 0; i < 50; ++i) {
		float randomValue = testUtility.GetRandomFloat(-3.14f, 3.14f);
		Matrix3x3 matrix1;
		Matrix3x3 result = matrix1.CreateRotationAroundY(randomValue);
		XMMATRIX dxResult = XMMatrixRotationY(randomValue);
		EXPECT_EQ(result, dxResult);
	}
}

//***********************************************************************
TEST(Matrix3x3Tests, CreateRotationAroundZ) {
	for(int i = 0; i < 50; ++i) {
		float randomValue = testUtility.GetRandomFloat(-3.14f, 3.14f);
		Matrix3x3 matrix1;
		Matrix3x3 result = matrix1.CreateRotationAroundZ(randomValue);
		XMMATRIX dxResult = XMMatrixRotationZ(randomValue);
		EXPECT_EQ(result, dxResult);
	}
}