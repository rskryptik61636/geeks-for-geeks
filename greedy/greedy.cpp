#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <array>
#include <map>

using namespace std;

// Source: https://practice.geeksforgeeks.org/problems/fractional-knapsack-1587115620/1
struct Item
{
    int value;
    int weight;
};

// Refer: https://www.geeksforgeeks.org/fractional-knapsack-problem/
double fractionalKnapsack( int W, Item arr[], int n )
{
    // Lifted from: https://ide.geeksforgeeks.org/jO07eJg6ai
    sort(
        arr,
        arr + n,
        []( const auto& x, const auto& y )
    {
        // Same as this but no need to cast!
        //return (double)x.value / (double)x.weight > (double)y.value / (double)y.weight;

        return x.value * y.weight > y.value * x.weight;
    } );
    double res = 0;
    for( int i = 0; i < n && W; i++ )
    {
        if( arr[ i ].weight > W ) // add fractional
            res += ( (double)arr[ i ].value / arr[ i ].weight ) * W, W = 0;
        else //add whole
            res += arr[ i ].value, W -= arr[ i ].weight;
    }
    return res;
}

string largestNumber( int n, int sum )
{

    // Accummulate the sum of digits.
    int remSum = sum, remDigits = n;

    // Init the result with all 0s
    string result( n, '0' );

    // To convert int in [0, 9] to a char.
    auto toChar = []( const auto& in )
    {
        return '0' + in;
    };

    // Insert the remainder in each i'th index of the result.
    for( size_t indx = 0; indx < n; ++indx )
    {
        // Early out if remSum is 0.
        if( remSum <= 0 )
            break;

        const int currDigit = ( remSum > 9 ) ? 9 : remSum;
        result[ indx ] = toChar( currDigit );
        remSum -= currDigit;
    }

    // If there's still a remainder of the sum, return -1, else the result.
    return ( remSum > 0 ) ? "-1" : result;
}

//Function to find the maximum number of activities that can
//be performed by a single person.
int activitySelection( vector<int> start, vector<int> end, int n )
{
    // Create a start,end pair list and sort by the end time.
    vector<pair<int, int>> temp( n );
    for( auto i = 0; i < temp.size(); ++i )
        temp[ i ] = make_pair( start[ i ], end[ i ] );
    sort(
        temp.begin(),
        temp.end(),
        []( const auto& a, const auto& b )
    {
        return a.second < b.second;
    }
    );

    // Accummulate the number of activities based on the current end day.
    int currStart = 0, numActs = 0;
    for( auto i = 0; i < temp.size(); ++i )
    {
        cout << "start = " << temp[ i ].first << "; end = " << temp[ i ].second << endl;
        if( currStart < temp[ i ].first )
        {
            currStart = temp[ i ].second;
            ++numActs;
            cout << "Taken. currStart = " << currStart << "; numActs = " << numActs << endl;
        }
    }

    cout << "Total num activities = " << numActs << endl;
    return numActs;
}

