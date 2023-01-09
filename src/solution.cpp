#include "solution.hpp"
#include "books.hpp"
#include "libraries.hpp"
#include "randomizer.hpp"
#include <algorithm>
#include <random>
using namespace std;

Solution::Solution(int aNOfBooks){
    nOfBooks = aNOfBooks;
    booksAssigned = 0;
    libraries = new std::vector<int>();
    assignedIds = new int[nOfBooks];
    for (int bookId = 0; bookId < nOfBooks;bookId++) {
        assignedIds[bookId] = -1;
    }
    evaluation = 0;
}
Solution::~Solution(){
    delete libraries;
    delete[] assignedIds;
}

Solution* Solution::copy() {
    Solution* newSol = new Solution(numberOfBooks());

    std::vector<int>* libsCopy = newSol->getLibs();
    std::copy(getLibs()->begin(), getLibs()->end(), back_inserter(*libsCopy));

    int* copiedIds = newSol->getAssignedIds();
    for (int i = 0; i < nOfBooks; i++) {
        copiedIds[i] = getAssignedIds()[i];
    }

    return newSol;
}

bool Solution::equals(Solution* sol) {
    if (sol == this) {
        return true;
    }
    if (numberOfLibs() != sol->numberOfBooks() ||
        !std::equal(getLibs()->begin(), getLibs()->end(), sol->getLibs()->begin())) {
        return false;
    }
    for (int bookId = 0; bookId < numberOfBooks(); bookId++) {
        if (getLibIdAssignedTo(bookId) != sol->getLibIdAssignedTo(bookId)) {
            return false;
        }
    }
    return true;
}

void Solution::assignBookToLib(int bookId, int libId) {
    getAssignedIds()[bookId] = libId;
}

void Solution::addLibId(int libId) {
    getLibs()->push_back(libId);
}


void Solution::setEvaluation(int eva){
    evaluation = eva;
}

