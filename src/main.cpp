#include<cstdio>
#include<vector>
#include<algorithm>
#include <chrono>
#include <fstream>
#include "books.hpp"
#include "libraries.hpp"
#include "solution.hpp"
#include "geneticAlgorithm.hpp"
#include "timer.hpp"
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
	std::cout << "Upper bound: " << scoresSum << '\n';//to be deleted
    return scoresSum;
}

void readLibs(Libraries* libs, istream& input, int nOfLibraries,int D) {
	int NoOfAllBooks = 0; //not neccesary different just all books that exist in liblaries 
	int SumOfScoresOfAllBooksInLibs = 0; //whenever they appear several times (it is needed just to calcualte average score of sccaned book)
	int SumOfSingupTimes = 0;
	int SumOfMaxScanned = 0;
	
    for (int libId = 0; libId < nOfLibraries; libId++){
        int nOfBooksInLib, timeToRegister, maxScanned; // N T M
        //fscanf(instance, " %i %i %i", &nOfBooksInLib, &timeToRegister, &maxScanned);
	    input >> nOfBooksInLib >> timeToRegister >> maxScanned;

        libs->modifyLib(libId,nOfBooksInLib, timeToRegister, maxScanned);
        
        NoOfAllBooks += nOfBooksInLib;
        SumOfSingupTimes += timeToRegister;
        SumOfMaxScanned += maxScanned;

        int scoreSum = 0;
        
        for (int i = 0; i < nOfBooksInLib; i++){
            int bookId;
	        input >> bookId;
            libs->addBook(libId, bookId);

            Books::addOccurence(bookId);

            scoreSum += Books::getScore(bookId);
            SumOfScoresOfAllBooksInLibs += Books::getScore(bookId);
        }
        libs->getLibByID(libId)->ScoresSum = scoreSum;
        libs->getLibByID(libId)->setAverageScore((double)scoreSum/nOfBooksInLib);
        //float estimatedValue = ((float)scoreSum / nOfBooksInLib) * maxScanned * (D - timeToRegister);
        //libs->setEstimatedValue(libId,estimatedValue<scoreSum?estimatedValue:scoreSum);

        libs->getLibByID(libId)->sortBooks(compareByScore);
    }
    libs->setAverageM((double)SumOfMaxScanned/nOfLibraries);
    cout<<"averageMaxScanned "<<libs->getAverageM()<<endl; //print to be deleted
    libs->setAverageT((double)SumOfSingupTimes/nOfLibraries); 
    cout<<"averageSignupTime "<<libs->getAverageT()<<endl; //print to be deleted
    Books::setAverageScore((double)SumOfScoresOfAllBooksInLibs/NoOfAllBooks);
    cout<<"AverageScore of book in liblary "<<Books::getAverageScore()<<endl; //print to be deleted
    
    libs->setLoss(libs->getAverageM()*Books::getAverageScore() / libs->getAverageT());
    cout<<"Loss/day "<<libs->getLoss()<<endl; // print to be deleted
}

void probabilityEstimate(int B,int D,int L) {
    double probabilityAvgBookScore = 0;
    for (int bookId = 0; bookId < B; bookId++) {
        probabilityAvgBookScore += (double)Books::getScore(bookId) * (double)Books::getFrequency(bookId) / B;
    }
    Libraries::setLoss((D / Libraries::getAverageT()) * Libraries::getAverageM() * probabilityAvgBookScore);

    for (int libId = 0; libId < L; libId++) {
        Library* lib = Libraries::getLibByID(libId);
        double probabilityScoreSum = 0;

        for (int bookId = 0; bookId < lib->getN();bookId++) {
            int bookScore = Books::getScore(bookId);
            probabilityScoreSum += (double)bookScore * (1-((double)Books::getFrequency(bookId) / B));
        }
        double estimatedValue = ((double)probabilityScoreSum / lib->getN());

        //Libraries::setEstimatedValue(libId, estimatedValue);
        //lib->setAverageScore(estimatedValue<probabilityScoreSum?estimatedValue:probabilityScoreSum);
        lib->setAverageScore(estimatedValue);
    }
}

int main(int argc, char** argv){
    Timer timer = Timer();
    timer.setMaxTime(240);
	cout<<"=========================================================="<<endl;//print to be deleted before sending the project
	
	Books books = Books();
	Libraries libs = Libraries();

	//ifstream file("C:\\Users\\£ukasz\\Desktop\\studia\\3rd semester\\CO\\project\\vs\\CO_project\\repo\\instances\\d_tough_choices.txt");
	//istream* input = &file;// 
	istream* input = &std::cin;

    //if(){
    //    std::cerr << "Can't open " << argv[1] <<'\n';
    //    return 1;
    //}

    int nOfBooks, nOfLibraries, nOfDays; // B L D
	*input >> nOfBooks >> nOfLibraries >> nOfDays;
    Libraries::setL(nOfLibraries);
    Books::setB(nOfBooks);
    //fscanf(instance," %i %i %i", &nOfBooks, &nOfLibraries, &nOfDays);
    
    long long scoresSum = readBooks(&books,*input,nOfBooks);
    
    readLibs(&libs, *input, nOfLibraries,nOfDays);
 
    probabilityEstimate(nOfBooks,nOfDays,nOfLibraries);

    Solution exampleSol = Solution(nOfBooks);
    exampleSol.constructGreedy(nOfDays,nOfBooks,nOfLibraries);
    exampleSol.evaluate(nOfDays, nOfBooks);
    long long int initialEval = exampleSol.getEvaluation();
    GeneticAlgorithm alg = GeneticAlgorithm(100,nOfDays, nOfBooks,nOfLibraries,0.05,0.6);
    //Solution allSol = Solution(0);
    //for (int libId = 0; libId < nOfLibraries; libId++) {
    //    allSol.addLibId(libId);
    //}
    //alg.initializePopulation(&allSol);
    //Solution emptySol = Solution(nOfBooks);
    //alg.initializePopulation(&emptySol,95);
    alg.initializePopulation(&exampleSol);
    alg.evolve(10000, 100);
    Solution* bestSol = alg.getBestSolution();
    long long int bestVal = bestSol->getEvaluation();
    cout<< "solution eval: "<< bestSol->getEvaluation()<<endl;
    cout<< "Solution value percentage: " << (double)bestVal / (double)scoresSum << '\n';//print to be deleted
    cout << "Improvement: " << bestVal -initialEval << endl;
    //std::cout << "Solution value percentage: " << (double)alg.evaluate(&exampleSol) / (double)scoresSum << '\n';
    //
    //exampleSol.print(nOfDays,nOfBooks); // only print the solution !!!!
    //exampleSol.print(nOfDays,nOfBooks);
    
	
    //file.close();
    std::cout << "Elapsed time: " << timer.elapsedTime().count() << " seconds" << std::endl;// to be deleted

    //double len = 20;
    //for (int val : *alg.bestValues) {
    //    int squares = (int)(len*(double)val / bestVal);
    //    for (int i = 0; i < squares;i++) {
    //        std::cout << 'E';
    //    }
    //    std::cout << endl;
    //}
    //exampleSol.print(nOfDays, nOfBooks);
    books.clear();
    libs.clear();
    return 0;
}

