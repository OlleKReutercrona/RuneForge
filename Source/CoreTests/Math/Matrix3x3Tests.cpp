#include <gtest/gtest.h>

#include <DirectXMath.h>
#include "Math/Matrix3x3.h"
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

namespace RFMath {
	//***********************************************************************
	TEST(Matrix3x3Tests, DefaultContructor) {
		Matrix3x3 matrix;

		EXPECT_EQ(matrix, XMMatrixIdentity());
	}

	//***********************************************************************
	TEST(Matrix3x3Tests, CopyContructor) {
		for (int i = 0; i < 50; ++i) {
			float randomValue = testUtility.GetRandomFloat();

			Matrix3x3 matrix1;
			matrix1(0, 0) = randomValue;
			matrix1(0, 1) = randomValue;
			matrix1(1, 1) = randomValue;
			matrix1(1, 2) = randomValue;
			matrix1(2, 2) = randomValue;

			Matrix3x3 matrix2(matrix1);
			EXPECT_EQ(matrix1, matrix2);

			XMMATRIX dxMatrix(matrix1);
			EXPECT_EQ(matrix1, dxMatrix);
		}
	}

	//***********************************************************************
	TEST(Matrix3x3Tests, AssignmentOperator) {
		float randomValue = testUtility.GetRandomFloat(1.5f, 10000.0f);

		auto row = testUtility.GetRandomInt(0, 3);
		auto column = testUtility.GetRandomInt(0, 3);

		Matrix3x3 matrix1;
		matrix1(row, column) = randomValue;

		Matrix3x3 matrix2;
		EXPECT_NE(matrix2(row, column), randomValue);

		matrix2 = matrix1;
		EXPECT_EQ(matrix2.mMatrix, matrix1.mMatrix);
	}

	//***********************************************************************
	TEST(Matrix3x3Tests, MultiplicationOperator) {
		const float r1 = testUtility.GetRandomFloat(-1000.0f, 1000.0f);
		Matrix3x3 randomMatrix1 = {
			r1, r1, r1,
			r1, r1, r1,
			r1, r1, r1,
		};

		const float r2 = testUtility.GetRandomFloat(-1000.0f, 1000.0f);
		Matrix3x3 randomMatrix2 = {
			r2, r2, r2,
			r2, r2, r2,
			r2, r2, r2,
		};

		auto resultMatrix = randomMatrix1 * randomMatrix2;

		//	| a | b | c |	| j | k | l |	| aj + bm + cp | ak + bn + cq | al + bo + cr |
		//	|---+---+---|	|---+---+---|	|--------------+--------------+--------------|
		//	| d | e | f | X | m | n | o | = | dj + em + fp | dk + en + fq | dl + eo + fr |
		//	|---+---+---|	|---+---+---|	|--------------+--------------+--------------|
		//	| g | h | i |	| p | q | r |	| gj + hm + ip | gk + hn + iq | gl + ho + ir |


		// row 0
		{
			// r0c0
			const float expR0C0 =
				randomMatrix1(0, 0) * randomMatrix2(0, 0) + // a * j
				randomMatrix1(0, 1) * randomMatrix2(1, 0) + // b * m
				randomMatrix1(0, 2) * randomMatrix2(2, 0);  // c * p

			EXPECT_NEAR(resultMatrix(0, 0), expR0C0, gFloatMargin);

			// r0c1
			const float expR0C1 =
				randomMatrix1(0, 0) * randomMatrix2(0, 1) + // a * k
				randomMatrix1(0, 1) * randomMatrix2(1, 1) + // b * n
				randomMatrix1(0, 2) * randomMatrix2(2, 1);  // c * q

			EXPECT_NEAR(resultMatrix(0, 1), expR0C1, gFloatMargin);

			// r0c2
			const float expR0C2 =
				randomMatrix1(0, 0) * randomMatrix2(0, 2) + // a * l
				randomMatrix1(0, 1) * randomMatrix2(1, 2) + // b * o
				randomMatrix1(0, 2) * randomMatrix2(2, 2);  // c * r

			EXPECT_NEAR(resultMatrix(0, 2), expR0C2, gFloatMargin);
		}

		// row 1
		{
			// r1c0
			const float expR1C0 =
				randomMatrix1(1, 0) * randomMatrix2(0, 0) + // d * j
				randomMatrix1(1, 1) * randomMatrix2(1, 0) + // e * m
				randomMatrix1(1, 2) * randomMatrix2(2, 0);  // f * p

			EXPECT_NEAR(resultMatrix(1, 0), expR1C0, gFloatMargin);

			// r1c1
			const float expR1C1 =
				randomMatrix1(1, 0) * randomMatrix2(0, 1) + // d * k
				randomMatrix1(1, 1) * randomMatrix2(1, 1) + // e * n
				randomMatrix1(1, 2) * randomMatrix2(2, 1);  // f * q

			EXPECT_NEAR(resultMatrix(1, 1), expR1C1, gFloatMargin);

			// r1c2
			const float expR1C2 =
				randomMatrix1(1, 0) * randomMatrix2(0, 2) + // d * l
				randomMatrix1(1, 1) * randomMatrix2(1, 2) + // e * o
				randomMatrix1(1, 2) * randomMatrix2(2, 2);  // f * r

			EXPECT_NEAR(resultMatrix(1, 2), expR1C2, gFloatMargin);
		}

		// row 2
		{
			// r2c0
			const float expR2C0 =
				randomMatrix1(2, 0) * randomMatrix2(0, 0) + // g * j
				randomMatrix1(2, 1) * randomMatrix2(1, 0) + // h * m
				randomMatrix1(2, 2) * randomMatrix2(2, 0);  // i * p

			EXPECT_NEAR(resultMatrix(2, 0), expR2C0, gFloatMargin);

			// r2c1
			const float expR2C1 =
				randomMatrix1(2, 0) * randomMatrix2(0, 1) + // g * k
				randomMatrix1(2, 1) * randomMatrix2(1, 1) + // h * n
				randomMatrix1(2, 2) * randomMatrix2(2, 1);  // i * q

			EXPECT_NEAR(resultMatrix(2, 1), expR2C1, gFloatMargin);

			// r2c2
			const float expR2C2 =
				randomMatrix1(2, 0) * randomMatrix2(0, 2) + // g * l
				randomMatrix1(2, 1) * randomMatrix2(1, 2) + // h * o
				randomMatrix1(2, 2) * randomMatrix2(2, 2);  // i * r

			EXPECT_NEAR(resultMatrix(2, 2), expR2C2, gFloatMargin);
		}
	}

