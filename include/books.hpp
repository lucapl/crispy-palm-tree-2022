#pragma once

class Books{
    private:
        static unsigned int B;

        static int* scores;
        static float averageScore;
        static int* bookCounts;
    public:
        static unsigned int getB(void);
        static void setB(unsigned int);

        static int getScore(int index);
        static void clear();
        static void modify(int id,int score);

        static bool compareByScore(int a, int b);
        static bool compareByID(int a, int b);
        
        static void setAverageScore(float score);
        static float getAverageScore();
        
        static int getFrequency(int bookId);
        static void addOccurence(int bookId);
};
