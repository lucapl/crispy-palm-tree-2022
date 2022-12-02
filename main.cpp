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

void printSolution(library* genotype[],int LenGenotype,int D, int B)
{
	int M, T, N, RemainingDaysForScanningInThisLiblary, bookIterator, RemainingBooksInLiblarary;
	book Thebook;
	vector<int>ScanningQueueOfTheLiblary;
	//unordered_set<book> scanned;
	bool scanned[B] = { false };
	
	cout<<LenGenotype<<endl;
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
				//if book not in scanned
				//if (scanned.contains(Thebook) == false)
				if(scanned[Thebook.ID] == false)
				{
					ScanningQueueOfTheLiblary.push_back(Thebook.ID);
					//add to scanned
					//scanned.insert(Thebook)
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
		cout<<genotype[i]->ID<<" "<<ScanningQueueOfTheLiblary.size()<<endl;
		for(int k = 0; k < ScanningQueueOfTheLiblary.size(); ++k)
		{
			cout<<ScanningQueueOfTheLiblary[k]<<" ";
		}
		cout<<endl;
		ScanningQueueOfTheLiblary.clear();
	}
}

bool compare2books(book a, book b)
{
	return a.score > b.score;
}

static library libs[100000];

static bool visited[100000];

int main(int argc, char** argv){
	
	library* genotype[100000];

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

    printf("Theoretical upper bound: %lli\n", book_scores_sum);

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
        
        sort(libs[i].books.begin(), libs[i].books.end(), compare2books);
        /*	to chect if is sorts correctly (it does)
        for(int k = 0; k < libs[i].books.size(); ++k)
		{
			cout<<libs[i].books[k].ID<<"-"<<libs[i].books[k].score<<" ";
		}
		cout<<endl;
        */
        
        //temporary:
        genotype[i] = &libs[i];
    }
    
    printSolution(genotype,L,D,B);
    
    fclose(instance);
    return 0;
}
