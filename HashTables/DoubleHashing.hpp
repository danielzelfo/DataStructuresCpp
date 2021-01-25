#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "../Entry.hpp"

using namespace std;

template <typename K, typename V1, typename V2, typename H>
class DoubleHashing {
public:						// public types
	//typedef pair<V1, V2> V;
	//typedef Entry<K, pair<V1, V2>><K, V> Entry<K, pair<V1, V2>>;			// a (key,value) pair

protected:
	typedef typename vector<Entry<K, pair<V1, V2>>>::iterator Itor;

public:						// public functions
	DoubleHashing(float lFactor = 0.5, int capacity = 10);			// constructor
	DoubleHashing(string filepath, float lFactor = 0.5, int capacity = 10);

	int size() const;					// number of entries
	bool empty() const;					// is the map empty?

	Itor find(const K& k, bool displayProbes = false);				// find entry with key k
	Itor put(const K& k, const V1& v1, const V2& v2, bool countingProbes = false);		// insert/replace (k,v)

	void erase(const K& k, bool displayProbes = false);				// remove entry with key k
	void erase(const Itor& p);			// erase entry at p

	Itor begin();					// iterator to first entry
	Itor end();					// iterator to end entry

	void list();
	void menu();

	void resize(int newSize);

protected:		    // bucket iterator

	Itor finder(const K& k, bool countingProbes = false);			    // find utility
	Itor inserter(const Itor& p, const Entry<K, pair<V1, V2>>& e);   // insert utility
	void eraser(const Itor& p);			    // remove utility

private:

	bool isPrime(int n) {
		for (int i = 2; i < n; ++i)
			if (n % i == 0)
				return false;
		return true;
	}
	int primeSize(int n) {
		while (!isPrime(n))
			++n;

		return n;
	}
	
	//entry used to replace an erased entry
	Entry<K, pair<V1, V2>> removedEntry;


	float loadFactor;

	int probesCounter;
	int maxProbes;


	unsigned int n;						// number of entries
	H hash;						// the hash comparator
	vector<Entry<K, pair<V1, V2>>> A;						// bucket array


	//double hashing data
	int pnBelow;
};


template <typename K, typename V1, typename V2, typename H>		// constructor
DoubleHashing<K, V1, V2, H>::DoubleHashing(float lFactor, int capacity) : n(0), A(primeSize((int)(capacity / lFactor))), loadFactor(lFactor), removedEntry(0, pair<int, string>(0, "removed")) {
	pnBelow = (int)(capacity / lFactor);

	while (!isPrime(pnBelow))
		--pnBelow;
}


template <typename K, typename V1, typename V2, typename H>		// constructor
DoubleHashing<K, V1, V2, H>::DoubleHashing(string filepath, float lFactor, int capacity) : n(0), A(primeSize((int)(capacity / lFactor))), loadFactor(lFactor), probesCounter(0), maxProbes(0), removedEntry(0, pair<int, string>(0, "removed")) {
	string s;
	int _size;
	ifstream data;
	string sCountyCode = "", sCountyPopulation = "";
	int countyCode, countyPopulation;
	string countyName;
	string line;
	string temp;
	bool countingProbes = true;
	

	data.open(filepath);
	//getting each line into a string
	std::getline(data, s);
	_size = stoi(s);


	pnBelow = (int)(capacity / lFactor);

	while (!isPrime(pnBelow))
		--pnBelow;

	if (_size > capacity)
		resize((int)(_size / lFactor));

	while (std::getline(data, line)) {
		int i = 0;
		int commaCount = 0;
		while (commaCount < 2) {
			if (line[i] == ',')
				++commaCount;
			++i;
		}
		string l1 = line.substr(0, i);
		std::replace(l1.begin(), l1.end(), ',', ' ');
		stringstream ss(l1);
		ss >> countyCode;
		ss >> countyPopulation;

		countyName = line.substr(i);


		put(countyCode, countyPopulation, countyName, countingProbes);
	}

	cout << "Table Size: " << A.size() << endl
		<< "Average number of probes: " << 1.0 * probesCounter / size() << endl
		<< "Maximum number of probes: " << maxProbes << "\n\n";

}


