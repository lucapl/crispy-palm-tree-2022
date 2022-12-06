#pragma once
#include "library.hpp"
#include <vector>

class Solution {
	private:
		std::vector<int>* libraries; //combination of libraries
		int* assignedIds; //array index = book id -> array value = library id 
		int evaluation; // value of a solution
	public:
		Solution();
		~Solution();
		//std::string* toString();
		int numberOfBooks();

		void mutateLibs();
		void mutateBooks();
		Solution* crossWith(Solution*);
		void setEvaluation(int);

		void printSolution(int D, int B) //used only for printing the final solution into standard output
};