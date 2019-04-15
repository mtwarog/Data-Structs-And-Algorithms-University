#pragma once
#include "bst.h"
#include "avl.h"

class hashTable :
	public bst
{
public:
	static const int tableSize = 50000;
	bst htable[tableSize];
	Node *hmax[11] = { NULL };

	hashTable();
	void insertElement(hashTable &table, string key);
	void checkWord(hashTable &table, string buf);
	void maxAppearances(Node *node);
	void maxAppearances(hashTable &table);
	void printMaxApp(hashTable &table);
	~hashTable();
};

