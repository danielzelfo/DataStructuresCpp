/*  Program: List v1.1
Author: Daniel Zelfo
Class: CSCI 220
Date: 10/16/2019
Description: 
			This program implements a List. The functions include insert and erase at any given position.
			The list is essentially a doubly linked list, and its positions are obtained by the Iterator class.
			v1.1: I also implemented a Sequence with the functions indexOf and atIndex.

I certify that the code below is my own work.

Exception(s): N/A

*/
#include <iostream>
#include "Sequence.h"

void listMain()
{
	cout << "Author: Daniel Zelfo\nList v1.0\n\n";


	
	//creating a new list and sequence
	List myList;
	Sequence mySeq;



	//inserting from the back
	cout << "Inserting \"one\" and \"two\" from the back...\n";
	myList.insertBack("one");
	myList.insertBack("two");

	myList.print();
	cout << endl;
	cout << "Size: " << myList.size() << "\n\n";


	cout << "Inserting \"three\" and \"four\" from the back...\n";
	myList.insertBack("three");
	myList.insertBack("four");

	myList.print();
	cout << endl;
	cout << "Size: " << myList.size() << "\n\n";

	//inserting from the front
	cout << "Inserting \"a\" and \"b\" from the front...\n";
	myList.insertFront("a");
	myList.insertFront("b");

	myList.print();
	cout << endl;
	cout << "Size: " << myList.size() << "\n\n";

	cout << "Inserting \"c\" and \"d\" from the front...\n";
	myList.insertFront("c");
	myList.insertFront("d");

	myList.print();
	cout << endl;
	cout << "Size: " << myList.size() << "\n\n";

	//erasing the 4th node from the front

	List::Iterator a = myList.begin();
	++++++a;

	cout << "Erasing the 4th node from the front...\n";
	myList.erase(a);
	myList.print();
	cout << endl;
	cout << "Size: " << myList.size() << "\n\n";

	
	//erasing the 2nd node from the end
	a = myList.end();
	----a;

	cout << "Erasing the the 2nd node from the end...\n";
	myList.erase(a);
	myList.print();
	cout << endl;
	cout << "Size: " << myList.size() << "\n\n";


	//inserting at the position of 4th node from the front
	a = myList.begin();
	++++++++a;
	cout << "Inserting at the 5th position from the front...\n";
	myList.insert(a, "e");
	myList.print();
	cout << endl;
	cout << "Size: " << myList.size() << "\n\n";

	cout << endl;


	
	//populating the sequence
	for (int i = 0; i < 10; i++) {
		char let = 'a' + i;
		mySeq.insertBack(string(1, let));
	}

	//printing the sequence
	mySeq.print();
	cout << "\n\n";

	//testing the atIndex and indexOf sequence functions
	for (int i = 0; i < 10; i++) {
		List::Iterator curIt = mySeq.atIndex(i);
		cout << mySeq.indexOf(curIt) << " : " << *curIt << endl;
	}
}