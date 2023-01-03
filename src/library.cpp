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

void Library::sortBooks(bool (*f)(int,int)){
    std::sort(books->begin(),books->end(),f);
}

int Library::getBookIDAt(int index) {
    return books->at(index);
}

