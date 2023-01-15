#include "geneticAlgorithm.hpp"
#include "books.hpp"
#include "libraries.hpp"
#include "sus.hpp"
#include "randomizer.hpp"
#include "timer.hpp"
#include <algorithm>

GeneticAlgorithm::GeneticAlgorithm(unsigned int popsize,unsigned int D, unsigned int B, unsigned int L,float pCrossover,float pMutation) : popsize(popsize), D(D), B(B),L(L) {
    this->bestSolution = new Solution(1);
    this->population = new Population();
    this->pMutateLibs = pMutation;
    this->pCrossover = pCrossover;

    bestValues = new std::vector<int>();
}

void cleanOld(Population& pop) {
    //std::sort(pop.begin(), pop.end());
    //pop.erase(std::unique(pop.begin(), pop.end()), pop.end());
    for (Solution* sol : pop) {
        if (sol != NULL && !sol->isInNew()) {
            delete sol;
        }
    }
}

void cleanPop(Population& pop) {
    pop.erase(std::remove_if(pop.begin(), pop.end(),
        [](Solution* sol) -> bool {return sol->isInNew();}),
        pop.end());
    std::sort(pop.begin(), pop.end());
    pop.erase(std::unique(pop.begin(), pop.end()), pop.end());
    for (Solution* sol : pop) {
        delete sol;
    }
    pop.clear();
    delete& pop;
}


GeneticAlgorithm::~GeneticAlgorithm() {
    cleanPop(*getPopulation());
    for (Solution* sol : *getPopulation()) {
        delete sol;
    }
    getPopulation()->clear();
    delete getPopulation();
    delete getBestSolution();
}

//
//int GeneticAlgorithm::evaluate(Solution* sol){
//    /*will be usefull for genetic algorithm (will add evaluation value for particular genotype).
//		the evaluation value should be the same as the final score, if this genotype will be choosen as a solution (if D and B are correct)*/
//    //int M, T, N, remainingDaysForScanningInThisLibrary, bookIterator, remainingBooksInLiblary;
//    int finalScore = 0;
//    //int theBook;
//    bool* scanned = new bool[getB()];
//    for (int i = 0; i < getB(); i++) {
//        scanned[i] = false;
//    }
//    
//    //Libraries* libs = new Libraries();
//    //Books* books = new Books();
//
//    //int LenGenotype = sol->numberOfLibs();
//    //for(int libID : *sol->getLibs()){
//    //    bookIterator = 0;
//    //    Library* lib = Libraries::getLibByID(libID);
//    //    D -= lib->getT();
//    //    remainingDaysForScanningInThisLibrary = D;
//    //    remainingBooksInLiblary = lib->getN();
//    //    M = 0;
//    //    while(remainingDaysForScanningInThisLibrary>0&&remainingBooksInLiblary>0){
//    //        for(int j = M;M>=0;--j)
//    //        {
//    //            theBook = lib->getBookIDAt(bookIterator);
//    //            if(scanned[theBook] == false)
//    //            {
//    //                finalScore += Books::getScore(theBook);
//    //                scanned[theBook] = true;
//    //            }
//    //            remainingBooksInLiblary--;
//    //            bookIterator++;
//    //            if(remainingBooksInLiblary == 0)
//    //            {
//    //                break;
//    //            }
//    //        }
//    //        remainingDaysForScanningInThisLibrary--;
//    //    }
//    //}
//
//    std::vector<int>** booksPerLib = getBooksToBeScanned(sol);
//    int dayLeftToScan = 0;
//    int libsScanned = -1;
//    int libIdScanned = 0;
//
//    unsigned int l = sol->getNumberOfLibs();
//    unsigned int* lastScannedBookId = new unsigned int[l];
//    //unsigned int* Ms = new unsigned int[l];
//    for (int solLibId = 0; solLibId < l; solLibId++) {
//        lastScannedBookId[solLibId] = -1;
//        //int m = Libraries::getLibByID(sol->getLibIdByIndex(solLibId))->getM();
//        //Ms[solLibId] = m;
//    }
//    
//    for (int day = 0; day < getD();day++) {
//        Library* scannedLib = Libraries::getLibByID(sol->getLibIdByIndex(libIdScanned));
//        if (dayLeftToScan == 0) {
//            libsScanned++;
//            libIdScanned++;
//            if (scannedLib != NULL) {
//                dayLeftToScan = scannedLib->getT();
//            }
//        }
//
//        //scanning
//        for (int solLibId = 0; solLibId < libsScanned;solLibId++) {
//            Library* lib = Libraries::getLibByID(sol->getLibIdByIndex(solLibId));
//            unsigned int zero = 0;
//            //int* booksToScan = lib->getMaxNextBooks(scanned, zero);
//            int m = lib->getM();
//            for (int i = 0; i < m; i++) {
//                if (lastScannedBookId[solLibId] >= 0) {
//                    break;
//                }
//                int bookId = booksPerLib[solLibId]->at(lastScannedBookId[solLibId]++);
//                finalScore += Books::getScore(bookId);
//            }
//            /*while (i < m && booksToScan[i] != -1) {
//                int bookId = booksToScan[i];
//                finalScore += Books::getScore(bookId);
//                scanned[bookId] = true;
//                i++;
//            }*/
//            //delete[] booksToScan;
//        }
//
//        dayLeftToScan--;
//    }
//    //for (int libId : *sol->getLibs()) {
//    //    Library* lib = Libraries::getLibByID(libId);
//    //    int daysOfScanning = lib->getT();
//    //    for (int otherLibId = 0; otherLibId < libId; otherLibId++) {
//    //        Library* otherLib = Libraries::getLibByID(otherLibId);
//    //        
//
//    //    }
//    //}
//    for (int i = 0; i < getL(); i++) {
//        booksPerLib[i]->clear();
//        delete booksPerLib[i];
//    }
//    delete[] booksPerLib;
//    delete[] scanned;
//    return finalScore;
//}

