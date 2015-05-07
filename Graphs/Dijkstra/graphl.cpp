/**
 * @author Daniel Sebastian Iliescu
 * @file graphl.cpp

 * This file contains the methods for GraphL class implementing a Graph
 * with support for Depth-First Search (DFS) traversal.
 */

#include <algorithm>
#include <limits>
#include "graphl.h"

using namespace std;

// Graph display layout definitions (0-based, i.e. first column is 0).
const int DATA_INDENT = 15;     // indentation of node data
const int EDGE_INDENT = 2;      // indentation of edge info

// ---------------------------------------------------------------------------
// Default constructor for class GraphL
GraphL::GraphL()
{
    initGraph();
}

// ---------------------------------------------------------------------------
// Destructor for class GraphL
GraphL::~GraphL()
{
    makeEmpty();
}

// ---------------------------------------------------------------------------
// isEmpty
// Checks whether the Graph is empty and returns true if it is.
bool GraphL::isEmpty() const
{
    return (size == 0);
}

// ---------------------------------------------------------------------------
// getSize
// Returns the number of vertices in the Graph.
int GraphL::getSize() const
{
    return size;
}

// ---------------------------------------------------------------------------
// makeEmpty
// Clears the Graph data.
void GraphL::makeEmpty()
{
    for (int i = 0; i < size; i++)
    {
        EdgeNode* edge = node[i].edgeHead;
        while (edge != NULL)
        {
            EdgeNode* temp = edge->nextEdge;
            delete edge;
            edge = temp;
        }
        node[i].edgeHead = NULL;
    }
    size = 0;
    dfsSize = 0;
}

//---------------------------------------------------------------------------
// insertEdge
// Sets an edge (i.e. sets the link connecting two vertices within the Graph).
// Returns true if data is valid and the edge is set.
// Note: the public interface assumes a 1-based indexing of nodes while
// the internal implementation uses a 0-based indexing scheme.
bool GraphL::insertEdge(int fromNode, int toNode)
{
    if ((fromNode >= 1) && (fromNode <= size) &&
        (toNode >= 1) && (toNode <= size) &&
        (toNode != fromNode))
    {
        int start = fromNode - 1;
        int end = toNode - 1;
        EdgeNode* current = node[start].edgeHead;
        EdgeNode* prev = NULL;

        // Locate the insertion point and check for duplicates
        while (current != NULL)
        {
            if (current->adjGraphNode == end)
            {
                // edge already exists
                return false;
            }
            else if (current->adjGraphNode > end)
            {
                // found insertion point
                break;
            }
            prev = current;
            current = current->nextEdge;
        }

        EdgeNode* edge = new EdgeNode;
        edge->adjGraphNode = end;
        edge->nextEdge = current;

        if (prev == NULL)
        {
            node[start].edgeHead = edge;
        }
        else
        {
            prev->nextEdge = edge;
        }
        return true;
    }

    return false;
}

//---------------------------------------------------------------------------
// removeEdge
// Resets an edge (i.e. removes the link connecting two vertices within the
// Graph). Returns true if data is valid and the edge is reset.
// Note: the public interface assumes a 1-based indexing of nodes while
// the internal implementation uses a 0-based indexing scheme.
bool GraphL::removeEdge(int fromNode, int toNode)
{
    if ((fromNode >= 1) && (fromNode <= size) &&
        (toNode >= 1) && (toNode <= size) &&
        (toNode != fromNode))
    {
        int start = fromNode - 1;
        int end = toNode - 1;
        EdgeNode* current = node[start].edgeHead;
        EdgeNode* prev = NULL;

        // Locate the insertion point and check for duplicates
        while (current != NULL)
        {
            if (current->adjGraphNode == end)
            {
                // edge to remove was found
                if (prev == NULL)
                {
                    node[start].edgeHead = current->nextEdge;
                }
                else
                {
                    prev->nextEdge = current->nextEdge;
                }
                delete current;
                return true;
            }
            else if (current->adjGraphNode > end)
            {
                // Since edges are ordered, we don't search beyond this point
                break;
            }
            prev = current;
            current = current->nextEdge;
        }
    }
    return false;
}

