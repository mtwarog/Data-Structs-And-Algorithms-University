#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "bst.h"
#include "avl.h"
#include "hashTable.h"
using namespace std;

void BSTmax(bst &tree) {
	string buf;
	fstream file;
	file.open("test.txt", ios::in | ios::out);
	if (file.good()) {
		while (file >> buf) {
			tree.checkWord(tree, buf);
		}
		file.close();
	}
	else cout << "File does not exist!" << endl;

}

/*void BSTmax(bst &tree) {
	string buf;
	//while (cin >> buf) {
		cin >> buf;
		tree.checkWord(tree, buf);
	//}
}*/

void BSTtime() {
	bst tree;

	cout << "BST:"<<endl;
	clock_t startTime = clock();
	BSTmax(tree);
	cout << "most often words:" << endl;
	tree.maxAppearances(tree);
	double stopTime = double(clock() - startTime) / (double)CLOCKS_PER_SEC;
	cout << "Time: " << stopTime << "s" << endl << endl;
}

void AVLmax(avl &tree) {
	string buf;
	fstream file;
	file.open("test.txt", ios::in | ios::out);
	if (file.good()) {
		while (file >> buf) {
			tree.checkWord(tree, buf);
		}
		file.close();
	}
	else cout << "File does not exist!" << endl;
}

/*void AVLmax(avl &tree) {
	string buf;
	while (cin >> buf) {
		tree.checkWord(tree, buf);
	}
}*/

void AVLtime() {
	avl tree;
	cout << "AVL:"<<endl;
	clock_t startTime = clock();
	AVLmax(tree);
	cout << "most often words:" << endl;
	tree.maxAppearances(tree);
	double stopTime = double(clock() - startTime) / (double)CLOCKS_PER_SEC;
	cout << "Time: " << stopTime << "s" << endl << endl;
}

void hashMax(hashTable &table) {
	string buf;
	fstream file;
	file.open("test.txt", ios::in | ios::out);
	if (file.good()) {
		while (file >> buf) {
			table.checkWord(table, buf);
		}
		file.close();
	}
	else cout << "File does not exist!" << endl;
}

/*void hashMax(hashTable &table) {
	string buf;
	while (cin >> buf) {
		table.checkWord(table, buf);
	}
}*/

void hashTime() {
	hashTable table;
	clock_t startTime = clock();
	cout << "Hash table:"<<endl;
	hashMax(table);
	table.maxAppearances(table);
	double stopTime = double(clock() - startTime) / (double)CLOCKS_PER_SEC;
	cout << "Time: " << stopTime << "s" << endl << endl;
}


int main(int argc, char *argv[]) {
	hashTime();
	BSTtime();
	AVLtime();
	return 0;
}