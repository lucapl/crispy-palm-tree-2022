

//Command: ./solution_test [instance]

#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

static int book_scores[100000];
static int book_visited[100000];

struct library{
    int T;
    int M;

    vector<int>books;
};

static library libs[100000];

static bool visited[100000];

int main(int argc, char** argv){
    if(argc < 2){
        fprintf(stderr, "Too few arguments!\nCorrect command: ./solution_test [instance] [solution]\n");
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

        libs[i].T = T;
        libs[i].M = M;

        for(int j = 0; j < N; ++j){
            int b;
            fscanf(instance," %i", &b);

            libs[i].books.push_back(b);
        }

        sort(libs[i].books.begin(), libs[i].books.end());
    }
    fclose(instance);
    return 0;
}
