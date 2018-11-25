// RandomGenerator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "../RandomGenerator/PoissonGenerator.h"
#include "../RandomGenerator/BernoulliGenerator.h"
#include "../RandomGenerator/GeometricGenerator.h"
#include "../RandomGenerator/FiniteGenerator.h"
#include "../RandomGenerator/RandomGeneratorFabric.h"

#include <iostream>
#include <map>

int main()
{
	std::map<double, double> p_to_xi;

	p_to_xi[0.05] = 1;
	p_to_xi[0.1] = 2;
	p_to_xi[0.15] = 3;
	p_to_xi[0.2] = 4;
	p_to_xi[0.25] = 5;
	p_to_xi[0.13] = 6;
	p_to_xi[0.12] = 7;

	double p_bernoulli = 0.5;

	double p_geometric = 0.1;

	double lambda_poisson = 3;

	std::unique_ptr<TRandomNumberGenerator> fg = RandonGeneratorFabric::getGenerator("finite", p_to_xi);
	std::unique_ptr<TRandomNumberGenerator> pg = RandonGeneratorFabric::getGenerator("poisson", lambda_poisson);
	std::unique_ptr<TRandomNumberGenerator> bg = RandonGeneratorFabric::getGenerator("bernoulli", p_bernoulli);
	std::unique_ptr<TRandomNumberGenerator> gg = RandonGeneratorFabric::getGenerator("geometric", p_geometric);

	double average100000 = 0;
	int i;

	if (bg != NULL) {
		for (i = 0; i < 10000; i++) {
			average100000 += bg->Generate();
		}


		std::cout << "bernoulli average100000 = " << average100000 / 10000 << std::endl;
		std::cout << "bernoulli theoretic average = " << p_bernoulli << std::endl;
	}

	average100000 = 0;

	if (pg != NULL) {
		for (i = 0; i < 10000; i++) {
			average100000 += pg->Generate();
		}


		std::cout << "poisson average100000 = " << average100000 / 10000 << std::endl;
		std::cout << "poisson theoretic average = " << lambda_poisson << std::endl;
	}

	average100000 = 0;

	if (fg != NULL) {
		for (i = 0; i < 10000; i++) {
			average100000 += fg->Generate();
		}
//		std :: map <double, double> ::iterator it = p_to_xi.begin();
		double sum = 0;
		for (auto it = p_to_xi.begin(); it != p_to_xi.end(); ++it) {
			sum = sum + (it->first) * (it->second);
		}


		std::cout << "finite average100000 = " << average100000 / 10000 << std::endl;
		std::cout << "finite theoretic average = " << sum << std::endl;
	}

	average100000 = 0;

	if (gg != NULL) {
		for (i = 0; i < 10000; i++) {
			average100000 += gg->Generate();
		}


		std::cout << "geometric average100000 = " << average100000 / 10000 << std::endl;
		std::cout << "geometric theoretic average = " << 1/ p_geometric << std::endl;
	}

}
