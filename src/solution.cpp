#include "solution.hpp"

void Solution::setEvaluation(int eva){
    evaluation = eva;
}

int Solution::numberOfBooks(){
    return libraries.size();
}

void Solution::printSolution(int D, int B)	//used only for printing the final solution into standard output
{
    int M, T, N, RemainingDaysForScanningInThisLiblary, bookIterator, RemainingBooksInLiblarary;
    book Thebook;
    vector<int>ScanningQueueOfTheLiblary;
    bool scanned[B] = { false };
    
    cout<<LenGenotype;
    
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
                    ScanningQueueOfTheLiblary.push_back(Thebook.ID);
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
        cout<<endl<<genotype[i]->ID<<" "<<ScanningQueueOfTheLiblary.size()<<endl;
        for(int k = 0; k < ScanningQueueOfTheLiblary.size(); ++k)
        {
            cout<<ScanningQueueOfTheLiblary[k]<<" ";
        }
        ScanningQueueOfTheLiblary.clear();
    }
}