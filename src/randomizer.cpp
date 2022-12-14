#include "randomizer.hpp"

std::default_random_engine Randomizer::generator = std::default_random_engine();

template<typename T,class Container>// for any container, which can be accessed through []
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
Int Randomizer::getRandomInt(Int a, Int b) {
    std::uniform_int_distribution<Int> dist(a, b);
    return dist(generator);
}