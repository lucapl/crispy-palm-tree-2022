#include "randomizer.hpp"
#include "sus.hpp"

Population* SUSampling::sample(Population* pop, int size) {
	return sus(pop,size);
}

// this function returns a new vector that needs to be deleted
Population* SUSampling::sus(Population* pop, int size) {
	unsigned int totalEvaluation = 0;
	for (Solution* sol : *pop) {
		totalEvaluation += sol->getEvaluation();
	}

	double pointerDistance = (double)(totalEvaluation) / size;

	Randomizer rand = Randomizer();
	double start = rand.getRandomReal<double>(0, pointerDistance);

	double* points = new double[size]; // deleted in RWS function
	for (int i = 0; i < size; i++) {
		points[i] = start + (i * pointerDistance);
	}

	return rouletteWheelSelection(pop,size,points);
}

unsigned int fitnessSum(Population* pop, int I) {
	unsigned int fitnessSumToI = 0;
	for (int i = 0; i < I;i++) {
		Solution* sol = pop->at(i);
		fitnessSumToI += sol->getEvaluation();
	}
	return fitnessSumToI;
}

Population* SUSampling::rouletteWheelSelection(Population* pop,int size, double* points) {
	Population* keep = new Population();
	
	std::sort(pop->begin(), pop->end(), [](Solution* sol1, Solution* sol2) -> bool {return sol1->getEvaluation() > sol2->getEvaluation();});
	for (int pI = 0; pI < size; pI++) {
		double point = points[pI];
		int I = -1;
		do {
			I++;
		} while (I + 1 < pop->size() && fitnessSum(pop, I+1) < point);
		keep->push_back(pop->at(I));
	}

	delete[] points;
	return keep;
}