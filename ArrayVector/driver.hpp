/*  Program: ArrayVector (with extra credit)
 *	Author: Daniel Zelfo
 *	Class: CSCI 220
 *	Date: 10/7/2019
 *	Description: This program implements a vector using an extendable array.
 *				 Member functions of the ArrayVector class include size, maxSize, empty, resize, append, eraseAt, eraseLast, and print.
 *
 *	I certify that the code below is my own work.
 *
 *	Exception(s): N/A
 *
 */


#include <iostream>
#include "ArrayVector.hpp"

using namespace std;

void arrayVectorMain()
{
    //creating a new vector with max size 50
	ArrayVector<int> vect(50);
	
	//appending 99 elements to the vector to test the auto resize
	for (int i = 0; i < 99; i++) {
		vect.append(i);
	}

	//printing the vector
	vect.print();

	//erasing the last 75 elements to test the auto shrink to fit (extra credit)
	for (int i = 0; i < 75; i++) {
		vect.eraseLast();
	}

	//printing the vector
	vect.print();
}
