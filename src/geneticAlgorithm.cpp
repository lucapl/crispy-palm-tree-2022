#include "geneticAlgorithm.hpp"

int GeneticAlgorithm::evaluate(Solution* sol,int D,int B){
    /*will be usefull for genetic algorithm (will add evaluation value for particular genotype).
		the evaluation value should be the same as the final score, if this genotype will be choosen as a solution (if D and B are correct)*/
    int M, T, N, RemainingDaysForScanningInThisLiblary, bookIterator, RemainingBooksInLiblarary;
    int finalScore = 0;
    book Thebook;
    bool scanned[B] = { false };
    
    int LenGenotype = sol.numberOfBooks();
    for(int i = 0; i<LenGenotype; ++i)
    {
        bookIterator = 0;
        D -= genotype[i]->T;
        RemainingDaysForScanningInThisLiblary = D;
        RemainingBooksInLiblarary = genotype[i]->N;
        while(RemainingDaysForScanningInThisLiblary>0&&RemainingBooksInLiblarary>0)
        {
            for(int j = M;M>=0;--j)
            {
                Thebook = genotype[i]->books[bookIterator];
                if(scanned[Thebook.ID] == false)
                {
                    finalScore += Thebook.score;
                    scanned[Thebook.ID] = true;
                }
                RemainingBooksInLiblarary--;
                bookIterator++;
                if(RemainingBooksInLiblarary == 0)
                {
                    break;
                }
            }
            RemainingDaysForScanningInThisLiblary--;
        }
    }
return finalScore;
}