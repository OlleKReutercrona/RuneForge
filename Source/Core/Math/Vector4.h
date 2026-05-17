#pragma once
#include <DirectXMath.h>
#include <cmath>

template <class T>
class Vector4 {
  public:
	T x;
	T y;
	T z;
	T w;

	Vector4<T>();
	Vector4<T>(T X, T Y, T Z, T W);
	Vector4<T>(const Vector4<T>& other) = default;
	~Vector4<T>() = default;

	Vector4<T>& operator=(const Vector4<T>& other) = default;

	// DirectX copying
	Vector4(const DirectX::XMFLOAT4& xmFloat4);
	Vector4(const DirectX::XMINT4& xm);
	Vector4(const DirectX::XMUINT4& xm);
	Vector4(DirectX::FXMVECTOR fxm);
	Vector4<T>& operator=(const DirectX::XMFLOAT4& xmFloat4);
	Vector4<T>& operator=(const DirectX::XMINT4& xmFloat4);
	Vector4<T>& operator=(const DirectX::XMUINT4& xmFloat4);
	Vector4<T>& operator=(DirectX::FXMVECTOR fxm);

	// Math functions
	T LengthSqrd() const;
	T Length() const;
	Vector4<T> GetNormalized() const;
	void Normalize();
	T Dot(const Vector4<T>& other) const;

	// DX Conversions
	DirectX::XMFLOAT4 ToXMFLOAT4() const;
	operator DirectX::XMFLOAT4() const;

	DirectX::XMINT4 ToXMINT4() const;
	operator DirectX::XMINT4() const;

	DirectX::XMUINT4 ToXMUINT4() const;
	operator DirectX::XMUINT4() const;
};

// Aliases
using Vector4f = Vector4<float>;
using Vector4d = Vector4<double>;
using Vector4i = Vector4<int>;
using Vector4ui = Vector4<unsigned int>;

// Constructors
//******************************************************************

template <class T>
inline Vector4<T>::Vector4() : x(0), y(0), z(0), w(0) {
}

template <class T>
inline Vector4<T>::Vector4(T X, T Y, T Z, T W) : x(X), y(Y), z(Z), w(W) {
}

// DirectX
template <class T>
inline Vector4<T>::Vector4(const DirectX::XMFLOAT4& xm) : x(static_cast<T>(xm.x)), y(static_cast<T>(xm.y)), z(static_cast<T>(xm.z)), w(static_cast<T>(xm.w)) {
}

template <class T>
inline Vector4<T>::Vector4(const DirectX::XMINT4& xm) : x(static_cast<T>(xm.x)), y(static_cast<T>(xm.y)), z(static_cast<T>(xm.z)), w(static_cast<T>(xm.w)) {
}

template <class T>
inline Vector4<T>::Vector4(const DirectX::XMUINT4& xm) : x(static_cast<T>(xm.x)), y(static_cast<T>(xm.y)), z(static_cast<T>(xm.z)), w(static_cast<T>(xm.w)) {
}

template <class T>
inline Vector4<T>::Vector4(DirectX::FXMVECTOR fxm) {
	DirectX::XMFLOAT4 tmp;
	DirectX::XMStoreFloat4(&tmp, fxm);
	x = static_cast<T>(tmp.x);
	y = static_cast<T>(tmp.y);
	z = static_cast<T>(tmp.z);
	w = static_cast<T>(tmp.w);
}

template <class T>
inline Vector4<T>& Vector4<T>::operator=(const DirectX::XMFLOAT4& xm) {
	x = static_cast<T>(xm.x);
	y = static_cast<T>(xm.y);
	z = static_cast<T>(xm.z);
	w = static_cast<T>(xm.w);
	return *this;
}

template <class T>
inline Vector4<T>& Vector4<T>::operator=(const DirectX::XMINT4& xm) {
	x = static_cast<T>(xm.x);
	y = static_cast<T>(xm.y);
	z = static_cast<T>(xm.z);
	w = static_cast<T>(xm.w);
	return *this;
}

template <class T>
inline Vector4<T>& Vector4<T>::operator=(const DirectX::XMUINT4& xm) {
	x = static_cast<T>(xm.x);
	y = static_cast<T>(xm.y);
	z = static_cast<T>(xm.z);
	w = static_cast<T>(xm.w);
	return *this;
}

