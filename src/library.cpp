#include "library.hpp"
#include <algorithm>

Library::Library(int timeToScan,int maxScannedPerDay){
    time = timeToScan;
    maxScanned = maxScannedPerDay;
    books = new std::vector<int>();
}

Library::~Library(){
    delete books;
}

void Library::setT(int aTime){
    time = aTime;
}

void Library::setM(int aMaxScanned){
    maxScanned = aMaxScanned;
}

void Library::addBook(int id){
    books->push_back(id);
}

int Library::getN(){
    return books->size();
}
int Library::getT(){
    return time;
}
int Library::getM(){
    return maxScanned;
}

std::vector<int>* Library::getBooks() {
    return books;
}

void Library::sortBooks(bool (*f)(int,int)){
    std::sort(books->begin(),books->end(),f);
}

int Library::getBookIDAt(int index) {
    return books->at(index);
}

int* Library::getMaxNextBooks(bool* scanned,int from) { //function assumes that books are scanned by score
	int n = 0;
    int* bestBooks = new int[getM()];
    for (int i = 0;i < getM();i++) {
        bestBooks[i] = -1;
    }
    std::vector<int>* booke = getBooks();
    for(int i = from; i < booke->size(); i++){
    	int bookId = booke->at(i);
        if (!scanned[bookId]) {
            bestBooks[n] = bookId;
            n++;
        }
        if (n >= getM()) {
            break;
        }
    }

    return bestBooks;
}
void Library::setAverageScore(int score)
{
	averageScore = score;
}
int Library::getAverageScore()
{
	return averageScore;
}
void Library::setNofBooks(int n)
{
	NofBooks = n;
}
int Library::getNofBooks()
{
	return NofBooks;
}

