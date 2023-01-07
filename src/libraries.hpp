#pragma once
#include "library.hpp"

class Libraries{
    private:
        static Library** libs;
        static float* estimatedValues;
    public:
        static Library* getLibByID(int index);
        static void modifyLib(int id,int T,int M);
        static void addBook(int lId, int bId);
        
        static int getEstimatedValue(int libId);
        static void setEstimatedValue(int libId,float value);
        static void clear();
        static bool compareByEstimatedValue(const int libId1, const int libId2);
};