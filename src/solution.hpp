#pragma once
#include "library.hpp"
#include <vector>

class Solution {
	private:
		std::vector<int>* libraries; //combination of libraries IDs
		int* assignedIds; //array index = book id -> array value = library id
		int nOfBooks;
		int evaluation; // value of a solution
	public:
		Solution(int);
		~Solution();
		//std::string* toString();
		int numberOfLibs();
		int numberOfBooks();

		void mutateLibs();
		void mutateBooks();
		Solution* crossWith(Solution*);
		void setEvaluation(int);

		std::vector<int>* getLibs();

		void printSolution(int D, int B); //used only for printing the final solution into standard output
};