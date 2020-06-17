#ifndef AVLTree_H
#define AVLTree_H

#include "../SearchTree/SearchTree.h"
#include "AVLEntry.h"
#include "../Entry.h"
#include <utility>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

typedef int Key;
typedef pair<int, string> Value;
typedef Entry<Key, Value> E;

class AVLTree : public SearchTree< AVLEntry<E> > {

public:						// public types
	//typedef AVLEntry<E> AVLEntry;			// an entry
	typedef typename SearchTree<AVLEntry<E>>::Iterator Iterator; // an iterator
protected:
	typedef SearchTree<AVLEntry<E>> ST;			// a search tree
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

	
	auto find(const Key& k)->SearchTree<AVLEntry<E>>::Iterator;

protected:						// utility functions 
	auto inserter(const int& k, const pair<int, string>& x)->TPos;
	auto finder(const Key& k, const TPos& v, int& numExamined)->TPos;
	int height(const TPos&) const;			// node height utility
	void setHeight(TPos);				// set height utility
	bool isBalanced(const TPos&) const;		// is v balanced?
	TPos tallGrandchild(const TPos&) const;		// get tallest grandchild
	void rebalance(const TPos&);			// rebalance utility
	TPos restructure(TPos&);
	int depth(TPos);
};

typedef Entry<int, pair<int, string>> E;
typedef typename LinkedBinaryTree<E>::Position TPos;

// constructor
AVLTree::AVLTree() : ST() {
	//data member to hold how many records were examined when finding a record
	numExamined = 0;
}

AVLTree::AVLTree(string filepath) : ST() {
	numExamined = 0;
	ifstream data;
	int countyCode, countyPopulation;
	string countyName;
	string line;
	string temp;
	data.open(filepath);
	//getting each line into a string
	while (getline(data, line)) {
		countyName = "";

		//replacing the first two commas with spaces
		std::replace(line.begin(), line.end() - 5, ',', ' ');

		//making a string stream
		stringstream ss(line);

		//getting the county code and population
		ss >> countyCode;
		ss >> countyPopulation;

		//inputting the county name
		for (int i = line.length() - 2; line[i] != '"'; --i)
			countyName = line[i] + countyName;
		insert(countyCode, countyPopulation, countyName);
	}
}


// node height utility
int AVLTree::height(const TPos& v) const
{
	return (v.isExternal() ? 0 : (*v).height());
}




// insert (code, population, name)
typename AVLTree::Iterator AVLTree::insert(const int& code, const int& pop, const string& name) {
	pair<int, string> val(pop, name);
	TPos v = inserter(code, val);				// insert in base tree
	setHeight(v);					// compute its height
	rebalance(v);					// rebalance if needed
	return Iterator(v);
}


//erase a record with the county code (key) k
void AVLTree::erase(const int& k) {// throw(NonexistentElement) {
	numExamined = 0;
	TPos v = finder(k, root(), numExamined);						// search from virtual root

	if (v.isExternal())								// not found?
		throw string("Erase of nonexistent");
	//else
		//cout << "Found." << endl;
	TPos w = eraser(v);
	//cout << "Erased from binary tree." << endl;
	rebalance(w);					// rebalance if needed
	//cout << "Rebalanced." << endl;
}

//erase a record with the iterator
void AVLTree::erase(Iterator p) {
	TPos w = eraser(p.v);				// compute its height
	rebalance(w);					// rebalance if needed
}


// rebalancing utility
void AVLTree::rebalance(const TPos& v) {
	//cout << "rebalancing..." << endl;
	TPos z = v;
	while (!(z == ST::root())) {			// rebalance up to root
		++numExamined;
		z = z.parent();
		setHeight(z);					// compute new height
		if (!isBalanced(z)) {				// restructuring needed
			TPos x = tallGrandchild(z);
			z = restructure(x);				// trinode restructure
			setHeight(z.left());				// update heights
			setHeight(z.right());
			setHeight(z);
		}
	}
}

// set height utility
void AVLTree::setHeight(TPos v) {
	int hl = height(v.left());
	int hr = height(v.right());
	(*v).setHeight(1 + std::max(hl, hr));			// max of left & right
}