template <class T>
inline Vector4<T>& Vector4<T>::operator=(DirectX::FXMVECTOR fxm) {
	DirectX::XMFLOAT4 tmp;
	DirectX::XMStoreFloat4(&tmp, fxm);
	x = static_cast<T>(tmp.x);
	y = static_cast<T>(tmp.y);
	z = static_cast<T>(tmp.z);
	w = static_cast<T>(tmp.w);
	return *this;
}

// MATH
//******************************************************************

template <class T>
inline T Vector4<T>::LengthSqrd() const {
	return x * x + y * y + z * z + w * w;
}

template <class T>
inline T Vector4<T>::Length() const {
	return static_cast<T>(sqrt(LengthSqrd()));
}

template <class T>
inline Vector4<T> Vector4<T>::GetNormalized() const {
	Vector4<T> vec(x, y, z, w);
	vec.Normalize();
	return vec;
}

template <class T>
inline void Vector4<T>::Normalize() {
	Vector4<T> vec(x, y, z, w);
	if (x + y != 0) {
		const auto length = vec.Length();
		x = vec.x / length;
		y = vec.y / length;
		z = vec.z / length;
		w = vec.w / length;
	}
}

template <class T>
inline T Vector4<T>::Dot(const Vector4<T>& vector) const {
	return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
}

// DX Conversions
//******************************************************************

template <class T>
inline DirectX::XMFLOAT4 Vector4<T>::ToXMFLOAT4() const {
	return DirectX::XMFLOAT4(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z),
							 static_cast<float>(w));
}

template <class T>
inline Vector4<T>::operator DirectX::XMFLOAT4() const {
	return ToXMFLOAT4();
}

template <class T>
inline DirectX::XMINT4 Vector4<T>::ToXMINT4() const {
	return DirectX::XMINT4(static_cast<int>(x), static_cast<int>(y), static_cast<int>(z), static_cast<int>(w));
}

template <class T>
inline Vector4<T>::operator DirectX::XMINT4() const {
	return ToXMINT4();
}

template <class T>
inline DirectX::XMUINT4 Vector4<T>::ToXMUINT4() const {
	return DirectX::XMUINT4(static_cast<unsigned int>(x), static_cast<unsigned int>(y), static_cast<unsigned int>(z),
							static_cast<unsigned int>(w));
}

template <class T>
inline Vector4<T>::operator DirectX::XMUINT4() const {
	return ToXMUINT4();
}

// Arithmetic Operators
//******************************************************************

template <typename T>
Vector4<T> operator+(const Vector4<T>& vector0, const Vector4<T>& vector1) {
	return {vector0.x + vector1.x, vector0.y + vector1.y, vector0.z + vector1.z, vector0.w + vector1.w};
}

template <class T>
void operator+=(Vector4<T>& vector0, const Vector4<T>& vector1) {
	vector0.x += vector1.x;
	vector0.y += vector1.y;
	vector0.z += vector1.z;
	vector0.w += vector1.w;
}

template <class T>
Vector4<T> operator-(const Vector4<T>& vector0, const Vector4<T>& vector1) {
	return {vector0.x - vector1.x, vector0.y - vector1.y, vector0.z - vector1.z, vector0.w - vector1.w};
}

template <class T>
void operator-=(Vector4<T>& vector0, const Vector4<T>& vector1) {
	vector0.x -= vector1.x;
	vector0.y -= vector1.y;
	vector0.z -= vector1.z;
	vector0.w -= vector1.w;
}

template <class T>
Vector4<T> operator*(const Vector4<T>& vector0, const Vector4<T>& vector1) {
	return {vector0.x * vector1.x, vector0.y * vector1.y, vector0.z * vector1.z, vector0.w * vector1.w};
}

template <class T>
void operator*=(Vector4<T>& vector0, const Vector4<T>& vector1) {
	vector0.x *= vector1.x;
	vector0.y *= vector1.y;
	vector0.z *= vector1.z;
	vector0.w *= vector1.w;
}

template <class T>
bool operator==(const Vector4<T>& vector0, const Vector4<T>& vector1) {
	return vector0.x == vector1.x && vector0.y == vector1.y && vector0.z == vector1.z && vector0.w == vector1.w;
}