	//***********************************************************************
	TEST(Matrix3x3Tests, MultiplicationAssignmentOperator) {
		const float r1 = testUtility.GetRandomFloat(-1000.0f, 1000.0f);
		Matrix3x3 randomMatrix1 = {
			r1, r1, r1,
			r1, r1, r1,
			r1, r1, r1,
		};

		const float r2 = testUtility.GetRandomFloat(-1000.0f, 1000.0f);
		Matrix3x3 randomMatrix2 = {
			r2, r2, r2,
			r2, r2, r2,
			r2, r2, r2,
		};

		Matrix3x3 originalMatrix1 = randomMatrix1;
		ASSERT_EQ(randomMatrix1, originalMatrix1);

		randomMatrix1 *= randomMatrix2;

		// row 0
		{
			// r0c0
			const float expR0C0 =
				originalMatrix1(0, 0) * randomMatrix2(0, 0) + // a * j
				originalMatrix1(0, 1) * randomMatrix2(1, 0) + // b * m
				originalMatrix1(0, 2) * randomMatrix2(2, 0);  // c * p

			EXPECT_NEAR(randomMatrix1(0, 0), expR0C0, gFloatMargin);

			// r0c1
			const float expR0C1 =
				originalMatrix1(0, 0) * randomMatrix2(0, 1) + // a * k
				originalMatrix1(0, 1) * randomMatrix2(1, 1) + // b * n
				originalMatrix1(0, 2) * randomMatrix2(2, 1);  // c * q

			EXPECT_NEAR(randomMatrix1(0, 1), expR0C1, gFloatMargin);

			// r0c2
			const float expR0C2 =
				originalMatrix1(0, 0) * randomMatrix2(0, 2) + // a * l
				originalMatrix1(0, 1) * randomMatrix2(1, 2) + // b * o
				originalMatrix1(0, 2) * randomMatrix2(2, 2);  // c * r

			EXPECT_NEAR(randomMatrix1(0, 2), expR0C2, gFloatMargin);
		}

		// row 1
		{
			// r1c0
			const float expR1C0 =
				originalMatrix1(1, 0) * randomMatrix2(0, 0) + // d * j
				originalMatrix1(1, 1) * randomMatrix2(1, 0) + // e * m
				originalMatrix1(1, 2) * randomMatrix2(2, 0);  // f * p

			EXPECT_NEAR(randomMatrix1(1, 0), expR1C0, gFloatMargin);

			// r1c1
			const float expR1C1 =
				originalMatrix1(1, 0) * randomMatrix2(0, 1) + // d * k
				originalMatrix1(1, 1) * randomMatrix2(1, 1) + // e * n
				originalMatrix1(1, 2) * randomMatrix2(2, 1);  // f * q

			EXPECT_NEAR(randomMatrix1(1, 1), expR1C1, gFloatMargin);

			// r1c2
			const float expR1C2 =
				originalMatrix1(1, 0) * randomMatrix2(0, 2) + // d * l
				originalMatrix1(1, 1) * randomMatrix2(1, 2) + // e * o
				originalMatrix1(1, 2) * randomMatrix2(2, 2);  // f * r

			EXPECT_NEAR(randomMatrix1(1, 2), expR1C2, gFloatMargin);
		}

		// row 2
		{
			// r2c0
			const float expR2C0 =
				originalMatrix1(2, 0) * randomMatrix2(0, 0) + // g * j
				originalMatrix1(2, 1) * randomMatrix2(1, 0) + // h * m
				originalMatrix1(2, 2) * randomMatrix2(2, 0);  // i * p

			EXPECT_NEAR(randomMatrix1(2, 0), expR2C0, gFloatMargin);

			// r2c1
			const float expR2C1 =
				originalMatrix1(2, 0) * randomMatrix2(0, 1) + // g * k
				originalMatrix1(2, 1) * randomMatrix2(1, 1) + // h * n
				originalMatrix1(2, 2) * randomMatrix2(2, 1);  // i * q

			EXPECT_NEAR(randomMatrix1(2, 1), expR2C1, gFloatMargin);

			// r2c2
			const float expR2C2 =
				originalMatrix1(2, 0) * randomMatrix2(0, 2) + // g * l
				originalMatrix1(2, 1) * randomMatrix2(1, 2) + // h * o
				originalMatrix1(2, 2) * randomMatrix2(2, 2);  // i * r

			EXPECT_NEAR(randomMatrix1(2, 2), expR2C2, gFloatMargin);
		}
	}

