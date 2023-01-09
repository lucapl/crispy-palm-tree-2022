#include<cstdio>
#include<vector>
#include<algorithm>
//#include <bits/stdc++.h>
#include <chrono>
#include "books.hpp"
#include "libraries.hpp"
#include "solution.hpp"
#include "geneticAlgorithm.hpp"
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
	int NoOfAllBooks = 0; //not neccesary different just all books that exist in liblaries 
	int SumOfScoresOfAllBooksInLibs = 0; //whenever they appear several times (it is needed just to calcualte average score of sccaned book)
	int SumOfSingupTimes = 0;
	int SumOfMaxScanned = 0;
	
    for (int libId = 0; libId < nOfLibraries; libId++)
	{
        int nOfBooksInLib, timeToRegister, maxScanned; // N T M
        fscanf(instance, " %i %i %i", &nOfBooksInLib, &timeToRegister, &maxScanned);

        libs->modifyLib(libId, timeToRegister, maxScanned, nOfBooksInLib);
        
        NoOfAllBooks += nOfBooksInLib;
        SumOfSingupTimes += timeToRegister;
        SumOfMaxScanned += maxScanned;

        int scoreSum = 0;
        
        for (int i = 0; i < nOfBooksInLib; i++)
		{
            int bookId;
            fscanf(instance, " %i", &bookId);
            libs->addBook(libId, bookId); // shallow copy

            scoreSum += Books::getScore(bookId);
            SumOfScoresOfAllBooksInLibs += Books::getScore(bookId);
        }
        libs->getLibByID(libId)->ScoresSum = scoreSum;
        libs->getLibByID(libId)->setAverageScore(scoreSum/nOfBooksInLib);
        float estimatedValue = (scoreSum / nOfBooksInLib) * maxScanned * (D - timeToRegister);
        libs->setEstimatedValue(libId,estimatedValue<scoreSum?estimatedValue:scoreSum);
        libs->getLibByID(libId)->sortBooks(compareByScore);
    }
    libs->averageMaxScanned = SumOfMaxScanned/nOfLibraries;
    cout<<"averageMaxScanned "<<libs->averageMaxScanned<<endl;
    libs->averageSignupTime = SumOfSingupTimes/nOfLibraries;
    cout<<"averageSignupTime "<<libs->averageSignupTime<<endl;
    Books::setAverageScore(SumOfScoresOfAllBooksInLibs/NoOfAllBooks);
    cout<<"AverageScore of book in liblary "<<Books::getAverageScore()<<endl;
    
    libs->loss = (D/libs->averageSignupTime)*libs->averageMaxScanned*Books::getAverageScore();
    cout<<"loss "<<libs->loss<<endl;
}

int main(int argc, char** argv){
    auto start = std::chrono::high_resolution_clock::now();
	cout<<"=========================================================="<<endl;
	
	Books books = Books();
	Libraries libs = Libraries();

    if(argc < 1){
        std::cerr << "Too few arguments!\nCorrect command: ./$name$ [instance]\n";
        return 1;
    }
    
    //this works only for particular instance:
    //string inst = "C:\\Users\\�ukasz\\Desktop\\studia\\3rd semester\\CO\\project\\vs\\CO_project\\repo\\instances\\b_read_on.txt";
    //FILE* instance = fopen(inst.c_str(), "r");
    
    //It's better to use this and chose instance in cmd:
	FILE* instance = fopen(argv[1],"r");

    if(!instance){
        std::cerr << "Can't open " << argv[1] <<'\n';
        return 1;
    }

    int nOfBooks, nOfLibraries, nOfDays; // B L D
    fscanf(instance," %i %i %i", &nOfBooks, &nOfLibraries, &nOfDays);
    
    long long scoresSum = readBooks(&books,instance,nOfBooks);
    
    readLibs(&libs, instance, nOfLibraries,nOfDays);

    Solution exampleSol = Solution(nOfBooks);
    exampleSol.constructGreedy(nOfDays,nOfBooks,nOfLibraries,&libs);
    exampleSol.evaluate(nOfDays,nOfBooks);
    //cout<< "solution eval: "<<exampleSol.getEvaluationJerzy()<<endl;
    cout<< "Solution value percentage: " << (double)exampleSol.getEvaluationJerzy() / (double)scoresSum << '\n';
    //GeneticAlgorithm alg = GeneticAlgorithm(nOfDays,nOfBooks);
    //std::cout << "Solution value percentage: " << (double)alg.evaluate(&exampleSol) / (double)scoresSum << '\n';
    //exampleSol.printSolution(nOfDays,nOfBooks);
    //exampleSol.print(nOfDays,nOfBooks);
    
	books.clear();
	libs.clear();
    fclose(instance);

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    std::cout << "Elapsed time: " << elapsed << " seconds" << std::endl;
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
