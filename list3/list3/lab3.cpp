#include<iostream>
#include <string>
#include <sstream>

using namespace std;


// Two-way unordered cycled list without sentinel
struct Element {
	int key;
	Element *next;
	Element *prev;
};

struct List2W {
	Element *head;
	Element *tail;
};

void init(List2W& l) {
	l.head = new Element;
	l.head = l.tail = NULL;
}

void insertHead(List2W& l, int x) {
	if (l.head == NULL) {
		Element *newEl = new Element;
		newEl->key = x;
		newEl->prev = newEl;
		newEl->next = newEl;
		l.head = l.tail = newEl;
	}
	else  {
		Element *newEl = new Element;
		newEl->key = x;
		l.head->prev = newEl;
		l.tail->next = newEl;
		newEl->next = l.head;
		newEl->prev = l.tail;
		l.head = newEl;
	}
}

bool deleteHead(List2W& l, int &value) {
	if (l.head != NULL) {
		if (l.head != l.tail) {
			Element *temp = l.head;
			value = temp->key;
			l.head = temp->next;
			l.tail->next = l.head;
			l.head->prev = l.tail;
			delete temp;
			return true;
		}
		else {
			Element *temp = l.head;
			value=temp->key;
			l.head = l.tail = NULL;
			return true;
		}
	}
	return false;
}

void insertTail(List2W& l, int x) {
	if (l.head == NULL) {
		insertHead(l, x);
	}
	else {
		Element *newEl = new Element;
		newEl->key = x;
		l.tail->next = newEl;
		l.head->prev = newEl;
		newEl->next = l.head;
		newEl->prev = l.tail;
		l.tail = newEl;
	}
}

bool deleteTail(List2W& l, int &value) {
	if (l.head != NULL) {
		if (l.head == l.tail) {
			deleteHead(l, value);
			return true;
		}
		else {
			Element *temp = l.tail;
			value = temp->key;
			l.tail = temp->prev;
			l.tail->next = l.head;
			l.head->prev = l.tail;
			delete temp;

		}
		return true;
	}
	return false;
}

int checkSize(List2W& l) {
	Element *p = l.head;
	int pos = 0; int size = 0;
	while (p != l.tail) {
		p = p->next;
		size++;
	}
	return size;
}

int findValue(List2W& l, int value) {
	if (l.head != NULL) {
		Element *p = l.head;
		int pos = 0;
		int size=checkSize(l);
		while (pos<=size) {
			if (p->key == value) {
				return pos;
			}
			p = p->next;
			pos++;
		}
	}
	return -1;
}

void removeAllValue(List2W& l, int value) {
	if (l.head != NULL) {
		if (l.head == l.tail && l.head->key == value) {
			deleteHead(l, value);
			return;
		}
		Element *p = l.head;
		int pos = 0;
		int size = checkSize(l);
		int value2;
		while (pos <= size) {
			if (p->key == value) {
				Element *temp = p;
				p = p->next;
				if (l.head == temp) {
					deleteHead(l, value2);
					size--;
					continue;
				}
				else if (l.tail==temp) {
					deleteTail(l, value2);
					size--;
					continue;
				}
				else {
					p->prev = temp->prev;
					temp->prev->next = p;
					delete temp;
					size--;
					continue;
				}
			}
			p = p->next;
			pos++;
		}
	}
}

void showListFromHead(List2W& l) {
	if (l.head != NULL) {
		Element *p = l.head;
		cout << p->key << ",";
		while (p != l.tail) {
			p = p->next;
			cout << p->key << ",";
		}
	}
	cout << endl;
}

void showListFromTail(List2W& l) {
	if (l.head != NULL) {
		Element *p = l.tail;
		cout << p->key << ",";
		while (p != l.head) {
			p = p->prev;
			cout << p->key << ",";
		}
	}
	cout << endl;
}

void clearList(List2W& l) {
	if (l.head != NULL) {
		int value;
		if (l.head == l.tail) {
			deleteHead(l, value);
			return;
		}
		int pos = 0;
		int size = checkSize(l);
		Element *p = l.head;
		while (size != -1) {
			Element *temp = p;
			p = p->next;
			delete temp;
			size--;
		}
		l.head = l.tail = NULL;
	}
}

void addList(List2W& l1, List2W& l2) {
	if (l1.head == l2.head)
		return;
	if (l1.head == NULL) {
		l1.head = l2.head;
		l1.tail = l2.tail;
		l2.head = l2.tail = NULL;
		return;
	}
	if (l2.head == NULL)
		return;
	l1.tail->next = l2.head;
	l1.head->prev = l2.tail;
	l2.head->prev = l1.tail;
	l2.tail->next = l1.head;
	l1.tail = l2.tail;
	l2.head = l2.tail = NULL;
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

		if (isCommand(command, "HA")) {
			cout << "END OF EXECUTION" << endl;
			break;
		}


		// zero-argument command
		if (isCommand(command, "DH")) //*
		{
			int retValue;
			bool retBool = deleteHead(list[currentL], retValue);
			if (retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}
		if (isCommand(command, "DT")) //*
		{
			int retValue;
			bool retBool = deleteTail(list[currentL], retValue);
			if (retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
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

		if (isCommand(command, "FV")) //*
		{
			int ret;
			ret = findValue(list[currentL], value);
			cout << ret << endl;
			continue;
		}

		if (isCommand(command, "RV")) //*
		{
			removeAllValue(list[currentL], value);
			continue;
		}


		if (isCommand(command, "AD")) //*
		{
			addList(list[currentL], list[value]);
			continue;
		}

		if (isCommand(command, "CH")) //*
		{
			currentL = value;
			continue;
		}

		if (isCommand(command, "IH")) //*
		{
			insertHead(list[currentL], value);
			continue;
		}

		if (isCommand(command, "IT")) //*
		{
			insertTail(list[currentL], value);
			continue;
		}

		if (isCommand(command, "GO")) //*
		{
			list = new List2W[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}
}