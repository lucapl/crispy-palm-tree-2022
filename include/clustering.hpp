#pragma once
#include "library.hpp"

class Clustering{
	public:
		/*
		Clculates distance between two liblaries with worst case time complexity a+b,
		where:
		a = number of books in liblary A
		b = number of books in liblary B
		both liblaries need to have their books sorted
		*/
		float distance(Library* A, Library* B);
};