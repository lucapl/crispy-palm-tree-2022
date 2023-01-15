#include "solution.hpp"
#include "books.hpp"
#include "libraries.hpp"
#include "randomizer.hpp"
#include <algorithm>
#include <random>
#include <limits>
using namespace std;
using LibCombination = std::vector<int>;

Solution::Solution(int aNOfBooks){
    nOfBooks = aNOfBooks;
    libraries = new LibCombination();
    //assignedIds = new int[nOfBooks];
    //for (int bookId = 0; bookId < nOfBooks;bookId++) {
    //    assignedIds[bookId] = -1;
    //}
    libsToConsider = new LibCombination();
    for (int libId = 0; libId < Libraries::getL(); libId++) {
        libsToConsider->push_back(libId);
    }
    evaluation = -1;
}
Solution::~Solution(){
    libraries->clear();
    delete libraries;
    libsToConsider->clear();
    delete libsToConsider;
    //delete[] assignedIds;
}

Solution* Solution::copy() {
    Solution* newSol = new Solution(getNumberOfBooks());

    std::vector<int>* libsCopy = getLibs();
    for (int libId : *libsCopy) {
        newSol->addLibId(libId);
    }
    //std::copy(getLibs()->begin(), getLibs()->end(), back_inserter(*libsCopy));

    //int* copiedIds = newSol->getAssignedIds();
    //for (int i = 0; i < nOfBooks; i++) {
    //    copiedIds[i] = getAssignedIds()[i];
    //}
    newSol->setEvaluation(getEvaluation());

    //std::vector<int>* considerLibsCopy = newSol->libsToConsider;
    //std::copy(libsToConsider->begin(), libsToConsider->end(), back_inserter(*considerLibsCopy));

    return newSol;
}

bool Solution::equals(Solution* sol) {
    if (sol == this) {
        return true;
    }
    if (getNumberOfLibs() != sol->getNumberOfBooks() ||
        !std::equal(getLibs()->begin(), getLibs()->end(), sol->getLibs()->begin())) {
        return false;
    }
    for (int bookId = 0; bookId < getNumberOfBooks(); bookId++) {
        if (getLibIdAssignedTo(bookId) != sol->getLibIdAssignedTo(bookId)) {
            return false;
        }
    }
    return true;
}

void Solution::assignBookToLib(int bookId, int libId) {
    getAssignedIds()[bookId] = libId;
}

void removeFromVector(std::vector<int>* v,int i) {
    v->erase(std::remove(v->begin(), v->end(), i), v->end());
}

