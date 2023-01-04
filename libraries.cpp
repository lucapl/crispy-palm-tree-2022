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

Library* Libraries::getLibByID(int index){
    return libs[index];
}

void Libraries::modifyLib(int id,int aTime, int aMaxScanned){
    libs[id]->setT(aTime);
    libs[id]->setM(aMaxScanned);
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