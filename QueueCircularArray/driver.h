/*  Program: Balancing Equations
 *	Author: Daniel Zelfo
 *	Class: CSCI 220
 *	Date: 9/30/2019
 *	Description: This program includes the Queue class, which implements a queue using an circular array
 *				 The Queue class incldues the member functions: enqueue(), dequeue(), size(), and front()
 *
 *	I certify that the code below is my own work.
 *
 *	Exception(s): N/A
 *
 */

#include <iostream>
#include "Queue.h"

void queueCircularArrayMain()
{

	//creating a queue object
	Queue queue1;

	//adding "Daniel" to the queue
	queue1.enqueue("Daniel");
	
	//printing the front of the queue and its size
	cout << "Front: " << queue1.front() << endl;
	cout << "Size: " << queue1.size() << "\n\n";

	//adding "Zelfo" to the queue
	queue1.enqueue("Zelfo");

	//printing the front of the queue and its size
	cout << "Front: " << queue1.front() << endl;
	cout << "Size: " << queue1.size() << "\n\n";

	//removing the oldest element in the queue
	queue1.dequeue();

	//printing the front of the queue and its size
	cout << "Front: " << queue1.front() << endl;
	cout << "Size: " << queue1.size() << "\n\n";

	//removing the oldest element int he queue
	queue1.dequeue();

	//printing the front of the queue and its size
	cout << "Front: " << queue1.front() << endl;
	cout << "Size: " << queue1.size() << endl;


}
