#include "TestUtility.h"

TestUtility::TestUtility() : mRandomEngine(6) {}

float TestUtility::GetRandomFloat(float aMin, float aMax) {
	std::uniform_real_distribution<float> rnd(aMin, aMax);
	return rnd(mRandomEngine);
}

double TestUtility::GetRandomDouble(double aMin, double aMax) {
	std::uniform_real_distribution<double> rnd(aMin, aMax);
	return rnd(mRandomEngine);
}

int TestUtility::GetRandomInt(int aMin, int aMax) {
	std::uniform_int_distribution<int> rnd(aMin, aMax);
	return rnd(mRandomEngine);
}