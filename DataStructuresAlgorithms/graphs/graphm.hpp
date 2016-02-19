/**
 * @author Daniel Sebastian Iliescu
 */

#pragma once

#include "node_data.hpp"

namespace dsa
{
    //---------------------------------------------------------------------------
    // GraphM class: implementation of a Graph holding nodes with data packaged
    // as NodeData objects and having directional edges with integer weights. 
    // Features:
    //  --  allows building the Graph with a stream of data
    //  --  allows insertion and removal of edges
    //  --  allows computing and displaying of Dijkstra's shortest path
    // Note: the public interface assumes a 1-based indexing of nodes while
    // the internal implementation uses a 0-based indexing scheme.
    //---------------------------------------------------------------------------
    class GraphM
    {
    public:
        GraphM();                           // constructor  
        ~GraphM();                          // destructor 

        // Accessors
        bool isEmpty() const;
        int getSize() const;

        // Graph operations
        void makeEmpty();
        bool insertEdge(int fromNode, int toNode, int label);
        bool removeEdge(int fromNode, int toNode);
        void buildGraph( std::istream& infile);
        void findShortestPath();

        // Display operations
        void display(int fromNode, int toNode) const;
        void displayAll() const;

    private:
        // Helper methods
        void initGraph();
        void clearShortestPath();
        int findNode(int fromNode) const;
        void displayPath(int fromNode, int toNode) const;
        void displayPathDistance(int fromNode, int toNode) const;

        // Display helpers
        static void addIntToString( std::string &info, int value);
        static void padString( std::string &info, int length);

        struct TableType
        {
            bool visited;   // whether node has been visited 
            int dist;       // currently known shortest distance from source 
            int path;       // previous node in path of min dist 
        };

        // Data members
        static const int MAXNODES = 100;    // max. number of graph nodes
        NodeData data[MAXNODES];            // data for graph nodes information 
        int C[MAXNODES][MAXNODES];          // Cost array, the adjacency matrix 
        int size;                           // number of nodes in the graph 
        TableType T[MAXNODES][MAXNODES];    // stores visited, distance, path
        bool shortestPath;                  // whether shortest path was computed
    };
}
