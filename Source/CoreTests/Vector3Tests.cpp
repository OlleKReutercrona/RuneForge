#include <gtest/gtest.h>
#include "Math/Vector3.h"
#include "Math/Math.h"


// ---------------- Vector3 (float) ---------------- //

TEST(Vector3Tests, ConstructorAndEquality) {
    Vector3 v1(1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(v1.x, 1.0f);
    EXPECT_FLOAT_EQ(v1.y, 2.0f);
    EXPECT_FLOAT_EQ(v1.z, 3.0f);

    Vector3 v2 = Vector3::Zero;
    EXPECT_FLOAT_EQ(v2.x, 0.0f);
    EXPECT_FLOAT_EQ(v2.y, 0.0f);
    EXPECT_FLOAT_EQ(v2.z, 0.0f);

    float arr[3] = { 7.0f, 8.0f, 9.0f };
    Vector3 v3(arr);
    EXPECT_FLOAT_EQ(v3.x, 7.0f);
    EXPECT_FLOAT_EQ(v3.y, 8.0f);
    EXPECT_FLOAT_EQ(v3.z, 9.0f);
}

TEST(Vector3Tests, ToXMVECTORConversion) {
    Vector3 v(1.0f, 2.0f, 3.0f);
    DirectX::XMVECTOR vec = v.ToXMVECTOR(1.0f); // w = 1.0f (position)

    DirectX::XMFLOAT4 result;
    DirectX::XMStoreFloat4(&result, vec);

    EXPECT_FLOAT_EQ(result.x, 1.0f);
    EXPECT_FLOAT_EQ(result.y, 2.0f);
    EXPECT_FLOAT_EQ(result.z, 3.0f);
    EXPECT_FLOAT_EQ(result.w, 1.0f);
}

TEST(Vector3Tests, AdditionSubtraction) {
    Vector3 a(1, 2, 3);
    Vector3 b(4, 5, 6);
    Vector3 c = a + b;
    EXPECT_FLOAT_EQ(c.x, 5);
    EXPECT_FLOAT_EQ(c.y, 7);
    EXPECT_FLOAT_EQ(c.z, 9);

    Vector3 d = c - a;
    EXPECT_FLOAT_EQ(d.x, 4);
    EXPECT_FLOAT_EQ(d.y, 5);
    EXPECT_FLOAT_EQ(d.z, 6);
}

TEST(Vector3Tests, ScalarMultiplicationDivision) {
    Vector3 v(2, -4, 6);
    Vector3 scaled = v * 2.0f;
    EXPECT_FLOAT_EQ(scaled.x, 4);
    EXPECT_FLOAT_EQ(scaled.y, -8);
    EXPECT_FLOAT_EQ(scaled.z, 12);

    Vector3 divided = scaled / 2.0f;
    EXPECT_FLOAT_EQ(divided.x, 2);
    EXPECT_FLOAT_EQ(divided.y, -4);
    EXPECT_FLOAT_EQ(divided.z, 6);
}

TEST(Vector3Tests, LengthAndLengthSquared) {
    Vector3 v(3.0f, 4.0f, 12.0f);

    float lenSq = v.LengthSquared();
    EXPECT_FLOAT_EQ(lenSq, 3 * 3 + 4 * 4 + 12 * 12); // 169

    float len = v.Length();
    EXPECT_FLOAT_EQ(len, 13.0f);
}

TEST(Vector3Tests, DotProduct) {
    Vector3 a(1, 2, 3);
    Vector3 b(4, -5, 6);
    float dot = a.Dot(b);
    EXPECT_FLOAT_EQ(dot, 1 * 4 + 2 * (-5) + 3 * 6); // 12
}

TEST(Vector3Tests, CrossProduct) {
    Vector3 a(1, 0, 0);
    Vector3 b(0, 1, 0);
    Vector3 c = a.Cross(b);
    EXPECT_FLOAT_EQ(c.x, 0);
    EXPECT_FLOAT_EQ(c.y, 0);
    EXPECT_FLOAT_EQ(c.z, 1);
}

TEST(Vector3Tests, Normalization) {
    Vector3 v(3, 0, 4);
    Vector3 n = v.Normalized();
    EXPECT_NEAR(n.Length(), 1.0f, 1e-6f);
}

TEST(Vector3Tests, Reflection) {
    Vector3 v(1, -1, 0);
    Vector3 normal = Vector3::UnitY; // (0,1,0)
    Vector3 r = v.Reflect(normal);
    EXPECT_FLOAT_EQ(r.x, 1);
    EXPECT_FLOAT_EQ(r.y, 1);
    EXPECT_FLOAT_EQ(r.z, 0);
}

TEST(Vector3Tests, Rotations) {
    Vector3 v(1, 0, 0);

    auto yaw90 = v.RotateYaw(math::HALF_PI); // +90° yaw
    EXPECT_NEAR(yaw90.x, 0, 1e-6f);
    EXPECT_NEAR(yaw90.z, -1, 1e-6f);

    auto pitch90 = v.RotatePitch(math::HALF_PI); // +90° pitch
    EXPECT_NEAR(pitch90.y, 0, 1e-6f); // stays 0
    EXPECT_NEAR(pitch90.z, 0, 1e-6f); // stays 0
}

TEST(Vector3Tests, SubVectorAccessors) {
    Vector3 v(1.0f, 2.0f, 3.0f);

    Vector2 xy = v.xy();
    EXPECT_FLOAT_EQ(xy.x, 1.0f);
    EXPECT_FLOAT_EQ(xy.y, 2.0f);

    Vector2 xz = v.xz();
    EXPECT_FLOAT_EQ(xz.x, 1.0f);
    EXPECT_FLOAT_EQ(xz.y, 3.0f);

    Vector2 yz = v.yz();
    EXPECT_FLOAT_EQ(yz.x, 2.0f);
    EXPECT_FLOAT_EQ(yz.y, 3.0f);
}

// ---------------- Vector3i (int) ---------------- //

TEST(Vector3iTests, ConstructorAndEquality) {
    Vector3i v1(1, 2, 3);
    EXPECT_EQ(v1.x, 1);
    EXPECT_EQ(v1.y, 2);
    EXPECT_EQ(v1.z, 3);

    Vector3i v2 = Vector3i::Zero;
    EXPECT_EQ(v2.x, 0);
    EXPECT_EQ(v2.y, 0);
    EXPECT_EQ(v2.z, 0);

    int arr[3] = { 7, 8, 9 };
    Vector3i v(arr);
    EXPECT_EQ(v.x, 7);
    EXPECT_EQ(v.y, 8);
    EXPECT_EQ(v.z, 9);
}

TEST(Vector3iTests, ToXMVECTORConversion) {
    Vector3i v(1, 2, 3);
    DirectX::XMVECTOR vec = v.ToXMVECTOR(0.0f); // w = 0.0f (direction)

    DirectX::XMFLOAT4 result;
    DirectX::XMStoreFloat4(&result, vec);

    EXPECT_FLOAT_EQ(result.x, 1.0f);
    EXPECT_FLOAT_EQ(result.y, 2.0f);
    EXPECT_FLOAT_EQ(result.z, 3.0f);
    EXPECT_FLOAT_EQ(result.w, 0.0f);
}

TEST(Vector3iTests, AdditionSubtraction) {
    Vector3i a(1, 2, 3);
    Vector3i b(4, 5, 6);
    Vector3i c = a + b;
    EXPECT_EQ(c.x, 5);
    EXPECT_EQ(c.y, 7);
    EXPECT_EQ(c.z, 9);

    Vector3i d = c - a;
    EXPECT_EQ(d.x, 4);
    EXPECT_EQ(d.y, 5);
    EXPECT_EQ(d.z, 6);
}

TEST(Vector3iTests, ScalarMultiplicationDivision) {
    Vector3i v(2, -4, 6);
    Vector3i scaled = v * 2;
    EXPECT_EQ(scaled.x, 4);
    EXPECT_EQ(scaled.y, -8);
    EXPECT_EQ(scaled.z, 12);

    Vector3i divided = scaled / 2;
    EXPECT_EQ(divided.x, 2);
    EXPECT_EQ(divided.y, -4);
    EXPECT_EQ(divided.z, 6);
}

TEST(Vector3iTests, LengthSquared) {
    Vector3i v(3, 4, 12);

    int lenSq = v.LengthSquared();
    EXPECT_EQ(lenSq, 3 * 3 + 4 * 4 + 12 * 12); // 169
}

TEST(Vector3iTests, Rotate90AroundAxes) {
    Vector3i v(1, 2, 3);

    auto r1 = v.Rotate90(Vector3i::RotateAxis::X, 1);
    EXPECT_EQ(r1.x, 1);
    EXPECT_EQ(r1.y, -3);
    EXPECT_EQ(r1.z, 2);

    auto r2 = v.Rotate90(Vector3i::RotateAxis::Y, -1); // negative steps
    EXPECT_EQ(r2.x, -3);
    EXPECT_EQ(r2.y, 2);
    EXPECT_EQ(r2.z, 1);

    auto r3 = v.Rotate90(Vector3i::RotateAxis::Z, 2);
    EXPECT_EQ(r3.x, -1);
    EXPECT_EQ(r3.y, -2);
    EXPECT_EQ(r3.z, 3);
}

TEST(Vector3iTests, SubVectorAccessors) {
    Vector3i v(1, 2, 3);

    Vector2i xy = v.xy();
    EXPECT_EQ(xy.x, 1);
    EXPECT_EQ(xy.y, 2);

    Vector2i xz = v.xz();
    EXPECT_EQ(xz.x, 1);
    EXPECT_EQ(xz.y, 3);

    Vector2i yz = v.yz();
    EXPECT_EQ(yz.x, 2);
    EXPECT_EQ(yz.y, 3);
}
