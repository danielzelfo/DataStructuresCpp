/*  Program: List-based Union-Find partition structure
 *	Author: Daniel Zelfo
 *	Class: CSCI 230
 *	Date: 4/13/2020
 *	Description: This program includes the UnionFind class, which represents a Disjoint Set.
 *               It has the operations makeset, union, and find.
 *               makeset creates a new set in the structure with the given element. 
 *				 union joins together the two sets given, and find returns the set with the given element.
 * 
 * I certify that the code below is my own work.
 *
 *	Exception(s): N/A
 *
 */

#include <iostream>

#include "UnionFind.h"

using namespace std;

void printSet(UnionFind<int>::Iterator);

void unionFindMain()
{
	UnionFind<int> uf;

	cout << "Making sets 1, 2, and 3" << endl;
	//making three sets
	UnionFind<int>::Iterator 
		a = uf.makeSet(1),
		b = uf.makeSet(2),
		c = uf.makeSet(3);

	//printing all the sets
	if (a != uf.end())
		printSet(a);
	cout << "| ";
	if (b != uf.end())
		printSet(b);
	cout << "| ";
	if (c != uf.end())
		printSet(c);
	cout << endl;

	cout << "Union of sets with 1 and set with 2" << endl;
	//union of a and b
	a = uf._union(b, a);

	//printing all the sets
	if (a != uf.end())
		printSet(a);
	cout << "| ";
	if (c != uf.end())
		printSet(c);
	cout << endl;

	cout << "Union of set with 1 and 2 and set with 3" << endl;
	//union of a and c
	a = uf._union(a, c);

	//printing all the sets
	if (a != uf.end())
		printSet(a);
	cout << endl;

	cout << "Making sets 4 and 4" << endl;
	//making two more sets
	b = uf.makeSet(4);
	c = uf.makeSet(4);

	//printing all the sets
	if (a != uf.end())
		printSet(a);
	cout << "| ";
	if (b != uf.end())
		printSet(b);
	cout << "| ";
	if (c != uf.end())
		printSet(c);
	cout << endl;

	cout << "Making a set with 5" << endl;
	c = uf.makeSet(5);
	if (a != uf.end())
		printSet(a);
	cout << "| ";
	if (b != uf.end())
		printSet(b);
	cout << "| ";
	if (c != uf.end())
		printSet(c);
	cout << endl;


	cout << "Union of set including 1 and set with 4" << endl;
	//union of set with element 1 and set b
	b = uf._union(uf._find(1), b);

	//printing all the sets
	if (b != uf.end())
		printSet(b);
	cout << "| ";
	if (c != uf.end())
		printSet(c);
	cout << endl;

	cout << "Union of set with 1, 2, 3, 4 and set including 5" << endl;
	//union of set b and set with element 5
	c = uf._union(b, uf._find(5));

	//printing all the sets
	if (c != uf.end())
		printSet(c);
	cout << endl;
}

//function to print a set
void printSet(UnionFind<int>::Iterator x) {
	list<int> z = *x;
	for (auto const& i : z)
		cout << i << " ";
}