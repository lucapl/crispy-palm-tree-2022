#include "libraries.hpp"

static Library* generateData(){
    Library** toReturn = new Library*[100000];
    for ( int i = 0; i < 100000; i++ ){
        toReturn[i] = new Library(-1,-1);
    }
    return toReturn;
}

Libraries::libs = generateData();

Library* Libraries::getLibByID(int index){
    return libs[index];
}

void Libraries::modifyLib(int id,int aTime, int aMaxScanned){
    libs[id]->setT(aTime);
    libs[id]->setM(aMaxScanned);
}

void Libraries::addBook(int libId,int bookId){
    libs[libId]->push_back(bookId);
}

static void Libraries::clear(){
    for(int i = 0; i < 100000; i++){
        delete libs[i];
    }
    delete libs;
}