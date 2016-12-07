/**
 * @author Daniel Sebastian Iliescu
 */

#pragma once

#include "node_data.hpp"

namespace dsa
{
    //---------------------------------------------------------------------------
    // EdgeNode: ordered link list of edge information for Graph nodes
    // An edge is a directed connection between to nodes in the Graph.
    struct EdgeNode
    {
        int adjGraphNode;               // index of the adjacent graph node
        EdgeNode* nextEdge;             // link to next ajacent node (if any)
    };

    //---------------------------------------------------------------------------
    // GraphNode: wrapper for the data of a Graph node (i.e. a vertice)
    struct GraphNode
    {
        NodeData data;                  // graph node information
        EdgeNode* edgeHead;             // head of the linked list of edges
        bool visited;                   // flag to mark a "visited" node
    };

    //---------------------------------------------------------------------------
    // GraphL class: implementation of a Graph holding nodes with data packaged
    // as NodeData objects and having directional edges. 
    // Features:
    //  --  allows building the Graph with a stream of data
    //  --  allows displaying the Graph info (including nodes data and edges)
    //  --  allows performing the depth-first traversal of the Graph
    // Note: the public interface assumes a 1-based indexing of nodes while
    // the internal implementation uses a 0-based indexing scheme.
    //---------------------------------------------------------------------------
    class GraphL
    {
    public:
        GraphL();                           // constructor
        ~GraphL();                          // destructor 

        // Accessors
        bool isEmpty() const;
        int getSize() const;

        // Graph operations
        void makeEmpty();
        bool insertEdge(int fromNode, int toNode);
        bool removeEdge(int fromNode, int toNode);
        void buildGraph( std::istream& infile);
        void depthFirstSearch();

        // Display operations
        void displayGraph() const;

    private:
        // Helper methods
        void initGraph();
        void clearDFS();
        void dfs(int fromNode);

        // Display helpers
        static void addIntToString( std::string &info, int value);
        static void padString( std::string &info, int length);

        // Data members
        static const int MAXNODES = 100;    // max. number of graph nodes
        GraphNode node[MAXNODES];           // Graph nodes
        int dfsPath[MAXNODES];              // Depth-First Search path
        int size;                           // number of nodes in the graph
        int dfsSize;                        // size of DFS path 
    };
}
