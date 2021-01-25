#include <string>
using namespace std;

class List {
private:
	/* List data members
	* Node - node struct used to make instances of nodes for doubly linked list
	* head - front of doubly linked list
	* tail - back of doubly linked list
	* listSize - size of list (number of elements)
	*/
	struct Node;
	Node* head;
	Node* tail;
	int listSize;

public:
	//declaring the list constructor
	List();

	//delcaring the Iterator class
	class Iterator;

	//declaring the begin and end functions
	Iterator begin() const;
	Iterator end() const;

	//declaring the size and empty functions
	int size() const;
	bool empty() const;

	//declaring the inserting functions
	void insertFront(const string&);
	void insertBack(const string&);
	void insert(const Iterator&, const string&);

	//declaring the erasing functions
	void eraseFront();
	void eraseBack();
	void erase(const Iterator&);

	//the print function
	void print();
};

//Node struct
struct List::Node {
	/* members:
	 * data - the actual data being held
	 * prev - points to previous node
	 * next - points to next node
	 */
	string data;
	Node* prev;
	Node* next;
};

//the List constructor
List::List() {
	//setting the list size to 0
	listSize = 0;

	//pointing head and tail empty nodes
	head = new Node;
	tail = new Node;

	//making tail the next of head and head the previous of tail
	head->next = tail;
	tail->prev = head;
}

//Iterator class
class List::Iterator {
private:
	// Data member: curNode - the node that the iterator currently represents
	Node* curNode;

	//declaring the Iterator constructor with a node parameter, which will be private so it  can only be used by the List 
	Iterator(Node*);

public:
	//declaring all the oeprator functions
	string& operator*();
	bool operator==(const Iterator&) const;
	bool operator!=(const Iterator&) const;
	Iterator& operator++();
	Iterator& operator--();

	//giving the List class access to private members
	friend class List;
};

//the begin function
List::Iterator List::begin() const {
	//returns the next of the dummy header
	return Iterator(head->next);
}
//the end function
List::Iterator List::end() const {
	//returns the trailer
	return Iterator(tail);
}

//the size function
int List::size() const {
	return listSize;
}
//the empty function
bool List::empty() const {
	return (listSize == 0);
}

//the insert function - to insert at a given position (iterator)
void List::insert(const List::Iterator& position, const string& data) {
	//getting the node at the given position
	Node* posNode = position.curNode;
	//getting the node before the given position
	Node* leftNode = posNode->prev;

	//creating a new node with the given data and setting the previous and next
	Node* newNode = new Node;
	newNode->data = data;
	newNode->prev = leftNode;
	newNode->next = posNode;

	//making the previos of node at the given position the new node
	posNode->prev = newNode;
	//making the next of the node at the given position the new node4
	leftNode->next = newNode;

	//incrementing the size
	listSize++;
}

//the insertFront function - uses the insert at the begin
void List::insertFront(const string& elem) {
	insert(begin(), elem);
}
//the insertFront function - uses the insert at the end
void List::insertBack(const string& elem) {
	insert(end(), elem);
}

//the erase function removes the ndoe at a given postion
void List::erase(const Iterator& position) {
	//getting the node at the given postion
	Node* posNode = position.curNode;
	//getting the nodes previous and next to the node being removed
	Node* leftNode = posNode->prev;
	Node* rightNode = posNode->next;

	//linking the left and right nodes
	leftNode->next = rightNode;
	rightNode->prev = leftNode;

	//deleting the node at the given postion
	delete posNode;

	//decrementing the list size
	listSize--;
}
//the eraseFront function - calls the erase function at the begin
void List::eraseFront() {
	erase(begin());
}
//the eraseFront function - calls the erase function one before the end
void List::eraseBack() {
	erase(--end());
}

//Iterator constructor
List::Iterator::Iterator(Node* theNode) {
	curNode = theNode;
}

//this operator (*) returns the data at the current iterator
string& List::Iterator::operator*() {
	return curNode->data;
}

//the comparison operators (== & !=) return a boolean
bool List::Iterator::operator==(const Iterator& otherIt) const {
	return (curNode == otherIt.curNode);
}
bool List::Iterator::operator!=(const Iterator& otherIt) const {
	return (curNode != otherIt.curNode);
}

//the incrementing operator (++) makes the iterator point to the next node
List::Iterator& List::Iterator::operator++() {
	curNode = curNode->next;
	return *this;
}
//the decrementing operator (--) makes the iterator point to the previous node
List::Iterator& List::Iterator::operator--() {
	curNode = curNode->prev;
	return *this;
}

//the print function - displays all the items in the list
void List::print() {
	cout << "{ ";
	for (Iterator it = begin(); it != end(); ++it) {
		cout << "\"" << *it << "\" ";
	}
	cout << "}";
}