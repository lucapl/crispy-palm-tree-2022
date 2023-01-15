#pragma once
#include "library.hpp"
#include "libraries.hpp"
#include <vector>
#include <set>

class Solution {
	private:
		std::vector<int>* libraries; //combination of libraries IDs
		std::vector<int>* libsToConsider;
		int* assignedIds; //array index = book id -> array value = library id
		int nOfBooks;
		int timeToRegister;
		int evaluation; // value of a solution
	public:
		Solution(int);
		~Solution();
		//std::string* toString();

		void mutateLibs(int D);
		void mutateBooks();
		Solution* crossWith(Solution*);

		void assignBookToLib(int bookId, int libId);
		void addLibId(int libId);
		void removeLIbId(int libId);
		void assignBooksInitially(int days,int bookCount);
		void constructGreedy(int D,int B,int L);

		// setters

		void setEvaluation(int);

		// getters

		std::vector<int>* getLibs();
		int* getAssignedIds();
		int getLibIdAssignedTo(int book);
		int getEvaluation();
		int getLibIdByIndex(int);
		int getNumberOfLibs();
		int getNumberOfBooks();
		int getTimeToRegister();

		//used only for printing the final solution into standard output
		void printSolution(int D, int B );
		void print(int D, int B);

		Solution* copy();
		bool equals(Solution*);
		
		void evaluate(int D, int B);
};