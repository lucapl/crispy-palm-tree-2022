#pragma once
#include "library.hpp"
#include <vector>

class Solution {
	private:
		std::vector<int>* libraries; //combination of libraries IDs
		int* assignedIds; //array index = book id -> array value = library id
		int nOfBooks;
		int booksAssigned;
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

		void assignBookToLib(int bookId, int libId);
		void addLibId(int libId);
		void assignBooksInitially(int days,int bookCount);
		void constructGreedy(int D,int B,int L);

		std::vector<int>* getLibs();
		int* getAssignedIds();
		int getLibIdAssignedTo(int book);
		int getEvaluation();
		int getLibIdByIndex(int);

		void printSolution(int D, int B ); //used only for printing the final solution into standard output

		Solution* copy();
		bool equals(Solution*);
};