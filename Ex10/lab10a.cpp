#include<iostream>
#include<string.h>
#include <sstream>

using namespace std;

#define INFINITY 10000000

struct Graph {
	double **arr;
	int size;
};

bool validConnection(Graph &g, int u, int v) {
	if (u == v)
		return false;
	else if (u > g.size - 1)
		return false;
	else if (v > g.size - 1)
		return false;
	else
		return true;
}

void insertEdge(Graph &g, int u, int v, double weight) {
	if (validConnection(g, u, v))
		g.arr[u][v] = weight;
}

void loadGraph(Graph &g, int n, int m) {
	g.size = n;
	g.arr = new double *[n];
	for (int i = 0; i < g.size; i++)
		g.arr[i] = new double[n];
	for (int i = 0; i < g.size; i++) {
		for (int j = 0; j < g.size; j++) {
			if (i == j)
				g.arr[i][j] = 0;
			else
				g.arr[i][j] = INT_MAX;
		}
	}
	int u, v;
	double weight;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> weight;
		insertEdge(g, u, v, weight);
	}
}

bool findEdge(Graph &g, int u, int v, double &weight) {
	if ((g.arr[u][v] != 0 && g.arr[u][v] != INT_MAX) && (u < g.size && v < g.size)) {
		weight = g.arr[u][v];
		return true;
	}
	return false;
}

void showAsMatrix(Graph &g) {
	for (int i = 0; i < g.size; i++) {
		for (int j = 0; j < g.size; j++) {
			if (g.arr[i][j] == INT_MAX) {
				cout << "-,";
			}
			else cout << g.arr[i][j] << ",";
		}
		cout << endl;
	}
}

void showAsArrayOfLists(Graph &g) {
	for (int i = 0; i < g.size; i++) {
		cout << i << ":";
		for (int j = 0; j < g.size; j++) {
			if (g.arr[i][j] != 0 && g.arr[i][j] != INT_MAX)
				cout << j << "(" << g.arr[i][j] << "),";
		}
		cout << endl;
	}
}

bool isCommand(const string command, const char *mnemonic) {
	return command == mnemonic;
}


int main() {
	string line;
	string command;
	Graph *graph;
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
		// zero-argument command
		if (isCommand(command, "SM"))
		{
			showAsMatrix(graph[currentT]);
			continue;
		}

		if (isCommand(command, "SA"))
		{
			showAsArrayOfLists(graph[currentT]);
			continue;
		}


		// read next argument, one int value
		stream >> value;

		if (isCommand(command, "LG"))
		{
			int m;
			stream >> m;
			loadGraph(graph[currentT], value, m);
			continue;
		}

		if (isCommand(command, "IE"))
		{
			int v;
			double w;
			stream >> v >> w;
			insertEdge(graph[currentT], value, v, w);
			continue;
		}

		if (isCommand(command, "FE"))
		{
			int v;
			stream >> v;
			double w;
			bool ret = findEdge(graph[currentT], value, v, w);

			if (ret)
				cout << w << endl;
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
			graph = new Graph[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
		return 1;
	}
}
