#include <iostream>

using namespace std;


//the ArrayVector class using a template
template <typename T>
class ArrayVector {
	/* Data members
	 * max_size - holds the size of the current array holding the data of the vector
	 * data - points to the array that holds the data for the vector
	 * cur - the index of the current element in the vector
 	 */
private:
	int max_size;
	T *data;
	int cur;

public:
	//default constructor, sets max size to 10
	ArrayVector() {
		max_size = 10;
		data = new T[max_size];
		cur = 0;
	}

	//constructor with max size field
	ArrayVector(int size) {
		max_size = size;
		data = new T[max_size];
		cur = 0;
	}

	//the size member function - returns the size of the occupied elements of the vector
	int size() {
		return (cur + 1);
	}

	//the maxSize member function - returns the max size of the vector
	int maxSize() {
		return max_size;
	}

	//returns a boolean for whether or not the vector is empty
	bool empty() {
		return (size == 0);
	}


	//the resize member function resizes the vector to the integer passed as a parameter
	void resize(unsigned int newSize) {
		//printing the new max size for testing
		cout << "New Max Size: " << newSize << endl;
		
		//setting the new max size
		max_size = newSize;

		//creating a temporary array with the new max size and copying all the elements of the old array
		int* temp = new T[max_size];
		for (int i = 0; i <= (cur < max_size ? cur : max_size); i++)
			temp[i] = data[i];

		//deleting the old array
		delete[] data;

		//pointing the data to the new array
		data = temp;
	}

	//the append member function adds an element the the end of the vector
	void append(T elem) {
		//resizing the vector to double the max size if needed
		if (cur >= (max_size-1)) {
			resize(2 * max_size);
		}
		//detting the last element and incrementin the cur data member
		data[cur++] = elem;
	}

	//the eraseAt function removes the element at a given index and moves down the other elements
	void eraseAt(int index) {
		//moving down all the elements and overwriting the element at the given index
		for (int i = index; i < cur; i++)
			data[i] = data[i + 1];
		//decrementing the cur data member
		cur--;

		//shrinking the vector if needed (extra credit)
		if (cur < max_size / 4)
			resize(max_size / 2);
	}

	//the eraseLast member function removes the last elements from the vector
	void eraseLast() {
		//decrementing the cur data member
		cur--;

		//shrrinking the vector if needed (extra credit)
		if (cur < max_size / 4)
			resize(max_size / 2);
	}

	//the print function
	void print() {
		cout << "[";
		for (int i = 0; i < cur; i++)
			cout << data[i] << (i == (cur-1) ? "" : ", ");
		cout << "]" << endl;
	}
};