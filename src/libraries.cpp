#include "libraries.hpp"

static Library** generateLibs(){
    Library** toReturn = new Library*[100000];
    for ( int i = 0; i < 100000; i++ ){
        toReturn[i] = new Library(-1,-1);
    }
    return toReturn;
}

Library** Libraries::libs = generateLibs();
float* Libraries::estimatedValues = new float[100000];
unsigned int Libraries::L = 0;
float Libraries::averageMaxScanned = 0;
float Libraries::averageSignupTime = 0;
double Libraries::loss = 0;

Library* Libraries::getLibByID(int index){
    if(index < 0){
        return NULL;
    }
    return libs[index];
}

void Libraries::modifyLib(int id,int nOfBooksInLibs,int aTime, int aMaxScanned){
    libs[id]->setT(aTime);
    libs[id]->setM(aMaxScanned);
    libs[id]->setN(nOfBooksInLibs);
    libs[id]->initializeBooks(nOfBooksInLibs);
}

void Libraries::addBook(int libId,int bookId){
    libs[libId]->addBook(bookId);
}

void Libraries::clear(){
    for(int i = 0; i < 100000; i++){
        delete libs[i];
    }
    delete libs;
    delete[] estimatedValues;
}

int Libraries::getEstimatedValue(int libId) {
    return estimatedValues[libId];
}
void Libraries::setEstimatedValue(int libId, float value) {
    estimatedValues[libId] = value;
}

bool Libraries::compareByEstimatedValue(const int libId1,const int libId2) {
    return getEstimatedValue(libId1) < getEstimatedValue(libId2);
}

unsigned int Libraries::getL() {
    return L;
}
void Libraries::setL(unsigned int l) {
    L = l;
}


//stat getters/setters

float Libraries::getAverageM() {
    return averageMaxScanned;
}
void Libraries::setAverageM(float avgM) {
    averageMaxScanned = avgM;
}
float Libraries::getAverageT() {
    return averageSignupTime;
}
void Libraries::setAverageT(float avgT) {
    averageSignupTime = avgT;
}
double Libraries::getLoss() {
    return loss;
}
void Libraries::setLoss(double newLoss){
    loss = newLoss;
}