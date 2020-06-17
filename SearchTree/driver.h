/*

SearchTree Data Structure By Daniel Zelfo



*/

#include "SearchTree.h"
#include "../Entry.h"

using namespace std;

void searchTreeMain()
{
	SearchTree<Entry<int, string>> tree;

	cout << "Inserting three elements... \n";

	tree.insert(1, "one");
	tree.insert(2, "two");
	tree.insert(3, "three");

	cout << "Size: " << tree.size() << endl;


	cout << "Inserting two elements... \n";

	tree.insert(-3, "negative three");
	tree.insert(-2, "negative two");


	cout << "Size: " << tree.size() << endl;


	cout << "Element with key 3: " << (*tree.find(3)).value() << endl;
	
	cout << "Element with lowest key: " << (*tree.begin()).value() << endl;

    std::cout << "end\n";
}
