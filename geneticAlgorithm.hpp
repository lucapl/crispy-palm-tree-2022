#pragma once
#include "solution.hpp"
#include "library.hpp"
#include <vector>

class GeneticAlgorithm {
	private:
		std::vector<Solution*>* population;
		float pMutateBooks;
		float pMutateLibs;
		float pCrossover;
	public:
		int evaluate(Solution*);//simulate the registration, scanning and shipping
		std::vector<Solution*>* newGeneration();
};