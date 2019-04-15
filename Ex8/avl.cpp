#include "avl.h"
#include <cstdlib>
#include <math.h>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

avl::avl()
{
	root = NULL;
}

void avl::checkBalance(avl &tree, Node *node) {
	if (tree.root != NULL) {
		Node *p = node->parent;
		Node *child = node;
		while (p != NULL) {
			if (child == p->right) {
				p->elem.balance++;
				if (p->elem.balance > 1) {
					if (child->elem.balance == -1)
						rightRotate(tree, child);
					leftRotate(tree, p);
					p->elem.balance = child->elem.balance = 0;
					break;
				} else if (p->elem.balance == 0)
					break;
			} else if (child == p->left) {
				p->elem.balance--;
				if (p->elem.balance < -1) {
					if (child->elem.balance == 1)
						leftRotate(tree, child);
					rightRotate(tree, p);
					p->elem.balance = child->elem.balance = 0;
					break;
				}
				else if (p->elem.balance == 0)
					break;
			}
			child = p;
			p = child->parent;
		}
	}
}

void avl::balance(avl &tree, Node *node) {
	Node *p = node->parent;
	while (node != NULL) {
		if (p == NULL)
			break;
		if (node == p->left) {
			if (p->elem.balance == 1) {
				if (node->elem.balance == -1)
					tree.leftRotate(tree, node);
				rightRotate(tree, p);
				break;
			}
			if (p->elem.balance == -1) {
				p->elem.balance = 0;
				break;
			}
			p->elem.balance = 1;
		}
		else {
			if (p->elem.balance == -1) {
				if (node->elem.balance == 1)
					rightRotate(tree, node);
				leftRotate(tree, p);
				break;
			}
			if (p->elem.balance == 1) {
				p->elem.balance = 0;
				break;
			}
			p->elem.balance = -1;
		}
		node = p;
		p = p->parent;
	}
}

void avl::checkWord(avl &tree, string buf) {
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
			Node *x = tree.insertElem(tree, elem);
			if (x!=NULL)
				tree.checkBalance(tree, x);
		}
		i++;
	}
}

void avl::leftRotate(avl &tree, Node *node) {
	Node *x = node;
	Node *y = x->right;
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == NULL)
		tree.root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else x->parent->right = y;
	y->left = x;
	x->parent = y;
}

void avl::rightRotate(avl &tree, Node *node) {
	Node *x = node;
	Node *y = x->left;
	x->left = y->right;
	if (y->right != NULL)
		y->right->parent = x;
	y->parent = x->parent;
	if (x->parent == NULL)
		tree.root = y;
	else if (x == x->parent->right)
		x->parent->right = y;
	else x->parent->left = y;
	y->right = x;
	x->parent = y;
}

avl::~avl()
{
}
