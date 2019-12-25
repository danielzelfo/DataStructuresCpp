#include "List.h"

class Sequence : public List {
public:
	//index to position
	Iterator atIndex(int i) const;
	//position to index
	int indexOf(const Iterator& p) const;
};


Sequence::Iterator Sequence::atIndex(int i) const {
	//getting an iterator for the front of the sequence
	Iterator p = begin();

	//while the given index is greater than 0 and we decrement it by 1, we will increase out iterator
	while(i-- > 0) ++p;

	return p;
}
// get index from position
int Sequence::indexOf(const Iterator& p) const {
	int j = 0;
	//getting an iterator for 1 before the front of the list because we will increment it in the first time we check the condition
	Iterator q = --begin();
	
	//incrementing our index while we increasing our iterator and it has not reached the given iterator
	while (++q != p) j++;

	return j;
}