#ifndef SearchTree_H
#define SearchTree_H

#include "LinkedBinaryTree.h"
#include "RuntimeException.h"

//Binary Search Tree
template < typename E >
class SearchTree {
public:
	typedef typename E::Key K;
	typedef typename E::Value V;
	class Iterator;
public:
	SearchTree();

	//tree information
	int size() const;
	bool empty() const;

	//find entry by key
	Iterator find(const K& k);

	//alter search tree
	Iterator insert(const K& k, const V& x);
	void erase(const K& k);// throw (NonexistentElement);
	void erase(const Iterator& p);

	//tree iterator functions
	Iterator begin();
	Iterator end();
protected:
	typedef LinkedBinaryTree<E> BinaryTree;
	typedef typename BinaryTree::Position TPos;
	TPos root() const;

	//protected tree altering function
	TPos finder(const K& k, const TPos& v);
	TPos inserter(const K& k, const V& x);
	TPos eraser(TPos& v);
	void increaseSize();
	void expandExt(const TPos&);

	
private:
	BinaryTree T;
	int n;
public:
};

template < typename E >
class SearchTree<E>::Iterator {
private: TPos v;
public:
	//constructor with binary tree position parameter
	Iterator(const TPos& vv) : v(vv) {}

	//accessor operator function
	const E& operator * () const {
		return *v;
	}
	E& operator * () {
		return *v;
	}

	//equality operator function
	bool operator == (const Iterator& p) const {
		return v == p.v;
	}
	//incrementing operator to inorder successor function
	Iterator& operator++();
	friend class SearchTree<E>;
	friend class AVLTree;
};

// iterator to first entry
template <typename E>
typename SearchTree<E>::Iterator SearchTree<E>::begin() {
	TPos v = root();						// start at virtual root				
	while (!v.isExternal()) v = v.left();	// find leftmost node
	return Iterator(v.parent());
}

// iterator to end entry
template <typename E>
typename SearchTree<E>::Iterator SearchTree<E>::end()
{

	return Iterator(T.root());	// return the super root
}

template < typename E >
SearchTree<E>::SearchTree() : T() {
	n = 0;
	T.addRoot();
	T.expandExternal(T.root());
}

//protecte root function
template < typename E >
typename SearchTree<E>::TPos SearchTree<E>::root() const {
	return T.root().left();
}

//tree size
template < typename E >
int SearchTree<E>::size() const {
	return n;
}
template < typename E >
bool SearchTree<E>::empty() const {
	return (n == 0);
}

//protected entry finder
template < typename E >
typename SearchTree<E>::TPos SearchTree<E>::finder(const K& k, const TPos& v) {
	if (v.isExternal()) return v;
	if (k < (*v).key()) return finder(k, v.left());
	else if ((*v).key() < k) return finder(k, v.right());
	else return v;
}

//public find function
template < typename E >
typename SearchTree<E>::Iterator SearchTree<E>::find(const K& k) {
	TPos v = finder(k, root()); //uses finder function
	if (!v.isExternal()) return Iterator(v);
	else return end();
}

//protected key and value inserter
template < typename E >
typename SearchTree<E>::TPos SearchTree<E>::inserter(const K& k, const V& x) {
	TPos v = finder(k, root());

	//overwriting old entry
	if ((*v).key() == k) {
		(*v).setValue(x);
	}
	else {
		T.expandExternal(v);
		(*v).setKey(k);
		(*v).setValue(x);
		n++;
	}


	
	return v;
}

//public insert function
template < typename E >
typename SearchTree<E>::Iterator SearchTree<E>::insert(const K& k, const V& x) {
	TPos v;
	v = inserter(k, x); //uses inserter function
	return Iterator(v);
}

// inorder successor
template <typename E>
typename SearchTree<E>::Iterator& SearchTree<E>::Iterator::operator++() {
	TPos w = v.right();
	if (!w.isExternal()) {				// have right subtree?
		do { v = w; w = w.left(); }		// move down left chain
		while (!w.isExternal());
	}
	else {
		w = v.parent();					// get parent
		while (v == w.right())			// move up right chain
		{
			v = w; w = w.parent();
		}
		v = w;							// and first link to left
	}
	return *this;
}

// remove utility
template <typename E>
typename SearchTree<E>::TPos SearchTree<E>::eraser(TPos& v) {
	TPos w;
	if (v.left().isExternal()) w = v.left();			// remove from left
	else if (v.right().isExternal()) w = v.right();		// remove from right
	else {												// both internal?
		w = v.right();									// go to right subtree
		do { w = w.left(); } while (!w.isExternal());	// get leftmost node
		TPos u = w.parent();
		(*v).setKey((*u).key());
		(*v).setValue((*u).value());					// copy w's parent to v
	}
	--n;												// one less entry
	return T.removeAboveExternal(w);					// remove w and parent
}

// remove key k entry
template <typename E>
void SearchTree<E>::erase(const K& k) {// throw(NonexistentElement) {
	TPos v = finder(k, root());						// search from virtual root
	if (v.isExternal())								// not found?
		throw NonexistentElement("Erase of nonexistent");
	eraser(v);										// remove it
}

template <typename E>								// erase entry at p
void SearchTree<E>::erase(const Iterator& p)
{
	eraser(p.v);
}

template < typename E >
void SearchTree<E>::increaseSize() {
	++n;
}

template < typename E >
void SearchTree<E>::expandExt(const TPos & p) {
	T.expandExternal(p);
}

#endif