#ifndef LIBRARY_HPP_
#define LIBRARY_HPP_
#include <iostream>
#include <vector>

typedef int book;//book as value

class Library{
    private:
        std::vector<book>* books;
        int time;
        int max_scanned;
    public:
        Library(){}
        ~Library(){}
        void scan(){}
};

#endif
