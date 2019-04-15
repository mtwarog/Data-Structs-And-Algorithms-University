#pragma once
class Queue
{
public:
	int *arr;
	int size;
	int end;

	Queue(int size);
	bool isEmpty(void);
	bool isFull(void);
	bool enqueue(int value);
	bool dequeue(int &value);
	void show(void);
	~Queue();
};

