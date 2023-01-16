#include "solution.hpp"
#include "books.hpp"
#include "libraries.hpp"
#include "randomizer.hpp"
#include <algorithm>
#include <random>
#include <limits>
#include <cmath>
#include "solutionPool.hpp"
using namespace std;
using LibCombination = std::vector<int>;
using LibSet = std::set<int>;

Solution::Solution(){
    nOfBooks = Books::getB();
    libraries = new LibCombination();
    libsToConsider = new LibSet();
    for (int libId = 0; libId < Libraries::getL(); libId++) {
        libsToConsider->insert(libId);
    }
    inNew = false;
    timeToRegister = 0;
    evaluation = -1;
    returned = false;
}
Solution::Solution(Solution* solToCopy) {
    nOfBooks = solToCopy->getNumberOfBooks();
    libraries = new LibCombination(*solToCopy->getLibs());
    libsToConsider = new LibSet(*solToCopy->getLibsToConsider());
    evaluation = solToCopy->getEvaluation();
}

Solution::~Solution(){
    libraries->clear();
    delete libraries;
    libsToConsider->clear();
    delete libsToConsider;
    //delete[] assignedIds;
}

Solution* Solution::copy() {
    SolutionPool* sp = SolutionPool::getInstance();
    Solution* copy = sp->getSolution();
    assignTo(copy);
    return copy;
}

bool Solution::equals(Solution* sol) {
    if (sol == this) {
        return true;
    }
    if (getNumberOfLibs() != sol->getNumberOfLibs() ||
        !std::equal(getLibs()->begin(), getLibs()->end(), sol->getLibs()->begin())) {
        return false;
    }
    //for (int bookId = 0; bookId < getNumberOfBooks(); bookId++) {
    //    if (getLibIdAssignedTo(bookId) != sol->getLibIdAssignedTo(bookId)) {
    //        return false;
    //    }
    //}
    return true;
}


void removeFromVector(std::vector<int>* v,int i) {
    v->erase(std::remove(v->begin(), v->end(), i), v->end());
}
void removeFromSet(std::set<int>* s, int i) {
    //s->erase(std::find(s->begin(),s->end(),i));
    s->erase(i);
}

void Solution::addLibId(int libId) {
    //removeFromVector(libsToConsider, libId);
    removeFromSet(libsToConsider,libId);
    getLibs()->push_back(libId);
    int T = Libraries::getLibByID(libId)->getT();
    timeToRegister += T;
}
void Solution::removeLIbId(int libId) {
    removeFromVector(getLibs(), libId);
    libsToConsider->insert(libId);
    int T = Libraries::getLibByID(libId)->getT();
    timeToRegister -= T;
}


void Solution::setEvaluation(int eva){
    evaluation = eva;
}

int Solution::getNumberOfLibs(){
    return (int)getLibs()->size();
}
std::vector<int>* Solution::getLibs() {
    return libraries;
}
int Solution::getLibIdByIndex(int index) {
    if (getNumberOfLibs()-1 < index) {
        return -1;
    }
    return getLibs()->at(index);
}
int Solution::getEvaluation() {
    return evaluation;
}
int Solution::getNumberOfBooks() {
    return nOfBooks;
}

void vectorSwap(LibCombination* comb1, LibCombination* comb2, int lib1, int lib2) {
    auto i = std::find(comb1->begin(), comb1->end(), lib1);
    auto j = std::find(comb2->begin(), comb2->end(), lib2);
    std::swap(i, j);
}

void Solution::mutateLibs(int D){
    Randomizer randomizer = Randomizer();
    setEvaluation(-1);

    if (timeToRegister < D && !libsToConsider->empty()) {
        addLibId(*randomizer.randomFromSet(libsToConsider));
    }
    
    double prob = 1-(double)getNumberOfLibs()/Libraries::getL();
    if (randomizer.roll(0.2*prob) && !libsToConsider->empty()) {
        auto vectorIter = getLibs()->begin()+randomizer.getRandomInt<>(0, (int)getLibs()->size()-1);
        int libInside = *vectorIter;
        int libOutside = *randomizer.randomFromSet(libsToConsider);
        removeFromSet(libsToConsider, libOutside);
        std::swap(*vectorIter, libOutside);
        libsToConsider->insert(libInside);

    }
    else {
        int n = getNumberOfLibs() - 1;
        int i = randomizer.getRandomInt<>(0, n);
        int j = randomizer.getRandomInt<>(0, n);
        // swap libraries
        std::iter_swap(getLibs()->begin() + i, getLibs()->begin() + j);
    }
}
//returns best library id based on dynamic evaluation
int pickBestByEval(int remainingDays,unsigned int L, bool* inSolution) {
    double loss = Libraries::getLoss();
    double bestLibraryEvaluation = -std::numeric_limits<double>::max();
    int bestLibId = -1;
    for (int libId = 0; libId < L; libId++) { // this for loop pick the best library based on evaluation
        if (inSolution[libId]) {
            continue;
        }
        Library* current = Libraries::getLibByID(libId);
        double evaluation = ((remainingDays - current->getT()) * current->getAverageScore() * current->getM()) - (loss * current->getT());

        if (evaluation <= bestLibraryEvaluation) {
            continue;
        }
        bestLibraryEvaluation = evaluation;
        bestLibId = libId;
    }
    return bestLibId;
}

