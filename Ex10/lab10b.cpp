#include<iostream>
#include<string.h>
#include <sstream>

using namespace std;

#define INFINITY 10000000

//list
struct Element {
	int key;
	double value;
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

//graph

struct Graph{
	List2W *arr;
	int size;
};


void insertEdge(Graph &g, int u, int v, double weight){
	Element elem;
	elem.key=v;
	elem.value=weight;
	insertElem(g.arr[u], elem);
}

void loadGraph(Graph &g, int n, int m){
	g.size=n;
	g.arr=new List2W [n];
	for (int i=0; i<n; i++) {
		init(g.arr[i]);
	}
	int u, v;
	double weight;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> weight;
		insertEdge(g, u, v, weight);
	}
}

bool findEdge(Graph &g, int u, int v, double &weight){
	Element elem;
	if (findKey(g.arr[u], v, elem)) {
		weight=elem.value;
		return true;
	}
	return false;
}

void showAsMatrix(Graph &g){
	for (int i=0; i<g.size; i++) {
		for (int j=0; j<g.size; j++) {
			Element elem;
			if (findKey(g.arr[i],j,elem))
				cout<<elem.value<<",";
			else 
				cout<<"-,";
		}
		cout<<endl;
	}
}

void showAsArrayOfLists(Graph &g){
	for (int i=0; i<g.size; i++) {
		cout<<i<<": ";
		showListFromHead(g.arr[i]);
	}
}

bool isCommand(const string command,const char *mnemonic){
	return command==mnemonic;
}


int main(){
	string line;
	string command;
	Graph *graph;
	int currentT=0;
	int value;
	cout << "START" << endl;
	while(true){
		getline(cin,line);
		std::stringstream stream(line);
		stream >> command;
		if(line=="" || command[0]=='#')
		{
			// ignore empty line and comment
			continue;
		}

		// copy line on output with exclamation mark
		cout << "!" << line << endl;;

		// change to uppercase
		command[0]=toupper(command[0]);
		command[1]=toupper(command[1]);

		// zero-argument command
		if(isCommand(command,"HA")){
			cout << "END OF EXECUTION" << endl;
			break;
		}
		// zero-argument command
		if(isCommand(command,"SM"))
		{
			showAsMatrix(graph[currentT]);
			continue;
		}

		if(isCommand(command,"SA"))
		{
			showAsArrayOfLists(graph[currentT]);
			continue;
		}


		// read next argument, one int value
		stream >> value;

		if(isCommand(command,"LG"))
		{
			int m;
			stream >> m;
			loadGraph(graph[currentT],value,m);
			continue;
		}

		if(isCommand(command,"IE"))
		{
			int v;
			double w;
			stream >> v >> w;
			insertEdge(graph[currentT],value,v,w);
			continue;
		}

		if(isCommand(command,"FE"))
		{
			int v;
			stream >> v;
			double w;
			bool ret=findEdge(graph[currentT],value,v,w);

			if(ret)
				cout << w << endl;
			else
				cout << "false" << endl;
			continue;
		}


		if(isCommand(command,"CH"))
		{
			currentT=value;
			continue;
		}

		if(isCommand(command,"GO"))
		{
			graph=new Graph[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
		return 1;
	}
}