vector<string> huffmanCodes( string S, vector<int> f, int N )
{
    // Create a multiset of each char in S and its frequency.
    struct CharSet
    {
        char ch;
        int freq;
        size_t leftIndx;    // Left child index in tree vector
        size_t rightIndx;   // Right child index in tree vector
    };

    struct CharSetCompare
    {
        bool operator()( const CharSet& a, const CharSet& b ) const
        {
            return a.freq < b.freq;
        }
    };

    using SortedCharSet = multiset<CharSet, CharSetCompare>;
    SortedCharSet sortedCharSet;
    static constexpr size_t nullIndx = std::numeric_limits<size_t>::max();
    for( auto i = 0; i < f.size(); ++i )
        sortedCharSet.insert( { S[ i ], f[ i ], nullIndx, nullIndx } );

    // The binary tree that stores the huffman codes is a vector<CharSet>
    vector<CharSet> huffmanCodes;
    huffmanCodes.reserve( (2 * N) + 1 );

    // Until there's only a single element left in sortedCharSet.
    size_t endIndx = 0;
    while( sortedCharSet.size() > 1 )
    {
        // Extract the first two elements and add them .
        //auto first = sortedCharSet.extract( sortedCharSet.begin() );
        auto pFirst = sortedCharSet.begin();
        const auto firstFreq = pFirst->freq;
        huffmanCodes.emplace_back( *pFirst );
        sortedCharSet.erase( sortedCharSet.begin() );

        auto pSecond = sortedCharSet.begin();
        const auto secondFreq = pSecond->freq;
        huffmanCodes.emplace_back( *pSecond );
        sortedCharSet.erase( sortedCharSet.begin() );

        endIndx += 2;

        // Insert an internal node to sortedCharSet whose frequency is the sum of the first two element's frequencies and set its left and right children to the indices of the extracted elements.
        sortedCharSet.insert( { '0', firstFreq + secondFreq, endIndx - 2, endIndx - 1 } );
    }

    // Insert the only element of sortedCharSet into huffmanCodes.
    huffmanCodes.emplace_back( *sortedCharSet.begin() );

    // Stacks to track the left\right subtrees as well as if left\right children have been traversed of each current node.
    struct InternalNode
    {
        size_t indx;
        bool leftDone;
        bool rightDone;
    };
    stack<InternalNode> internalStack;
    internalStack.push( { huffmanCodes.size() - 1, false, false } );

    // Traverse the huffman codes tree pre-order and append to the results string vector.
    vector<string> codes;
    string currString;
    while( codes.size() != N )
    {
        // Get the current node.
        auto& currNode = internalStack.top();
        auto& currSet = huffmanCodes[ currNode.indx ];

        // Set the left and right done flags if the left and right child indices are null respectively.
        if( !currNode.leftDone )
        {
            currNode.leftDone = ( currSet.leftIndx == nullIndx );
        }
        if( !currNode.rightDone )
        {
            currNode.rightDone = ( currSet.rightIndx == nullIndx );
        }

        // If both left and right children have been visited: 
        // Pop the current top of the internalStack
        // Remove the last char from currString
        // Make the new top of the internalStack the current Node and continue.
        if( currNode.leftDone && currNode.rightDone )
        {
            // Only add a leaf node's code.
            if( currSet.ch != '0' )
            {
                codes.push_back( currString );
            }

            internalStack.pop();
            if( !currString.empty() )
                currString.pop_back();
            if( !internalStack.empty() )
                currNode = internalStack.top();
        }
        
        // Push the left child onto the internal stack if it hasn't already been visited, else do the same for the right child index onto the right stack.
        else if( !currNode.leftDone )
        {
            internalStack.push( { currSet.leftIndx, false, false } );
            currString += '0';
            currNode.leftDone = true;
        }
        else if( !currNode.rightDone )
        {
            internalStack.push( { currSet.rightIndx, false, false } );
            currString += '1';
            currNode.rightDone = true;
        }
    }

    return codes;
}

// Source: https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/
// C++ program for Kruskal's algorithm
// to find Minimum Spanning Tree of a
// given connected, undirected and weighted
// graph

// a structure to represent a
// weighted edge in graph
class Edge
{
public:
    int v1, v2, weight;
};

// a structure to represent a connected,
// undirected and weighted graph
class Graph
{
public:

    int numVerts, numEdges;

    // graph is represented as an array of edges.
    // Since the graph is undirected, the edge
    // from src to dest is also edge from dest
    // to src. Both are counted as 1 edge here.
    Edge* edge;
};

// Creates a graph with V vertices and E edges
Graph* createGraph( int V, int E )
{
    Graph* graph = new Graph;
    graph->numVerts = V;
    graph->numEdges = E;

    graph->edge = new Edge[ E ];

    return graph;
}

// A structure to represent a subset for union-find
class subset
{
public:
    int parent;
    int rank;
};

