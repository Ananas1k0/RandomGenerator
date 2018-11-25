#pragma once
#include <random>
#include <chrono>
#include "../RandomGenerator/TRandomNumberGenerator.h"

class PoissonGenerator : public TRandomNumberGenerator
{
public:

	PoissonGenerator(const double &_lamb) : lamb{ _lamb }
	{}

	~PoissonGenerator()
	{}

	double Generate() const
	{
		int k = -1;

		double s = 0;

		std::default_random_engine generator;

		generator.seed(std::chrono::system_clock::now().time_since_epoch().count());

		std::exponential_distribution<double> distribution(1);

		do {
			s += distribution(generator);

			++k;
		} while (s < lamb);

		return k;
	}

private:

	double lamb;
};