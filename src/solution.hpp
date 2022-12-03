#pragma once
#include "library.hpp"
#include <vector>

class Solution {
	private:
		std::vector<int>* libraries; //combination of libraries
		int* assignedIds; //array index = book id -> array value = library id 
	public:
		Solution();
		~Solution();
		std::string* toString();
		void mutateLibs();
		void mutateBooks();
		Solution* crossWith(Solution*);
};