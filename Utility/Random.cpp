#include "Random.h"
#include <random>

Random::Random()
{
	std::random_device rd;
	m_generator.seed(rd());
}

Random::~Random() {}

int Random::GetIntIE(int nLowBound, int nHighBound)
{
	std::uniform_int_distribution<int> distribution(nLowBound, nHighBound);
	return distribution(m_generator);
}

int Random::GetIntII(int nLowBound, int nHighBound)
{
	return GetIntIE(nLowBound, nHighBound + 1);
}

float Random::GetFloatIE(float nLowBound, float nHighBound)
{
	std::uniform_real_distribution<float> distribution(nLowBound, nHighBound);
	return distribution(m_generator);
}
