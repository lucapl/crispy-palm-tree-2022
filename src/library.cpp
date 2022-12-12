#include "library.hpp"

Library::Library(int timeToScan,int maxScannedPerDay){
    time = timeToScan;
    maxScanned = maxScannedPerDay;
}

Library::~Library(){
    delete books;
}

Library::setT(int aTime){
    time = aTime;
}

Library::setM(int aMaxScanned){
    maxScanned = aMaxScanned;
}

Library::addBook(int id){
    books->push_back(id);
}

Library::getN(){
    return books->size();
}
Library::getT(){
    return time;
}
Library::getM(){
    return maxScanned;
}

