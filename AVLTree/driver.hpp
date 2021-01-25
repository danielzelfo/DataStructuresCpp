/*  Program: California Counties Database Program (with extra credit)
 *	Author: Daniel Zelfo
 *	Class: CSCI 220
 *	Date: 11/4/2019
 *	Description: This Program includes an AVLTree that holds the content of the California counties database. The AVLTree is a derived class of SearchTree, which uses a Linked Binary Tree to hold its content.
 * The AVLTree can be constructed using a file that has the county code, population, and name in each line.
 * Each record is held inside an AVLEntry, which is derived from a Search Tree Entry.
 *
 *
 I certify that the code below is my own work.
 *
 *	Exception(s): N/A
 *
 */

#include <iostream>
#include "AVLTree.hpp"


void avlTreeMain()
{
	cout << "Calfifornia Counties Population Database Program" << endl << "Author: Daniel Zelfo" << endl;
	AVLTree population("AVLTree/P4Medium.txt");
	population.menu();
}