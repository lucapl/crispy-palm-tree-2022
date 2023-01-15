#pragma once
#include "solution.hpp"
using Population = std::vector<Solution*>;
//sampler interface
class Sampler {
	public:
		// this function returns a population initiated using new
		virtual Population* sample(Population* pop, int size) = 0;
};