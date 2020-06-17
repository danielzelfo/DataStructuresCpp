// driver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AdjacencyList/driver.h"
#include "AdjacencyMatrix/driver.h"
#include "UnionFind/driver.h"
#include "StandardTrie/driver.h"
//#include "HashTables/driver.h"
//#include "QueueCircularArray/driver.h"
//#include "ArrayVector/driver.h"
//#include "AVLTree/driver.h"
//#include "SearchTree/driver.h"
//#include "List/driver.h"

using namespace std;

int main()
{
    int option;
    string options = "Please enter the number for the program to run\n";
           options += "0. To Exit\n";
           options += "1. AdjacencyList\n";
           options += "2. AdjacencyMatrix\n";
           options += "3. UnionFind\n";
           options += "4. StandardTrie\n";
           options += "5. HashTables\n";
           options += "6. QueueCircularArray\n";
           options += "7. ArrayVector\n";
           options += "8. AVLTree\n";
		   options += "9. SearchTree\n";
		   options += "10. List\n";

    cout << options << ">";
    cin >> option;

    while (option != 0) {
        switch (option) {
        case 1:
            adjacencyListMain();
            break;
        case 2:
            adjacencyMatrixMain();
            break;
        case 3:
            unionFindMain();
            break;
        case 4:
            standardTrieMain();
            break;
        case 5:
            //hashTablesMain();
            break;
        case 6:
            //queueCircularArrayMain();
            break;
        case 7:
            //arrayVectorMain();
            break;
        case 8:
            //avlTreeMain();
            break;
		case 9:
            //searchTreeMain();
            break;
		case 10:
            //listMain();
            break;
        default:
            cout << "Invalid Option (" << option << ")\n";
            break;
        }

        cout << "End.\n\n";

        cout << options << ">";
        cin >> option;
    }

}