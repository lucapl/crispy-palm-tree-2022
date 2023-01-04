#pragma once

class Books{
    private:
        static int* scores;
    public:
        //Books();
        //~Books();
        static int getScore(int index);
        static void clear();
        static void modify(int id,int score);

        static bool compareByScore(int a, int b);
        static bool compareByID(int a, int b);
};