void Solution::constructGreedy(int days, int bookCount, int libCount) {
	
    bool* inSolution = new bool[libCount]();
    int SolutionLength = 0;
    int remainingDays = days;
    while(remainingDays > 0 && SolutionLength < libCount){	
        int bestLib = pickBestByEval(remainingDays, libCount, inSolution);
        Library* current = Libraries::getLibByID(bestLib);

		remainingDays -= current->getT();
		addLibId(bestLib);
		inSolution[bestLib] = true;

		SolutionLength++;
	}
}

//changed evaluate so it sets evaluation not evaluationJerzy
void Solution::evaluate(int D, int B){
    /*will be usefull for genetic algorithm (will add evaluation value for particular genotype).
	the evaluation value should be the same as the final score, if this genotype will be choosen as a solution (if D and B are correct)*/
	int LenGenotype = libraries->size();
	int M, T, N,bookId, remainingDays, bookIterator, booksInLib;
	int finalScore = 0;
	bool* scanned = new bool[B]();
    //for (int i = 0;i < B;i++) {
    //    scanned[i] = false;
    //}
			
	for(int libId : *getLibs()){
        Library* lib = Libraries::getLibByID(libId);
		bookIterator = 0;
		D -= lib->getT();
		remainingDays = D;
		booksInLib = lib->getN();
		while(remainingDays>0&&booksInLib>0){
			M = lib->getM();
			while(M>0&&booksInLib>0){
				bookId = lib->getBookIDAt(bookIterator);
				if(!scanned[bookId])	//if first book which we take was not scanned
				{
					finalScore += Books::getScore(bookId);
					scanned[bookId] = true;
					M--;
				}
				booksInLib--;
				bookIterator++;
			}
			remainingDays--;
		}
	}
    setEvaluation(finalScore);
    delete[] scanned;
}
void Solution::print(int D, int B){
	int LenGenotype = libraries->size();
	int M, T, N,bookID, remainingDays, bookIterator, booksInLib;
	vector<int>bookQueue;
    bool* scanned = new bool[B]();
			
	for(int libId : *getLibs()){
        Library* lib = Libraries::getLibByID(libId);
		bookIterator = 0;
		D -= lib->getT();
		remainingDays = D;
		booksInLib = lib->getN();
		while(remainingDays>0&&booksInLib>0){
			M = lib->getM();
			while(M>0&&booksInLib>0){
				bookID = lib->getBookIDAt(bookIterator);
				if(scanned[bookID] == false){	//if first book which we take was not scanned
					bookQueue.push_back(bookID);
					scanned[bookID] = true;
					M--;
				}
				booksInLib--;
				bookIterator++;
			}
			remainingDays--;
		}
		cout<<libId<<' '<<bookQueue.size()<<endl;
		for(int k = 0; k < bookQueue.size(); ++k){
			cout<<bookQueue[k]<<' ';
		}
		bookQueue.clear();
	}
    delete[] scanned;
}

int Solution::getTimeToRegister() {
    return timeToRegister;
}

bool Solution::isInNew() {
    return inNew;
}

void Solution::setInNew(bool b) {
    inNew = b;
}

LibSet* Solution::getLibsToConsider() {
    return libsToConsider;
}

void Solution::assignTo(Solution* sol) {
    sol->getLibsToConsider()->clear();
    sol->getLibsToConsider()->insert(getLibsToConsider()->begin(), getLibsToConsider()->end());
    sol->getLibs()->clear();
    sol->getLibs()->assign(getLibs()->begin(), getLibs()->end());
    sol->setEvaluation(getEvaluation());
    sol->timeToRegister = getTimeToRegister();
}

void Solution::defaultState() {
    getLibsToConsider()->clear();
    getLibs()->clear();
    for (int libId = 0; libId < Libraries::getL(); libId++) {
        libsToConsider->insert(libId);
    }
    timeToRegister = 0;
    evaluation = -1;
}