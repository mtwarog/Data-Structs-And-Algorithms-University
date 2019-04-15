#include<iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

void showArray(int array[], int size) {
	for (int i = 0; i < size; i++)
	{
		cout << array[i] << ",";
	}
	cout << endl;
}

void insertSort(int array[], int size) {
	int temp, j;
	bool changed = false;
	for (int i = size - 2; i >= 0; i--) {
		temp = array[i];
		j = i + 1;
		while (j < size && array[j] < temp) {
			array[j - 1] = array[j];
			j++;
		}
		array[j - 1] = temp;
		showArray(array, size);
	}
}

void bubbleSort(int array[], int size) {
	int temp;
	for (int i = 1; i < size; i++) {
		for (int j = size-1; j >= i; j--) {
			if (array[j - 1] > array[j]) {
				temp = array[j];
				array[j] = array[j - 1];
				array[j - 1] = temp;
			}
		}
		showArray(array, size);
	}
}

void merge(int array[], int left, int mid, int right, int size) {
	int sizeLeft = mid - left + 1;
	int sizeRight = right - mid;
	if (mid >= size) {
		sizeLeft = size - left;
		sizeRight = 0;
	}
	int *L = new int[sizeLeft];
	int *R = new int[sizeRight];

	for (int i = 0; i < sizeLeft; i++)
		L[i] = array[left + i];
	for (int i = 0; i < sizeRight; i++)
		R[i] = array[mid + 1 + i];

	int i, j, k = left;
	i = j = 0;
	while (i < sizeLeft && j < sizeRight) {
		if (L[i] <= R[j]) {
			array[k] = L[i];
			i++;
		}
		else {
			array[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < sizeLeft) {
		array[k] = L[i];
		i++;
		k++;
	}
	while (j < sizeRight) {
		array[k] = R[j];
		j++;
		k++;
	}

	delete L;
	delete R;
}

void mergeSortIter(int array[], int size) {
	int currSize, leftStart, mid, rightEnd;
	for (currSize = 1; currSize < size; currSize = currSize * 2) {
		for (leftStart = 0; leftStart < size; leftStart += currSize * 2) {
			mid = leftStart + currSize - 1;
			if (leftStart + currSize * 2 - 1 < size - 1)
				rightEnd = leftStart + currSize * 2 - 1;
			else
				rightEnd = size - 1;
			merge(array, leftStart, mid, rightEnd, size);
		}
		showArray(array, size);
	}
}

int * loadArray(int size) {
	int* a = new int[size];
	for (int i = 0; i < size; i++)
		cin >> a[i];
	return a;
}

bool isCommand(const string command, const char *mnemonic) {
	return command == mnemonic;
}

int main() {
	string line;
	string command;
	int size = 0;
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

		// read next argument, one int size
		stream >> size;

		// one-argument command
		if (isCommand(command, "HA")) {
			cout << "END OF EXECUTION" << endl;
			break;
		}

		if (isCommand(command, "IS")) //*
		{
			int *arr = loadArray(size);
			showArray(arr, size);
			insertSort(arr, size);
			continue;
		}

		if (isCommand(command, "BS")) //*
		{
			int *arr = loadArray(size);
			showArray(arr, size);
			bubbleSort(arr, size);
			continue;
		}

		if (isCommand(command, "MI")) //*
		{
			int *arr = loadArray(size);
			showArray(arr, size);
			mergeSortIter(arr, size);
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}
	return 0;
}