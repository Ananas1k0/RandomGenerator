#pragma once
#include <random>
#include <chrono>
#include "../RandomGenerator/TRandomNumberGenerator.h"

#define MAX_RANDOM_VALUE 100000.0

class BernoulliGenerator : public TRandomNumberGenerator
{
public:

	BernoulliGenerator(const double &p)
	{
		boundary = (1 - p) * MAX_RANDOM_VALUE;
	}

	~BernoulliGenerator()
	{}

	double Generate() const
	{
		std::default_random_engine generator;

		generator.seed(std::chrono::system_clock::now().time_since_epoch().count());

		std::uniform_real_distribution<> distribution(0.0, MAX_RANDOM_VALUE);

		return distribution(generator) > boundary;
	}

private:

	unsigned long long boundary;
};
