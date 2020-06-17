#ifndef AVLEntry_H
#define AVLEntry_H

template <typename E>
class AVLEntry : public E {				// an AVL entry
private:
	int ht;						// node height
protected:						// local types
	typedef typename E::Key K;				// key type
	typedef typename E::Value V;			// value type
	int height() const { return ht; }			// get height
	void setHeight(int h) { ht = h; }			// set height
public:						// public functions
	AVLEntry(const K& k = K(), const V& v = V())	// constructor
		: E(k, v), ht(0) { }
	friend class AVLTree;				// allow AVLTree access
};

#endif