//---------------------------------------------------------------------------
// buildGraph
// Populates the Graph with data from an input stream.
// Stream data is assumed to be organized as follows:
//      First line has an integer telling the number of nodes, say n.
//      Following is a text description of each of the 1 through n nodes.
//      After that, each line consists of 2 integer representing an edge.
//          {fromNode toNode}
//      A zero for any of the integers signifies the end of the data for
//      that one graph.
// A graph has at most 100 nodes.
void GraphL::buildGraph(istream& infile)
{
    int noNodes = 0;            // number of nodes
    bool done = false;          // whether data read is complete
    string error;               // error info (if any)

    makeEmpty();                // clear the graph of memory

    while (!done && infile.good())
    {
        if (noNodes == 0)
        {
            infile >> noNodes;  // read the number of nodes
            if (!infile.eof())
            {
                string s;       // used to read through to end of line
                getline(infile, s);
            }
        }
        else if ((noNodes < 0) || (noNodes > MAXNODES))
        {
            // invalid number of nodes: bail out
            error = "Invalid number of nodes!";
            done = true;
        }
        else if (size < noNodes)
        {
            // read graph node information
            if (node[size].data.setData(infile))
            {
                size++;
            }
            else
            {
                // error
                error = "Invalid node data!";
                done = true;
            }
        }
        else
        {
            int fromNode = 0, toNode = 0;

            // read the edge data and add to the adjacency list
            infile >> fromNode;
            infile >> toNode;
            if ((fromNode == 0) || (toNode == 0))
            {
                // end of edge data
                done = true;
            }
            else if (!insertEdge(fromNode, toNode))
            {
                // error
                error = "Invalid edge data!";
                done = true;
            }
            else
            {
                if (!infile.eof())
                {
                    string s;       // used to read through to end of line
                    getline(infile, s);
                }
            }
        }
    }

    if (!error.empty())
    {
        // Error exit
        cerr << error << endl;
        makeEmpty();                    // reset data (as it is invalid)
        infile.seekg(0, infile.end);    // move input stream to the end
    }
}

//---------------------------------------------------------------------------
// depthFirstSearch
// Rebuilds the Depth-First Search path
void GraphL::depthFirstSearch()
{
    if (size > 0)
    {
        clearDFS();     // clear previous data
        dfs(0);         // perform DFS

        //  Display result
        cout << "Depth - first ordering:";
        if (dfsSize != size)
        {
            cout << " search failed!";
        }
        else
        {
            for (int i = 0; i < dfsSize; i++)
            {
                cout << " " << (dfsPath[i] + 1);
            }
        }
        cout << endl;
        cout << endl;
    }
}

//---------------------------------------------------------------------------
// displayGraph
// Displays the Graph info including the data for nodes and edges.
// The display layout is as follows:
//
//  1_3_______16
//  Node #    data
//    edge from to
//
void GraphL::displayGraph() const
{
    cout << endl;
    cout << "Graph:" << endl;
    for (int i = 0; i < size; i++)
    {
        string info = "Node ";
        addIntToString(info, i + 1);
        padString(info, DATA_INDENT);
        cout << info;
        cout << node[i].data << endl;

        EdgeNode* edge = node[i].edgeHead;
        while (edge != NULL)
        {
            for (int col = 0; col < EDGE_INDENT; col++)
            {
                cout << " ";
            }
            cout << "edge " << (i + 1);
            cout << " " << (edge->adjGraphNode + 1);
            cout << endl;
            edge = edge->nextEdge;
        }
    }
    cout << endl;
}

// ---------------------------------------------------------------------------
// initGraph
// Helper method for initializing Graph data within constructors
void GraphL::initGraph()
{
    size = 0;
    dfsSize = 0;
    for (int i = 0; i < MAXNODES; i++)
    {
        node[i].edgeHead = NULL;
        node[i].visited = false;
        dfsPath[i] = -1;
    }
}

//---------------------------------------------------------------------------
// clearDFS
// Helper method used to clear the Depth-First Search data
void GraphL::clearDFS()
{
    for (int i = 0; i < size; i++)
    {
        node[i].visited = false;
        dfsPath[i] = -1;
    }
    dfsSize = 0;
}

//---------------------------------------------------------------------------
// clearDFS
// Helper method implementing Depth-First Search starting from a given node
void  GraphL::dfs(int fromNode)
{
    if ((fromNode >= 0) && (fromNode < size) && !node[fromNode].visited)
    {
        EdgeNode* edge = node[fromNode].edgeHead;

        dfsPath[dfsSize++] = fromNode;
        node[fromNode].visited = true;
        while (edge != NULL)
        {
            dfs(edge->adjGraphNode);
            edge = edge->nextEdge;
        }
    }
}

//---------------------------------------------------------------------------
// addIntToString
// Helper method for converting an integer into a string and appending it to
// a reference string.
void GraphL::addIntToString(string &info, int value)
{
    stringstream ss;
    ss << value;
    info += ss.str();
}

//---------------------------------------------------------------------------
// padString
// Helper method for padding as string with spaces until it reaches a
// required length.
void GraphL::padString(string& info, int length)
{
    if (length > 0)
    {
        stringstream ss;

        for (int i = length - info.length(); i > 0; i--)
        {
            ss << " ";
        }
        info += ss.str();
    }
}
