/*  Program: California Counties Database Program (with extra credit)
 *	Author: Daniel Zelfo
 *	Class: CSCI 220
 *	Date: 11/4/2019
 *	Description: This Program includes an AVLTree that holds teh content of the califronia counties database. The AVLTree is a drived class of a Search Tree, which uses a Linked Binary Tree to hold its content.
 * The AVLTree can be constructed using a file that has the county code, population and name in each line
 * Each record is held inside an AVLEntry, which is derived from an Search Tree Entry
 *
 *
 I certify that the code below is my own work.
 *
 *	Exception(s): N/A
 *
 */

#include <iostream>
#include "AVLTree.h"


int main()
{
	cout << "Calfifornia Counties Population Database Program" << endl << "Author: Daniel Zelfo" << endl;
	AVLTree population;// ("P4Medium.txt");
	population.menu();
}