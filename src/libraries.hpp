#pragma once
#include "library.hpp"

class Libraries{
    private:
        static Library** libs;
    public:
        static Library* getLibByID(int index);
        static void modifyLib(int id,int T,int M);
        static void addBook(int lId, int bId);

        static void clear();
};