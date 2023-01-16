#include "solutionPool.hpp"

SolutionPool* SolutionPool::instance = NULL;

Solution* SolutionPool::getSolution() {
    if (pool->empty()) {
        return new Solution();
    }
    else {
        Solution* sol = pool->back();
        pool->pop_back();
        sol->defaultState();
        sol->returned = false;
        return sol;
    }
}

void SolutionPool::returnSolution(Solution* sol) {
    if (pool->size() < poolSize) {
        pool->push_back(sol);
        sol->returned = true;
    }
    else {
        delete sol;
    }
}
void SolutionPool::setPoolSize(int size) {
    poolSize = size;
}

SolutionPool* SolutionPool::getInstance() {
    if (!instance) {
        instance = new SolutionPool();
        instance->pool = new std::vector<Solution*>();
        instance->poolSize = 50;
    }
    return instance;
}