// iterator to front
template <typename K, typename V1, typename V2, typename H>
typename DoubleHashing<K, V1, V2, H>::Itor DoubleHashing<K, V1, V2, H>::begin() {
	if (empty()) return end();				// emtpty - return end
	Itor bkt = A.begin();				// else search for an entry
	while (*bkt == Entry<K, pair<V1, V2>>() || *bkt == removedEntry) ++bkt;				// find nonempty bucket
	return bkt;		// return first of bucket
}
// iterator to end
template <typename K, typename V1, typename V2, typename H>
typename DoubleHashing<K, V1, V2, H>::Itor DoubleHashing<K, V1, V2, H>::end()
{
	return A.end();
}

// number of entries
template <typename K, typename V1, typename V2, typename H>
int DoubleHashing<K, V1, V2, H>::size() const { return n; }
// is the map empty?
template <typename K, typename V1, typename V2, typename H>
bool DoubleHashing<K, V1, V2, H>::empty() const { return size() == 0; }

// find key
template <typename K, typename V1, typename V2, typename H>
typename DoubleHashing<K, V1, V2, H>::Itor DoubleHashing<K, V1, V2, H>::find(const K& k, bool displayProbes) {
	if (!displayProbes)
		return finder(k);
	else {
		probesCounter = 0;
		Itor r = finder(k, displayProbes);
		cout << "Number of probes: " << probesCounter << endl;
		return r;
	}
}
// find utility
template <typename K, typename V1, typename V2, typename H>
typename DoubleHashing<K, V1, V2, H>::Itor DoubleHashing<K, V1, V2, H>::finder(const K& k, bool countingProbes) {
	unsigned int probes = 0;
	int i = hash(k);
	int inc = pnBelow - i % pnBelow;
	i %= A.size();
	Itor it = A.begin() + i;


	while (!(*it == Entry<K, pair<V1, V2>>()) && probes < A.size()) {

		if ((*it).key() == k) {

			if (countingProbes)
				probesCounter += probes + 1;

			return it;

		}


		i = (i + inc) % A.size();
		it = A.begin() + i;

		++probes;
	}

	if (countingProbes)
		probesCounter += probes + 1;


	return end();
	
}


// insert(v,k)
template <typename K, typename V1, typename V2, typename H>
typename DoubleHashing<K, V1, V2, H>::Itor DoubleHashing<K, V1, V2, H>::put(const K& k, const V1& v1, const V2& v2, bool countingProbes) {
	pair<V1, V2> v(v1, v2);
	int probes = 0;

	if (size() >= loadFactor * A.size())
		resize((int)(A.size() / loadFactor));

	int i = hash(k);
	int inc = pnBelow - i % pnBelow;
	i %= A.size();
	Itor it = A.begin() + i;

	//iterating through bucket until we reach an empty slot or a record that already exists with the given key
	while (probes < A.size()) {

		//if the entry is empty or has the key of the entry that will be inserted
		if (*it == Entry<K, pair<V1, V2>>() || *it == removedEntry || (*it).key() == k) {
			if ((*it).key() != k) n++;

			if (countingProbes) {
				probesCounter += probes + 1;
				if (probes + 1 > maxProbes)
					maxProbes = probes + 1;
			}

			return inserter(it, Entry<K, pair<V1, V2>>(k, v));
		}

		i = (i + inc) % A.size();
		it = A.begin() + i;
		++probes;
	}
	if (countingProbes) {
		probesCounter += probes + 1;
		if (probes + 1 > maxProbes)
			maxProbes = probes + 1;
	}


	return end();
}
// insert utility
template <typename K, typename V1, typename V2, typename H>
typename DoubleHashing<K, V1, V2, H>::Itor DoubleHashing<K, V1, V2, H>::inserter(const Itor& p, const Entry<K, pair<V1, V2>>& e) {


	*p = e;

	return p;
}

