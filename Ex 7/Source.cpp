#include<iostream>
#include <string>
#include <sstream>

// BST

using namespace std;


struct Element {
	int key;
	int value;
};

struct Node {
	Element elem;
	Node *left, *right, *parent;
};

// Binary search tree
struct BST {
	Node *root;
};

void init(BST & tree) {
	tree.root = NULL;
}

Node * createNode(Element elem, Node * PARENT = NULL) {
	Node *newNode = new Node;
	newNode->elem.key = elem.key;
	newNode->elem.value = elem.value;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = PARENT;

	return newNode;
}

bool insertElem(Node *node, Element elem) {
	if (node->elem.key < elem.key) {
		if (node->right != NULL) return insertElem(node->right, elem);
		else {
			node->right = createNode(elem, node);
			return true;
		}
	}
	else {
		if (node->elem.key > elem.key) {
			if (node->left != NULL) return insertElem(node->left, elem);
			else {
				node->left = createNode(elem, node);
				return true;
			}
		}
	}
	return false;
}

bool insertElem(BST & tree, Element elem) {
	if (tree.root != NULL) {
		return insertElem(tree.root, elem);
		return true;
	}
	else {
		tree.root=createNode(elem);
		return true;
	}
	return false;
}

void show(Element elem) {
	cout << elem.key << "(" << elem.value << "),";
}

void showInorder(Node *node) {
	if (node != NULL) {
		showInorder(node->left);
		show(node->elem);
		showInorder(node->right);
	}
}

void showInorder(BST & tree) {
	if (tree.root != NULL)
		showInorder(tree.root);
	cout << endl;
}

void showPreorder(Node *node) {
	show(node->elem);
	if (node->left != NULL) showPreorder(node->left);
	if (node->right != NULL) showPreorder(node->right);
}

void showPreorder(BST & tree) {
	if (tree.root != NULL)
		showPreorder(tree.root);
	cout << endl;
}

void showPostorder(Node *node) {
	if (node->left != NULL) showPostorder(node->left);
	if (node->right != NULL) showPostorder(node->right);
	show(node->elem);
}

void showPostorder(BST & tree) {
	if (tree.root != NULL)
		showPostorder(tree.root);
	cout << endl;
}

Node *findNode(Node *node, int key) {
	return NULL;
}

Node *findKey(Node *node, int key) {
	while (node != NULL && node->elem.key!=key) {
		if (key < node->elem.key)
			node = node->left;
		else
			node = node->right;
	}
	return node;
}

bool findKey(BST & tree, int key, Element &elem) {
	if (tree.root != NULL) {
		Node *x = findKey(tree.root, key);
		if (x != NULL) 
			elem = x->elem;
		else return false;
		return true;
	}
	return false;
}

Node *minimalNode(Node *node) {
	while (node->left != NULL)
		node = node->left;
	return node;
}

Node * findSuccesor(Node * node) {
	if (node->right != NULL)
		return minimalNode(node->right);
	int key = node->elem.key;
	do {
		node = node->parent;
	} while (node->elem.key <key);

	return node;
}



bool removeKey(BST & tree, int key, Element &elem) {

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

void clear(Node * node) {
	if (!node) return;
	clear(node->left);
	clear(node->right);
	delete node;
}

void clear(BST & tree) {
	clear(tree.root);
	init(tree);

}


int numberOfNodes(Node* node) {
	if (!node)
		return 0;

	int count = 0;

	count += numberOfNodes(node->left);
	count++;
	count += numberOfNodes(node->right);
	return count;
}

int numberOfNodes(BST & tree) {
	return numberOfNodes(tree.root);
}

int height(Node *node)
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

void countLeaves(Node *node, int &leaves) {
	if (node != NULL) {
		countLeaves(node->left, leaves);
		countLeaves(node->right, leaves);
		if (node->left == NULL && node->right == NULL)
			leaves++;
	}
}

int countLeaves(BST & tree) {
	int leaves = 0;
	if (tree.root != NULL)
		countLeaves(tree.root, leaves);
	return leaves;
}

int height(BST & tree) {
	return height(tree.root);
}

int functionA(BST & tree) {
	return -1;
}

int functionB(BST & tree, int key) {
	return -1;
}

bool functionC(BST & tree, int key, Element &elem) {
	return false;
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
	BST *tree;
	int currentT = 0;
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

		// zero-argument command
		if (isCommand(command, "HA")) {
			cout << "END OF EXECUTION" << endl;
			break;
		}

		if (isCommand(command, "SI"))
		{
			showInorder(tree[currentT]);
			continue;
		}

		if (isCommand(command, "SP"))
		{
			showPreorder(tree[currentT]);
			continue;
		}

		if (isCommand(command, "SQ"))
		{
			showPostorder(tree[currentT]);
			continue;
		}

		if (isCommand(command, "CL"))
		{
			clear(tree[currentT]);
			continue;
		}

		if (isCommand(command, "IN"))
		{
			init(tree[currentT]);
			continue;
		}

		if (isCommand(command, "NN"))
		{
			cout << numberOfNodes(tree[currentT]) << endl;
			continue;
		}

		if (isCommand(command, "HE"))
		{
			cout << height(tree[currentT]) << endl;
			continue;
		}

		if (isCommand(command, "LE"))
		{
			cout << countLeaves(tree[currentT]) << endl;
			continue;
		}

		if (isCommand(command, "FA"))
		{
			cout << functionA(tree[currentT]) << endl;
			continue;
		}

		// read next argument, one int value
		stream >> value;


		if (isCommand(command, "IE"))
		{
			int variable2;
			stream >> variable2;
			Element elem;
			elem.key = value;
			elem.value = variable2;
			showBool(insertElem(tree[currentT], elem));
			continue;
		}

		if (isCommand(command, "FK"))
		{
			Element elem;
			bool ret = findKey(tree[currentT], value, elem);
			if (ret)
				cout << elem.key << '(' << elem.value << ')' << endl;
			else
				cout << "false" << endl;
			continue;
		}

		if (isCommand(command, "RK"))
		{
			Element elem;
			bool ret = removeKey(tree[currentT], value, elem);
			if (ret)
				cout << elem.key << '(' << elem.value << ')' << endl;
			else
				cout << "false" << endl;
			continue;
		}


		if (isCommand(command, "CH"))
		{
			currentT = value;
			continue;
		}

		if (isCommand(command, "GO"))
		{
			tree = new BST[value];
			continue;
		}

		if (isCommand(command, "FB"))
		{
			cout << functionB(tree[currentT], value) << endl;
			continue;
		}

		if (isCommand(command, "FC"))
		{
			Element elem;
			bool ret = functionC(tree[currentT], value, elem);
			if (ret)
				cout << elem.key << '(' << elem.value << ')' << endl;
			else
				cout << "false" << endl;
			continue;
		}

		cout << "wrong argument in test: " << command << endl;

	}
	return 0;
}