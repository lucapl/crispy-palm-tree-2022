#ifndef LIBRARY_HPP_
#define LIBRARY_HPP_
#include <iostream>
#include <vector>

class Library{
    private:
        std::vector<int>* books; // vector of book ids, size of N
        int time; // T
        int maxScanned; // M
        int NofBooks; // number of books in a liblary
        int averageScore; //average score of book
    public:
    	int ScoresSum;
    	
        Library(int T, int M);
        ~Library();
        //void scan(){}
        int getN();
        int getT();
        void setT(int);
        int getM();
        void setM(int);

        std::vector<int>* getBooks();
        void sortBooks(bool (*f)(int,int));
        int getBookIDAt(int index);

        int* getMaxNextBooks(bool* scanned, int from);

        void addBook(int);
        
        void setAverageScore(int score);
        int getAverageScore();
        void setNofBooks(int n);
        int getNofBooks();
};

#endif
