#include<iostream>
#include <string>
#include <sstream>

using namespace std;


struct Element {
	int key;
	int value;
};

struct ElementLL {
	Element elem;
	ElementLL *next, *prev;
};

// Two-way ordered cycled list with sentinel
struct List2W {
	ElementLL *sentinel;
};

void init(List2W& l) {
	l.sentinel = new ElementLL();
	l.sentinel->next = l.sentinel;
	l.sentinel->prev = l.sentinel;
}

void insertElem(List2W & l, Element elem) {
	ElementLL *sen = l.sentinel;
	ElementLL *newEl = new ElementLL;
	ElementLL *p = l.sentinel->next;
	newEl->elem.key = elem.key;
	newEl->elem.value = elem.value;

	if (sen->next == sen) {
		newEl->prev = sen;
		newEl->next = sen;
		sen->next = newEl;
		sen->prev = newEl;
	} else {
		if (newEl->elem.key < p->elem.key) {
			newEl->next = p;
			newEl->prev = p->prev;
			newEl->prev->next = newEl;
			newEl->next->prev = newEl;
		}
		else {
			while (newEl->elem.key >= p->next->elem.key && p->next != sen)
				p = p->next;
			newEl->next = p->next;
			newEl->prev = p;
			newEl->prev->next = newEl;
			newEl->next->prev = newEl;
		}
	}


}

bool findKey(List2W & l, int key, Element &elem) {
	ElementLL *sen = l.sentinel;
	ElementLL *p = sen->next;
	if (sen->next != sen) {
		while (p!= sen) {
			if (p->elem.key == key) {
				elem = p->elem;
				return true;
			}
			p = p->next;
		}
	}
	return false;
}

void removeAllKeys(List2W& l, int key) {
	ElementLL *sen = l.sentinel;
	ElementLL *p = sen->next;
	ElementLL *temp;
	if (sen->next != sen) {
		while (p != sen) {
			if (p->elem.key == key) {
				temp = p;
				p = p->next;
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				delete temp;
				continue;
			}
			p = p->next;
		}
	}
}

void showListFromHead(List2W& l) {
	ElementLL *sen = l.sentinel;
	ElementLL *p = l.sentinel->next;

	if (sen->next != sen) {
		while (p != sen) {
			cout << p->elem.key << "(" << p->elem.value << "),";
			p = p->next;
		}
	}
	cout << endl;
}

void showListFromTail(List2W& l) {
	ElementLL *sen = l.sentinel;
	ElementLL *p = l.sentinel->prev;

	if (sen->prev != sen) {
		while (p != sen) {
			cout << p->elem.key << "(" << p->elem.value << "),";
			p = p->prev;
		}
	}
	cout << endl;
}

void clearList(List2W& l) {
	ElementLL *sen = l.sentinel;
	ElementLL *p = sen->next;
	ElementLL *temp;
	if (sen->next != sen) {
		while (p != sen) {
			temp = p;
			p = p->next;
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp;
		}
	}
}

void addList(List2W& l1, List2W& l2) {
	ElementLL *sen1 = l1.sentinel;
	ElementLL *p1 = sen1->next;
	ElementLL *sen2 = l2.sentinel;
	ElementLL *p2 = sen2->next;
	ElementLL *temp;
	if (l1.sentinel == l2.sentinel) {
		return;
	}
	while (p2 != sen2) {
		temp = p2;
		p2 = p2->next;
		insertElem(l1, temp->elem);
	}
	clearList(l2);
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
	List2W *list;
	int currentL = 0;
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

		if (isCommand(command, "SH")) //*
		{
			showListFromHead(list[currentL]);
			continue;
		}

		if (isCommand(command, "ST")) //*
		{
			showListFromTail(list[currentL]);
			continue;
		}

		if (isCommand(command, "CL")) //*
		{
			clearList(list[currentL]);
			continue;
		}

		if (isCommand(command, "IN")) //*
		{
			init(list[currentL]);
			continue;
		}

		// read next argument, one int value
		stream >> value;

		if (isCommand(command, "FK"))
		{
			Element elem;
			bool ret = findKey(list[currentL], value, elem);
			if (ret)
				cout << elem.key << '(' << elem.value << ')' << endl;
			else
				cout << "false" << endl;
			continue;
		}

		if (isCommand(command, "RK"))
		{
			removeAllKeys(list[currentL], value);
			continue;
		}

		if (isCommand(command, "CH"))
		{
			currentL = value;
			continue;
		}

		if (isCommand(command, "IE"))
		{
			int variable2;
			stream >> variable2;
			Element elem;
			elem.key = value;
			elem.value = variable2;
			insertElem(list[currentL], elem);
			continue;
		}

		if (isCommand(command, "GO"))
		{
			list = new List2W[value];
			continue;
		}

		if (isCommand(command, "AD"))
		{
			addList(list[currentL], list[value]);
			continue;
		}
		cout << "wrong argument in test: " << command << endl;
	}
	return 0;
}