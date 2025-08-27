#pragma once
#include <DirectXMath.h>

/// <summary>
/// Matrix3x3 wrapper class for DirectXMath's XMMATRIX.
/// </summary>
class Matrix3x3 {
public:
	Matrix3x3() : mMatrix(DirectX::XMMatrixIdentity()) {}
	Matrix3x3(const Matrix3x3& other) : mMatrix(other) {}
	Matrix3x3(Matrix3x3& other) : mMatrix(other) {}
	Matrix3x3(const DirectX::XMMATRIX& other) : mMatrix(other) {}
	Matrix3x3(DirectX::XMMATRIX& other) : mMatrix(other) {}

	float& operator()(const unsigned int row, const unsigned int column) noexcept;
	Matrix3x3& operator=(const Matrix3x3& other) noexcept;
	Matrix3x3 operator*(const Matrix3x3& other) const noexcept;
	Matrix3x3& operator*=(const Matrix3x3& other) noexcept;
	Matrix3x3 operator+(const Matrix3x3& other) const noexcept;
	Matrix3x3& operator+=(const Matrix3x3& other) noexcept;
	Matrix3x3 operator-(const Matrix3x3& other) const noexcept;
	Matrix3x3& operator-=(const Matrix3x3& other) noexcept;
	Matrix3x3 operator*(const float scalar) const noexcept;
	Matrix3x3& operator*=(const float scalar) noexcept;
	Matrix3x3 operator/(const float scalar) const noexcept;
	Matrix3x3& operator/=(const float scalar) noexcept;
	operator DirectX::XMMATRIX() const noexcept { return mMatrix; }

	Matrix3x3 Transpose() const;
	Matrix3x3 Inverse() const; // Todo, add parameter for determinant when Vector3 is implemented
	Matrix3x3 CreateRotationAroundX(const float angle) const;
	Matrix3x3 CreateRotationAroundY(const float angle) const;
	Matrix3x3 CreateRotationAroundZ(const float angle) const;

	// Todo, implement these methods when Vector3 is implemented
	//Matrix3x3 CreateTranslationMatrix(const Vector3& scaleVector);
	//Matrix3x3 CreateScaleMatrix(const Vector3& scaleVector);
	//Matrix3x3 CreateRotationMatrix(const Vector3& scaleVector);

	DirectX::XMMATRIX mMatrix = {};
};

static inline Matrix3x3 zerMatrix = Matrix3x3();

float& Matrix3x3::operator()(const unsigned int row, const unsigned int column) noexcept {
	assert(row < 3 && column < 3 && "Matrix3x3: Index out of bounds");

	return mMatrix.r[row].m128_f32[column];
}

Matrix3x3& Matrix3x3::operator=(const Matrix3x3& other) noexcept {
	if(this != &other) {
		mMatrix = other.mMatrix;
	}

	return *this;
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& other) const noexcept {
	return mMatrix * other.mMatrix;
}

Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& other) noexcept {
	mMatrix *= other.mMatrix;
	return *this;
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3& other) const noexcept {
	return mMatrix + other;
}

Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& other) noexcept {
	mMatrix += other.mMatrix;
	return *this;
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3& other) const noexcept {
	return mMatrix - other;
}

Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& other) noexcept {
	mMatrix -= other.mMatrix;
	return *this;
}

Matrix3x3 Matrix3x3::operator*(const float scalar) const noexcept {
	return mMatrix * scalar;
}

Matrix3x3& Matrix3x3::operator*=(const float scalar) noexcept {
	mMatrix *= scalar;
	return *this;
}

Matrix3x3 Matrix3x3::operator/(const float scalar) const noexcept {
	return mMatrix / scalar;
}

Matrix3x3& Matrix3x3::operator/=(const float scalar) noexcept {
	mMatrix /= scalar;
	return *this;
}

Matrix3x3 Matrix3x3::Transpose() const {
	return DirectX::XMMatrixTranspose(mMatrix);
}

Matrix3x3 Matrix3x3::Inverse() const {
	return DirectX::XMMatrixInverse(nullptr, mMatrix);
}

Matrix3x3 Matrix3x3::CreateRotationAroundX(const float angle) const {
	return DirectX::XMMatrixRotationX(angle);
}

Matrix3x3 Matrix3x3::CreateRotationAroundY(const float angle) const {
	return DirectX::XMMatrixRotationY(angle);
}

Matrix3x3 Matrix3x3::CreateRotationAroundZ(const float angle) const {
	return DirectX::XMMatrixRotationZ(angle);
}
