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
#include <sstream>

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;
using::std::queue;
using std::stringstream;

class Graph
{
public:
	struct Node
	{
		Node(int value);
		int value;
		vector<Node*> children;
	};

	Graph();
	~Graph();
	void build(ifstream &fin, const int depth);
	int findMaxScore();
	static const int MAX_CHILD;

private:
	Node *root;
	void deleteGraph(Node *node);
};

// --------------------------------------------
// Graph Functions
// --------------------------------------------
Graph::Node::Node(int value) : value(value)
{
	children.reserve(MAX_CHILD);
}

const int Graph::MAX_CHILD = 2;

Graph::Graph()
{
	root = NULL;
}

Graph::~Graph()
{
	deleteGraph(root);
}

void Graph::build(ifstream &fin, const int depth)
{
	queue<Node*> builder;
	for (int i = 1; i <= depth; i++)
	{
		string line;
		getline(fin, line);
		stringstream s(line);
		int numIn;
		int numCount = 1;

		while (s >> numIn)
		{
			Node* node = new Node(numIn);
			if (builder.empty())
			{
				root = node;
				builder.push(node);
			}
			else
			{
				// If the parent has one child and the new node is not 
				// to be the last node of this level. This means it will 
				// have 2 parents
				if (builder.front()->children.size() == MAX_CHILD - 1 && numCount != i)
				{
					builder.front()->children.push_back(node);
				}
				// If the parent to be already has the max number of children
				if (builder.front()->children.size() >= MAX_CHILD)
				{
					builder.pop();
				}
				// No matter the above conditions, always place the new
				// node into the queue and the graph
				builder.front()->children.push_back(node);
				builder.push(node);
			}
			numCount++;
		}
	}
}

int Graph::findMaxScore()
{
	return 1;
}

// This needs to be changed - NOT A TREE
void Graph::deleteGraph(Node *node)
{
	if (node != NULL)
	{
		for (Node *child : node->children)
		{
			deleteGraph(child);
		}
		delete node;
	}
}

// -----------------------------------------
// End Graph Functions
// -----------------------------------------

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
		stringstream s(line);
		int depth;
		s >> depth;
		
		Graph plinkoBoard;
		plinkoBoard.build(fin, depth);
		fout << plinkoBoard.findMaxScore();
		
		getline(fin, line);
		if (line != "0")
			fout << endl;
	}
	return 0;
}