int GeneticAlgorithm::evaluate(Solution* sol) {
    sol->evaluate(getD(), getB());
    return sol->getEvaluation();
}

Solution* GeneticAlgorithm::getBestSolution() {
    return bestSolution;
}

void GeneticAlgorithm::setBestSolution(Solution* contender) {
    if (getBestSolution() == NULL || contender->getEvaluation() > getBestSolution()->getEvaluation()) {
        delete bestSolution;
        bestSolution = contender->copy(); // to ensure it wont get deleted
        setSolutionChange(true);
        bestValues->push_back(bestSolution->getEvaluation());
    }
}

// function copies the solution under pointer
void GeneticAlgorithm::add(Solution* sol) {
    getPopulation()->push_back(sol);//copying to be optimized
}

Solution* GeneticAlgorithm::selectBetter(Solution* sol1, Solution* sol2) {
    return sol1->getEvaluation() > sol2->getEvaluation() ? sol1:sol2;
}

Solution* GeneticAlgorithm::pickRandomSolution() {
    return pickRandomSolution(getPopulation());
}
Solution* GeneticAlgorithm::pickRandomSolution(Population* population) {
    Randomizer random = Randomizer();
    return random.choose<Solution*,Population&>(*population, (int)population->size());
}

// Tournament selection would take too long with sampling using Fisher-Yates shuffle
// Considered Stochastic Remainder with replacement method
// Settled down for the Stochastic Universal Sampling (SUS)
Population* GeneticAlgorithm::select(Sampler* sampler,Population* pop) {
    return sampler->sample(pop,getPopSize());
}

Population* GeneticAlgorithm::select(Population* pop) {
    Sampler* sampler = new SUSampling();
    Population* newPop = select(sampler,pop);
    delete sampler;
    return newPop;
}

void addToChild(Solution* child, bool* libsInChild, int libId1) {
    if (!libsInChild[libId1]) {
        child->addLibId(libId1);
        libsInChild[libId1] = true;
    }
}

// THIS WILL NOT FREE THE MEMORY!
void removeOneOccurence(Population* pop, Solution* sol) {
    std::remove(pop->begin(), pop->end(), sol);
    pop->erase(pop->end());
}

