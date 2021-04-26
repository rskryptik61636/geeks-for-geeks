#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <array>
#include <map>
#include <list>

using namespace std;

// Source: https://www.geeksforgeeks.org/topological-sorting/
// A C++ program to print topological
// sorting of a DAG

// Class to represent a graph
class Graph
{
	// No. of vertices'
	int V;

	// Pointer to an array containing adjacency listsList
	vector<list<int>> adj;

	// A function used by topologicalSort
	void topologicalSortUtil( int v, vector<bool>& visited, stack<int>& Stack );

public:
	// Constructor
	Graph( int inV );

	// function to add an edge to graph
	void addEdge( int v, int w );

	// prints a Topological Sort of
	// the complete graph
	void topologicalSort();
};

Graph::Graph( int inV ) :
	V(inV),
	adj(inV)
{
}

void Graph::addEdge( int v, int w )
{
	// Add w to v’s list.
	adj[ v ].emplace_back( w );
}

#if 0
// A recursive function used by topologicalSort
void Graph::topologicalSortUtil( int v, vector<bool>& visited, stack<int>& Stack )
{
	// Mark the current node as visited.
	visited[ v ] = true;

	// Recur for all the vertices
	// adjacent to this vertex
	list<int>::iterator i;
	for( i = adj[ v ].begin(); i != adj[ v ].end(); ++i )
		if( !visited[ *i ] )
			topologicalSortUtil( *i, visited, Stack );

	// Push current vertex to stack
	// which stores result
	Stack.push( v );
}
#endif // 0


// An iterative function used by topologicalSort
void Graph::topologicalSortUtil( int v, vector<bool>& visited, stack<int>& Stack )
{
	/*
	* hs = Helper stack
	* hs <- v
	* keepGoing = true
	* while keepGoing:
	*	keepGoing = false
	*	i <- hs.top
	*	if i not in visited:
	*		visited <- i
	*		for j in adj[i]:
	*			if j not in visited:
	*				hs <- j
	*				keepGoing = true
	*				break
	* while hs not empty:
	*	Stack <- hs.pop()
	*/
	stack<int> helper;
	helper.push( v );
	bool keepGoing = true;
	while( keepGoing )
	{
		keepGoing = false;
		auto i = helper.top();
		if( !visited[ i ] )
		{
			visited[ i ] = true;
			for( auto j = adj[ i ].begin(); j != adj[ i ].end(); ++j )
			{
				if( !visited[ *j ] )
				{
					helper.push( *j );
					keepGoing = true;
					break;
				}
			}
		}
	}
	while( !helper.empty() )
	{
		Stack.push( helper.top() );
		helper.pop();
	}
}

// The function to do Topological Sort.
// It uses recursive topologicalSortUtil()
void Graph::topologicalSort()
{
	stack<int> Stack;

	// Mark all the vertices as not visited
	vector<bool> visited( V, false );

	// Call the recursive helper function
	// to store Topological
	// Sort starting from all
	// vertices one by one
	for( int i = 0; i < V; i++ )
		if( visited[ i ] == false )
			topologicalSortUtil( i, visited, Stack );

	// Print contents of stack
	while( Stack.empty() == false )
	{
		cout << Stack.top() << " ";
		Stack.pop();
	}
}

// Driver Code
int main()
{
	// Create a graph given in the above diagram
	Graph g( 6 );
	g.addEdge( 5, 2 );
	g.addEdge( 5, 0 );
	g.addEdge( 4, 0 );
	g.addEdge( 4, 1 );
	g.addEdge( 2, 3 );
	g.addEdge( 3, 1 );

	cout << "Following is a Topological Sort of the given "
		"graph \n";

	// Function Call
	g.topologicalSort();

	return 0;
}
