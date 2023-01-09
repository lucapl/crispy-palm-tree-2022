#include<cstdio>
#include<vector>
#include<algorithm>
//#include <bits/stdc++.h>
#include <chrono>
#include <fstream>
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

long long readBooks(Books* books,istream& input,int nOfBooks){
    long long scoresSum = 0;
    for(int bookId = 0; bookId < nOfBooks; bookId++){
		int score;
        //fscanf(instance," %i", &score);
	input >> score;
		books->modify(bookId,score);
        scoresSum += score;
    }
	std::cout >> "Upper bound: " >> scoresSum >> '\n';//to be deleted
    return scoresSum;
}

void readLibs(Libraries* libs, istream& input, int nOfLibraries,int D) {
	int NoOfAllBooks = 0; //not neccesary different just all books that exist in liblaries 
	int SumOfScoresOfAllBooksInLibs = 0; //whenever they appear several times (it is needed just to calcualte average score of sccaned book)
	int SumOfSingupTimes = 0;
	int SumOfMaxScanned = 0;
	
    for (int libId = 0; libId < nOfLibraries; libId++)
	{
        int nOfBooksInLib, timeToRegister, maxScanned; // N T M
        //fscanf(instance, " %i %i %i", &nOfBooksInLib, &timeToRegister, &maxScanned);
	input >> nOfBooksInLib >> timeToRegister >> maxScanned;

        libs->modifyLib(libId, timeToRegister, maxScanned, nOfBooksInLib);
        
        NoOfAllBooks += nOfBooksInLib;
        SumOfSingupTimes += timeToRegister;
        SumOfMaxScanned += maxScanned;

        int scoreSum = 0;
        
        for (int i = 0; i < nOfBooksInLib; i++)
		{
            int bookId;
            //fscanf(instance, " %i", &bookId);
	    input >> bookId;
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
    cout<<"averageMaxScanned "<<libs->averageMaxScanned<<endl; //print to be deleted
    libs->averageSignupTime = SumOfSingupTimes/nOfLibraries; 
    cout<<"averageSignupTime "<<libs->averageSignupTime<<endl; //print to be deleted
    Books::setAverageScore(SumOfScoresOfAllBooksInLibs/NoOfAllBooks);
    cout<<"AverageScore of book in liblary "<<Books::getAverageScore()<<endl; //print to be deleted
    
    libs->loss = (D/libs->averageSignupTime)*libs->averageMaxScanned*Books::getAverageScore();
    cout<<"loss "<<libs->loss<<endl; // print to be deleted
}

int main(int argc, char** argv){
    auto start = std::chrono::high_resolution_clock::now();
	cout<<"=========================================================="<<endl;//print to be deleted before sending the project
	
	Books books = Books();
	Libraries libs = Libraries();

	//ifstream file(argv[1]);
	//istream* input = &file;// 
	istream* input = &std::cin;

    //if(){
    //    std::cerr << "Can't open " << argv[1] <<'\n';
    //    return 1;
    //}

    int nOfBooks, nOfLibraries, nOfDays; // B L D
	*input >> nOfBooks >> nOfLibraries >> nOfDays;
    //fscanf(instance," %i %i %i", &nOfBooks, &nOfLibraries, &nOfDays);
    
    long long scoresSum = readBooks(&books,*input,nOfBooks);
    
    readLibs(&libs, *input, nOfLibraries,nOfDays);

    Solution exampleSol = Solution(nOfBooks);
    exampleSol.constructGreedy(nOfDays,nOfBooks,nOfLibraries,&libs);
    exampleSol.evaluate(nOfDays,nOfBooks);
    //cout<< "solution eval: "<<exampleSol.getEvaluationJerzy()<<endl;
    cout<< "Solution value percentage: " << (double)exampleSol.getEvaluationJerzy() / (double)scoresSum << '\n';//print to be deleted
    //GeneticAlgorithm alg = GeneticAlgorithm(nOfDays,nOfBooks);
    //std::cout << "Solution value percentage: " << (double)alg.evaluate(&exampleSol) / (double)scoresSum << '\n';
    //
    exampleSol.printSolution(nOfDays,nOfBooks); // only print the solution !!!!
    //exampleSol.print(nOfDays,nOfBooks);
    
	books.clear();
	libs.clear();

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    std::cout << "Elapsed time: " << elapsed << " seconds" << std::endl;// to be deleted
    return 0;
}

