#include "books.hpp"

static int* generateData(){
    int * toReturn = new int[100000];
    for ( int i = 0; i < 100000; i++ ){
        toReturn[i] = -1;
    }
    return toReturn;
}

Books::scores = generateData();

int Books::getScore(int index){
    return scores[index];
}

void Books::modify(int id, int aScore){
    scores[id] = aScore;
}

static void Books::clear(){
    delete scores;
}