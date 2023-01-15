#include "library.hpp"
#include <algorithm>
#include "books.hpp"

Library::Library(int timeToScan,int maxScannedPerDay){
    time = timeToScan;
    maxScanned = maxScannedPerDay;
    books = NULL;
    nOfBooks = -1;
    bookIter = 0;
}

void Library::initializeBooks(int N) {
    books = new int[N]();
}

Library::~Library(){
    delete books;
}

void Library::setN(int n) {
    nOfBooks = n;
}

void Library::setT(int aTime){
    time = aTime;
}

void Library::setM(int aMaxScanned){
    maxScanned = aMaxScanned;
}

void Library::addBook(int id){
    books[bookIter] = id;
    bookIter++;
}

int Library::getN(){
    return nOfBooks;
}
int Library::getT(){
    return time;
}
int Library::getM(){
    return maxScanned;
}

//std::vector<int>* Library::getBooks() {
//    return books;
//}

void Library::sortBooks(bool (*f)(int,int)){
    //std::cout << '\n';
    //for (int i = 0; i < 10; i++) {
    //    std::cout << Books::getScore(getBookIDAt(i)) << ' ';
    //}
    std::sort(books,books+getN()-1, f);
    //std::cout << '\n';
    //for (int i = 0; i < 10; i++) {
    //    std::cout << Books::getScore(getBookIDAt(i)) << ' ';
    //}
}

int Library::getBookIDAt(int index) {
    return books[index];
}

// function assumes that books are scanned by score
// constantly assigning new arrays and freeing them is bad for performance
int* Library::getMaxNextBooks(bool* scanned,unsigned int& from) { 
	//int n = 0;
 //   int m = getM();
 //   int* bestBooks = new int[getM()];
 //   for (int i = 0;i < m;i++) {
 //       bestBooks[i] = -1;
 //   }
 //   std::vector<int>* books = getBooks();
 //   for(int i = from; i < books->size(); i++){
 //   	int bookId = books->at(i);
 //       if (!scanned[bookId]) {
 //           bestBooks[n] = bookId;
 //           n++;
 //           from++;
 //       }
 //       if (n >= m) {
 //           break;
 //       }
 //   }

 //   return bestBooks;
    return NULL;
}

void Library::setAverageScore(double score){
	averageScore = score;
}
double Library::getAverageScore(){
	return averageScore;
}