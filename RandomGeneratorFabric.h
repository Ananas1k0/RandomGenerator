#pragma once

#include <string>
#include <math.h> 
#include "../RandomGenerator/TRandomNumberGenerator.h"
#include "../RandomGenerator/PoissonGenerator.h"
#include "../RandomGenerator/BernoulliGenerator.h"
#include "../RandomGenerator/GeometricGenerator.h"
#include "../RandomGenerator/FiniteGenerator.h"

class RandonGeneratorFabric
{
public:

	RandonGeneratorFabric()
	{}

	~RandonGeneratorFabric()
	{}

	static std::unique_ptr<TRandomNumberGenerator> getGenerator(const std::string &type, const double &param)
	{
		if (type.empty())
			return NULL;

		if (type.compare("bernoulli") == 0) {
			//p should be between [0;1]
			if (param < 0 || param > 1)
				return NULL;

			return std::make_unique<BernoulliGenerator>(param);
		}
		else if (type.compare("geometric") == 0) {
			//p should be between [0;1]
			if (param < 0 || param > 1)
				return NULL;

			return std::make_unique<GeometricGenerator>(param);
		}
		else if (type.compare("poisson") == 0) {
			//lamb should be > 0
			if (param < 0)
				return NULL;

			return std::make_unique<PoissonGenerator>(param);
		}

		return NULL;
	}

	static std::unique_ptr<TRandomNumberGenerator> getGenerator(const std::string &type, const std::map<double, double> &_p_to_xi)
	{
		if (type.empty() || _p_to_xi.empty())
			return NULL;

		double p_sum = 0.0;

		//every pi should be between [0;1]
		for (std::map<double, double>::const_iterator it = _p_to_xi.begin(); it != _p_to_xi.end(); ++it)
		{
			if (it->first < 0 || it->first > 1)
				return NULL;

			p_sum += it->first;
		}

		//sum of pi should be 1
		if (round(p_sum) != 1)
			return NULL;

		if (type.compare("finite") == 0)
			return std::make_unique<FiniteGenerator>(_p_to_xi);

		return NULL;
	}
};
