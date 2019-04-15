#pragma once
#include <iostream>
#include <string>

using namespace std;

struct Element {
	string word;
	int appearances, balance;
};

struct Node {
	Element elem;
	Node *left, *right, *parent;
};

class tree {
public:
	class bst;
	class avl;
};

class bst
{
public:
	Node *root;

	Node * createNode(Element elem, Node * PARENT = NULL);
	Node * insertElem(Node *node, Element elem);
	void show(Element elem);
	void show2(Element elem);
	void showInorder(Node *node);
	Node *findKey(Node *node, string key);
	Node * findSuccesor(Node * node);
	void clear(Node * node);
	int height(Node *node);

	bst();
	Node * insertElem(bst & tree, Element elem);
	void showInorder(bst & tree);
	bool findKey(bst & tree, string key, Element &elem);
	Node * minimalNode(Node *node);
	bool removeKey(bst & tree, string key, Element &elem);
	void clear(bst & tree);
	void checkWord(bst &tree, string buf);
	int height(bst & tree);
	void maxAppearances(Node *node, Node *max[]);
	void maxAppearances(bst &tree);
	void printMaxApp(bst &tree, Node *max[]);
	int quantity(bst &tree);
	int quantity(Node *node, int &counter);
	~bst();
};

