/*  Program: Adjacency Matrix Graph
 *	Author: Daniel Zelfo
 *	Class: CSCI 230
 *	Date: 5/4/2020
 *	Description: This program includes the AdjacencyMatrixGraph class, which is a list representation of an undirected graph
 *               The AdjacencyMatrixGraph class can insert vertices and edges, remove vertices and edges, print a graph, and more
 *				 The AdjacencyMatrixGraph class inherits from the Graph class, and it includes the classes InnerVertex and InnerEdge, which respectively inherit from Vertex and Edge
 *				 The AdjacencyMatrixGraph class has a constructor that takes a boolean value for whether or not the graph is directed
 *
 * I certify that the code below is my own work.
 *
 *	Exception(s): N/A
 *
 *
 */

#include <iostream>
#include <string>
#include "AdjacencyMatrixGraph.h"
#include "Graph.h"

using namespace std;


void adjacencyMatrixMain()
{
	AdjacencyMatrixGraph g1, g2(true);

	/*
		A - B
		|
		|
		C
	*/

	//inserting vertices A, B, C
	Vertex* v11 = g1.insertVertex("A");
	Vertex* v12 = g1.insertVertex("B");
	Vertex* v13 = g1.insertVertex("C");

	//inserting edges
	Edge* e11 = g1.insertEdge(v11, v12, 100);
	Edge* e12 = g1.insertEdge(v11, v13, 200);

	//printing graph 1
	cout << "Graph number 1:" << endl;
	g1.print();
	cout << endl;

	/*
		A - B
		| X |
		D - C
	*/

	//inserting vertices A,B,C,D
	Vertex* v21 = g2.insertVertex("A");
	Vertex* v22 = g2.insertVertex("B");
	Vertex* v23 = g2.insertVertex("C");
	Vertex* v24 = g2.insertVertex("D");

	//inserting edges
	Edge* e21 = g2.insertEdge(v21, v22, 100);
	Edge* e22 = g2.insertEdge(v22, v23, 100);
	Edge* e23 = g2.insertEdge(v23, v24, 100);
	Edge* e24 = g2.insertEdge(v24, v21, 100);
	Edge* e25 = g2.insertEdge(v21, v23, 140);
	Edge* e26 = g2.insertEdge(v22, v24, 150);

	//printing graph 2
	cout << "Graph number two:" << endl;
	g2.print();
	cout << endl;
}