// remove utility
template <typename K, typename V1, typename V2, typename H>
void DoubleHashing<K, V1, V2, H>::eraser(const Itor& p) {
	//replacing the entry with the removedEntry entry
	*p = removedEntry;
	n--;
}
// remove entry at p
template <typename K, typename V1, typename V2, typename H>
void DoubleHashing<K, V1, V2, H>::erase(const Itor& p)
{
	eraser(p);
}
// remove entry with key k
template <typename K, typename V1, typename V2, typename H>
void DoubleHashing<K, V1, V2, H>::erase(const K& k, bool displayProbes) {
	if (displayProbes)
		probesCounter = 0;
	
	Itor p = finder(k, displayProbes);

	if (displayProbes)
		cout << "Number of probes: " << probesCounter << endl;

	if (p == A.end())
		throw string("Erase of nonexistant");

	eraser(p);
}

template <typename K, typename V1, typename V2, typename H>
void DoubleHashing<K, V1, V2, H>::resize(int newSize) {
	vector<Entry<K, pair<V1, V2>>> oldB;
	int i = 0;
	Itor it = begin();

	while (i < size()) {
		if (!(*it == Entry<K, pair<V1, V2>>())) {
			oldB.push_back(*it);
			++i;
		}
		++it;
	}

	n = 0;
	A.clear();
	A.resize(primeSize(newSize));

	pnBelow = newSize;
	while (!isPrime(pnBelow))
		--pnBelow;


	for (unsigned int i = 0; i < oldB.size(); ++i)
		put(oldB[i].key(), oldB[i].value().first, oldB[i].value().second);
}


//list all records
template <typename K, typename V1, typename V2, typename H>
void DoubleHashing<K, V1, V2, H>::list() {
	Itor cur = begin();
	cout << "Size: " << size() << endl;
	int i = 0;
	//traversing through hash map
	while (i < size()) {
		if (!(*cur == Entry<K, pair<V1, V2>>())) {
			cout << (*cur).key() << " " << (*cur).value().first << " " << (*cur).value().second << endl;
			++i;
		}
		++cur;
	}
}

//menu to use program
template <typename K, typename V1, typename V2, typename H>
void DoubleHashing<K, V1, V2, H>::menu() {
	int option, code, population;
	string name;
	bool displayProbes = true;

	cout << "1. Search for a record \n2. Insert a record \n3. Delete a record \n4. List all records \n5. Exit\n>";
	cin >> option;

	//enter 5 to exit
	while (option != 5) {


		//enter 1 to search for a record
		if (option == 1) {
			cout << "Enter County Code to Search: ";
			cin >> code;
			Itor record = find(code, displayProbes);
			if (record == end())
				cout << "Record not found.\n";
			else
				cout << "Record found: " << endl << (*record).key() << " " << (*record).value().first << " " << (*record).value().second << endl;
		}

		//enter 2 to insert a record
		else if (option == 2) {
			cout << "Enter record to insert\n";
			cout << "Enter county code: ";
			cin >> code;
			cout << "Enter county population: ";
			cin >> population;
			cout << "Enter county Name: ";
			cin.ignore();
			getline(cin, name);
			Itor p = put(code, population, name);
			if (p == end())
				cout << "Hash Table is full." << endl;
			else
				cout << "Record added." << endl;
		}

		//enter 3 to erase a record
		else if (option == 3) {
			cout << "Enter County Code to Delete: ";
			cin >> code;
			try {
				erase(code, displayProbes);
				cout << "Record removed." << endl;
			}
			catch (string e) {
				cout << e << endl;
			}
		}

		//enter 4 to list all records
		else if (option == 4)
			list();

		cout << ">";

		cin >> option;
		cin.ignore(10000, '\n');
	}

}