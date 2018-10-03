// -------------------------------------------
// plinko.cpp
// Jeremy Campbell
// Project that will ...
// -------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;
using::std::queue;

class Graph
{
public:
	struct Node
	{
		int value;
		int children = 0;
		Node *left;
		Node *right;
	};

	Graph();
	~Graph();
	void build(const ifstream &fin);
	static const int MAX_CHILD;

private:
	Node *root;
	void deleteGraph();
};

const int Graph::MAX_CHILD = 2;

Graph::Graph()
{
	root = NULL;
}

Graph::~Graph()
{
	deleteGraph();
}

void Graph::build(const ifstream &fin)
{

}

void Graph::deleteGraph()
{

}

int main()
{
	ifstream fin("plinko.in");
	if (!fin)
	{
		cerr << "Could not open nessecary files. Aborting..." << endl;
		return -1;
	}

	ofstream fout("plinko.out");
	string line;

	getline(fin, line);

	while (line != "0")
	{
		// Build a Graph?
		Graph plinkoBoard;
		plinkoBoard.build(fin);

		getline(fin, line);
	}
}
