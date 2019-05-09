// Code to read graph instances from a file.  Uses the Boost Graph Library (BGL).

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <fstream>
#include <time.h>

#include <boost/graph/adjacency_list.hpp>

#define LargeValue 99999999

using namespace std;
using namespace boost;


int const NONE = -1;  // Used to represent a node that does not exist

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;
typedef graph_traits<Graph>::vertex_descriptor VertexDescriptor;
int exhaustiveColoring(Graph &g, int numColors, int t);
bool increment(Graph &g, int numColors);
int getColorConflicts(Graph &g);

struct VertexProperties
{
	pair<int,int> cell; // maze cell (x,y) value
	Graph::vertex_descriptor pred;
	bool visited;
	bool marked;
	int weight;
	int color;
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
	int weight;
	bool visited;
	bool marked;
};

void initializeGraph(Graph &g, ifstream &fin)
	// Initialize g using data from fin.  
{
	int n, e;
	int j,k;

	fin >> n >> e;
	Graph::vertex_descriptor v;

	// Add nodes.
	for (int i = 0; i < n; i++)
		v = add_vertex(g);

	for (int i = 0; i < e; i++)
	{
		fin >> j >> k;
		add_edge(j,k,g);  // Assumes vertex list is type vecS
	}
}

void setNodeWeights(Graph &g, int w)
	// Set all node weights to w.
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);

	for (Graph::vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		g[*vItr].weight = w;
	}
}

int main()
{
	char x;
	ifstream fin;
	string fileName;

	// Read the name of the graph from the keyboard or
	// hard code it here for testing.

	// fileName = "instances/color12-3.input";

	cout << "Enter filename" << endl;
	cin >> fileName;

	int t=10; // default to 10 seconds
	cout << "Enter time to run" << endl;
	cin >> t;

	fin.open(fileName.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}

	try
	{
		cout << "Reading graph" << endl;
		Graph g;

		int numColors;
		fin >> numColors;
		cout << "Num Colors: " << numColors << endl;

		initializeGraph(g,fin);

		cout << "Num nodes: " << num_vertices(g) << endl;
		cout << "Num edges: " << num_edges(g) << endl;
		cout << endl;

		int least_conflicts = exhaustiveColoring(g, numColors, t);

		cout << "Least Conflicts: " << least_conflicts << endl;

		cout << "done" << endl;
	}
	catch (...)
	{
		cout << "Program shouldn't be here..." << endl;
		throw;
	}
}

/*
 * Exhaustively searches through coloring patterns for a graph.
 * Starts with all nodes set to color 0. 
 *
 * @param g: a graph to color
 * @param numColors: number of colors to use when filling the graph
 * @param t: time in seconds to run the algorithm
 */
int exhaustiveColoring(Graph &g, int numColors, int t)
{
	clock_t start = clock();
	Graph best_g = g;
	int least_conflicts = num_edges(g);

	do{
		// Check if new graph is best	
		int conflicts = getColorConflicts(g);
		if(conflicts == 0)
		{
			return 0;
		}
		else if(conflicts < least_conflicts)
		{
			best_g = g;
			least_conflicts = conflicts;
		}
		float time_diff = (float) (clock() - start) / CLOCKS_PER_SEC;
		if(time_diff > t) 
		{
			g = best_g;
			break;
		}
	} while(increment(g, numColors));

	return least_conflicts;
}

/*
 * Counts the number of conflicts in a colored graph.
 * Runtime: O(n)
 *
 * @param g: a colored graph
 */
int getColorConflicts(Graph &g)
{
	unsigned int n_cons = 0;
	graph_traits<Graph>::edge_iterator ei, ei_end;
	VertexDescriptor v1, v2;
	for(tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
	{
		v1 = source(*ei, g);
		v2 = target(*ei, g);
		if (g[v1].color == g[v2].color) {
			n_cons += 1;
		}
	}
	//cout << "num conflicts: " << n_cons << endl;
	return n_cons;
}

/*
 * Tries a new colorization of a graph
 *
 * @param g: a colored graph to modify
 * @param numColors: the maximum number of colors to try when coloring
 *
 * TODO: find a better way to iterate. currently wasting a lot of time iterating
 * through all possible colors on first nodes while other nodes don't ever get 
 * their colors changed.
 */
bool increment(Graph &g, int numColors)
{
	unsigned int num_verts = num_vertices(g);

	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		if(g[*vItr].color == numColors - 1)
		{
			g[*vItr].color = 0;
		}
		else
		{
			g[*vItr].color += 1;
			return true;
		}
	}
	return false;
}