// A utility function to find set of an element i
// (uses path compression technique)
int findRoot( subset subsets[], int i )
{
    // find root and make root as parent of i
    // (path compression)

    // Lazy update
    if( subsets[ i ].parent != i )
    {
        int root = i;
        while( subsets[ root ].parent != root )
        {
            root = subsets[ root ].parent;
        }
        subsets[ i ].parent = root;
    }

    //// Stack based iterative
    //int root = i;
    //if( subsets[ root ].parent != root )
    //{
    //    stack<int> toUpdate;
    //    while( subsets[ root ].parent != root )
    //    {
    //        toUpdate.push( root );
    //        root = subsets[ root ].parent;
    //    }

    //    while( !toUpdate.empty() )
    //    {
    //        subsets[ toUpdate.top() ].parent = root;
    //        toUpdate.pop();
    //    }
    //}

    //// Recursive
    //if( subsets[ i ].parent != i )
    //    subsets[ i ].parent
    //    = findRoot( subsets, subsets[ i ].parent );

    return subsets[ i ].parent;
}

// A function that does union of two sets of x and y
// (uses union by rank)
void Union( subset subsets[], int x, int y )
{
    int xroot = findRoot( subsets, x );
    int yroot = findRoot( subsets, y );

    // Attach smaller rank tree under root of high
    // rank tree (Union by Rank)
    if( subsets[ xroot ].rank < subsets[ yroot ].rank )
        subsets[ xroot ].parent = yroot;
    else if( subsets[ xroot ].rank > subsets[ yroot ].rank )
        subsets[ yroot ].parent = xroot;

    // If ranks are same, then make one as root and
    // increment its rank by one
    else
    {
        subsets[ yroot ].parent = xroot;
        subsets[ xroot ].rank++;
    }
}

// Compare two edges according to their weights.
// Used in qsort() for sorting an array of edges
int myComp( const void* a, const void* b )
{
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    return a1->weight > b1->weight;
}

// The main function to construct MST using Kruskal's
// algorithm
// This code is contributed by rathbhupendra
void KruskalMST( Graph* graph )
{
    int V = graph->numVerts;
    vector<Edge> result( V ); // Tnis will store the resultant MST
    int outEdge = 0; // An index variable, used for result[]
    int inEdge = 0; // An index variable, used for sorted edges

    // Step 1: Sort all the edges in non-decreasing
    // order of their weight. If we are not allowed to
    // change the given graph, we can create a copy of
    // array of edges
    qsort( graph->edge, graph->numEdges, sizeof( graph->edge[ 0 ] ),
        myComp );

    // Allocate memory for creating V ssubsets
    subset* subsets = new subset[ ( V * sizeof( subset ) ) ];

    // Create V subsets with single elements
    for( int v = 0; v < V; ++v )
    {
        subsets[ v ].parent = v;
        subsets[ v ].rank = 0;
    }

    // Number of edges to be taken is equal to V-1
    while( outEdge < V - 1 && inEdge < graph->numEdges )
    {
        // Step 2: Pick the smallest edge. And increment
        // the index for next iteration
        Edge next_edge = graph->edge[ inEdge++ ];

        int v1Root = findRoot( subsets, next_edge.v1 );
        int v2Root = findRoot( subsets, next_edge.v2 );

        // If including this edge does't cause cycle,
        // include it in result and increment the index
        // of result for next edge
        if( v1Root != v2Root )
        {
            result[ outEdge++ ] = next_edge;
            Union( subsets, v1Root, v2Root );
        }
        // Else discard the next_edge
    }

    // print the contents of result[] to display the
    // built MST
    cout << "Following are the edges in the constructed "
        "MST\n";
    int minimumCost = 0;
    for( inEdge = 0; inEdge < outEdge; ++inEdge )
    {
        cout << result[ inEdge ].v1 << " -- " << result[ inEdge ].v2
            << " == " << result[ inEdge ].weight << endl;
        minimumCost = minimumCost + result[ inEdge ].weight;
    }
    // return;
    cout << "Minimum Cost Spanning Tree: " << minimumCost
        << endl;

    delete[] subsets;
}

// Prim's MST: https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/
// Number of vertices in the graph 
#define NUM_PRIM_VERTS 5 

// A utility function to find the vertex with 
// minimum key value, from the set of vertices 
// not yet included in MST 
int minKey( int key[], bool mstSet[] )
{
    // Initialize min value 
    int min = INT_MAX, min_index;

    for( int v = 0; v < NUM_PRIM_VERTS; v++ )
        if( mstSet[ v ] == false && key[ v ] < min )
            min = key[ v ], min_index = v;

    return min_index;
}

