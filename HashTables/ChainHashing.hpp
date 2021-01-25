#pragma once
#include <list>
#include <vector>
#include <iostream>
#include <string>
#include <utility>
#include <algorithm>
#include <fstream>
#include <sstream>

#include "../Entry.hpp"

using namespace std;

template <typename K, typename V1, typename V2, typename H>
class ChainHashing {
public:						// public types
	//typedef pair<V1, V2> V;
	//typedef Entry<K, V> Entry;			// a (key,value) pair
	class Iterator;					// a iterator/position
public:						// public functions
	ChainHashing(float lFactor = 0.5, int capacity = 10);			// constructor
	ChainHashing(string filepath, float lFactor = 0.5, int capacity = 10);

	int size() const;					// number of entries
	bool empty() const;					// is the map empty?
	Iterator find(const K& k, bool displayProbes = false);				// find Entry<K, pair<V1, V2>> with key k
	Iterator put(const K& k, const V1& v1, const V2& v2, bool countingProbes = false);		// insert/replace (k,v)
	void erase(const K& k, bool displayProbes = false);				// remove Entry<K, pair<V1, V2>> with key k
	void erase(const Iterator& p);			// erase Entry<K, pair<V1, V2>> at p
	Iterator begin();					// iterator to first Entry<K, pair<V1, V2>>
	Iterator end();					// iterator to end Entry<K, pair<V1, V2>>

	void list();
	void menu();

	void resize(int newSize);

protected:						// protected types

	typedef std::list<Entry<K, pair<V1, V2>>> Bucket;			// a bucket of entries
	typedef std::vector<Bucket> BktArray;		// a bucket array
	Iterator finder(const K& k, bool countingProbes = false);			    // find utility
	Iterator inserter(const Iterator& p, const Entry<K, pair<V1, V2>>& e);   // insert utility
	void eraser(const Iterator& p);			    // remove utility
	typedef typename BktArray::iterator BItor;		    // bucket iterator
	typedef typename Bucket::iterator EItor;		    // Entry<K, pair<V1, V2>> iterator
	static void nextEntry(Iterator& p)			    // bucket's next Entry<K, pair<V1, V2>>
	{
		++p.ent;
	}
	static bool endOfBkt(const Iterator& p)		    // end of bucket?
	{
		return p.ent == p.bkt->end();
	}
private:

	float loadFactor;

	int probesCounter;
	int maxProbes;


	int n;						// number of entries
	H hash;						// the hash comparator
	BktArray B;						// bucket array
public:						// public types
	class Iterator {	                      		// an iterator (& position)
	private:
		EItor ent;					// which Entry<K, pair<V1, V2>>
		BItor bkt;					// which bucket
		const BktArray* ba;				// which bucket array
	public:
		Iterator(const BktArray& a, const BItor& b, const EItor& q = EItor())
			: ent(q), bkt(b), ba(&a) { }
		Entry<K, pair<V1, V2>>& operator*() const;				// get Entry<K, pair<V1, V2>>
		bool operator==(const Iterator& p) const;		// are iterators equal?
		Iterator& operator++();				// advance to next Entry<K, pair<V1, V2>>


		K getKey() const;
		pair<V1, V2> getValue() const;


		friend class ChainHashing;				// give ChainHashing access


	};
};

template <typename K, typename V1, typename V2, typename H>		// iterator to end
typename ChainHashing<K, V1, V2, H>::Iterator ChainHashing<K, V1, V2, H>::end()
{
	return Iterator(B, B.end());
}

template <typename K, typename V1, typename V2, typename H>		// iterator to front
typename ChainHashing<K, V1, V2, H>::Iterator ChainHashing<K, V1, V2, H>::begin() {
	if (empty()) return end();				// emtpty - return end
	BItor bkt = B.begin();				// else search for an Entry<K, pair<V1, V2>>
	while (bkt->empty()) ++bkt;				// find nonempty bucket
	return Iterator(B, bkt, bkt->begin());		// return first of bucket
}


