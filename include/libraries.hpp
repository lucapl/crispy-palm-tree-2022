#pragma once
#include "library.hpp"

class Libraries{
    private:
        static Library** libs;
        static unsigned int L;

        // stats for greedy
        static float* estimatedValues;
        static float averageMaxScanned;
        static float averageSignupTime;
        static double loss;
    public:
    	//if you want, you can encapsulate it.
    	
        static Library* getLibByID(int index);
        static void modifyLib(int id,int N,int T,int M);
        static void addBook(int lId, int bId);
        static unsigned int getL(void);
        static void setL(unsigned int);
        
        static int getEstimatedValue(int libId);
        static void setEstimatedValue(int libId,float value);
        static bool compareByEstimatedValue(const int libId1, const int libId2);
		
        static void clear();


        static float getAverageM();
        static void setAverageM(float);
        static float getAverageT();
        static void setAverageT(float);
        static double getLoss();
        static void setLoss(double);

};