// is v balanced?
bool AVLTree::isBalanced(const TPos& v) const {
	int bal = height(v.left()) - height(v.right());
	return ((-1 <= bal) && (bal <= 1));
}

// get tallest grandchild
typename AVLTree::TPos AVLTree::tallGrandchild(const TPos& z) const {
	TPos zl = z.left();
	TPos zr = z.right();
	if (height(zl) >= height(zr))			// left child taller
		if (height(zl.left()) >= height(zl.right()))
			return zl.left();
		else
			return zl.right();
	else 						// right child taller
		if (height(zr.right()) >= height(zr.left()))
			return zr.right();
		else
			return zr.left();
}

//rotate right given node that will become the root
void AVLTree::rotateRight(TPos& y) {
	TPos x = y.left();
	TPos z = y.parent();
	TPos t3 = y.right();


	//setting z's parent's appropriate child to y
	if (z.parent().right() == z)
		z.v->par->right = y.v;
	else
		z.v->par->left = y.v;

	//setting y's parent to z's parent
	y.v->par = z.v->par;

	//setting y's right to z
	y.v->right = z.v;
	//setting z's parent to y
	z.v->par = y.v;

	//setting z's left to y's right
	z.v->left = t3.v;
	//setting the parent of y's right to z
	t3.v->par = z.v;
}

//rotate left given the node that will become the root
void AVLTree::rotateLeft(TPos& y) {
	TPos x = y.right();
	TPos z = y.parent();
	TPos t2 = y.left();


	//setting z's parent's appropriate child to y
	if (z.parent().right() == z)
		z.v->par->right = y.v;
	else
		z.v->par->left = y.v;

	//setting y's parent to z's parent
	y.v->par = z.v->par;

	//setting y's left to z
	y.v->left = z.v;

	//setting z's parent to y
	z.v->par = y.v;

	//setting z's right to y's left
	z.v->right = t2.v;
	//setting the parent of y's left to z
	t2.v->par = z.v;
}



typename AVLTree::TPos AVLTree::restructure(TPos& p) {

	TPos z = p.parent().parent();

	numExamined += 3;
	//left rotate
	if (!(p.parent().parent().right() == nullptr) && p.parent().parent().right().right() == p) {
		p = p.parent();
		rotateLeft(p);
	}
	//right left rotate
	else  if (!(p.parent().parent().right() == nullptr) && p.parent().parent().right().left() == p) {
		rotateRight(p);
		rotateLeft(p);

	}
	//right rotate
	else if (p.parent().parent().left().left() == p) {
		p = p.parent();
		rotateRight(p);
	}
	//left right rotate
	else if (p.parent().parent().left().right() == p) {
		rotateLeft(p);
		rotateRight(p);
	}
	return p;
}

void AVLTree::draw() {
	queue<TPos> tposQueue;
	tposQueue.push(ST::root());
	int c = 0;
	string space(4 * pow(2, (*ST::root()).height())/2 - 1, ' ');
	TPos cur = tposQueue.front();
	int spaceLength = 1;
	while (!tposQueue.empty())
	{
		

		if (!cur.isExternal()){
			tposQueue.push(cur.left());
			tposQueue.push(cur.right());
		}
		else {
			TPos x, y;
			x.v->par = cur.v;
			y.v->par = cur.v;

			tposQueue.push(x);
			tposQueue.push(y);
		}
		tposQueue.pop();


		cout << space << (cur.isExternal() ? "|  |" : to_string((*cur).key()));
		
		if (!tposQueue.empty() && depth(tposQueue.front()) > depth(cur)){
			cout << "\n\n";
			spaceLength = 4 * pow(2, (*ST::root()).height() - depth(cur) - 2);
		}
		else
			spaceLength = 4 * (pow(2, (*ST::root()).height() - depth(cur)) - 1);

		space = string(spaceLength > 0 ? spaceLength : 1, (c % 2 == 0 ? ' ' : '-'));

		cur = tposQueue.front();
		

		bool cont = false;
		for (unsigned int i = 0; i < tposQueue.size(); ++i) {
			
			TPos x = tposQueue.front();
			if (!x.isExternal()){
				cont = true;
			}
			tposQueue.push(x);
			tposQueue.pop();
		}
		if (!cont)
			break;
		++c;
	}

	cout << endl;

}

