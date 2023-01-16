#pragma once
#include "sus.hpp"
#include "solution.hpp"
#include "solutionPool.hpp"
#include "library.hpp"
#include <vector>

using Population = std::vector<Solution*>;

class GeneticAlgorithm {
	private:
		Population* population;
		const unsigned int popsize;

		float pMutateBooks;
		float pMutateLibs;
		float pCrossover;
		Solution* bestSolution;
		bool solutionChange;
		const unsigned int D;
		const unsigned int B;
		const unsigned int L;

		
	public:
		SolutionPool* solutionPool;
		GeneticAlgorithm(unsigned int popsize, unsigned int D, unsigned int B,unsigned int L, float pCrossover,float pMutation);
		~GeneticAlgorithm();

		std::vector<int>* bestValues;

		void initializePopulation(Solution* sol, int copies);
		void initializePopulation(Solution* sol);
		void randomPopulation(int copies);
		void randomPopulation();

		int evaluate(Solution*);//simulate the registration, scanning and shipping
		
		void crossover(int,int,Population*);
		void mutate(int,Population*);

		Population* newGeneration();
		Population* select(Sampler* sampler,Population* pop);
		Population* select(Population* pop);

		Solution* selectBetter(Solution*, Solution*);
		Solution* pickRandomSolution();
		Solution* pickRandomSolution(Population* population);

		void evaluatePopulation(Population* population);
		void evaluatePopulation();

		void evolutionStep();

		void evolve(unsigned int maxIters,unsigned int noImprovIters);

		void add(Solution* sol);

		//setters

		void setPopulation(Population*);
		void setBestSolution(Solution*);
		void setSolutionChange(bool);

		//getters

		std::vector<int>** getBooksToBeScanned(Solution*);
		Population* getPopulation();
		Solution* getBestSolution();
		float getPMutateBooks();
		float getPMutateLibs();
		float getPCrossover();
		unsigned int getD();
		unsigned int getB();
		unsigned int getL();
		unsigned int getPopSize();
		bool hasSolutionChanged();
};