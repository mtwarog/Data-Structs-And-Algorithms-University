#include<iostream>
#include<string.h>
#include <string>
#include <sstream>

using namespace std;

struct Heap {
	int max_size, size, *heapArray;
	bool sorted;
};

void init(Heap &h, int size) {
	h.max_size = size;
	h.heapArray = new int[size];
	h.size = 0;
	h.sorted = false;
}

void heapAdjustment(Heap& h) {
	bool changed = true;
	int *heap = h.heapArray;
	int size = h.size;
	while (changed == true) {
		int parent;
		int child1;
		int child2;
		if (size % 2 == 0)  child1 = size - 1;
		else child1 = size - 2;
		changed = false;
		while (child1 > 0) {
			parent = (child1 - 1) / 2;
			child2 = child1 + 1;
			if (heap[child1] > heap[parent]) {
				int temp = heap[parent];
				heap[parent] = heap[child1];
				heap[child1] = temp;
				changed = true;
			}
			else if (heap[child2] > heap[parent] && child2 < size) {
				int temp = heap[parent];
				heap[parent] = heap[child2];
				heap[child2] = temp;
				changed = true;
			}
			child1 -= 2;
		}
	}
}

void loadAndMakeHeap(Heap &h, int howMany) {
	if (h.max_size < howMany) {
		int i;
		for (i = 0; i < h.max_size; i++) {
			cin >> h.heapArray[i];
			h.size++;
		}
		while (i < howMany) {
			int d;
			cin>>d;
			i++;
		}
		heapAdjustment(h);
	}
	else {
		for (int i = 0; i < howMany; i++) {
			cin >> h.heapArray[i];
			h.size++;
		}
		heapAdjustment(h);
	}
}

void add(Heap &h, int value) {
	if (h.size + 1 <= h.max_size && h.sorted==false) {
		h.size++;
		int *heap = h.heapArray;
		int child = h.size - 1;
		int parent = (child - 1) / 2;
		heap[child] = value;
		while (heap[child] > heap[parent]) {
			int temp = heap[parent];
			heap[parent] = heap[child];
			heap[child] = temp;
			child = parent;
			parent = (child - 1) / 2;
		}
	}
}

void makeSorted(Heap& h) {
	int arr_size = h.size;
	int *heap = h.heapArray;
	for (int i = h.size - 1; i >= 0; i--) {
		h.size--;
		int temp = heap[0];
		heap[0] = heap[i];
		heap[i] = temp;
		heapAdjustment(h);
	}
	h.size = arr_size;
	h.sorted = true;
}

void show(Heap& h) {
	for (int i = 0; i < h.size; i++) {
		cout << h.heapArray[i] << ",";
	}
	cout << endl;
}

void showBool(bool val) {
	if (val)
		cout << "true" << endl;
	else
		cout << "false" << endl;
}

bool isCommand(const string command, const char *mnemonic) {
	return command == mnemonic;
}

int main() {
	string line;
	string command;
	Heap *heap;
	int currentH = 0;
	int value;
	cout << "START" << endl;
	while (true) {
		getline(cin, line);
		std::stringstream stream(line);
		stream >> command;
		if (line == "" || command[0] == '#')
		{
			// ignore empty line and comment
			continue;
		}

		// copy line on output with exclamation mark
		cout << "!" << line << endl;;

		// change to uppercase
		command[0] = toupper(command[0]);
		command[1] = toupper(command[1]);

		if (isCommand(command, "HA")) {
			cout << "END OF EXECUTION" << endl;
			break;
		}

		// zero-argument command
		if (isCommand(command, "MS"))
		{
			makeSorted(heap[currentH]);
			continue;
		}
		if (isCommand(command, "SH"))
		{
			show(heap[currentH]);
			continue;
		}

		// read next argument, one int value
		stream >> value;

		if (isCommand(command, "GO"))
		{
			heap = new Heap[value];
			continue;
		}
		if (isCommand(command, "CH"))
		{
			currentH = value;
			continue;
		}

		if (isCommand(command, "IN"))
		{
			init(heap[currentH], value);
			continue;
		}

		if (isCommand(command, "LD"))
		{
			loadAndMakeHeap(heap[currentH], value);
			continue;
		}

		if (isCommand(command, "AD"))
		{
			add(heap[currentH], value);
			continue;
		}
		cout << "wrong argument in test: " << command << endl;
	}
}