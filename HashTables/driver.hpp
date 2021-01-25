/*  Program: Hashing
 *	Author: Daniel Zelfo
 *	Class: CSCI 230
 *	Date: 3/23/2020
 *	Description: This program is made up of three different hash table classes, which use three different hashing schemes: Chain Hashing, Linear Probe Hashing, and Double Hashing.
 *				 Each class can be constructed using an input file and can take a load factor to use.
 *				 The hash tables use the Hasher class to generate a hash code for any given key.
 *				 Each record is stored in an Entry.
 *				 The user can search, insert, and erase records in O(1) using these hash tables.
 *
 *
 I certify that the code below is my own work.
 *
 *	Exception(s): N/A
 *
 */

#include <iostream>
#include <string>

#include "ChainHashing.hpp"
#include "LinearProbeHashing.hpp"
#include "DoubleHashing.hpp"

#include "Hash.hpp"


using namespace std;

void hashTablesMain()
{
	int fn;
	string filename;
	int hashScheme;
	float loadFactor;

	//inputting the file name


	cout << "Enter file name: " << endl
		<< "1 for p1small.txt" << endl
		<< "2 for p1large.txt" << endl
		<< "3 for other\n>";
	cin >> fn;


	while (fn < 1 || fn > 3) {
		cout << "Enter file name: " << endl
			<< "1 for p1small.txt" << endl
			<< "2 for p1large.txt" << endl
			<< "3 for other\n>";
		cin >> fn;
	}

	if (fn == 1)
		filename = "HashTables/p1small.txt";
	else if(fn == 2)
		filename = "HashTables/p1large.txt";
	else {
		cout << "Enter file name: ";
		cin >> filename;
		filename = "HashTables/" + filename;
	}

	cout << endl;

	//inputting the hashing scheme

	cout << "Enter hashing scheme:" << endl
		<< "1 for Chain Hashing" << endl
		<< "2 for Linear Probe Hashing" << endl
		<< "3 for Double Hashing\n>";
	cin >> hashScheme;
	while (hashScheme < 1 || hashScheme > 3) {
		cout << "Enter hashing scheme:" << endl
			<< "1 for Chain Hashing" << endl
			<< "2 for Linear Probe Hashing" << endl
			<< "3 for Double Hashing\n>";
		cin >> hashScheme;
	}

	cout << endl;


	//inputting the load factor


	cout << "Enter load factor: ";
	cin >> loadFactor;
	while (loadFactor <= 0 || loadFactor > 1) {
		cout << "Enter load factor: ";
		cin >> loadFactor;
	}

	cout << endl;

	if (hashScheme == 1) {
		ChainHashing<int, int, string, Hasher<int>> cHashTable(filename, loadFactor);
		cHashTable.menu();
	} else if (hashScheme == 2) {
		LinearProbeHashing<int, int, string, Hasher<int>> lHashTable(filename, loadFactor);
		lHashTable.menu();
	} else {
		DoubleHashing<int, int, string, Hasher<int>> dHashTable(filename, loadFactor);
		dHashTable.menu();
	}
	
}