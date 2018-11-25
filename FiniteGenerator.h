#pragma once
#include <random>
#include <chrono>
#include <math.h>
#include <map>
#include "../RandomGenerator/TRandomNumberGenerator.h"

class FiniteGenerator : public TRandomNumberGenerator
{
public:

	FiniteGenerator(const std::map<double, double> &_p_to_xi) : p_to_xi{ _p_to_xi }
	{}

	~FiniteGenerator()
	{}

	double Generate() const
	{
		std::default_random_engine generator;

		generator.seed(std::chrono::system_clock::now().time_since_epoch().count());

		std::uniform_real_distribution<> distribution(0.0, 1.0);

		//generating of the random values from 0 to 1. It will be used for finding of the nearlest events
		double rand = distribution(generator);

		double last = 0;

		//http://stratum.ac.ru/education/textbooks/modelir/lection24.html Метод ступенчатой аппроксимации
		for (std::map<double, double>::const_iterator it = p_to_xi.begin(); it != p_to_xi.end(); ++it)
		{
			if (rand > it->first) {
				rand = rand - it->first;
				last = it->second;
			}
			else
				return it->second;
		}

		return last;
	}

private:

	//ordered map used because propabilities will be sorted from least to biggest.
	std::map<double, double> p_to_xi;
}; 
