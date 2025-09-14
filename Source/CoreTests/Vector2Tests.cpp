#include <gtest/gtest.h>
#include "Math/Vector2.h"

TEST(Vector2Tests, ConstructorFromArray) {
    float arr[2] = { 3.5f, -2.0f };
    Vector2 v(arr);
    EXPECT_FLOAT_EQ(v.x, 3.5f);
    EXPECT_FLOAT_EQ(v.y, -2.0f);
}

TEST(Vector2Tests, LengthAndLengthSquared) {
    Vector2 v(3.0f, 4.0f);
    EXPECT_FLOAT_EQ(v.LengthSquared(), 25.0f);
    EXPECT_FLOAT_EQ(v.Length(), 5.0f);
}

TEST(Vector2Tests, DotProduct) {
    Vector2 a(1.0f, 2.0f);
    Vector2 b(3.0f, 4.0f);
    EXPECT_FLOAT_EQ(a.Dot(b), 11.0f); // 1*3 + 2*4
}

TEST(Vector2Tests, Normalize) {
    Vector2 v(3.0f, 4.0f);
    Vector2 n = v.Normalized();
    EXPECT_NEAR(n.Length(), 1.0f, 1e-6f);
    EXPECT_NEAR(n.x, 0.6f, 1e-6f);
    EXPECT_NEAR(n.y, 0.8f, 1e-6f);
}

TEST(Vector2Tests, Reflect) {
    Vector2 v(1, -1);
    Vector2 n(0, 1); // unit Y
    Vector2 r = v.Reflect(n);
    EXPECT_FLOAT_EQ(r.x, 1);
    EXPECT_FLOAT_EQ(r.y, 1);
}

TEST(Vector2Tests, OperatorsArithmetic) {
    Vector2 a(2, 3);
    Vector2 b(1, -1);

    EXPECT_EQ(a + b, Vector2(3, 2));
    EXPECT_EQ(a - b, Vector2(1, 4));

    EXPECT_EQ(a * 2.0f, Vector2(4, 6));
    EXPECT_EQ(2.0f * a, Vector2(4, 6));
    EXPECT_EQ(a / 2.0f, Vector2(1, 1.5f));
}

TEST(Vector2Tests, ToXMVECTOR) {
    Vector2 v(1.5f, -2.5f);
    DirectX::XMVECTOR vec = v.ToXMVECTOR(1.0f);

    DirectX::XMFLOAT4 unpack;
    DirectX::XMStoreFloat4(&unpack, vec);
    EXPECT_FLOAT_EQ(unpack.x, 1.5f);
    EXPECT_FLOAT_EQ(unpack.y, -2.5f);
    EXPECT_FLOAT_EQ(unpack.z, 0.0f);
    EXPECT_FLOAT_EQ(unpack.w, 1.0f);
}

TEST(Vector2iTests, ConstructorFromArray) {
    int arr[2] = { 3, -2 };
    Vector2i v(arr);
    EXPECT_EQ(v.x, 3);
    EXPECT_EQ(v.y, -2);
}

TEST(Vector2iTests, DotProduct) {
    Vector2i a(2, 3);
    Vector2i b(4, -1);
    EXPECT_EQ(a.Dot(b), 5); // 2*4 + 3*(-1)
}

TEST(Vector2iTests, OperatorsArithmetic) {
    Vector2i a(2, 3);
    Vector2i b(1, -1);

    EXPECT_EQ(a + b, Vector2i(3, 2));
    EXPECT_EQ(a - b, Vector2i(1, 4));

    EXPECT_EQ(a * 2, Vector2i(4, 6));
    EXPECT_EQ(2 * a, Vector2i(4, 6));
    EXPECT_EQ(a / 2, Vector2i(1, 1));
}

TEST(Vector2iTests, ToXMVECTOR) {
    Vector2i v(3, -4);
    DirectX::XMVECTOR vec = v.ToXMVECTOR(0.0f);

    DirectX::XMFLOAT4 unpack;
    DirectX::XMStoreFloat4(&unpack, vec);
    EXPECT_FLOAT_EQ(unpack.x, 3.0f);
    EXPECT_FLOAT_EQ(unpack.y, -4.0f);
    EXPECT_FLOAT_EQ(unpack.z, 0.0f);
    EXPECT_FLOAT_EQ(unpack.w, 0.0f);
}

TEST(Vector2iTests, ConversionToXMINT2) {
    Vector2i v(7, -8);
    DirectX::XMINT2 dx = static_cast<DirectX::XMINT2>(v);
    EXPECT_EQ(dx.x, 7);
    EXPECT_EQ(dx.y, -8);
}

TEST(Vector2iTests, AssignFromXMINT2) {
    DirectX::XMINT2 dx(9, -10);
    Vector2i v;
    v = dx;
    EXPECT_EQ(v.x, 9);
    EXPECT_EQ(v.y, -10);
}

