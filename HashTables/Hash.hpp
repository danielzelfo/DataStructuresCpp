#pragma once


#include <string>
#include <iostream>
#include <sstream>
#include <math.h>

using namespace std;




template <typename E>
class Hasher {
private:

public:
	int operator()(const E p) const
	{
		int hashcode;
		stringstream ss;
		string s;
		int a = 33;

		//converting the key to a string using a string stream
		ss << p;
		s = ss.str();


		
    hashcode = 0;
    //making the hashcode using the polynomial approach
    for (unsigned int i = 0; i < s.length(); ++i)
      hashcode += (int)pow(a, i) * s[s.length() - 1 - i];

		return hashcode;
	}
};