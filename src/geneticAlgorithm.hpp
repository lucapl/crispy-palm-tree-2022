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
		int evaluate(Solution*,int,int);//simulate the registration, scanning and shipping
		
		Solution** cross(Solution*,Solution*);
		Solution* mutate(Solution*);
		std::vector<Solution*>* newGeneration();
};