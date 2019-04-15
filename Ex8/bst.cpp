#include <iostream>
#include <string>
#include "bst.h"

using namespace std;

bst::bst() {
	root = NULL;
}

Node * bst::createNode(Element elem, Node * PARENT) {
	Node *newNode = new Node;
	newNode->elem.word = elem.word;
	newNode->elem.appearances = 1;
	newNode->elem.balance=0;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = PARENT;

	return newNode;
}

Node * bst::insertElem(Node *node, Element elem) {
	if (node->elem.word < elem.word) {
		if (node->right != NULL) return insertElem(node->right, elem);
		else {
			node->right = createNode(elem, node);
			return node->right;
		}
	}
	else {
		if (node->elem.word > elem.word) {
			if (node->left != NULL) return insertElem(node->left, elem);
			else {
				node->left = createNode(elem, node);
				return node->left;
			}
		}
	}
	node->elem.appearances++;
	return NULL;
}

Node * bst::insertElem(bst & tree, Element elem) {
	if (tree.root != NULL) {
		return insertElem(tree.root, elem);
	}
	else {
		tree.root = createNode(elem);
		return tree.root;
	}
	return NULL;
}

void bst::show(Element elem) {
	cout << elem.word<<"("<<elem.appearances<<")"<<endl;
}

void bst::show2(Element elem) {
	cout << elem.word << "(" << elem.appearances << ") ";
}

void bst::showInorder(Node *node) {
	if (node != NULL) {
		showInorder(node->left);
		show(node->elem);
		showInorder(node->right);
	}
}

void bst::showInorder(bst & tree) {
	if (tree.root != NULL)
		showInorder(tree.root);
	cout << endl;
}

int bst::quantity(Node *node, int &counter) {
	if (node != NULL) {
		quantity(node->left, counter);
		counter++;
		quantity(node->right, counter);
	}
	return counter;
}

int bst::quantity(bst & tree) {
	int counter = 0;
	if (tree.root != NULL)
		quantity(tree.root, counter);
	return counter;
}

Node * bst::findKey(Node *node, string key) {
	while (node != NULL && strcmp(node->elem.word.c_str(), key.c_str())!=0) {
		if (key < node->elem.word)
			node = node->left;
		else
			node = node->right;
	}
	return node;
}

bool bst::findKey(bst & tree, string key, Element &elem) {
	if (tree.root != NULL) {
		Node *x = findKey(tree.root, key);
		if (x != NULL) {
			elem = x->elem;
			x->elem.appearances++;
			return true;
		}
		else 
			return false;
	}
	return false;
}

Node * bst::minimalNode(Node *node) {
	while (node->left != NULL)
		node = node->left;
	return node;
}

Node * bst::findSuccesor(Node * node) {
	if (node->right != NULL)
		return minimalNode(node->right);
	string key = node->elem.word;
	do {
		node = node->parent;
	} while (node->elem.word <key);

	return node;
}



bool bst::removeKey(bst & tree, string key, Element &elem) {

	Node * deleteNode = findKey(tree.root, key);
	if (deleteNode != NULL) {
		Node * x;
		Node * y;
		elem = deleteNode->elem;

		if (deleteNode->right == NULL && deleteNode->left == NULL)
			y = deleteNode;
		else
			y = findSuccesor(deleteNode);
		if (y->left != NULL)
			x = y->left;
		else
			x = y->right;
		if (x != NULL)
			x->parent = y->parent;
		if (y->parent == NULL)
			tree.root = x;
		else
			if (y == y->parent->left)
				y->parent->left = x;
			else
				y->parent->right = x;
		if (y != deleteNode)
			deleteNode->elem = y->elem;
		return true;
	}
	return false;

}

int bst::height(Node *node)
{
	if (!node)
		return 0;

	int h = 0;
	h++;

	int left = height(node->left);
	int right = height(node->right);

	(left > right) ? h += left : h += right;
	return h;
}

int bst::height(bst & tree) {
	return height(tree.root);
}


void bst::clear(Node * node) {
	if (!node) return;
	clear(node->left);
	clear(node->right);
	delete node;
}

void bst::clear(bst & tree) {
	clear(tree.root);
	tree.root = NULL;
}

void bst::checkWord(bst &tree, string buf) {
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
			tree.insertElem(tree, elem);
		}
		i++;
	}
}

void bst::maxAppearances(Node *node, Node *max[]) {
	if (node != NULL) {
		maxAppearances(node->left, max);

		if (max[0] == NULL)
			max[0] = node;
		else {
			int i = 9;
			while (i > 0 && max[i] == NULL)
				i--;
			max[i + 1] = node;
			while (i > -1) {
				if (max[i]->elem.appearances < max[i + 1]->elem.appearances) {
					Node *temp = max[i];
					max[i] = max[i + 1];
					max[i + 1] = temp;
				}
				i--;
			}
		}

		maxAppearances(node->right, max);
	}
}

void bst::maxAppearances(bst &tree) {
	Node *max[11] = { NULL };
	if (tree.root != NULL) {
		maxAppearances(tree.root, max);
	}
	printMaxApp(tree, max);
}

void bst::printMaxApp(bst &tree, Node *max[]) {
	for (int i = 0; i < 10; i++)
		cout << i + 1 << ".\t" << max[i]->elem.word << "\t" << max[i]->elem.appearances << endl;
}

bst::~bst()
{
}