template <typename K, typename V1, typename V2, typename H>		// remove utility
void ChainHashing<K, V1, V2, H>::eraser(const Iterator& p) {
	p.bkt->erase(p.ent);				// remove Entry<K, pair<V1, V2>> from bucket
	n--;						// one fewer Entry<K, pair<V1, V2>>
}

template <typename K, typename V1, typename V2, typename H>		// remove Entry<K, pair<V1, V2>> at p
void ChainHashing<K, V1, V2, H>::erase(const Iterator& p)
{
	eraser(p);
}

template <typename K, typename V1, typename V2, typename H>		// remove Entry<K, pair<V1, V2>> with key k
void ChainHashing<K, V1, V2, H>::erase(const K& k, bool displayProbes) {
	if (displayProbes)
		probesCounter = 0;
	Iterator p = finder(k, displayProbes);				// find k

	if (displayProbes)
		cout << "Number of probes: " << probesCounter << endl;

	if (endOfBkt(p))					// not found?
										//throw NonexistentElement("Erase of nonexistent");	// ...error
		throw std::string("Erase of nonexistent");	// ...error

	eraser(p);						// remove it
}


template <typename K, typename V1, typename V2, typename H>		// find utility
typename ChainHashing<K, V1, V2, H>::Iterator ChainHashing<K, V1, V2, H>::finder(const K& k, bool countingProbes) {
	int probes = 1;
	int i = hash(k) % B.size();				// get hash index i
	BItor bkt = B.begin() + i;				// the ith bucket
	Iterator p(B, bkt, bkt->begin());			// start of ith bucket
	while (!endOfBkt(p) && (*p).key() != k) {		// search for k
		nextEntry(p);
		if (countingProbes)
			++probes;
	}
	if (countingProbes) {
		probesCounter += probes;
		if (probes > maxProbes)
			maxProbes = probes;
	}
	return p;						// return final position
}

template <typename K, typename V1, typename V2, typename H>		// find key
typename ChainHashing<K, V1, V2, H>::Iterator ChainHashing<K, V1, V2, H>::find(const K& k, bool displayProbes) {
	if (displayProbes)
		probesCounter = 0;
	Iterator p = finder(k, displayProbes);				// look for k

	if (displayProbes)
		cout << "Number of probes: " << probesCounter << endl;

	if (endOfBkt(p))					// didn't find it?
		return end();					// return end iterator
	else
		return p;						// return its position
}

template <typename K, typename V1, typename V2, typename H>		// are iterators equal?
bool ChainHashing<K, V1, V2, H>::Iterator::operator==(const Iterator& p) const {
	if (ba != p.ba || bkt != p.bkt) return false;	// ba or bkt differ?
	else if (bkt == ba->end()) return true;		// both at the end?
	else return (ent == p.ent);				// else use Entry<K, pair<V1, V2>> to decide
}

template <typename K, typename V1, typename V2, typename H>		// advance to next Entry<K, pair<V1, V2>>
typename ChainHashing<K, V1, V2, H>::Iterator& ChainHashing<K, V1, V2, H>::Iterator::operator++() {
	++ent;						// next Entry<K, pair<V1, V2>> in bucket
	if (endOfBkt(*this)) {				// at end of bucket?
		++bkt;						// go to next bucket
		while (bkt != ba->end() && bkt->empty())		// find nonempty bucket
			++bkt;
		if (bkt == ba->end()) return *this;		// end of bucket array?
		ent = bkt->begin();				// first nonempty Entry<K, pair<V1, V2>>
	}
	return *this;					// return self
}

template <typename K, typename V1, typename V2, typename H>		// get Entry<K, pair<V1, V2>>
Entry<K, pair<V1, V2>>& ChainHashing<K, V1, V2, H>::Iterator::operator*() const
{
	return *ent;
}

