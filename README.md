# DataStructuresCpp
A Collection of Data Structures in C++

[![Run on Repl.it](https://repl.it/badge/github/danielzelfo/DataStructuresCpp)](https://repl.it/github/danielzelfo/DataStructuresCpp)

## AdjacencyList
C++ Adjacency List Graph Program

This program includes the AdjacencyListGraph class, which is a list representation of an undirected graph The AdjacencyListGraph class can insert vertices and edges, remove vertices and edges, print a graph, and more The AdjacencyListGraph class has a constructor with a boolean value for whether or not the graph is directed It uses a template for the data type of the vertex element and edge element


## AdjacencyMatrix
C++ Adjacency Matrix Graph Program

This program includes the AdjacencyMatrixGraph class, which is a list representation of an undirected graph The AdjacencyMatrixGraph class can insert vertices and edges, remove vertices and edges, print a graph, and more The AdjacencyMatrixGraph class inherits from the Graph class, and it includes the classes InnerVertex and InnerEdge, which respectively inherit from Vertex and Edge The AdjacencyMatrixGraph class has a constructor that takes a boolean value for whether or not the graph is directed


## Union-Find
C++ Union-Find Data Structure Program

This program includes the UnionFind class, which represents a Disjoint Set It has the operations makeset, union, and find makeset creates a new set in the structure with the given element union joins together the two sets given, and find returns the set with the given element


## StandardTrie
C++ StandardTrie Program

This program includes a StandardTrie class, which can construct a standard trie using a text file The constructor of the StandardTrie class reads each word in the text file, ignoring any characters that aren't letter Each character of the word being inserted into the standard trie is checked to see if it is the child of the current node The StandardTrie class has an includes function which can be used to check whether or not a given word is in the standard trie. It returns an integer for the number of occurrences of the word in the text.


## HashTables
C++ HashTables Program

This program is made up of three different hash table classes, which use three diferent hashing schemes: Chain Hashing, Linear Probe Hashing, and Double Hashing Each class can be constructed using an input file and can take a load factor to use The hash tables use the Hasher class to generate a hash code for any given key Each record is stored in an Entry The user can search, insert, and erase records in O(1) using these hash tables


## QueueCircularArray
C++ Queue implemented using a circular array

This program includes the Queue class, which implements a queue using an circular array The Queue class incldues the member functions: enqueue(), dequeue(), size(), and front()


## ArrayVector
C++ Array Vector Data Structure

This program implements a vector using an extendable array. Member functions of the ArrayVector class include: size, maxSize, empty, resize, append, eraseAt, eraseLast, and print


## AVLTree
C++ AVLTree Program

This Program includes an AVLTree that holds the content of the califronia counties database. The AVLTree is a drived class of a Search Tree, which uses a Linked Binary Tree to hold its content. The AVLTree can be constructed using a file that has the county code, population and name in each line Each record is held inside an AVLEntry, which is derived from an Search Tree Entry


## SearchTree
C++ SearchTree Data Structure

with functions find, insert, erase, and more


## List
C++ List Data Structure and Sequence Data Structure

This program implements a List. functions include inserting and erasing at any given position the list was essentially a doubly linked list positions are obtained by the itertator class I also implemented a sequence with the functions indexOf and atIndex