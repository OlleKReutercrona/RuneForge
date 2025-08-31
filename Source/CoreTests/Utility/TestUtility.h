#pragma once
#include <random>

namespace {
	constexpr float gFloatMargin = 0.00001f;
}

class TestUtility {
public:
	TestUtility();

	float GetRandomFloat(float aMin = -10000.0f, float aMax = 10000.0f);
	double GetRandomDouble(double aMin = -10000.0, double aMax = 10000.0);
	int GetRandomInt(int aMin = -10000, int aMax = 10000);
private:
	std::mt19937 mRandomEngine;
};