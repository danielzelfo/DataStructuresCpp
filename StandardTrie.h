#pragma once

#include <string>
#include <fstream>
#include <vector>

using namespace std;

//alphabet size and first character
const int ALPHABET_SIZE = 26;
const char ZEROCHAR = 'a';

struct Node {
	int occurrences;
	Node* children[ALPHABET_SIZE + 1]{ nullptr };
	/*
		index 0 for terminal node
		indexes 1+ for alphabet characters
	*/
};



//the StandardTrie class
class StandardTrie {
	int wordCount;
	Node* root;

	//function to check if a character is in the alphabet
	bool inAlphabet(const char c) const {
		return (c >= ZEROCHAR && c <= ZEROCHAR + ALPHABET_SIZE);
	}
public:

	//constructor with filepath
	StandardTrie(string filepath) : wordCount(0) {
		ifstream data;
		string str;
		Node* cur;

		root = new Node;
		data.open(filepath);

		//inputting words from file
		while (data >> str) {
			//resetting the current node to the root
			cur = root;
			//checking if the word is not already in the standard trie
			//if (!includes(str)) {
				//incrementing the word count


				//looping through each character
			for (int i = 0; i < str.length(); ++i) {
				//lower case
				str[i] = tolower(str[i]);

				//skipping characters not in the alphabet
				if (!inAlphabet(str[i]))
					continue;


				//the index of the character in the children array ( plus one because index 0 is used for the terminal node )
				int charIndex = str[i] - ZEROCHAR + 1;

				//getting the child of the current node
				Node* n = cur->children[charIndex];

				//if it does not already exist
				if (n == nullptr) {
					//we will create a new node and set it to the child node
					Node* e = new Node;
					cur->children[charIndex] = e;

					//we will make the current node the new node
					cur = e;
				}
				//we will make the current node the child node
				else
					cur = n;

			}
			//if there is no terminal node, we will make one
			if (cur->children[0] == nullptr) {
				cur->children[0] = new Node;
				cur->occurrences = 1;
				wordCount++;
			}
			else {
				cur->occurrences++;
			}
			//}
		}

	}


	//function to check if a word is in the standard trie
	int includes(string str) const {

		//current node (starting at the root)
		Node* cur = root;

		//looping through each character
		for (int i = 0; i < str.length(); i++) {

			//lower case
			str[i] = tolower(str[i]);

			//we will skip over any character in the word that isn't in the alphabet
			if (!inAlphabet(str[i]))
				continue;

			//child node
			int charIndex = str[i] - ZEROCHAR + 1;
			Node* n = cur->children[charIndex];

			//if the child node with that character does not exist, the word is not in the standard trie
			if (n == nullptr)
				return 0;

			//otherwise, we will make the current node the child node
			cur = n;
		}

		//checking if there is a terminal child node at the end of the  last character
		if (cur->children[0] != nullptr)
			return cur->occurrences;
		return 0;
	}

	//word count getter
	int getWordCount() const {
		return wordCount;
	}
};
