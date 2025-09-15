//#include <gtest/gtest.h>
//#include "Math/Vector3.h"
//#include "Math/Math.h"
//
//
//// ---------------- Vector3 (float) ---------------- //
//#pragma region Vector3Tests
//
//TEST(Vector3Tests, ConstructorAndEquality) {
//    // Default constructor
//    Vector3 v0;
//    EXPECT_FLOAT_EQ(v0.x, 0.0f);
//    EXPECT_FLOAT_EQ(v0.y, 0.0f);
//    EXPECT_FLOAT_EQ(v0.z, 0.0f);
//
//    // Parameterized constructor
//    Vector3 v1(1.0f, 2.0f, 3.0f);
//    EXPECT_FLOAT_EQ(v1.x, 1.0f);
//    EXPECT_FLOAT_EQ(v1.y, 2.0f);
//    EXPECT_FLOAT_EQ(v1.z, 3.0f);
//
//    // XMFLOAT3 constructor
//    DirectX::XMFLOAT3 xf{ 4.0f, 5.0f, 6.0f };
//    Vector3 v2(xf);
//    EXPECT_FLOAT_EQ(v2.x, 4.0f);
//    EXPECT_FLOAT_EQ(v2.y, 5.0f);
//    EXPECT_FLOAT_EQ(v2.z, 6.0f);
//
//    // Array constructor
//    float arr[3] = { 7.0f, 8.0f, 9.0f };
//    Vector3 v3(arr);
//    EXPECT_FLOAT_EQ(v3.x, arr[0]);
//    EXPECT_FLOAT_EQ(v3.y, arr[1]);
//    EXPECT_FLOAT_EQ(v3.z, arr[2]);
//
//    // Zero constant
//    Vector3 vZero = Vector3::Zero;
//    EXPECT_FLOAT_EQ(vZero.x, 0.0f);
//    EXPECT_FLOAT_EQ(vZero.y, 0.0f);
//    EXPECT_FLOAT_EQ(vZero.z, 0.0f);
//}
//
//TEST(Vector3Tests, ToXMVECTORConversion) {
//    Vector3 v(1.0f, 2.0f, 3.0f);
//    DirectX::XMVECTOR vec = v.ToXMVECTOR(1.0f); // w = 1.0f (position)
//
//    DirectX::XMFLOAT4 result;
//    DirectX::XMStoreFloat4(&result, vec);
//
//    EXPECT_FLOAT_EQ(result.x, 1.0f);
//    EXPECT_FLOAT_EQ(result.y, 2.0f);
//    EXPECT_FLOAT_EQ(result.z, 3.0f);
//    EXPECT_FLOAT_EQ(result.w, 1.0f);
//}
//
//TEST(Vector3Tests, ArithmeticOperators) {
//    Vector3 a(1, 2, 3);
//    Vector3 b(4, 5, 6);
//
//    // Addition & Subtraction
//    Vector3 c = a + b;
//    EXPECT_EQ(c, Vector3(5, 7, 9));
//    Vector3 d = c - a;
//    EXPECT_EQ(d, b);
//
//    // Scalar Multiplication
//    Vector3 scaled = a * 2.0f;
//    EXPECT_EQ(scaled, Vector3(2, 4, 6));
//    Vector3 scaled2 = 2.0f * a;
//    EXPECT_EQ(scaled2, Vector3(2, 4, 6));
//
//    // Scalar Division
//    Vector3 divided = scaled / 2.0f;
//    EXPECT_EQ(divided, a);
//
//    EXPECT_DEATH({ a /= 0.0f; }, "Division by zero in Vector3::operator/=");
//}
//
//TEST(Vector3Tests, OperatorsCompoundAssignment) {
//    Vector3 a(2, 3, 4);
//    Vector3 b(1, -1, 2);
//
//    a += b;
//    EXPECT_EQ(a, Vector3(3, 2, 6));
//
//    a -= Vector3(1, 1, 1);
//    EXPECT_EQ(a, Vector3(2, 1, 5));
//
//    a *= 2.0f;
//    EXPECT_EQ(a, Vector3(4, 2, 10));
//
//    a /= 2.0f;
//    EXPECT_EQ(a, Vector3(2, 1, 5));
//
//    EXPECT_DEATH({ a / 0.0f; }, "Division by zero in Vector3::operator/");
//}
//
//TEST(Vector3Tests, LengthAndLengthSquared) {
//    Vector3 v(3.0f, 4.0f, 12.0f);
//
//    float lenSq = v.LengthSquared();
//    EXPECT_FLOAT_EQ(lenSq, 3 * 3 + 4 * 4 + 12 * 12); // 169
//
//    float len = v.Length();
//    EXPECT_FLOAT_EQ(len, 13.0f);
//}
//
//TEST(Vector3Tests, DotProduct) {
//    Vector3 a(1, 2, 3);
//    Vector3 b(4, -5, 6);
//    float dot = a.Dot(b);
//    EXPECT_FLOAT_EQ(dot, 1 * 4 + 2 * (-5) + 3 * 6); // 12
//}
//
//TEST(Vector3Tests, CrossProduct) {
//    Vector3 a(1, 0, 0);
//    Vector3 b(0, 1, 0);
//    Vector3 c = a.Cross(b);
//    EXPECT_FLOAT_EQ(c.x, 0);
//    EXPECT_FLOAT_EQ(c.y, 0);
//    EXPECT_FLOAT_EQ(c.z, 1);
//}
//
//TEST(Vector3Tests, Normalization) {
//    Vector3 v(3, 0, 4);
//    Vector3 n = v.Normalized();
//    EXPECT_NEAR(n.Length(), 1.0f, vecEpsilon);
//}
//
//TEST(Vector3Tests, Reflection) {
//    Vector3 v(1, -1, 0);
//    Vector3 normal = Vector3::UnitY; // (0,1,0)
//    Vector3 r = v.Reflect(normal);
//    EXPECT_FLOAT_EQ(r.x, 1);
//    EXPECT_FLOAT_EQ(r.y, 1);
//    EXPECT_FLOAT_EQ(r.z, 0);
//
//    Vector3 noDiscardCache = Vector3::Zero; // just to avoid warning from [[nodiscard]]
//    Vector3 badNormal(0, 1.5f, 0); // not normalized
//    Vector3 badNormal2(0, 0.9f, 0); // not normalized
//
//    // Expect assert/death
//    EXPECT_DEATH({ noDiscardCache = v.Reflect(badNormal); }, "Vector3::Reflect received non-normalized normal");
//    EXPECT_DEATH({ noDiscardCache = v.Reflect(badNormal2); }, "Vector3::Reflect received non-normalized normal");
//}
//
//TEST(Vector3Tests, Rotations) {
//    Vector3 v(1, 0, 0);
//
//    auto yaw90 = v.RotateYaw(math::HALF_PI); // +90° yaw
//    EXPECT_NEAR(yaw90.x, 0, vecEpsilon);
//    EXPECT_NEAR(yaw90.z, -1, vecEpsilon);
//
//    auto pitch90 = v.RotatePitch(math::HALF_PI); // +90° pitch
//    EXPECT_NEAR(pitch90.y, 0, vecEpsilon); // stays 0
//    EXPECT_NEAR(pitch90.z, 0, vecEpsilon); // stays 0
//}
//
//TEST(Vector3Tests, SubVectorAccessors) {
//    Vector3 v(1.0f, 2.0f, 3.0f);
//
//    Vector2 xy = v.xy();
//    EXPECT_FLOAT_EQ(xy.x, 1.0f);
//    EXPECT_FLOAT_EQ(xy.y, 2.0f);
//
//    Vector2 xz = v.xz();
//    EXPECT_FLOAT_EQ(xz.x, 1.0f);
//    EXPECT_FLOAT_EQ(xz.y, 3.0f);
//
//    Vector2 yz = v.yz();
//    EXPECT_FLOAT_EQ(yz.x, 2.0f);
//    EXPECT_FLOAT_EQ(yz.y, 3.0f);
//}
//
//#pragma endregion
//
//// ---------------- Vector3i (int) ---------------- //
//#pragma region Vector3iTests
//
//TEST(Vector3iTests, ConstructorAndEquality) {
//    // Default constructor
//    Vector3i v0;
//    EXPECT_EQ(v0.x, 0);
//    EXPECT_EQ(v0.y, 0);
//    EXPECT_EQ(v0.z, 0);
//
//    // Parameterized constructor
//    Vector3i v1(1, 2, 3);
//    EXPECT_EQ(v1.x, 1);
//    EXPECT_EQ(v1.y, 2);
//    EXPECT_EQ(v1.z, 3);
//
//    // Array constructor
//    int arr[3] = { 4, 5, 6 };
//    Vector3i v2(arr);
//    EXPECT_EQ(v2.x, 4);
//    EXPECT_EQ(v2.y, 5);
//    EXPECT_EQ(v2.z, 6);
//
//    // Zero constant
//    Vector3i vZero = Vector3i::Zero;
//    EXPECT_EQ(vZero.x, 0);
//    EXPECT_EQ(vZero.y, 0);
//    EXPECT_EQ(vZero.z, 0);
//}
//
//TEST(Vector3iTests, ToXMVECTORConversion) {
//    Vector3i v(1, 2, 3);
//    DirectX::XMVECTOR vec = v.ToXMVECTOR(0.0f); // w = 0.0f (direction)
//
//    DirectX::XMFLOAT4 result;
//    DirectX::XMStoreFloat4(&result, vec);
//
//    EXPECT_FLOAT_EQ(result.x, 1.0f);
//    EXPECT_FLOAT_EQ(result.y, 2.0f);
//    EXPECT_FLOAT_EQ(result.z, 3.0f);
//    EXPECT_FLOAT_EQ(result.w, 0.0f);
//}
//
//TEST(Vector3iTests, ArithmeticOperators) {
//    Vector3i a(1, 2, 3);
//    Vector3i b(4, 5, 6);
//
//    // Addition & Subtraction
//    Vector3i c = a + b;
//    EXPECT_EQ(c, Vector3i(5, 7, 9));
//    Vector3i d = c - a;
//    EXPECT_EQ(d, b);
//
//    // Scalar Multiplication
//    Vector3i scaled = a * 2;
//    EXPECT_EQ(scaled, Vector3i(2, 4, 6));
//    Vector3i scaled2 = 2 * a;
//    EXPECT_EQ(scaled2, Vector3i(2, 4, 6));
//
//    // Scalar Division
//    Vector3i divided = scaled / 2;
//    EXPECT_EQ(divided, a);
//
//    EXPECT_DEATH({ a / 0; }, "Division by zero in Vector3i::operator/");
//}
//
//TEST(Vector3iTests, OperatorsCompoundAssignment) {
//    Vector3i a(2, 3, 4);
//    Vector3i b(1, -1, 2);
//
//    a += b;
//    EXPECT_EQ(a, Vector3i(3, 2, 6));
//
//    a -= Vector3i(1, 1, 1);
//    EXPECT_EQ(a, Vector3i(2, 1, 5));
//
//    a *= 2;
//    EXPECT_EQ(a, Vector3i(4, 2, 10));
//
//    a /= 2;
//    EXPECT_EQ(a, Vector3i(2, 1, 5));
//
//    EXPECT_DEATH({ a /= 0; }, "Division by zero in Vector3i::operator/=");
//}
//
//TEST(Vector3iTests, LengthSquared) {
//    Vector3i v(3, 4, 12);
//
//    int lenSq = v.LengthSquared();
//    EXPECT_EQ(lenSq, 3 * 3 + 4 * 4 + 12 * 12); // 169
//}
//
//TEST(Vector3iTests, Rotate90AroundAxes) {
//    Vector3i v(1, 2, 3);
//
//    auto r1 = v.Rotate90(Vector3i::RotateAxis::X, 1);
//    EXPECT_EQ(r1.x, 1);
//    EXPECT_EQ(r1.y, -3);
//    EXPECT_EQ(r1.z, 2);
//
//    auto r2 = v.Rotate90(Vector3i::RotateAxis::Y, -1); // negative steps
//    EXPECT_EQ(r2.x, -3);
//    EXPECT_EQ(r2.y, 2);
//    EXPECT_EQ(r2.z, 1);
//
//    auto r3 = v.Rotate90(Vector3i::RotateAxis::Z, 2);
//    EXPECT_EQ(r3.x, -1);
//    EXPECT_EQ(r3.y, -2);
//    EXPECT_EQ(r3.z, 3);
//}
//
//TEST(Vector3iTests, SubVectorAccessors) {
//    Vector3i v(1, 2, 3);
//
//    Vector2i xy = v.xy();
//    EXPECT_EQ(xy.x, 1);
//    EXPECT_EQ(xy.y, 2);
//
//    Vector2i xz = v.xz();
//    EXPECT_EQ(xz.x, 1);
//    EXPECT_EQ(xz.y, 3);
//
//    Vector2i yz = v.yz();
//    EXPECT_EQ(yz.x, 2);
//    EXPECT_EQ(yz.y, 3);
//}
//
//#pragma endregion
