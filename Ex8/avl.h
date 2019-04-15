#pragma once
#include "bst.h"

class avl :
	public bst
{
public:

	avl();
	void checkWord(avl &tree, string buf);
	void checkBalance(avl &tree, Node *node);
	void leftRotate(avl &tree, Node *node);
	void rightRotate(avl &tree, Node *node);
	void balance(avl &tree, Node *node);
	~avl();
};