void Solution::addLibId(int libId) {
    removeFromVector(libsToConsider, libId);
    getLibs()->push_back(libId);
    int T = Libraries::getLibByID(libId)->getT();
    timeToRegister += T;
}
void Solution::removeLIbId(int libId) {
    removeFromVector(getLibs(), libId);
    libsToConsider->push_back(libId);
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
int Solution::getLibIdAssignedTo(int bookId) {
    return getAssignedIds()[bookId];
}
int* Solution::getAssignedIds() {
    return assignedIds;
}
int Solution::getEvaluation() {
    return evaluation;
}
int Solution::getNumberOfBooks() {
    return nOfBooks;
}
// params are D, B
void Solution::printSolution(int nDays,int nBooks){ //used only for printing the final solution into standard output
    int A = getNumberOfLibs();// # of libraries to sign up - int A
    std::cout << A << '\n';
    std::vector<int>* booksInLibs = new std::vector<int>[A];

    for(int bookId = 0; bookId < getNumberOfBooks(); bookId++) {
        int libId = assignedIds[bookId]; // Id of the assigned library to a book

        if (libId < 0){ continue; } // skip the iteration if Id not valid
        booksInLibs[libId].push_back(bookId);
    }

    //Books allBooks = Books();

    for(auto libId : *libraries){
        std::vector<int>* booksInLib = &booksInLibs[libId];
        std::cout << libId << ' ' << booksInLib->size() << '\n'; // Y K
        std::sort(booksInLib->begin(),booksInLib->end(), Books::compareByScore); //sort by score // this should be fine because the function is static
        for(auto bookId : *booksInLib){
            std::cout << bookId << ' '; // k_bookId
        }
        std::cout << '\n';
    }
    delete[] booksInLibs;
}

void Solution::mutateLibs(int D){
    Randomizer randomizer = Randomizer();
    setEvaluation(-1);

    if (timeToRegister < D) {
        addLibId(randomizer.choose<int, LibCombination&>(*libsToConsider, libsToConsider->size()));
    }
    
    // add libraries
    if (randomizer.roll(0.5)) {
        int considerLib = randomizer.choose<int, LibCombination&>(*libsToConsider, libsToConsider->size());
        int inSolLib = randomizer.choose<int, LibCombination&>(*getLibs(), getLibs()->size());
        addLibId(considerLib);
        removeLIbId(inSolLib);
    }
    else {
        int n = getNumberOfLibs() - 1;
        int i = randomizer.getRandomInt<>(0, n);
        int j = randomizer.getRandomInt<>(0, n);
        // swap libraries
        std::iter_swap(getLibs()->begin() + i, getLibs()->begin() + j);
    }
}

void Solution::assignBooksInitially(int days,int bookCount) {
    int dayLeftToScan = 0;
    int libsScanned = -1;
    int libIdScanned = 0;

    //int theBook;
    bool* scanned = new bool[bookCount];
    for (int i = 0; i < bookCount; i++) {
        scanned[i] = false;
    }

	unsigned int FromWhichBookStartScanning[100000] = {0};
	
    for (int day = 0; day < days;day++) {
        Library* scannedLib = Libraries::getLibByID(getLibIdByIndex(libIdScanned));
        if (dayLeftToScan == 0) {
            libsScanned++;
            libIdScanned++;
            if (scannedLib != NULL) {
                dayLeftToScan = scannedLib->getT();
            }
        }
		
        //scanning
        for (int libId = 0; libId < libsScanned;libId++) {
            Library* lib = Libraries::getLibByID(getLibIdByIndex(libId));
            int* booksToScan = lib->getMaxNextBooks(scanned,FromWhichBookStartScanning[libId]);
            int i = 0;
            while (i< lib->getM() && booksToScan[i] != -1) {
                int bookId = booksToScan[i];
                assignBookToLib(bookId,libId);
                scanned[bookId] = true;
                i++;
            }
            delete booksToScan;
        }

        dayLeftToScan--;
    }
} 

//returns best library id based on dynamic evaluation
int pickBestByEval(int remainingDays,unsigned int L, bool* inSolution) {
    double loss = Libraries::getLoss();
    double bestLibraryEvaluation = -std::numeric_limits<double>::max();
    int bestLibId = -1;
    for (int libId = 0; libId < L; libId++) { // this for loop pick the best library based on evaluation, should it be a separate function?
        if (inSolution[libId]) {
            continue;
        }
        Library* current = Libraries::getLibByID(libId);
        double evaluation = (remainingDays - current->getT()) * current->getAverageScore() * current->getM() - loss * current->getT();
        //double evaluation2 = (remainingDays - current->getT()) * current->getAverageScore() * current->getM() - loss * current->getT();
        //std::cout << (int)current->getAverageScore() << ' ' << current->getAverageScore() << endl;
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

        if (current == NULL) {
            break;
        }

		remainingDays -= current->getT();
		addLibId(bestLib);
		inSolution[bestLib] = true;

		SolutionLength++;
	}
}
/*
void Solution::constructGreedy(int days, int bookCount, int libCount) {
    LibCombination libComb = LibCombination();
    for (int libId = 0; libId < libCount; libId++) {
        libComb.push_back(libId);
    }
    
    
    //std::cout<<"started sorting	... ";
    std::sort(libComb.begin(), libComb.end(), Libraries::compareByEstimatedValue);
    //std::cout<<"ended sorting";
    
	//up to this moment it is ok
	
    //int libId = 0;
    int countDays = days;
    for (int libId: libComb) {
        addLibId(libId);
        countDays -= Libraries::getLibByID(libId)->getT();

        if (countDays < 0) {
            break;
        }
    }

    //while (countDays > 0) {
    //    //auto iter = 
    //    //libId = *iter;
    //    addLibId(libId);
    //    countDays -= Libraries::getLibByID(libId)->getT();
    //    libComb.erase(libId);
    //    libId++;
    //}
    
	std::cout<<"started assigning books	... ";
    assignBooksInitially(days,bookCount);
    std::cout<<"ended assigning books";
}*/

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
	int M, T, N,bookID, RemainingDaysForScanningInThisLiblary, bookIterator, RemainingBooksInLiblarary;
	vector<int>ScanningQueueOfTheLiblary;
    bool* scanned = new bool[B];
    for (int i = 0;i < B;i++) {
        scanned[i] = false;
    }
			
	for(int i = 0; i<LenGenotype; ++i){
		bookIterator = 0;
		D -= Libraries::getLibByID(libraries->at(i))->getT();
		RemainingDaysForScanningInThisLiblary = D;
		RemainingBooksInLiblarary = Libraries::getLibByID(libraries->at(i))->getN();
		while(RemainingDaysForScanningInThisLiblary>0&&RemainingBooksInLiblarary>0){
			M = Libraries::getLibByID(libraries->at(i))->getM();
			while(M>0&&RemainingBooksInLiblarary>0){
				bookID = Libraries::getLibByID(libraries->at(i))->getBookIDAt(bookIterator);
				if(scanned[bookID] == false){	//if first book which we take was not scanned
					ScanningQueueOfTheLiblary.push_back(bookID);
					scanned[bookID] = true;
					M--;
				}
				RemainingBooksInLiblarary--;
				bookIterator++;
			}
			RemainingDaysForScanningInThisLiblary--;
		}
		cout<<endl<<libraries->at(i)<<' '<<ScanningQueueOfTheLiblary.size()<<endl;
		for(int k = 0; k < ScanningQueueOfTheLiblary.size(); ++k){
			cout<<ScanningQueueOfTheLiblary[k]<<' ';
		}
		ScanningQueueOfTheLiblary.clear();
	}
    delete[] scanned;
}

int Solution::getTimeToRegister() {
    return timeToRegister;
}
