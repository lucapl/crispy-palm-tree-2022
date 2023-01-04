#include "geneticAlgorithm.hpp"
#include "books.hpp"
#include "libraries.hpp"
#include "randomizer.hpp"
#include <algorithm>

using Generation = std::vector<Solution*>;

int GeneticAlgorithm::evaluate(Solution* sol){
    /*will be usefull for genetic algorithm (will add evaluation value for particular genotype).
		the evaluation value should be the same as the final score, if this genotype will be choosen as a solution (if D and B are correct)*/
    //int M, T, N, remainingDaysForScanningInThisLibrary, bookIterator, remainingBooksInLiblary;
    int finalScore = 0;
    //int theBook;
    bool* scanned = new bool[getB()];
    for (int i = 0; i < getB(); i++) {
        scanned[i] = false;
    }
    
    //Libraries* libs = new Libraries();
    //Books* books = new Books();

    //int LenGenotype = sol->numberOfLibs();
    //for(int libID : *sol->getLibs()){
    //    bookIterator = 0;
    //    Library* lib = Libraries::getLibByID(libID);
    //    D -= lib->getT();
    //    remainingDaysForScanningInThisLibrary = D;
    //    remainingBooksInLiblary = lib->getN();
    //    M = 0;
    //    while(remainingDaysForScanningInThisLibrary>0&&remainingBooksInLiblary>0){
    //        for(int j = M;M>=0;--j)
    //        {
    //            theBook = lib->getBookIDAt(bookIterator);
    //            if(scanned[theBook] == false)
    //            {
    //                finalScore += Books::getScore(theBook);
    //                scanned[theBook] = true;
    //            }
    //            remainingBooksInLiblary--;
    //            bookIterator++;
    //            if(remainingBooksInLiblary == 0)
    //            {
    //                break;
    //            }
    //        }
    //        remainingDaysForScanningInThisLibrary--;
    //    }
    //}

    std::vector<int>** booksPerLib = getBooksToBeScanned(sol);
    int dayLeftToScan = 0;
    int libsScanned = -1;
    int libScanned = 0;
    
    for (int day = 0; day < getD();day++) {
        Library* scannedLib = Libraries::getLibByID(sol->getLibIdByIndex(libScanned));
        if (dayLeftToScan <= 0 && scannedLib != NULL) {
            dayLeftToScan = scannedLib->getT();
            libsScanned++;
            libScanned++;
        }

        //scanning
        for (int libId = 0; libId < libsScanned;libId) {
            Library* lib = Libraries::getLibByID(sol->getLibIdByIndex(libId));
            int* booksToScan = lib->getMaxNextBooks(scanned);
            int i = 0;
            while (booksToScan[i] != NULL) {
                int bookId = booksToScan[i];
                finalScore += Books::getScore(bookId);
                scanned[bookId] = true;
                i++;
            }
        }

        dayLeftToScan--;
    }
    //for (int libId : *sol->getLibs()) {
    //    Library* lib = Libraries::getLibByID(libId);
    //    int daysOfScanning = lib->getT();
    //    for (int otherLibId = 0; otherLibId < libId; otherLibId++) {
    //        Library* otherLib = Libraries::getLibByID(otherLibId);
    //        

    //    }
    //}

    
    delete[] scanned;
    return finalScore;
}

Solution* GeneticAlgorithm::getBestSolution() {
    return bestSolution;
}

void GeneticAlgorithm::setBestSolution(Solution* contender) {
    if (getBestSolution() == NULL || contender->getEvaluation() > getBestSolution()->getEvaluation())
        bestSolution = contender;
}

void GeneticAlgorithm::evaluatePopulation(Generation* population) {
    for (Solution* sol : *population) {
        evaluate(sol);
    }
}

void GeneticAlgorithm::evaluatePopulation() {
    evaluatePopulation(getPopulation());
}

void GeneticAlgorithm::evolutionStep() {
    evaluatePopulation();
}

Solution* GeneticAlgorithm::selectBetter(Solution* sol1, Solution* sol2) {
    return sol1->getEvaluation() > sol2->getEvaluation() ? sol1:sol2;
}

Solution* GeneticAlgorithm::pickRandomSolution() {
    return pickRandomSolution(getPopulation());
}
Solution* GeneticAlgorithm::pickRandomSolution(Generation* population) {
    Randomizer random = Randomizer();
    return random.choose<Solution*,Generation&>(*population, population->size());
}

std::vector<Solution*>* GeneticAlgorithm::newGeneration() {
    Generation* newGeneration = new Generation();
    int days = 0;

    //Selection
    while(days < getD()){
        Solution *sol1, *sol2;
        sol1 = pickRandomSolution();
        do {
            sol2 = pickRandomSolution();
        }while (sol1->equals(sol2));
        newGeneration->push_back(selectBetter(sol1, sol2)->copy());//deepcopy
    }

    Randomizer random = Randomizer();

    //Mutation
    for (Solution* sol : *newGeneration) {
        if (random.roll(getPMutateLibs())) {
            sol->mutateLibs();
        }
        //if (random.roll(getPMutateBooks())) {
        //    sol->mutateBooks();
        //}
    }

    //Crossover
    //for (Solution* sol1 : *newGeneration) {
    //    Solution* sol2;
    //    do {
    //        sol2 = pickRandomSolution();
    //    } while (sol2->equals(sol1));
    //    newGeneration->
    //}



    evaluatePopulation(newGeneration);

    return newGeneration;
}

std::vector<int>** GeneticAlgorithm::getBooksToBeScanned(Solution* sol) {
    std::vector<int>** booksPerLib = new std::vector<int>*[sol->numberOfLibs()];
    for (int libId = 0; libId < sol->numberOfLibs();libId++) {
        booksPerLib[libId] = new std::vector<int>();
    }

    for (int bookId = 0; bookId < sol->numberOfBooks();bookId++) {
        int libId = sol->getLibIdAssignedTo(bookId);
        booksPerLib[libId]->push_back(bookId);
        //Library* lib = Libraries::getLibByID(libId);
    }

    for (int libId = 0; libId < sol->numberOfLibs();libId++) {
        std::vector<int>* booksAtLib = booksPerLib[libId];
        std::sort(booksAtLib->begin(),booksAtLib->end(),Books::compareByScore);
    }

    return booksPerLib;
}

int GeneticAlgorithm::getD() {
    return D;
}
int GeneticAlgorithm::getB() {
    return B;
}
Generation* GeneticAlgorithm::getPopulation() {
    return population;
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