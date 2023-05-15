#include "books.hpp"

static int* generateBooks(int def){
    int * toReturn = new int[100000];
    for ( int i = 0; i < 100000; i++ ){
        toReturn[i] = def;
    }
    return toReturn;
}

int* Books::scores = generateBooks(-1);
int* Books::bookCounts = generateBooks(0);

unsigned int Books::B = 100000;

float Books::averageScore = 0;

unsigned int Books::getB(void) {
    return B;
}

void Books::setB(unsigned int b) {
    B = b;
}

int Books::getScore(int index){
    return scores[index];
}

void Books::modify(int id, int aScore){
    scores[id] = aScore;
}

void Books::clear(){
    delete scores;
}

// comparators

bool Books::compareByScore(int a, int b){	
	return getScore(a) < getScore(b);
}
bool Books::compareByID(int a, int b){
	return a < b;
}


// stats for greedy

int Books::getFrequency(int bookId) {
    return bookCounts[bookId];
}
void Books::addOccurence(int bookId) {
    bookCounts[bookId]++;
}
void Books::setAverageScore(float score){
	averageScore = score;
}
float Books::getAverageScore(){
	return averageScore;
}

