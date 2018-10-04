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
#include <stack>

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
using std::stack;

class Graph
{
public:
	struct Node
	{
		Node(int value);
		int value;
		int maxScore;
		bool markToDelete;
		bool visited;
		vector<Node*> children;
		Node* lparent;
		Node* rparent;
	};

	Graph();
	~Graph();
	void build(ifstream &fin, const int depth);
	int findMaxScore();
	static const int MAX_CHILD;

private:
	Node *root;
	void depthFirstSearch(Node* node);
	void deleteGraph(Node *node);
};

// --------------------------------------------
// Graph Functions
// --------------------------------------------
Graph::Node::Node(int value) : value(value), maxScore(value), markToDelete(false), visited(false),
								lparent(NULL), rparent(NULL)
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
					node->lparent = builder.front();
					builder.front()->children.push_back(node);
				}
				// If the parent to be already has the max number of children
				if (builder.front()->children.size() >= MAX_CHILD)
				{
					builder.pop();
				}
				// Determine which side your parent is one
				if (builder.front()->children.size() == 0)
					node->rparent = builder.front();
				else
					node->lparent = builder.front();
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
	int result = 0;
	if (root->children.size() == 0)
		result = root->value;
	else
	{
		depthFirstSearch(root);
		result = root->maxScore;
	}
	
	return result;
}


void Graph::depthFirstSearch(Node* node)
{
	// Base case - If you do not have children
	if (node->children.size() > 0)
	{
		// visit
		if (!node->visited)
		{
			depthFirstSearch(node->children[0]);
			depthFirstSearch(node->children[1]);
			int max0 = node->maxScore + node->children[0]->maxScore;
			int max1 = node->maxScore + node->children[1]->maxScore;
			if (max0 > max1)
				node->maxScore = max0;
			else
				node->maxScore = max1;
			node->visited = true;
		}
	}
}

// This needs to be changed
void Graph::deleteGraph(Node *node)
{
	if (node != NULL)
	{
		for (int i = 0; i < node->children.size(); i++)
		{
			deleteGraph(node->children[i]);
		}
		// Make sure the parents are no longer pointing to you
		if (node->lparent != NULL)
			node->lparent->children[1] = NULL;
		if (node->rparent != NULL)
			node->rparent->children[0] = NULL;

		delete node;
		node = NULL;
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
		cout << "Done with building. Searching..." << endl;
		fout << plinkoBoard.findMaxScore();
		cout << "Found it." << endl;
		getline(fin, line);
		if (line != "0")
			fout << endl;
	}
	return 0;
}
