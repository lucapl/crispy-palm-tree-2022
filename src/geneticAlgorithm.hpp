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
		Solution* bestSolution;
		int D;
		int B;
	public:
		GeneticAlgorithm(int D, int B);
		~GeneticAlgorithm();

		int evaluate(Solution*);//simulate the registration, scanning and shipping
		
		Solution** cross(Solution*,Solution*);
		Solution* mutate(Solution*);
		std::vector<Solution*>* newGeneration();
		Solution* selectBetter(Solution*, Solution*);
		Solution* pickRandomSolution();
		Solution* pickRandomSolution(std::vector<Solution*>* population);

		void evaluatePopulation(std::vector<Solution*>* population);
		void evaluatePopulation();

		void evolutionStep();

		void setPopulation(std::vector<Solution*>*);
		void setBestSolution(Solution*);

		std::vector<int>** getBooksToBeScanned(Solution*);
		std::vector<Solution*>* getPopulation();
		Solution* getBestSolution();
		float getPMutateBooks();
		float getPMutateLibs();
		float getPCrossover();
		int getD();
		int getB();
};