// A utility function to print the 
// constructed MST stored in parent[] 
void printMST( int parent[], int graph[ NUM_PRIM_VERTS ][ NUM_PRIM_VERTS ] )
{
    cout << "Edge \tWeight\n";
    for( int i = 1; i < NUM_PRIM_VERTS; i++ )
        cout << parent[ i ] << " - " << i << " \t" << graph[ i ][ parent[ i ] ] << " \n";
}

// Function to construct and print MST for 
// a graph represented using adjacency 
// matrix representation 
void primMST( int graph[ NUM_PRIM_VERTS ][ NUM_PRIM_VERTS ] )
{
    // Array to store constructed MST 
    int parent[ NUM_PRIM_VERTS ];

    // Key values used to pick minimum weight edge in cut 
    int key[ NUM_PRIM_VERTS ];

    // To represent set of vertices included in MST 
    bool mstSet[ NUM_PRIM_VERTS ];

    // Initialize all keys as INFINITE 
    for( int i = 0; i < NUM_PRIM_VERTS; i++ )
        key[ i ] = INT_MAX, mstSet[ i ] = false;

    // Always include first 1st vertex in MST. 
    // Make key 0 so that this vertex is picked as first vertex. 
    key[ 0 ] = 0;
    parent[ 0 ] = -1; // First node is always root of MST 

    // The MST will have V vertices 
    for( int count = 0; count < NUM_PRIM_VERTS - 1; count++ )
    {
        // Pick the minimum key vertex from the 
        // set of vertices not yet included in MST 
        int u = minKey( key, mstSet );

        // Add the picked vertex to the MST Set 
        mstSet[ u ] = true;

        // Update key value and parent index of 
        // the adjacent vertices of the picked vertex. 
        // Consider only those vertices which are not 
        // yet included in MST 
        for( int v = 0; v < NUM_PRIM_VERTS; v++ )

            // graph[u][v] is non zero only for adjacent vertices of m 
            // mstSet[v] is false for vertices not yet included in MST 
            // Update the key only if graph[u][v] is smaller than key[v] 
            if( graph[ u ][ v ] && mstSet[ v ] == false && graph[ u ][ v ] < key[ v ] )
                parent[ v ] = u, key[ v ] = graph[ u ][ v ];
    }

    // print the constructed MST 
    printMST( parent, graph );
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
#define DSTRA_VERTS 9
void dijkstra( int graph[ DSTRA_VERTS ][ DSTRA_VERTS ], int src )
{
    // Min heap of paths from src
    // element = <node, path cost>
    struct ShortestPath
    {
        ShortestPath( const int node, const int cost ) :
            m_Node( node ),
            m_PathCost( cost )
        {
        }

        bool operator<( const ShortestPath& a ) const
        {
            return m_PathCost < a.m_PathCost;
        }

        bool operator==( const ShortestPath& a ) const
        {
            return m_Node == a.m_Node;
        }

        int m_Node, m_PathCost;
    };
    std::multiset<ShortestPath> minPaths;
    for( auto i = 0; i < DSTRA_VERTS; ++i )
    {
        minPaths.insert( ShortestPath( i, INT_MAX ) );
    }

    // Shortest path to reach each node from src.
    std::array<int, DSTRA_VERTS> shortestPaths;
    std::fill( shortestPaths.begin(), shortestPaths.end(), INT_MAX );

    // Parents of each node in the shortest path graph.
    std::array<int, DSTRA_VERTS> parents;
    std::fill( parents.begin(), parents.end(), INT_MAX );

    // Function to help find a node in minPaths.
    auto fnFindNode = [&]( const auto node )
    {
        auto i = minPaths.begin();
        for( ; i != minPaths.end(); ++i )
        {
            if( i->m_Node == node )
                break;
        }
        return i;
    };

    // Function to help update the cost of a node.
    //auto dummyFind = ShortestPath( src, INT_MAX );
    auto fnUpdateCost = [&]( const auto node, const auto newCost )
    {
        //dummyFind.m_Node = node;
        auto pElem = minPaths.extract( fnFindNode( node ) );
        pElem.value().m_Node = node;
        pElem.value().m_PathCost = newCost;
        minPaths.insert( std::move( pElem ) );
    };

    // Start with the src node and set its minPaths\shortestPaths\parents to 0.
    //minPaths[ src ] = 0;
    fnUpdateCost( src, 0 );
    shortestPaths[ src ] = 0;
    parents[ src ] = 0;

    // Continue until minPaths is empty.
    while( !minPaths.empty() )
    {
        // Grab the smallest element from minPaths and remove it.
        auto currNode = *minPaths.begin();
        shortestPaths[ currNode.m_Node ] = currNode.m_PathCost;
        minPaths.erase( minPaths.begin() );

        // Iterate over the neighbours for currNode.
        for( auto i = 0; i < DSTRA_VERTS; ++i )
        {
            auto currSrc = currNode.m_Node, currDst = i;

            // Skip the current node if src and dst are the same or if a shortest path has already been computed for it.
            if( currSrc == currDst || shortestPaths[ currDst ] != INT_MAX )
                continue;

            // If the path to the curr dst is lower than the cost of the src + cost of (src -> dst):
            //dummyFind.m_Node = currDst;
            auto dstMinPath = fnFindNode( currDst );
            const auto currDstCost = dstMinPath->m_PathCost, newDstCost = currNode.m_PathCost + graph[ currSrc ][ currDst ];
            if( graph[ currSrc ][ currDst ] != 0 && newDstCost < currDstCost )
            {
                // Update dst's cost and it's parent.
                fnUpdateCost( currDst, newDstCost );
                //dstMinPath->m_PathCost = newDstCost;
                parents[ currDst ] = currSrc;
            }
        }
    }

    // Print the shortest paths for each node from the src.
    cout << "Src: " << src << endl;
    for( auto i = 0; i < DSTRA_VERTS; ++i )
    {
        if( i != src )
        {
            cout << "Dst: " << i << "; path = " << shortestPaths[ i ] << endl;
        }
    }
}

// Source: https://practice.geeksforgeeks.org/problems/-minimum-number-of-coins4426/1
vector<int> minPartition( int N )
{
    // Denominations.
    static const int den[] = { 1, 2, 5, 10, 20, 50, 100, 200, 500, 2000 };
    static const int numDen = sizeof( den ) / sizeof( den[ 0 ] );

    // Start from the largest denomination.
    int cdi = numDen - 1;   // Current denomination index.
    int balance = N;    // Remaining balance.
    vector<int> result;
    while( cdi >= 0 && balance >= 0 )
    {
        const int currDen = den[ cdi ];

        // If the balance >= currDen.
        if( balance >= currDen )
        {
            // Calculate the no. of notes of the current denomination to be subtracted.
            const int numNotes = ( balance / currDen );

            // Decrement the balance by the appropriate amount.
            balance -= ( numNotes * currDen );

            // Append numNotes of currDen to the result.
            for( auto i = 0; i < numNotes; ++i )
                result.emplace_back( currDen );
        }

        // Decrement cdi.
        --cdi;
    }

    return result;
}

int main( int argc, char* argv[] )
{
    //// fractional knapsack.
    //int N = 3, W = 50;
    //Item arr[] =
    //{
    //    {60, 10},
    //    {100, 20},
    //    {120, 30}
    //};
    //cout << "fractionalKnapsack( W, arr[], n ) = " << fractionalKnapsack( W, arr, N ) << endl;
    ///*int values[] = { 60,100,120 };
    //int weight[] = { 10,20,30 };*/

    //// Activity selection.
    //int n = 4;
    //vector<int> start { 1, 3, 2, 5 };
    //vector<int> end { 2, 3, 4, 6 };
    //int acts = activitySelection( start, end, n );

    //// Huffman coding
    //string S = "abcdef";
    //vector<int> f { 5, 9, 12, 13, 16, 45 };
    //huffmanCodes( S, f, static_cast<int>( f.size() ) );

    //// Kruskal's MST

    //// Graph from: https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/
    //int numVerts = 9;  // Num vertices
    //int numEdges = 14; // Num edges.
    //int cedge = 0; // Edge counter
    //Graph* graph = createGraph( numVerts, numEdges );

    //// add edge 0 - 1
    //graph->edge[ cedge ].v1 = 0;
    //graph->edge[ cedge ].v2 = 1;
    //graph->edge[ cedge ].weight = 4;
    //++cedge;

    //// add edge 0 - 7
    //graph->edge[ cedge ].v1 = 0;
    //graph->edge[ cedge ].v2 = 7;
    //graph->edge[ cedge ].weight = 8;
    //++cedge;

    //// add edge 1 - 7
    //graph->edge[ cedge ].v1 = 1;
    //graph->edge[ cedge ].v2 = 7;
    //graph->edge[ cedge ].weight = 11;
    //++cedge;

    //// add edge 1 - 2
    //graph->edge[ cedge ].v1 = 1;
    //graph->edge[ cedge ].v2 = 2;
    //graph->edge[ cedge ].weight = 8;
    //++cedge;

    //// add edge 7 - 8
    //graph->edge[ cedge ].v1 = 7;
    //graph->edge[ cedge ].v2 = 8;
    //graph->edge[ cedge ].weight = 7;
    //++cedge;

    //// add edge 7 - 6
    //graph->edge[ cedge ].v1 = 7;
    //graph->edge[ cedge ].v2 = 6;
    //graph->edge[ cedge ].weight = 1;
    //++cedge;

    //// add edge 2 - 3
    //graph->edge[ cedge ].v1 = 2;
    //graph->edge[ cedge ].v2 = 3;
    //graph->edge[ cedge ].weight = 7;
    //++cedge;

    //// add edge 2 - 8
    //graph->edge[ cedge ].v1 = 2;
    //graph->edge[ cedge ].v2 = 8;
    //graph->edge[ cedge ].weight = 2;
    //++cedge;

    //// add edge 2 - 5
    //graph->edge[ cedge ].v1 = 2;
    //graph->edge[ cedge ].v2 = 5;
    //graph->edge[ cedge ].weight = 4;
    //++cedge;

    //// add edge 8 - 6
    //graph->edge[ cedge ].v1 = 8;
    //graph->edge[ cedge ].v2 = 6;
    //graph->edge[ cedge ].weight = 6;
    //++cedge;

    //// add edge 6 - 5
    //graph->edge[ cedge ].v1 = 6;
    //graph->edge[ cedge ].v2 = 5;
    //graph->edge[ cedge ].weight = 2;
    //++cedge;

    //// add edge 3 - 5
    //graph->edge[ cedge ].v1 = 3;
    //graph->edge[ cedge ].v2 = 5;
    //graph->edge[ cedge ].weight = 14;
    //++cedge;

    //// add edge 3 - 4
    //graph->edge[ cedge ].v1 = 3;
    //graph->edge[ cedge ].v2 = 4;
    //graph->edge[ cedge ].weight = 9;
    //++cedge;

    //// add edge 5 - 4
    //graph->edge[ cedge ].v1 = 5;
    //graph->edge[ cedge ].v2 = 4;
    //graph->edge[ cedge ].weight = 10;
    //++cedge;

    //// Function call
    //KruskalMST( graph );

    //delete graph;

    //// Prim's MST
    ///* Let us create the following graph
    //    2   3
    //(0)--(1)--(2)
    // |   / \   |
    //6| 8/   \5 |7
    // | /     \ |
    //(3)-------(4)
    //      9     */
    //int graph[ NUM_PRIM_VERTS ][ NUM_PRIM_VERTS ] = 
    //{ { 0, 2, 0, 6, 0 },
    //  { 2, 0, 3, 8, 5 },
    //  { 0, 3, 0, 0, 7 },
    //  { 6, 8, 0, 0, 9 },
    //  { 0, 5, 7, 9, 0 } };
    //
    //// Print the solution 
    //primMST( graph );

    // Test input: https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
    // Dijkstra's shortest path
    /* Let us create the example graph discussed above */
    int graph[ DSTRA_VERTS ][ DSTRA_VERTS ] = 
                    {   { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
    
    dijkstra( graph, 0 );

    return 0;
}