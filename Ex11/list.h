#pragma once
#include <iostream>

using namespace std;

struct Element {
	int key;
	double value;
};

enum color {
	white,
	grey,
	black
};

struct ElementLL {
	Element elem;
	ElementLL *prev, *next;
};

class list
{
public:
	ElementLL *sentinel;
	color c;
	int t;
	int f;
	int parent;

	list();
	void insertElem(Element elem, int u);
	bool findKey(int key, Element &elem);
	void showListFromHead(void);
	~list();
};