/*
void AVLTree::draw()
{
	// Create an empty stack and push root to it 
	stack<TPos> tposStack;
	tposStack.push(ST::root());
	while (!tposStack.empty())
	{
		// Pop the top item from stack and print it 

		TPos cur = tposStack.top();
		cout << string(4 * depth(cur), '_') << (*cur).key() << endl;
		if (!cur.right().isExternal() && !cur.left().isExternal())
			cout << string(4 * depth(cur), ' ') << '|' << endl;
		tposStack.pop();

		// Push right and left children of the popped node to stack 
		if (!cur.right().isExternal())
			tposStack.push(cur.right());
		if (!cur.left().isExternal())
			tposStack.push(cur.left());
	}
}
*/

//list all records
void AVLTree::list() {
	Iterator cur = begin();
	cout << "Size: " << size() << endl;
	int i = 0;
	//traversing through search tree
	while (i < size()) {
		cout << (*cur).key() << " " << (*cur).value().first << " " << (*cur).value().second << endl;
		++cur;
		++i;
	}
}

//menu to use program
void AVLTree::menu() {
	int option, code, population;
	string name;
	cout << "0. Display tree \n1. Search for a record \n2. Insert a record \n3. Delete a record \n4. List all records \n5. Exit\n>";
	cin >> option;

	//enter 5 to exit
	while (option != 5) {

		//enter 0 to draw the tree
		if (option == 0)
			draw();

		//enter 1 to search for a record
		else if (option == 1) {
			cout << "Enter County Code to Search: ";
			cin >> code;
			Iterator record = find(code);
			if ((*record).height() == 0)
				cout << "Record not found.\n";
			else
				cout << "Record found: " << endl << (*record).key() << " " << (*record).value().first << " " << (*record).value().second << endl;
			cout << numExamined << " records examined." << endl;
		}

		//enter 2 to insert a record
		else if (option == 2) {
			cout << "Enter record to insert\n";
			cout << "Enter county code: ";
			cin >> code;
			cout << "Enter county population: ";
			cin >> population;
			cout << "Enter county Name: ";
			cin.ignore();
			getline(cin, name);
			insert(code, population, name);
			cout << "Record added." << endl;
			cout << numExamined << " records examined." << endl;
		}

		//enter 3 to erase a record
		else if (option == 3) {
			cout << "Enter County Code to Delete: ";
			cin >> code;
			try {
				erase(code);
				cout << "Record removed." << endl;
			}
      catch (string e) {
				cout << e << endl;
			}
			catch (...) {
				cout << "There was an error" << endl;
			}
			cout << numExamined << " records examined." << endl;
		}

		//enter 4 to list all records
		else if (option == 4)
			list();

		cout << ">";

		cin >> option;
		cin.ignore(10000, '\n');
		numExamined = 0;
	}

}

//finder that increments the number of nodes examined
auto AVLTree::finder(const Key& k, const TPos& v, int& numExamined) -> TPos {
	++numExamined;
	if (v.isExternal()) return v;
	if (k < (*v).key()) return finder(k, v.left(), numExamined);
	else if ((*v).key() < k) return finder(k, v.right(), numExamined);
	else return v;
}

//find that resets the number of examined
auto AVLTree::find(const Key& k) -> SearchTree<AVLEntry<E>>::Iterator {
	numExamined = 0;
	TPos v = finder(k, root(), numExamined); //uses finder function
	if (!v.isExternal()) return Iterator(v);
	else return end();
}


//inserter that resets the number of nodes examined
auto AVLTree::inserter(const int& k, const pair<int, string>& x) -> TPos {
	numExamined = 0;
	TPos v = finder(k, root(), numExamined);
	//overwriting
	if ((*v).key() == k) {
		(*v).setValue(x);
	}
	else {
		expandExt(v);
		(*v).setKey(k);
		(*v).setValue(x);
		increaseSize();
	}



	return v;
}

//find the depth of a given binary tree position
int AVLTree::depth(TPos p) {
	int d = 0;
	while ( !(p == ST::root())) {
		++d;
		p = p.parent();
	}
	return d;
}


#endif