#include "libraries.hpp"
#include "books.hpp"

float Clustering::distance(Library* A, Library* B)
{           
            int SimmilarBooks = 0;
			int a = 0;
			int b = 0;
			int Abook;
			int Bbook;
			while(a<A->getN()&&b<B->getN())
			{
				Abook = A->books->get(a);
				Bbook = B->books->get(b);
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
		float intersectionCardinality = SimmilarBooks;
		float unionCardinality = A->getN() + B->getN() - SimmilarBooks;
		float simmilarity = intersectionCardinality/unionCardinality;
		return 1.0 - simmilarity;
		}