#pragma once
#include <iostream>
#include <vector>

class Library {
private:
    int* books; // array of book ids, size of N // change to array for optimization reasons
    int time; // T
    int maxScanned; // M
    int nOfBooks; // N
    double averageScore; //average score of book
    int bookIter;
public:
    int ScoresSum;

    Library(int T, int M);
    ~Library();
    //void scan(){}
    int getN();
    void setN(int);
    int getT();
    void setT(int);
    int getM();
    void setM(int);

    //std::vector<int>* getBooks();
    void sortBooks(bool (*f)(int, int));
    int getBookIDAt(int index);

    int* getMaxNextBooks(bool* scanned, unsigned int& from);

    void addBook(int);
    void initializeBooks(int N);

    void setAverageScore(double score);
    double getAverageScore();
};
