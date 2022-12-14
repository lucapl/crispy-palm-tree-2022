#pragma once

class Randomizer{
	private:
		static std::default_random_engine generator;
	public:
		Randomizer();
		template <typename T, typename Container>
		T choose(Container,int);
		bool roll(float p);
		std::default_random_engine* getGenerator();
		template<typename Real = float>
		Real getRandomReal(Real a, Real b);
		template<typename Int = int>
		Int getRandomInt(Int a, Int b);
		
};