template <typename K, typename V1, typename V2, typename H>		// get Entry<K, pair<V1, V2>>
K ChainHashing<K, V1, V2, H>::Iterator::getKey() const
{
	return (*ent).key();
}

template <typename K, typename V1, typename V2, typename H>		// get Entry<K, pair<V1, V2>>
pair<V1, V2> ChainHashing<K, V1, V2, H>::Iterator::getValue() const
{
	return (*ent).value();
}

template <typename K, typename V1, typename V2, typename H>		// insert utility
typename ChainHashing<K, V1, V2, H>::Iterator ChainHashing<K, V1, V2, H>::inserter(const Iterator& p, const Entry<K, pair<V1, V2>>& e) {
	EItor ins = p.bkt->insert(p.ent, e);		// insert before p
	return Iterator(B, p.bkt, ins);			// return this position
}

template <typename K, typename V1, typename V2, typename H>		// insert/replace (v,k)
typename ChainHashing<K, V1, V2, H>::Iterator ChainHashing<K, V1, V2, H>::put(const K& k, const V1& v1, const V2& v2, bool countingProbes) {
	pair<V1, V2> v(v1, v2);

	//resizing the hashtable if necessary
	if (size() >= loadFactor* B.size())
		//B.resize((int)(B.size() / loadFactor));
		resize((int)(B.size() / loadFactor));

	Iterator p = finder(k, countingProbes);				// search for k
	if (endOfBkt(p)) {					// k not found?
		++n;
		return inserter(p, Entry<K, pair<V1, V2>>(k, v));			// insert at end of bucket
		
	}
	else {						// found it?
		p.ent->setValue(v);				// replace value with v
		return p;						// return this position
	}
}

template <typename K, typename V1, typename V2, typename H>		// constructor
ChainHashing<K, V1, V2, H>::ChainHashing(float lFactor, int capacity) : n(0), B((int)(capacity / lFactor)),
loadFactor(lFactor) {}


template <typename K, typename V1, typename V2, typename H>		// constructor
ChainHashing<K, V1, V2, H>::ChainHashing(string filepath, float lFactor, int capacity) : n(0), B((int)(capacity / lFactor)), loadFactor(lFactor), probesCounter(0), maxProbes(0) {

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
	if (_size > capacity)
		B.resize((int)(_size / lFactor));


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


	cout << "Table Size: " << B.size() << endl
		<< "Average number of probes: " << 1.0 * probesCounter / size() << endl
		<< "Maximum number of probes: " << maxProbes << "\n\n";
}


template <typename K, typename V1, typename V2, typename H>		// number of entries
int ChainHashing<K, V1, V2, H>::size() const { return n; }

template <typename K, typename V1, typename V2, typename H>		// is the map empty?
bool ChainHashing<K, V1, V2, H>::empty() const { return size() == 0; }

template <typename K, typename V1, typename V2, typename H>
void ChainHashing<K, V1, V2, H>::resize(int newSize) {
	vector<Entry<K, pair<V1, V2>>> oldB;
	int i = 0;
	Iterator it = begin();

	while (i < size()) {
		oldB.push_back(*it);
		++i; ++it;
	}

	n = 0;
	B.clear();
	B.resize(newSize);

	for(unsigned int i = 0; i < oldB.size(); ++i)
		put(oldB[i].key(), oldB[i].value().first, oldB[i].value().second);
}


//list all records
template <typename K, typename V1, typename V2, typename H>
void ChainHashing<K, V1, V2, H>::list() {
	Iterator cur = begin();
	cout << "Size: " << size() << endl;
	int i = 0;
	//traversing through hash map
	while (i < size()) {
		cout << (*cur).key() << " " << (*cur).value().first << " " << (*cur).value().second << endl;
		++cur; ++i;
	}
}

//menu to use program
template <typename K, typename V1, typename V2, typename H>
void ChainHashing<K, V1, V2, H>::menu() {
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
			Iterator record = find(code, displayProbes);
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
			put(code, population, name);
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