#include "LinkedBinaryTree.h"

template < typename E >
class SearchTree {
public:
	typedef typename E::Key K;
	typedef typename E::Value V;
	class Iterator;
public:
	SearchTree();
	int size() const;
	bool empty() const;
	Iterator find(const K& k);
	Iterator insert(const K& k, const V& x);
	void erase(const K& k) throw ();
	void erase(const Iterator& p);
	Iterator begin();
	Iterator end();
protected:
	typedef LinkedBinaryTree < E > BinaryTree;
	typedef typename BinaryTree::Position TPos;
	TPos root() const;
	TPos finder(const K& k, const TPos& v);
	TPos inserter(const K& k, const V& x);
	TPos eraser(TPos& v);
private:
	BinaryTree T;
	int n;
public:
	class Iterator;
};

template < typename E >
class SearchTree < E > ::Iterator {
private: TPos v;
public: Iterator(const TPos& vv) : v(vv) {}
		const E& operator * () const {
			return *v;
		}
		E& operator * () {
			return *v;
		}
		bool operator == (const Iterator& p) const {
			return v == p.v;
		}
		Iterator& operator++();
		friend class SearchTree;
};

template <typename E>					// iterator to first entry
typename SearchTree<E>::Iterator SearchTree<E>::begin() {
	TPos v = root();// start at virtual root				
	while (!v.isExternal()) v = v.left();		// find leftmost node
	return Iterator(v.parent());
}

template <typename E>					// iterator to end entry
typename SearchTree<E>::Iterator SearchTree<E>::end()
{
	return Iterator(T.root());
}			// return the super root

template < typename E >
SearchTree < E > ::SearchTree() : T() {
	n = 0;
	T.addRoot();
	T.expandExternal(T.root());
}

template < typename E >
typename SearchTree < E > ::TPos SearchTree < E > ::root() const {
	return T.root().left();
}

template < typename E >
int SearchTree < E > ::size() const {
	return n;
}

template < typename E >
bool SearchTree < E > ::empty() const {
	return (n == 0);
}

template < typename E >
typename SearchTree < E > ::TPos SearchTree < E > ::finder(const K& k, const TPos& v) {
	if (v.isExternal()) return v;
	if (k < (*v).key()) return finder(k, v.left());
	else if ((*v).key() < k) return finder(k, v.right());
	else return v;
}

template < typename E >
typename SearchTree < E > ::Iterator SearchTree < E > ::find(const K& k) {
	TPos v = finder(k, root());
	if (!v.isExternal()) return Iterator(v);
	else return end();
}

template < typename E >
typename SearchTree < E > ::TPos SearchTree < E > ::inserter(const K& k,
	const V& x) {
	TPos v = finder(k, root());
	while (!v.isExternal())
		v = finder(k, v.right());
	T.expandExternal(v);
	(*v).setKey(k);
	(*v).setValue(x);
	n++;
	return v;
}

template < typename E >
typename SearchTree < E > ::Iterator SearchTree < E > ::insert(const K& k,
	const V& x) {
	TPos v = inserter(k, x);
	return Iterator(v);
}

template <typename E>					// inorder successor
typename SearchTree<E>::Iterator& SearchTree<E>::Iterator::operator++() {
	TPos w = v.right();
	if (!w.isExternal()) {				// have right subtree?
		do { v = w; w = w.left(); }			// move down left chain
		while (!w.isExternal());
	}
	else {
		w = v.parent();					// get parent
		while (v == w.right())				// move up right chain
		{
			v = w; w = w.parent();
		}
		v = w;						// and first link to left
	}
	return *this;
}

template <typename E>					// remove utility
typename SearchTree<E>::TPos SearchTree<E>::eraser(TPos& v) {
	TPos w;
	if (v.left().isExternal()) w = v.left();		// remove from left
	else if (v.right().isExternal()) w = v.right();	// remove from right
	else {						// both internal?
		w = v.right();					// go to right subtree
		do { w = w.left(); } while (w.isInternal());	// get leftmost node
		TPos u = w.parent();
		v->setKey(u->key()); v->setValue(u->value());	// copy w's parent to v
	}
	n--;						// one less entry
	return T.removeAboveExternal(w);			// remove w and parent
}

template <typename E>					// remove key k entry
void SearchTree<E>::erase(const K& k) throw() {
	TPos v = finder(k, root());				// search from virtual root
	if (v.isExternal())					// not found?
		throw std::string("Erase of nonexistent");
	eraser(v);						// remove it
}

template <typename E>					// erase entry at p
void SearchTree<E>::erase(const Iterator& p)
{
	eraser(p.v);
}