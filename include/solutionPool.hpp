#pragma once
#include "solution.hpp"
#include <vector>

class SolutionPool {
public:
    static SolutionPool* getInstance();
    Solution* getSolution();
    void returnSolution(Solution* sol);
    void setPoolSize(int size);
private:
    SolutionPool() {};
    SolutionPool(SolutionPool const&) = delete;
    int poolSize;
    std::vector<Solution*>* pool;
    static SolutionPool* instance;
};