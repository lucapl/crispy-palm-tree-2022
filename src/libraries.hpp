#pragma once
#include "library.hpp"

class Libraries{
    private:
        static Library** libs;
    public:
        Library* getLibByID(int index);
        void modifyLib(int id,int T,int M);
        void addBook(int lId, int bId);

        static void clear();
};