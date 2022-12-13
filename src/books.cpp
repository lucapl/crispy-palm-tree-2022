#include "books.hpp"

static int* generateBooks(){
    int * toReturn = new int[100000];
    for ( int i = 0; i < 100000; i++ ){
        toReturn[i] = -1;
    }
    return toReturn;
}

Books::scores = generateBooks();

static int Books::getScore(int index){
    return scores[index];
}

static void Books::modify(int id, int aScore){
    scores[id] = aScore;
}

static void Books::clear(){
    delete scores;
}

static bool Books::compareByScore(int a, int b){	
	return getScore(a) > getScore(b);
}
static bool Books::compareByID(int a, int b){
	return a < b;
}
