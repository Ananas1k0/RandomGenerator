#pragma once
#include <random>
#include <chrono>
#include <math.h>
#include "../RandomGenerator/TRandomNumberGenerator.h"

class GeometricGenerator : public TRandomNumberGenerator
{
public:

	GeometricGenerator(const double &p)
	{
		rate = -log(1 - p);
	}

	~GeometricGenerator()
	{}

	double Generate() const
	{
		std::default_random_engine generator;

		generator.seed(std::chrono::system_clock::now().time_since_epoch().count());

		std::exponential_distribution<double> distribution(rate);

		return floor(distribution(generator));
	}

private:

	double rate;
};
