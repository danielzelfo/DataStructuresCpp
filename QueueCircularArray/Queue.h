#pragma once
#include <iostream>
using namespace std;

//the maximum size of the queue
const int MAX_SIZE = 5;

//the queue class
class Queue {
private:
	//data member
	/* array with the content
	 * the size of the array
	 * the curretn index of the array
	 */
	string data [MAX_SIZE];
	int dataSize;
	int cur;

public:
	//default contructor
	Queue() {
		dataSize = 0;
		cur = -1;
	}

	//the enqueue function - to add an element to the queue
	void enqueue(string elem) {
		if (dataSize < MAX_SIZE) {
			//adding 1 to the current index variable and making sure it stays between 0 and (MAX_SIZE - 1)
			cur = (cur + 1) % MAX_SIZE;

			//setting the element
			data[cur] = elem;

			//increasing the size of the queue
			dataSize++;
		}
	}

	//the dequeue function to remove the oldest added element from the queue
	//to do this, i am just shrinking the size of the queue
	void dequeue() {
		if (dataSize > 0)
			dataSize--;
	}

	//the size function - returns the size of the queue
	int size() {
		return dataSize;
	}

	//the front function - returns the OLDEST added element in the queue
	string front() {
		if (dataSize > 0)
			return data[abs((cur-dataSize+1)%MAX_SIZE)];
		return "";
	}
};