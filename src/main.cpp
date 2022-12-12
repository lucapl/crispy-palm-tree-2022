//Command: ./solution_test [instance] //no more valid (idk how to run it)
/*
#include<cstdio>
#include<vector>
#include<algorithm>
*/
#include <bits/stdc++.h>
#include "books.hpp"
#include "libraries.hpp"

using namespace std;

bool compareByScore(int a, int b){	
	Books books = Books();
	return books.getScore(a) > books.getScore(b);
}
bool compareByID(int a, int b){
	return a < b;
}


int main(int argc, char** argv){
	
	//Genome solutionGenotype;
	Books books = Books();
	Libraries libs = Libraries();

    if(argc < 2){
        fprintf(stderr, "Too few arguments!\nCorrect command: ./main.cpp [instance]\n");
        return 1;
    }

    FILE* instance = fopen(argv[1],"r");

    if(!instance){
        fprintf(stderr, "Can't open %s\n", argv[1]);
        return 1;
    }

    int nOfBooks, nOfLibraries, nOfDays; // B L D
    fscanf(instance," %i %i %i", &nOfBooks, &nOfLibraries, &nOfDays);

    long long scoresSum = 0;
    for(int i = 0; i < nOfBooks; ++i){
		int score;
        fscanf(instance," %i", &score);
		books.modify(i,score);
        scoresSum += score;
    }
    printf("Theoretical upper bound: %lli\n", scoresSum);

    for(int i = 0; i < nOfLibraries; ++i){
        int nOfBooksInLib, timeToRegister, maxScanned; // N T M
        fscanf(instance," %i %i %i", &nOfBooksInLib, &timeToRegister, &maxScanned);
		
		libs.modifyLib(i,timeToRegister,maxScanned);

        for(int j = 0; j < nOfBooksInLib; ++j){
            int id;
            fscanf(instance," %i", &id);
            libs.addBook(i,id); // shallow copy
        }
        
		Library* lib = libs.getLibById(i);
        sort(lib->.begin(), lib.books.end(), compareByID);
        /*	to chect if is sorts correctly (it does)
        for(int k = 0; k < libs[i].books.size(); ++k)
		{
			cout<<libs[i].books[k].ID<<"-"<<libs[i].books[k].score<<" ";
		}
		cout<<endl;
        */
        
        //temporary:
        
        
        
        solutionGenotype.genotype[i] = &libs[i];
    }
    solutionGenotype.LenGenotype = L;
    solutionGenotype.printSolution(D,B);
    //used for testing distnce function:
    Clustering cluster;
    cout<<"distance between lib 0 and lib 1: "<<cluster.distance(&libs[0],&libs[1])<<endl;
    for(int i = 0; i<L;i++)
    {
    sort(libs[i].books.begin(), libs[i].books.end(), compareByScore);
	}
    
    solutionGenotype.LenGenotype = L;
    solutionGenotype.printSolution(D,B);
    solutionGenotype.evaluate(D,B);
    //cout<<"this solution score: "<<solutionGenotype.evaluation<<endl;
    
	books.clear();
	libs.clear();
    fclose(instance);
    return 0;
}
