#include "bst.h"
#include "hashTable.h"



hashTable::hashTable()
{
	for (int i = 0; i < tableSize; i++) {
		htable[i].root = NULL;
	}
}

void hashTable::insertElement(hashTable &table, string key) {
	hash<string> str_hash;
	int index = str_hash(key) % tableSize;
	table.htable[index].checkWord(table.htable[index], key);
}

void hashTable::checkWord(hashTable &table, string buf) {
	char buf2[100];
	Element elem, selem;
	int i = 0;
	int k = 0;
	while (i<buf.size()) {
		k = 0;
		while (isalpha(buf[i])) {
			buf2[k] = buf[i];
			k++;
			i++;
		}
		buf2[k] = NULL;
		string bword(buf2);
		elem.word = bword;
		if (elem.word[0] != NULL) {
			int j = 0;
			while (elem.word[j] != NULL) {
				elem.word[j] = tolower(elem.word[j]);
				j++;
			}
			insertElement(table, elem.word);
		}
		i++;
	}
}

void hashTable::maxAppearances(Node *node) {
	if (node != NULL) {
		maxAppearances(node->left);

		if (hmax[0] == NULL)
			hmax[0] = node;
		else {
			int i = 9;
			while (i > 0 && hmax[i] == NULL)
				i--;
			hmax[i + 1] = node;
			while (hmax[i]->elem.appearances < hmax[i + 1]->elem.appearances && i > -1) {
				Node *temp = hmax[i];
				hmax[i] = hmax[i + 1];
				hmax[i + 1] = temp;
				i--;
			}
		}

		maxAppearances(node->right);
	}
}

void hashTable::maxAppearances(hashTable &table) {
	for (int i = 0; i < table.tableSize; i++)
		if (table.htable[i].root != NULL)
			maxAppearances(table.htable[i].root);
		printMaxApp(table);
}

void hashTable::printMaxApp(hashTable &table) {
	for (int i = 0; i < 10; i++)
		cout << i + 1 << ".\t" << hmax[i]->elem.word << "\t" << hmax[i]->elem.appearances << endl;
}

hashTable::~hashTable()
{
}