// swap mutation
void GeneticAlgorithm::mutate(int i, Population* pop) {
    Solution* sol = pop->at(i);
    Solution* newSol = sol->copy();
    newSol->mutateLibs(getD());
    //std::swap((*pop)[i], newSol);
    pop->push_back(newSol);
    //removeOneOccurence(pop,sol);
}

// Alternating position crossover
void GeneticAlgorithm::crossover(int parent1i,int parent2i, Population* pop) {
    Solution* parent1 = pop->at(parent1i);
    Solution* parent2 = pop->at(parent2i);
    Solution* child1 = new Solution(getB());
    Solution* child2 = new Solution(getB());
    bool* child1Libs = new bool[getL()]();
    bool* child2Libs = new bool[getL()]();

    //min n of libs
    Solution* longer = parent1;
    int smallerN = parent2->getNumberOfLibs();
    if (parent1->getNumberOfLibs() < parent2->getNumberOfLibs()) {
        longer = parent2;
        smallerN = parent1->getNumberOfLibs();
    }
    for (int i = 1; i < smallerN; i++) {
        int sol1Lib1, sol1Lib2, sol2Lib1, sol2Lib2;
        sol1Lib1 = parent1->getLibIdByIndex(i-1);
        sol1Lib2 = parent1->getLibIdByIndex(i);
        sol2Lib1 = parent2->getLibIdByIndex(i - 1);
        sol2Lib2 = parent2->getLibIdByIndex(i);
        addToChild(child1, child1Libs,sol1Lib1);
        addToChild(child1, child1Libs, sol2Lib2);
        addToChild(child2, child2Libs, sol2Lib1);
        addToChild(child2, child2Libs, sol1Lib2);
    }
    for (int i = smallerN; i < longer->getNumberOfLibs();i++){
        int libId = longer->getLibIdByIndex(i);
        addToChild(child1, child1Libs, libId);
        addToChild(child2, child2Libs, libId);
    }

    pop->push_back(child1);
    pop->push_back(child2);
    //std::swap(child1, (*pop)[parent1i]);
    //std::swap(child2, (*pop)[parent2i]);
    /*pop->push_back(child1);
    pop->push_back(child2);

    removeOneOccurence(pop, parent1);
    removeOneOccurence(pop, parent2);*/

    delete[] child1Libs;
    delete[] child2Libs;
}

// returns a new Population* that needs to be deleted later
Population* GeneticAlgorithm::newGeneration() {
    Randomizer random = Randomizer();
    Population* crossedOverPop = new Population();

    //uses SUS algorithm 
    Population* newGeneration = select(getPopulation());

    //Crossover
    random.shuffle<Population&>(*newGeneration, newGeneration->size());
    int n = newGeneration->size();
    for (int i = 1; i < n;i+=2) {
        if (!random.roll(getPCrossover())) {
            continue;
        }
        crossover(i-1,i, newGeneration);
    }
    /*for (Solution* sol1 : *newGeneration) {
        if(!random.roll(getPCrossover())){
            continue;
        }
        Solution* sol2;
        do {
            sol2 = pickRandomSolution(newGeneration);
        } while (false);
        crossover(sol1, sol2,newGeneration);
    }*/

    //Mutation
    for (int i = 0;i < n;i++) {
        if (random.roll(getPMutateLibs())) {
            mutate(i, newGeneration);
        }
        //if (random.roll(getPMutateBooks())) {
        //    sol->mutateBooks();
        //}
    }
    
    // Elitism
    newGeneration->push_back(getBestSolution()->copy());

    // Evaluate
    evaluatePopulation(newGeneration);

    // Sort according to evaluation
    std::sort(newGeneration->begin(), newGeneration->end(), [](Solution* sol1, Solution* sol2) -> bool {return sol1->getEvaluation() > sol2->getEvaluation();});

    // Reduce to popsize
    for (auto it = newGeneration->begin();it < newGeneration->begin() + getPopSize()+1; it++) {
        (*it)->setInNew(true);
    }
    cleanOld(*newGeneration);
    newGeneration->erase(newGeneration->begin()+getPopSize()+1,newGeneration->end());

    return newGeneration;
}

