#ifndef LinkedBinaryTree_H
#define LinkedBinaryTree_H

#include <string>
#include <list>
#include <queue>

//Binary Tree
template < typename Elem >
class LinkedBinaryTree {
protected:
	//Binary Tree Node
	struct Node {
		Elem data;
		Node* par;
		Node* left;
		Node* right;
		Node();
	};

public:
	//Binary Tree Position
	class Position {
	private:
		Node* v;
	public:
		//position constructor
		Position(Node* _v = new Node) : v(_v) {}
		//operator function to return the data of a position
		Elem& operator * () const;
		//euqality operator function
		bool operator == (Position p) const;
		auto left() const->Position;
		auto right() const->Position;
		auto parent() const->Position;
		bool isRoot() const;
		bool isExternal() const;

		friend class LinkedBinaryTree<Elem>;
		friend class AVLTree;
	};
	typedef std::list < Position > PositionList;

public:
	//default constructor
	LinkedBinaryTree();

	//functions to access tree information
	int size() const;
	bool empty() const;

	//returns the positon of the root node
	auto root() const->Position;

	//traversal position lists
	//these will call the approriate traversal function and return a list of positions
	auto preorderPositions() const->PositionList;
	auto inorderPositions() const->PositionList;
	auto levelorderPositions() const->PositionList;
	auto postorderPositions() const->PositionList;

	//function to alter tree
	void addRoot();
	void expandExternal(const Position& p);
	void expandLeft(const Position& p);
	void expandRight(const Position& p);
	auto removeAboveExternal(const Position& p)->Position;

protected:
	//traversal function
	void preorder(Node* v, PositionList& pl) const;
	void inorder(Node* v, PositionList& pl) const;
	void levelorder(Node* v, PositionList& pl) const;
	void postorder(Node* v, PositionList& pl) const;

private:
	Node* _root;
	int n;
};

//node constructor
template < typename Elem >
LinkedBinaryTree<Elem>::Node::Node() {
	par = nullptr;
	left = nullptr;
	right = nullptr;
}

//the operator function to return the data
template < typename Elem >
Elem& LinkedBinaryTree<Elem>::Position::operator * () const {
	return v->data;
}

//equality operator function
template < typename Elem >
bool LinkedBinaryTree<Elem>::Position::operator == (LinkedBinaryTree<Elem>::Position p) const {
	return v == p.v;
}

//return left child node position
template < typename Elem >
auto LinkedBinaryTree<Elem>::Position::left() const -> LinkedBinaryTree<Elem>::Position {
	return Position(v->left);
}

//return right child node position
template < typename Elem >
auto LinkedBinaryTree<Elem>::Position::right() const -> LinkedBinaryTree<Elem>::Position {
	return Position(v->right);
}

//returns parent node position
template < typename Elem >
auto LinkedBinaryTree<Elem>::Position::parent() const -> LinkedBinaryTree<Elem>::Position {
	return Position(v->par);
}

//returns boolean for is a postion is a root
template < typename Elem >
bool LinkedBinaryTree<Elem>::Position::isRoot() const {
	return v->par == nullptr;
}

//return boolean for if a position is exteranal
template < typename Elem >
bool LinkedBinaryTree<Elem>::Position::isExternal() const {
	return v == nullptr || v->left == nullptr && v->right == nullptr;
}

//tree default constrtuctor
template < typename Elem >
LinkedBinaryTree<Elem>::LinkedBinaryTree() : _root(nullptr), n(0) {}

//returns size of tree
template < typename Elem >
int LinkedBinaryTree<Elem>::size() const {
	return n;
}
//returns boolean for is the tree is empty
template < typename Elem >
bool LinkedBinaryTree<Elem>::empty() const {
	return size() == 0;
}
//returns the position of the root node
template < typename Elem >
auto LinkedBinaryTree<Elem>::root() const -> LinkedBinaryTree<Elem>::Position {
	return Position(_root);
}
//function to create a new node and set it to the root
template < typename Elem >
void LinkedBinaryTree<Elem>::addRoot() {
	_root = new Node;
	n = 1;
}

