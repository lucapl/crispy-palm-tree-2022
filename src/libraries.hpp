#pragma once
#include "library.hpp"

class Libraries{
    private:
        static Library** libs;
        static float* estimatedValues;
        
    public:
    	//if you want, you can encapsulate it.
		//I don't think, that Synak will care about encapsulation to much
		float averageMaxScanned;
		float averageSignupTime;
		long long int loss;
    	
        static Library* getLibByID(int index);
        static void modifyLib(int id,int T,int M,int NofBooks);
        static void addBook(int lId, int bId);
        
        static int getEstimatedValue(int libId);
        static void setEstimatedValue(int libId,float value);
        static void clear();
        static bool compareByEstimatedValue(const int libId1, const int libId2);
		
};
