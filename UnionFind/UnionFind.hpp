#pragma once
#include <list>

using namespace std;

template <typename E>
class UnionFind {
	list<list<E>> sets;

public:
	typedef typename list<list<E>>::iterator Iterator;

	Iterator end() { return sets.end(); }

	//the makeset function - adds a new set with the given element
	Iterator makeSet(E elem) {
		//checking if value already exists
		if (_find(elem) == sets.end()) {
			list<E> l{ elem };
			sets.push_front(l);

			return sets.begin();
		}
		return sets.end();
	}

	//the union function - joins the two given sets (removing the orginal sets and adding the new joined set)
	Iterator _union(Iterator ai, Iterator bi) {
		//getting a copy of the sets
		list<E> a = *ai, b = *bi;

		//erasing the old sets
		sets.erase(ai);
		sets.erase(bi);

		//adding the elements of the smaller set to the larger set
		if (a.size() > b.size()) {	
			a.splice(a.end(), b);
			sets.push_front(a);
		}
		else {
			b.splice(b.end(), a);
			sets.push_front(b);
		}

		return sets.begin();
	}

	//the find function - returns the set with the given element
	Iterator _find(E elem) {
		//looping through each set
		for (Iterator set = sets.begin(); set != sets.end(); ++set) {
			//if the current set includes the given element, we will return it
			for (auto const& e : *set)
				if (e == elem)
					return set;
		}

		return sets.end();
	}
};