//creates two nodes for left and right child nodes
template < typename Elem >
void LinkedBinaryTree<Elem>::expandExternal(const Position& p) {
	Node* v = p.v;
	v->left = new Node;
	v->left->par = v;
	v->right = new Node;
	v->right->par = v;
	n += 2;
}

//creates a new node for the left node and moves down
template < typename Elem >
void LinkedBinaryTree<Elem>::expandLeft(const Position& p) {
	Node* v = p.v;
	Node* temp = v->left;
	v->left = new Node;
	v->left->par = v;
	v->left->left = temp;
	n++;
}

//moves down the right child node and creates a new node for the right child
template < typename Elem >
void LinkedBinaryTree<Elem>::expandRight(const Position& p) {
	Node* v = p.v;
	Node* temp = v->right;
	v->right = new Node;
	v->right->par = v;
	v->right->right = temp;
	n++;
}

//preorder traversal positions
template < typename Elem >
auto LinkedBinaryTree<Elem>::preorderPositions() const -> LinkedBinaryTree<Elem>::PositionList {
	PositionList pl;
	preorder(_root, pl);
	return PositionList(pl);
}

//returns a list of postions for the inorder traversal

template < typename Elem >
auto LinkedBinaryTree<Elem>::inorderPositions() const -> LinkedBinaryTree<Elem>::PositionList {
	PositionList pl;
	inorder(_root, pl);
	return PositionList(pl);
}

//returns a list of postions for the levelorder traversal
template < typename Elem >
auto LinkedBinaryTree<Elem>::levelorderPositions() const -> LinkedBinaryTree<Elem>::PositionList {

	PositionList pl;
	levelorder(_root, pl);
	return PositionList(pl);

}

//returns a list of postions for the postorder traversal
template < typename Elem >
auto LinkedBinaryTree<Elem>::postorderPositions() const -> LinkedBinaryTree<Elem>::PositionList {
	PositionList pl;
	postorder(_root, pl);
	return PositionList(pl);
}

//returns a list of postions for the preorder traversal
template < typename Elem >
void LinkedBinaryTree<Elem>::preorder(Node* v, PositionList& pl) const {
	pl.push_back(Position(v));
	if (v->left != nullptr)
		preorder(v->left, pl);
	if (v->right != nullptr)
		preorder(v->right, pl);
}

//the inorder traversal function
template < typename Elem >
void LinkedBinaryTree<Elem>::inorder(Node* v, PositionList& pl) const {
	if (v->left != nullptr)
		inorder(v->left, pl);
	pl.push_back(Position(v));
	if (v->right != nullptr)
		inorder(v->right, pl);
}

//the levelorder traversal function
template < typename Elem >
void LinkedBinaryTree<Elem>::levelorder(Node* v, PositionList& pl) const {
	std::queue<Node*> levelQ;
	levelQ.push(v);
	while (!levelQ.empty()) {
		if (levelQ.front()->left != nullptr)
			levelQ.push(levelQ.front()->left);
		if (levelQ.front()->right != nullptr)
			levelQ.push(levelQ.front()->right);
		pl.push_back(Position(levelQ.front()));
		levelQ.pop();
	}
}

//the postorder traversal function
template < typename Elem >
void LinkedBinaryTree<Elem>::postorder(Node* v, PositionList& pl) const {
	if (v->left != nullptr)
		postorder(v->left, pl);
	if (v->right != nullptr)
		postorder(v->right, pl);
	pl.push_back(Position(v));
}

//the remove function
template < typename Elem >
auto LinkedBinaryTree<Elem>::removeAboveExternal(const Position& p) -> LinkedBinaryTree<Elem>::Position {
	Node* w = p.v;
	Node* v = w->par;
	Node* sib = (w == v->left ? v->right : v->left);
	if (v == _root) {
		_root = sib;
		sib->par = nullptr;
	}
	else {
		Node* gpar = v->par;
		if (v == gpar->left) gpar->left = sib;
		else gpar->right = sib;
		sib->par = gpar;
	}
	delete w;
	delete v;
	n -= 2;
	return Position(sib);
}

#endif