int Solution::numberOfLibs(){
    return (int)getLibs()->size();
}
std::vector<int>* Solution::getLibs() {
    return libraries;
}
int Solution::getLibIdByIndex(int index) {
    if (numberOfLibs()-1 < index) {
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
int Solution::numberOfBooks() {
    return nOfBooks;
}
// params are D, B
void Solution::printSolution(int nDays,int nBooks){ //used only for printing the final solution into standard output
    int A = numberOfLibs();// # of libraries to sign up - int A
    std::cout << A << '\n';
    std::vector<int>* booksInLibs = new std::vector<int>[A];

    for(int bookId = 0; bookId < numberOfBooks(); bookId++) {
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

void Solution::mutateLibs(){
    Randomizer randomizer = Randomizer();
    int n = numberOfLibs();
    int i = randomizer.getRandomInt<>(0,n);
    int j = randomizer.getRandomInt<>(0,n);

    // swap libraries
    int temp = libraries->at(i);
    libraries->at(i) = libraries->at(j);
    libraries->at(j) = temp;
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

	int FromWhichBookStartScanning[100000] = {0};
	
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
                FromWhichBookStartScanning[libId]++;
                assignBookToLib(bookId,libId);
                scanned[bookId] = true;
                i++;
            }
            delete booksToScan;
        }

        dayLeftToScan--;
    }
} 

using LibCombination = std::vector<int>;

void Solution::constructGreedy(int days, int bookCount, int libCount, Libraries* libs) {
	
	bool InSolution[libCount] = {false};
    LibCombination libComb = LibCombination();
    int SolutionLength = 0;
    int RemainingDays = days;
    long long int loss = libs->loss;
    
    int BestLibraryID = 0;
    long long int BestLibraryEvaluation;
    long long int Evaluation;
    int RegisterTime;
    
    Library* Current;
    
    while(RemainingDays!=0&&SolutionLength!=libCount)
    {
    	BestLibraryEvaluation = -10000000000000000;
    	for(int ID = 0; ID<libCount; ID++)
    	{
    		if(InSolution[ID] == false)
    		{
    			Current = Libraries::getLibByID(ID);
    			Evaluation = (RemainingDays - Current->getT())*Current->getAverageScore()*Current->getM() - loss*Current->getT();
    			if(Evaluation>BestLibraryEvaluation)
    			{
    				RegisterTime = Current->getT();
    				BestLibraryEvaluation = Evaluation;
    				BestLibraryID = ID;
				}
			}
		}
		//cout<<"added "<<BestLibraryID<<" to solution"<<endl;
		RemainingDays -= RegisterTime;
		addLibId(BestLibraryID);
		InSolution[BestLibraryID] = true;
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
void Solution::evaluate(int D, int B) /*will be usefull for genetic algorithm (will add evaluation value for particular genotype).
		the evaluation value should be the same as the final score, if this genotype will be choosen as a solution (if D and B are correct)*/
		{
			int LenGenotype = libraries->size();
			int M, T, N,bookID, RemainingDaysForScanningInThisLiblary, bookIterator, RemainingBooksInLiblarary;
			int finalScore = 0;
			bool scanned[B] = { false };
			
			for(int i = 0; i<LenGenotype; ++i)
			{
				bookIterator = 0;
				D -= Libraries::getLibByID(libraries->at(i))->getT();
				RemainingDaysForScanningInThisLiblary = D;
				RemainingBooksInLiblarary = Libraries::getLibByID(libraries->at(i))->getN();
				while(RemainingDaysForScanningInThisLiblary>0&&RemainingBooksInLiblarary>0)
				{
					M = Libraries::getLibByID(libraries->at(i))->getM();
					while(M>0&&RemainingBooksInLiblarary>0)
					{
						bookID = Libraries::getLibByID(libraries->at(i))->getBookIDAt(bookIterator);
						if(scanned[bookID] == false)	//if first book which we take was not scanned
						{
							finalScore += Books::getScore(bookID);
							scanned[bookID] = true;
							M--;
						}
						RemainingBooksInLiblarary--;
						bookIterator++;
					}
					RemainingDaysForScanningInThisLiblary--;
				}
			}
		this->evaluationJerzy = finalScore;
		}
void Solution::print(int D, int B) /*will be usefull for genetic algorithm (will add evaluation value for particular genotype).
		the evaluation value should be the same as the final score, if this genotype will be choosen as a solution (if D and B are correct)*/
		{
			int LenGenotype = libraries->size();
			int M, T, N,bookID, RemainingDaysForScanningInThisLiblary, bookIterator, RemainingBooksInLiblarary;
			vector<int>ScanningQueueOfTheLiblary;
			bool scanned[B] = { false };
			
			for(int i = 0; i<LenGenotype; ++i)
			{
				bookIterator = 0;
				D -= Libraries::getLibByID(libraries->at(i))->getT();
				RemainingDaysForScanningInThisLiblary = D;
				RemainingBooksInLiblarary = Libraries::getLibByID(libraries->at(i))->getN();
				while(RemainingDaysForScanningInThisLiblary>0&&RemainingBooksInLiblarary>0)
				{
					M = Libraries::getLibByID(libraries->at(i))->getM();
					while(M>0&&RemainingBooksInLiblarary>0)
					{
						bookID = Libraries::getLibByID(libraries->at(i))->getBookIDAt(bookIterator);
						if(scanned[bookID] == false)	//if first book which we take was not scanned
						{
							ScanningQueueOfTheLiblary.push_back(bookID);
							scanned[bookID] = true;
							M--;
						}
						RemainingBooksInLiblarary--;
						bookIterator++;
					}
					RemainingDaysForScanningInThisLiblary--;
				}
				cout<<endl<<libraries->at(i)<<" "<<ScanningQueueOfTheLiblary.size()<<endl;
				for(int k = 0; k < ScanningQueueOfTheLiblary.size(); ++k)
				{
					cout<<ScanningQueueOfTheLiblary[k]<<" ";
				}
				ScanningQueueOfTheLiblary.clear();
			}
		}
int Solution::getEvaluationJerzy()
{
	return evaluationJerzy;
}

