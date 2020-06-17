#ifndef AVLTree_H
#define AVLTree_H

#include "SearchTree.h"
#include "AVLEntry.h"
#include "Entry.h"
#include <utility>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>

using namespace std;


typedef Entry<int, pair<int, string>> E;

class AVLTree : public SearchTree< AVLEntry<E> > {

public:						// public types
	typedef AVLEntry<E> AVLEntry;			// an entry
	typedef typename SearchTree<AVLEntry>::Iterator Iterator; // an iterator
protected:
	typedef SearchTree<AVLEntry> ST;			// a search tree
	typedef typename ST::TPos TPos;			// a tree position


private:
	void rotateRight(TPos&);
	void rotateLeft(TPos&);
	int numExamined;
public:						// public functions
	AVLTree();						// constructor
	AVLTree(string filepath);
	Iterator insert(const int& countyCode, const int& population, const string& countyName);		// insert (k,x)
	void erase(const int& countyCode);// throw(NonexistentElement);	// remove keyentry
	void erase(Iterator);			// remove entry with iterator
	
	//draw a tree
	void draw();

	//list all entries
	void list();
	void menu();

	
	auto find(const K& k)->SearchTree<AVLEntry>::Iterator;

protected:						// utility functions 
	auto inserter(const int& k, const pair<int, string>& x)->TPos;
	auto finder(const K& k, const TPos& v, int& numExamined)->TPos;
	int height(const TPos&) const;			// node height utility
	void setHeight(TPos);				// set height utility
	bool isBalanced(const TPos&) const;		// is v balanced?
	TPos tallGrandchild(const TPos&) const;		// get tallest grandchild
	void rebalance(const TPos&);			// rebalance utility
	TPos restructure(TPos&);
	int depth(TPos);
};

#endif