#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <array>
#include <map>
#include <list>
#include <queue>

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

	// Depth first search of the graph starting from node start.
	void dfs( int start );
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
	*	Stack ls;	// Local stack
	*	ls.push(node);
	*
	*	While ls not empty:
	*		Curr = ls.top()
	*		If curr not in visited:
	*			Visited <- curr
	*
	*		addCurrToMs = false
	*		For each node ‘adj’ adjacent to curr in graph:
	*			If adj not in visited:
	*				addCurrToMs = true
	*				ls.push(adj)
	*		
	*		If addCurrToMs:
	*			Ms <- curr
	* 
	*		If curr is ls.top()	// Remove curr if it is top of ls
	*			ls.pop()
	*
	*/
	stack<int> localStack;
	localStack.push( v );

	while( !localStack.empty() )
	{
		const auto currNode = localStack.top();

		// Add currNode to visited
		if( !visited[ currNode ] )
		{
			visited[ currNode ] = true;
		}

		// Add all non-visited nodes adjacent to currNode to localStack.
		bool addCurrNode = true;
		for( auto i = adj[ currNode ].begin(); i != adj[ currNode ].end(); ++i )
		{
			if( !visited[ *i ] )
			{
				addCurrNode = false;
				localStack.push( *i );
			}
		}

		// If nothing was added, push currNode onto Stack.
		if( addCurrNode )
		{
			Stack.push( currNode );
		}

		// If the top of the localStack is currNode, pop it off the localStack
		if( currNode == localStack.top() )
		{
			localStack.pop();
		}
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

// Depth first search of the graph starting from node start.
void Graph::dfs( int start )
{
	// DFS stack.
	stack<int> dfsStack;
	dfsStack.push( start );

	// Visited nodes.
	vector<bool> visited( V, false );

	// Until the stack is empty:
	while( !dfsStack.empty() )
	{
		// Pop the top of the stack.
		const auto top = dfsStack.top();
		dfsStack.pop();

		// Print the current node if its not yet visited.
		if( !visited[ top ] )
		{
			visited[ top ] = true;
			cout << top << " ";
		}

		// Push all the non-visited nodes adjacent to top onto the stack.
		for( auto i = adj[ top ].begin(); i != adj[ top ].end(); ++i )
		{
			if( !visited[ *i ] )
			{
				dfsStack.push( *i );
			}
		}
	}
}

// Source: https://www.geeksforgeeks.org/bipartite-graph/
bool isBipartite(int V, vector<int> adj[])
{
	// vector to store colour of vertex
	// assigning all to -1 i.e. uncoloured
	// colours are either 0 or 1
	// for understanding take 0 as red and 1 as blue
	vector<int> col(V, -1);

	// queue for BFS storing {vertex , colour}
	queue<pair<int, int> > q;

	//loop incase graph is not connected
	for (int i = 0; i < V; i++) {

		//if not coloured
		if (col[i] == -1) {

			//colouring with 0 i.e. red
			q.push({ i, 0 });
			col[i] = 0;

			cout << "Color[" << i << "] = " << 0 << endl;

			while (!q.empty()) {
				pair<int, int> p = q.front();
				q.pop();

				//current vertex
				int v = p.first;
				//colour of current vertex
				int c = p.second;

				//traversing vertexes connected to current vertex
				for (int j : adj[v]) {

					//if already coloured with parent vertex color
					//then bipartite graph is not possible
					if (col[j] == c)
						return 0;

					//if uncoloured
					if (col[j] == -1) {
						//colouring with opposite color to that of parent
						col[j] = (c) ? 0 : 1;
						q.push({ j, col[j] });

						cout << "Color[" << j << "] = " << col[j] << endl;
					}
				}
			}
		}
	}
	//if all vertexes are coloured such that 
	//no two connected vertex have same colours
	return 1;
}

// Driver Code
int main()
{
	static const int V = 4, E = 8;
	
	//adjacency list for storing graph
	vector<int> adj[V];
	adj[0] = { 1,3 };
	adj[1] = { 0,2 };
	adj[2] = { 1,3 };
	adj[3] = { 0,2 };


	bool ans = isBipartite(V, adj);
	//returns 1 if bipartite graph is possible
	if (ans)
		cout << "isBipartite\n";
	//returns 0 if bipartite graph is not possible
	else
		cout << "isNotBipartite\n";

	//// Create a graph given in the above diagram
	//Graph g( 6 );
	//g.addEdge( 5, 2 );
	//g.addEdge( 5, 0 );
	//g.addEdge( 4, 0 );
	//g.addEdge( 4, 1 );
	//g.addEdge( 2, 3 );
	//g.addEdge( 3, 1 );

	//// Do topological sort.
	//cout << "Following is a Topological Sort of the given "
	//	"graph \n";
	//g.topologicalSort();

	// DFS
	//// Create a graph given in the above diagram
	//Graph g(10);
	//g.addEdge( 0, 1 );
	//g.addEdge( 0, 9 );
	//g.addEdge( 1, 2 );
	//g.addEdge( 2, 0 );
	//g.addEdge( 2, 3 );
	//g.addEdge( 9, 3 );

	//cout << "Following is Depth First Traversal"
	//	" (starting from vertex 2) \n";
	//g.dfs( 2 );

	return 0;
}
