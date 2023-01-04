#include "solution.hpp"
#include "books.hpp"
#include "randomizer.hpp"
#include <algorithm>
#include <random>

Solution::Solution(int aNOfBooks){
    nOfBooks = aNOfBooks;
    libraries = new std::vector<int>();
    assignedIds = new int[nOfBooks];
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
    return (int)libraries->size();
}
std::vector<int>* Solution::getLibs() {
    return libraries;
}
int Solution::getLibIdByIndex(int index) {
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

    for(int bookId = 0; bookId < nBooks; bookId ++){
        int libId = assignedIds[bookId]; // Id of the assigned library to a book

        if (libId < 0){ continue; } // skip the iteration if Id not valid
        booksInLibs[libId].push_back(bookId);
    }

    //Books allBooks = Books();

    for(auto libId : *libraries){
        std::vector<int>* booksInLib = &booksInLibs[libId];
        std::cout << libId << booksInLib->size() << '\n'; // Y K
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