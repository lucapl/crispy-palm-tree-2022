#pragma once

class Books{
    private:
        static int* scores;
    public:
        //Books();
        //~Books();
        int getScore(int index);
        static void clear();
        modify(int id,int score);

        compareByScore(int a, int b);
        compareByID(int a, int b);
};