	//***********************************************************************
	TEST(Matrix3x3Tests, AdditionOperator) {
		for (int i = 0; i < 50; ++i) {
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
		for (int i = 0; i < 50; ++i) {
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
		for (int i = 0; i < 50; ++i) {
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
		for (int i = 0; i < 50; ++i) {
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
		for (int i = 0; i < 50; ++i) {
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
		for (int i = 0; i < 50; ++i) {
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
		for (int i = 0; i < 50; ++i) {
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
		for (int i = 0; i < 50; ++i) {
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
		for (int i = 0; i < 50; ++i) {
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
		for (int i = 0; i < 50; ++i) {

			Matrix3x3 matrix;
			//DirectX::XMMATRIX dxMatrix;

			// Assign random values to the matrixes
			{
				for (int r = 0; r < 3; ++r) {
					for (int c = 0; c < 3; ++c) {
						const float randomValue = testUtility.GetRandomFloat(-100.0f, 100.0f);

						matrix(r, c) = randomValue;
						//dxMatrix.r[r].m128_f32[c] = randomValue;
					}
				}
			}

			Matrix3x3 result = matrix.Inverse();
			DirectX::XMMATRIX dxResult = DirectX::XMMatrixInverse(nullptr, matrix);

			// Test values 
			{
				for (int r = 0; r < 3; ++r) {
					for (int c = 0; c < 3; ++c) {
						const float matrixFloatValue = result(r, c);
						const float dxFloatValue = dxResult.r[r].m128_f32[c];

						EXPECT_NEAR(matrixFloatValue, dxFloatValue, gFloatMargin);
					}
				}
			}
		}
	}

	//***********************************************************************
	TEST(Matrix3x3Tests, CreateRotationAroundX) {
		for (int i = 0; i < 50; ++i) {
			float randomValue = testUtility.GetRandomFloat(-3.14f, 3.14f);
			Matrix3x3 result = Matrix3x3::CreateRotationAroundX(randomValue);
			XMMATRIX dxResult = XMMatrixRotationX(randomValue);
			EXPECT_EQ(result, dxResult);
		}
	}

	//***********************************************************************
	TEST(Matrix3x3Tests, CreateRotationAroundY) {
		for (int i = 0; i < 50; ++i) {
			float randomValue = testUtility.GetRandomFloat(-3.14f, 3.14f);
			Matrix3x3 result = Matrix3x3::CreateRotationAroundY(randomValue);
			XMMATRIX dxResult = XMMatrixRotationY(randomValue);
			EXPECT_EQ(result, dxResult);
		}
	}

	//***********************************************************************
	TEST(Matrix3x3Tests, CreateRotationAroundZ) {
		for (int i = 0; i < 50; ++i) {
			float randomValue = testUtility.GetRandomFloat(-3.14f, 3.14f);
			Matrix3x3 result = Matrix3x3::CreateRotationAroundZ(randomValue);
			XMMATRIX dxResult = XMMatrixRotationZ(randomValue);
			EXPECT_EQ(result, dxResult);
		}
	}

	//***********************************************************************
	TEST(Matrix3x3Tests, DivideByZero) {
		float randomValue = testUtility.GetRandomFloat(1.0f, 10000.0f);
		Matrix3x3 matrix1;
		matrix1(0, 0) = randomValue;
		matrix1(1, 1) = randomValue;
		matrix1(2, 2) = randomValue;

		EXPECT_DEATH({auto result = matrix1 / 0.0f;}, "Attempting to divide by zero");

		EXPECT_DEATH({ matrix1 /= 0.0f; }, "Attempting to divide by zero");
	}
	//***********************************************************************
	TEST(Matrix3x3Tests, ParenthesisOperatorOutOfBounds) {
		Matrix3x3 matrix;

		EXPECT_DEATH({ matrix(4,0) = 1.0f; }, "Matrix3x3: Index out of bounds");
		EXPECT_DEATH({ matrix(0,4) = 1.0f; }, "Matrix3x3: Index out of bounds");
	}
}
// namespace RFMath