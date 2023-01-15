#pragma once
#include "sampler.hpp"

// suSampling supports divergence of a population
class SUSampling: public Sampler {
	public:
		Population* sample(Population* pop, int size);
	private:
		Population* rouletteWheelSelection(Population* pop, int size, double* points);
		Population* sus(Population* pop, int size);

};