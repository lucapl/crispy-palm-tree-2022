#ifndef LIBRARY_HPP_
#define LIBRARY_HPP_
#include <iostream>

typedef int book;//book as value

class Library{
    private:
        book* books;
        int time;
        int max_scanned_;
    public:
        Library(){}
        ~Library(){}
        void scan(){}
};

#endif
