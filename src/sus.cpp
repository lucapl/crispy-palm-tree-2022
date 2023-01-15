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
		points[i] = start + i * pointerDistance;
	}

	return rouletteWheelSelection(pop,size,points);
}


Population* SUSampling::rouletteWheelSelection(Population* pop,int size, double* points) {
	Population* keep = new Population();
	
	for (int pI = 0; pI < size; pI++) {
		double point = points[pI];
		unsigned int I = 0;
		unsigned int fitnessSumToI;
		
		do {
			fitnessSumToI = 0;
			I++;

			for (Solution* sol:*pop) {
				fitnessSumToI += sol->getEvaluation();
			}
			keep->push_back(pop->at(I));
		} while (fitnessSumToI < point);
	}

	delete[] points;
	return keep;
}