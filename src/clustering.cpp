#include "libraries.hpp"
#include "books.hpp"
#include "clustering.hpp"

float Clustering::distance(Library* A, Library* B){
            int SimmilarBooks = 0;
			int a = 0;
			int b = 0;
			int Abook;
			int Bbook;
			while(a<A->getN()&&b<B->getN())
			{
				Abook = A->getBookIDAt(a);
				Bbook = B->getBookIDAt(b);
				if(Abook == Bbook)
				{
					++a;
					++b;
					++SimmilarBooks;
				}
				else if(Abook > Bbook)
				{
					++b;
				}
				else
				{
					++a;
				}
			}
		//this is formula proposed by me:
		float intersectionCardinality = (float)SimmilarBooks;
		float unionCardinality = A->getN() + B->getN() - intersectionCardinality;
		float simmilarity = intersectionCardinality/unionCardinality;
		return 1.0 - simmilarity;
		}