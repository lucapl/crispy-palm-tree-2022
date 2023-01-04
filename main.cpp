#include<cstdio>
#include<vector>
#include<algorithm>
//#include <bits/stdc++.h>
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

long long readBooks(Books* books,FILE* instance,int nOfBooks){
    long long scoresSum = 0;
    for(int bookId = 0; bookId < nOfBooks; bookId++){
		int score;
        fscanf(instance," %i", &score);
		books->modify(bookId,score);
        scoresSum += score;
    }
    printf("Theoretical upper bound: %lli\n", scoresSum);
    return scoresSum;
}

void readLibs(Libraries* libs, FILE* instance, int nOfLibraries,int D) {
    for (int libId = 0; libId < nOfLibraries; libId++) {
        int nOfBooksInLib, timeToRegister, maxScanned; // N T M
        fscanf(instance, " %i %i %i", &nOfBooksInLib, &timeToRegister, &maxScanned);

        libs->modifyLib(libId, timeToRegister, maxScanned);

        float scoreSum = 0;
        for (int i = 0; i < nOfBooksInLib; i++) {
            int bookId;
            fscanf(instance, " %i", &bookId);
            libs->addBook(libId, bookId); // shallow copy

            scoreSum += Books::getScore(bookId);
        }
        float estimatedValue = (scoreSum / nOfBooksInLib) * maxScanned * (D - timeToRegister);
        libs->setEstimatedValue(libId,estimatedValue<scoreSum?estimatedValue:scoreSum);
        libs->getLibByID(libId)->sortBooks(compareByID);
    }
}

int main(int argc, char** argv){
	
	Books books = Books();
	Libraries libs = Libraries();

    if(argc < 1){
        std::cerr << "Too few arguments!\nCorrect command: ./$name$ [instance]\n";
        return 1;
    }
    string inst = "C:\\Users\\£ukasz\\Desktop\\studia\\3rd semester\\CO\\project\\vs\\CO_project\\repo\\instances\\a_example.txt";
    FILE* instance = fopen(inst.c_str(), "r");

    if(!instance){
        std::cerr << "Can't open " << argv[1] <<'\n';
        return 1;
    }

    int nOfBooks, nOfLibraries, nOfDays; // B L D
    fscanf(instance," %i %i %i", &nOfBooks, &nOfLibraries, &nOfDays);

    long long scoresSum = readBooks(&books,instance,nOfBooks);
    
    readLibs(&libs, instance, nOfLibraries,nOfDays);
    
	books.clear();
	libs.clear();
    fclose(instance);
    return 0;
}

//Library* lib = libs.getLibById(i);
    //sort(lib->.begin(), lib.books.end(), compareByID);
    /*	to chect if is sorts correctly (it does)
    for(int k = 0; k < libs[i].books.size(); ++k)
    {
        cout<<libs[i].books[k].ID<<"-"<<libs[i].books[k].score<<" ";
    }
    cout<<endl;
    */

    //temporary:

// i did not touch the code below   

    //solutionGenotype.genotype[i] = &libs[i];
// solutionGenotype.LenGenotype = L;
// solutionGenotype.printSolution(D,B);

//used for testing distnce function:
// Clustering cluster;
// cout<<"distance between lib 0 and lib 1: "<<cluster.distance(&libs[0],&libs[1])<<endl;
// for(int i = 0; i<L;i++)
// {
// sort(libs[i].books.begin(), libs[i].books.end(), compareByScore);
// }

// solutionGenotype.LenGenotype = L;
// solutionGenotype.printSolution(D,B);
// solutionGenotype.evaluate(D,B);
//cout<<"this solution score: "<<solutionGenotype.evaluation<<endl;