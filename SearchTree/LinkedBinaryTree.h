#include <iostream>
#include <string>
#include <list>
#include <queue>

template < typename Elem >
class LinkedBinaryTree {
protected:
	struct Node {
		Elem data;
		Node* par;
		Node* left;
		Node* right;
		Node();
	};

public:
	class Position {
	private:
		Node* v;
	public:
		Position(Node* _v = nullptr) : v(_v) {}
		Elem& operator * () const;
		bool operator == (Position p);
		auto left() const->Position;
		auto right() const->Position;
		auto parent() const->Position;
		bool isRoot() const;
		bool isExternal() const;

		friend class LinkedBinaryTree;
	};
	typedef std::list < Position > PositionList;

public:
	LinkedBinaryTree();
	int size() const;
	bool empty() const;
	auto root() const->Position;
	auto preorderPositions() const->PositionList;
	auto inorderPositions() const->PositionList;
	auto levelorderPositions() const->PositionList;
	auto postorderPositions() const->PositionList;
	void addRoot();
	void expandExternal(const Position& p);
	void expandLeft(const Position& p);
	void expandRight(const Position& p);
	auto removeAboveExternal(const Position& p)->Position;

protected:
	void preorder(Node* v, PositionList& pl) const;
	void inorder(Node* v, PositionList& pl) const;
	void levelorder(Node* v, PositionList& pl) const;
	void postorder(Node* v, PositionList& pl) const;

private:
	Node* _root;
	int n;
};

template < typename Elem >
LinkedBinaryTree<Elem>::Node::Node() {
	par = nullptr;
	left = nullptr;
	right = nullptr;
}

template < typename Elem >
Elem& LinkedBinaryTree<Elem>::Position::operator * () const {
	return v->data;
}

template < typename Elem >
bool LinkedBinaryTree<Elem>::Position::operator == (LinkedBinaryTree<Elem>::Position p) {
	return v == p.v;
}

template < typename Elem >
auto LinkedBinaryTree<Elem>::Position::left() const -> LinkedBinaryTree<Elem>::Position {
	return Position(v->left);
}

template < typename Elem >
auto LinkedBinaryTree<Elem>::Position::right() const -> LinkedBinaryTree<Elem>::Position {
	return Position(v->right);
}

template < typename Elem >
auto LinkedBinaryTree<Elem>::Position::parent() const -> LinkedBinaryTree<Elem>::Position {
	return Position(v->par);
}

template < typename Elem >
bool LinkedBinaryTree<Elem>::Position::isRoot() const {
	return v->par == nullptr;
}

template < typename Elem >
bool LinkedBinaryTree<Elem>::Position::isExternal() const {
	return v->left == nullptr && v->right == nullptr;
}

template < typename Elem >
LinkedBinaryTree<Elem>::LinkedBinaryTree() : _root(nullptr), n(0) {}

template < typename Elem >
int LinkedBinaryTree<Elem>::size() const {
	return n;
}
template < typename Elem >
bool LinkedBinaryTree<Elem>::empty() const {
	return size() == 0;
}
template < typename Elem >
auto LinkedBinaryTree<Elem>::root() const -> LinkedBinaryTree<Elem>::Position {
	return Position(_root);
}
template < typename Elem >
void LinkedBinaryTree<Elem>::addRoot() {
	_root = new Node;
	n = 1;
}

template < typename Elem >
void LinkedBinaryTree<Elem>::expandExternal(const Position& p) {
	Node* v = p.v;
	v->left = new Node;
	v->left->par = v;
	v->right = new Node;
	v->right->par = v;
	n += 2;
}

template < typename Elem >
void LinkedBinaryTree<Elem>::expandLeft(const Position& p) {
	Node* v = p.v;
	Node* temp = v->left;
	v->left = new Node;
	v->left->par = v;
	v->left->left = temp;
	n++;
}

template < typename Elem >
void LinkedBinaryTree<Elem>::expandRight(const Position& p) {
	Node* v = p.v;
	Node* temp = v->right;
	v->right = new Node;
	v->right->par = v;
	v->right->right = temp;
	n++;
}

template < typename Elem >
auto LinkedBinaryTree<Elem>::preorderPositions() const -> LinkedBinaryTree<Elem>::PositionList {
	PositionList pl;
	preorder(_root, pl);
	return PositionList(pl);
}

template < typename Elem >
auto LinkedBinaryTree<Elem>::inorderPositions() const -> LinkedBinaryTree<Elem>::PositionList {
	PositionList pl;
	inorder(_root, pl);
	return PositionList(pl);
}

template < typename Elem >
auto LinkedBinaryTree<Elem>::levelorderPositions() const -> LinkedBinaryTree<Elem>::PositionList {

	PositionList pl;
	levelorder(_root, pl);
	return PositionList(pl);

}

template < typename Elem >
auto LinkedBinaryTree<Elem>::postorderPositions() const -> LinkedBinaryTree<Elem>::PositionList {
	PositionList pl;
	postorder(_root, pl);
	return PositionList(pl);
}

template < typename Elem >
void LinkedBinaryTree<Elem>::preorder(Node* v, PositionList& pl) const {
	pl.push_back(Position(v));
	if (v->left != nullptr)
		preorder(v->left, pl);
	if (v->right != nullptr)
		preorder(v->right, pl);
}

template < typename Elem >
void LinkedBinaryTree<Elem>::inorder(Node* v, PositionList& pl) const {
	if (v->left != nullptr)
		inorder(v->left, pl);
	pl.push_back(Position(v));
	if (v->right != nullptr)
		inorder(v->right, pl);
}


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

template < typename Elem >
void LinkedBinaryTree<Elem>::postorder(Node* v, PositionList& pl) const {
	if (v->left != nullptr)
		postorder(v->left, pl);
	if (v->right != nullptr)
		postorder(v->right, pl);
	pl.push_back(Position(v));
}

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