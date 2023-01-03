#include "geneticAlgorithm.hpp"
#include "books.hpp"
#include "libraries.hpp"

int GeneticAlgorithm::evaluate(Solution* sol,int D,int B){
    /*will be usefull for genetic algorithm (will add evaluation value for particular genotype).
		the evaluation value should be the same as the final score, if this genotype will be choosen as a solution (if D and B are correct)*/
    int M, T, N, remainingDaysForScanningInThisLiblary, bookIterator, remainingBooksInLiblarary;
    int finalScore = 0;
    int theBook;
    bool* scanned = new bool[B];
    for (int i = 0; i < B; i++) {
        scanned[i] = false;
    }
    
    //Libraries* libs = new Libraries();
    //Books* books = new Books();

    int LenGenotype = sol->numberOfLibs();
    for(int libID : *sol->getLibs()){
        bookIterator = 0;
        Library* lib = Libraries::getLibByID(libID);
        D -= lib->getT();
        remainingDaysForScanningInThisLiblary = D;
        remainingBooksInLiblarary = lib->getN();
        M = 0;
        while(remainingDaysForScanningInThisLiblary>0&&remainingBooksInLiblarary>0){
            for(int j = M;M>=0;--j)
            {
                theBook = lib->getBookIDAt(bookIterator);
                if(scanned[theBook] == false)
                {
                    finalScore += Books::getScore(theBook);
                    scanned[theBook] = true;
                }
                remainingBooksInLiblarary--;
                bookIterator++;
                if(remainingBooksInLiblarary == 0)
                {
                    break;
                }
            }
            remainingDaysForScanningInThisLiblary--;
        }
    }
    delete[] scanned;
    return finalScore;
}