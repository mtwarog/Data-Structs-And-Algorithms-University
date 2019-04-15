#include <iostream>
#include "Queue.h"

using namespace std;

Queue::Queue(int size)
{
	this->end = 0;
	this->arr = new int[size];
	this->size = size;
}

bool Queue::isEmpty(void) {
	return this->end == 0;
}

bool Queue::isFull(void) {
	return this->end == this->size;
}

bool Queue::enqueue(int value) {
	if (this->isFull())
		return false;
	this->arr[this->end++] = value;
	return true;
}

bool Queue::dequeue(int &value) {
	if (this->isEmpty())
		return false;
	value = this->arr[0];
	this->arr[0] = 0;
	for (int i = 0; i < this->end; i++)
		this->arr[i] = this->arr[i + 1];
	this->end--;
	cout << value << ",";
	return true;
}

void Queue::show(void) {
	for (int i = 0; i < this->end; i++) {
		if (i > this->size)
			i = 0;
		if (this->arr[i] != 0)
			cout << this->arr[i] << ",";
	}
	cout << endl;
}

Queue::~Queue()
{
}
