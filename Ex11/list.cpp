#include "list.h"



list::list()
{
	this->sentinel = new ElementLL();
	this->sentinel->next = this->sentinel;
	this->sentinel->prev = this->sentinel;
}

void list::insertElem(Element elem, int u) {
	ElementLL *sen = this->sentinel;
	sen->elem.key = u;
	ElementLL *newEl = new ElementLL;
	ElementLL *p = this->sentinel->next;
	newEl->elem.key = elem.key;
	newEl->elem.value = elem.value;

	if (sen->next == sen) {
		newEl->prev = sen;
		newEl->next = sen;
		sen->next = newEl;
		sen->prev = newEl;
	}
	else {
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

bool list::findKey(int key, Element &elem) {
	ElementLL *sen = this->sentinel;
	ElementLL *p = sen->next;
	if (sen->next != sen) {
		while (p != sen) {
			if (p->elem.key == key) {
				elem = p->elem;
				return true;
			}
			p = p->next;
		}
	}
	return false;
}

void list::showListFromHead(void) {
	ElementLL *sen = this->sentinel;
	ElementLL *p = this->sentinel->next;

	if (sen->next != sen) {
		while (p != sen) {
			cout << p->elem.key << "(" << p->elem.value << "),";
			p = p->next;
		}
	}
	cout << endl;
}

list::~list()
{
}
