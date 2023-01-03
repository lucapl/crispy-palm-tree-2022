#ifndef LIBRARY_HPP_
#define LIBRARY_HPP_
#include <iostream>
#include <vector>

class Library{
    private:
        std::vector<int>* books; // vector of book ids, size of N
        int time; // T
        int maxScanned; // M
    public:
        Library(int T, int M);
        ~Library();
        //void scan(){}
        int getN();
        int getT();
        void setT(int);
        int getM();
        void setM(int);

        void sortBooks(bool (*f)(int,int));
        int getBookIDAt(int index);

        void addBook(int);
};

#endif
