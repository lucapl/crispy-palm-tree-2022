#include "randomizer.hpp"
#include "solution.hpp"

std::default_random_engine Randomizer::generator = std::default_random_engine();

template<typename T,class Container>
// for any container, which can be accessed through []
T Randomizer::choose(Container container, int n) {
    std::uniform_int_distribution<int> dist(0, n-1);
    return container[dist(generator)];
}

bool Randomizer::roll(float probability) {
    std::uniform_real_distribution<float> dist(0.0, 1.0);
    return dist(generator) < probability;
}

std::default_random_engine* Randomizer::getGenerator() {
    return &generator;
}

template<typename Real>
Real Randomizer::getRandomReal(Real a, Real b) {
    std::uniform_real_distribution<Real> dist(a, b);
    return dist(generator);
}

template<typename Int>
Int Randomizer::getRandomInt(Int a, Int b) { // closed interval [a,b]
    std::uniform_int_distribution<Int> dist(a, b);
    return dist(generator);
}

// shuffling using Fisher-Yates algorithm - O(n)
// too long for selection
template<typename Container>
void Randomizer::shuffle(Container cont, int n) {
    for (int i = n - 1;i >= 1;i--) {
        int j = getRandomInt<>(0, i);
        std::swap(cont[i],cont[j]);
        /*auto temp = cont[i];
        cont[i] = cont[j];
        cont[j] = temp;*/
    }
}

std::set<int>::iterator Randomizer::randomFromSet(std::set<int>* set) {
    int k = getRandomInt<>(0, (int)set->size() - 1);
    std::set<int>::iterator it = set->begin();
    std::advance(it, k);
    return it;
}

Randomizer::Randomizer() {}


template int Randomizer::getRandomInt(int, int);
template unsigned int Randomizer::getRandomInt(unsigned int, unsigned int);
template float Randomizer::getRandomReal(float, float);
template double Randomizer::getRandomReal(double, double);
template std::string Randomizer::choose<std::string>(std::string* array, int n);
template std::string* Randomizer::choose<std::string*>(std::vector<std::string*>& vector, int n);
using Population = std::vector<Solution*>;
template Solution* Randomizer::choose<Solution*>(Population&, int);
template int Randomizer::choose<int>(std::vector<int>&, int);
template void Randomizer::shuffle<>(Population&, int);
template void Randomizer::shuffle<>(int*, int);