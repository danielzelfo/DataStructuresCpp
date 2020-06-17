/*  Program: Standard Trie (WITH EXTRA CREDIT)
 *	Author: Daniel Zelfo
 *	Class: CSCI 230
 *	Date: 5/11/2020
 *	Description: This program includes a StandardTrie class, which can construct a standard trie using a text file
 *               The constructor of the StandardTrie class reads each word in the text file, ignoring any characters that aren't letter
 *               Each character of the word being inserted into the standard trie is checked to see if it is the child of the current node
 *               The StandardTrie class has an includes function which can be used to check whether or not a given word is in the standard trie
 *				 V1.1: the includes function now returns an integer for the number of occurrences of the word in the text
 *
 * I certify that the code below is my own work.
 *
 *	Exception(s): N/A
 *
 */

#include <iostream>
#include "StandardTrie.h"

int main()
{
    string filepath;
    //words to be searched
    vector<string> searchWords{ "honor", "honour", "government", "computer" };

    //creating a standard trie using the input file


    cout << "Enter filepath: ";
    cin >> filepath;

    //creating an object with the filepath parameter
    StandardTrie st(filepath);


    //outputting the number of words
    cout << st.getWordCount() << " words" << endl;

    //checking if the words in the searchWords vector are in the standard trie
    for (int i = 0; i < searchWords.size(); ++i) {
        int o = st.includes(searchWords[i]);
        cout << "Found " << searchWords[i] << " " << o << (o > 1 || o == 0 ? " times." : " time.") << endl;
    }
}

