//Command: ./solution_test [instance] //no more valid (idk how to run it)
/*
#include<cstdio>
#include<vector>
#include<algorithm>
*/
#include <bits/stdc++.h>

using namespace std;

static int book_scores[100000];
static int book_visited[100000];

struct book
{
	int ID;
	int score;
};

struct library
{
	int ID;
    int T;
    int M;
    int N;

    vector<book>books;
};

class Clustering
{
	public:
		/*
		Clculates distance between two liblaries with worst case time complexity a+b,
		where:
		a = number of books in liblary A
		b = number of books in liblary B
		both liblaries need to have their books sorted
		*/
		float distance(library* A, library* B)
		{
			int SimmilarBooks = 0;
			int a = 0;
			int b = 0;
			int Abook;
			int Bbook;
			while(a<A->N&&b<B->N)
			{
				Abook = A->books[a].ID;
				Bbook = B->books[b].ID;
				if(Abook == Bbook)
				{
					++a;
					++b;
					++SimmilarBooks;
				}
				else if(Abook > Bbook)
				{
					++b;
				}
				else
				{
					++a;
				}
			}
		//this is formula proposed by me:
		float intersectionCardinality = SimmilarBooks;
		float unionCardinality = A->N + B->N - SimmilarBooks;
		float simmilarity = intersectionCardinality/unionCardinality;
		return 1.0 - simmilarity;
		}
};

class Genome
{
	public:
		library* genotype[100000];
		int LenGenotype;
		int evaluation;
		
		void printSolution(int D, int B)	//used only for printing the final solution into standard output
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
		void evaluate(int D, int B) /*will be usefull for genetic algorithm (will add evaluation value for particular genotype).
		the evaluation value should be the same as the final score, if this genotype will be choosen as a solution (if D and B are correct)*/
		{
			int M, T, N, RemainingDaysForScanningInThisLiblary, bookIterator, RemainingBooksInLiblarary;
			int finalScore = 0;
			book Thebook;
			bool scanned[B] = { false };
			
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
		this->evaluation = finalScore;
		}
};

bool compareByScore(book a, book b)
{
	return a.score > b.score;
}
bool compareByID(book a, book b)
{
	return a.ID < b.ID;
}

static library libs[100000];

static bool visited[100000];

int main(int argc, char** argv){
	
	Genome solutionGenotype;
	
    if(argc < 2){
        fprintf(stderr, "Too few arguments!\nCorrect command: ./main.cpp [instance]\n");
        return 1;
    }

    FILE* instance = fopen(argv[1],"r");

    if(!instance){
        fprintf(stderr, "Can't open %s\n", argv[1]);
        return 1;
    }

    int B, L, D;
    fscanf(instance," %i %i %i", &B, &L, &D);

    long long book_scores_sum = 0;

    for(int i = 0; i < B; ++i){
        fscanf(instance," %i", book_scores + i);
        book_scores_sum += book_scores[i];
    }

    //printf("Theoretical upper bound: %lli\n", book_scores_sum);

    for(int i = 0; i < L; ++i){
        int N, T, M;
        fscanf(instance," %i %i %i", &N, &T, &M);
		
		libs[i].ID = i;
        libs[i].T = T;
        libs[i].M = M;
        libs[i].N = N;

        for(int j = 0; j < N; ++j){
            book *b;
            b = new book;
            int score, id;
            fscanf(instance," %i", &id);
			score = book_scores[id];
			b->ID = id;
			b->score = score;
            libs[i].books.push_back(*b); //deep or shallow copy?
        }
        
        sort(libs[i].books.begin(), libs[i].books.end(), compareByID);
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
    
    fclose(instance);
    return 0;
}