void GeneticAlgorithm::evaluatePopulation(Population* population) {
    for (Solution* sol : *population) {
        if (sol->getEvaluation() < 0) {
            sol->setEvaluation(evaluate(sol));
        }
        setBestSolution(sol);
    }
}

void GeneticAlgorithm::evaluatePopulation() {
    evaluatePopulation(getPopulation());
}

std::vector<int>** GeneticAlgorithm::getBooksToBeScanned(Solution* sol) {
    std::vector<int>** booksPerLib = new std::vector<int>*[sol->getNumberOfLibs()];
    for (int libId = 0; libId < sol->getNumberOfLibs();libId++) {
        booksPerLib[libId] = new std::vector<int>();
    }

    for (int bookId = 0; bookId < sol->getNumberOfBooks();bookId++) {
        int libId = sol->getLibIdAssignedTo(bookId);
        if (libId < 0) {
            break;
        }
        booksPerLib[libId]->push_back(bookId);
        //Library* lib = Libraries::getLibByID(libId);
    }

    for (int libId = 0; libId < sol->getNumberOfLibs();libId++) {
        std::vector<int>* booksAtLib = booksPerLib[libId];
        std::sort(booksAtLib->begin(),booksAtLib->end(),Books::compareByScore);
    }

    return booksPerLib;
}

void GeneticAlgorithm::evolutionStep() {
    evaluatePopulation();
    Population* newPop = newGeneration();
    cleanPop(*getPopulation());
    setPopulation(newPop);
    for (Solution* sol : *getPopulation()) {
        sol->setInNew(false);
    }
}

void GeneticAlgorithm::evolve(unsigned int maxIters, unsigned int maxNoImprovIters) {
    unsigned int noImprovIters = 0;
    for (int iter = 0; iter < maxIters && noImprovIters < maxNoImprovIters; iter++, noImprovIters++) {
        evolutionStep();

        if (hasSolutionChanged()) {
            noImprovIters = 0;
            setSolutionChange(false);
        }
        if (Timer::shouldEnd()) {
            break;
        }
    }
}
//copies solution copies of times
void GeneticAlgorithm::initializePopulation(Solution* sol, int copies) {
    for (int _ = 0; _ < copies;_++) {
        add(sol);
    }
}
//copies solution popsize of times
void GeneticAlgorithm::initializePopulation(Solution* sol) {
    initializePopulation(sol, getPopSize());
}

void GeneticAlgorithm::randomPopulation(int copies) {
    int* libs = new int[getL()]();
    for(int libId = 0; libId < getL(); libId++){
        libs[libId] = libId;
    }
    Randomizer rand = Randomizer();
    for (int i = 0;i < copies;i++) {
        rand.shuffle<int*>(libs, (int)getL());
        Solution* newSol = new Solution(getB());
        for(int libId = 0;libId < getL() && newSol->getTimeToRegister() < getD();libId++) {
            newSol->addLibId(libs[libId]);
        }
        add(newSol);
    }
    delete[] libs;
}
void GeneticAlgorithm::randomPopulation() {
    randomPopulation(getPopSize());
}
bool GeneticAlgorithm::hasSolutionChanged() {
    return solutionChange;
}

void GeneticAlgorithm::setSolutionChange(bool b) {
    solutionChange = b;
}

void GeneticAlgorithm::setPopulation(Population* pop) {
    population = pop;
}

unsigned int GeneticAlgorithm::getD() {
    return D;
}
unsigned int GeneticAlgorithm::getB() {
    return B;
}
unsigned int GeneticAlgorithm::getL() {
    return L;
}

Population* GeneticAlgorithm::getPopulation() {
    return population;
}
unsigned int GeneticAlgorithm::getPopSize() {
    return popsize;
}

float GeneticAlgorithm::getPCrossover() {
    return pCrossover;
}
float GeneticAlgorithm::getPMutateBooks() {
    return pMutateBooks;
}
float GeneticAlgorithm::getPMutateLibs() {
    return pMutateLibs;
}
