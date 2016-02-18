/**
 * @author Daniel Sebastian Iliescu

 * This file contains the methods for GraphM class implementing a Graph
 * with support for Dijkstra's shortest path algorithm.
 */

#include "graphm.hpp"

#include <limits.h>
#include <sstream>
#include <iostream>

namespace dsa
{
    // Path cost range
    const int MIN_COST_PATH = 0;
    const int MAX_COST_PATH = INT_MAX;

    // Graph display layout definitions (0-based, i.e. first column is 0).
    const int DESCRIPTION_LENGTH = 21;  // length of node data (padded)
    const int FROM_NODE_INDENT = 4;     // indentation of "From Node" data
    const int TO_NODE_INDENT = 13;      // indentation of "To Node" data
    const int DISTANCE_INDENT = 20;     // indentation of "Dijkstra's Distance"
    const int PATH_INDENT = 32;         // indentation of "Path" data

    // ---------------------------------------------------------------------------
    // Default constructor for class GraphM
    GraphM::GraphM()
    {
        initGraph();
    }

    // ---------------------------------------------------------------------------
    // Destructor for class GraphM
    GraphM::~GraphM()
    {
    }

    // ---------------------------------------------------------------------------
    // isEmpty
    // Checks whether the Graph is empty and returns true if it is.
    bool GraphM::isEmpty() const
    {
        return (size == 0);
    }

    // ---------------------------------------------------------------------------
    // getSize
    // Returns the number of vertices in the Graph.
    int GraphM::getSize() const
    {
        return size;
    }

    // ---------------------------------------------------------------------------
    // makeEmpty
    // Clears the Graph data.
    void GraphM::makeEmpty()
    {
        for (int fromNode = 0; fromNode < size; fromNode++)
        {
            for (int toNode = 0; toNode < size; toNode++)
            {
                C[fromNode][toNode] =
                    (toNode == fromNode) ? MIN_COST_PATH : MAX_COST_PATH;
            }
        }
        clearShortestPath();
        size = 0;
    }

    //---------------------------------------------------------------------------
    // insertEdge
    // Sets an edge (i.e. sets the value of the link connecting two vertices
    // within the Graph). Returns true if data is valid and the edge is modified.
    // Note: the public interface assumes a 1-based indexing of nodes while
    // the internal implementation uses a 0-based indexing scheme.
    bool GraphM::insertEdge(int fromNode, int toNode, int label)
    {
        if ((fromNode >= 1) && (fromNode <= size) &&
            (toNode >= 1) && (toNode <= size) &&
            (toNode != fromNode) &&
            (label >= MIN_COST_PATH) && (label <= MAX_COST_PATH))
        {
            if (C[fromNode - 1][toNode - 1] != label)
            {
                C[fromNode - 1][toNode - 1] = label;
                shortestPath = false;
                return true;
            }
        }
        return false;
    }

    //---------------------------------------------------------------------------
    // removeEdge
    // Resets an edge (i.e. removes the link connecting two vertices within the
    // Graph). Returns true if data is valid and the edge is reset.
    // Note: the public interface assumes a 1-based indexing of nodes while
    // the internal implementation uses a 0-based indexing scheme.
    bool GraphM::removeEdge(int fromNode, int toNode)
    {
        if ((fromNode >= 1) && (fromNode <= size) &&
            (toNode >= 1) && (toNode <= size) &&
            (toNode != fromNode))
        {
            if (C[fromNode - 1][toNode - 1] != MAX_COST_PATH)
            {
                C[fromNode - 1][toNode - 1] = MAX_COST_PATH;
                shortestPath = false;
                return true;
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
    //      After that, each line consists of 3 integers representing an edge.
    //          {fromNode toNode label}
    //      A zero for any of the node index integers signifies the end of the
    //      data for that one graph.
    // A graph has at most 100 nodes.
    void GraphM::buildGraph( std::istream& infile)
    {
        int noNodes = 0;            // number of nodes
        bool done = false;          // whether data read is complete
        std::string error;               // error info (if any)

        makeEmpty();                // clear the graph of memory

        while (!done && infile.good())
        {
            if (noNodes == 0)
            {
                infile >> noNodes;  // read the number of nodes
                if (!infile.eof())
                {
                    std::string s;       // used to read through to end of line
                    std::getline(infile, s);
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
                if (data[size].setData(infile))
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
                int fromNode = 0, toNode = 0, label = 0;

                // read the edge data and add to the adjacency list
                infile >> fromNode;
                infile >> toNode;
                infile >> label;
                if ((fromNode == 0) || (toNode == 0))
                {
                    // end of edge data
                    done = true;
                }
                else if (!insertEdge(fromNode, toNode, label))
                {
                    // error
                    error = "Invalid edge data!";
                    done = true;
                }
                else
                {
                    if (!infile.eof())
                    {
                        std::string s;       // used to read through to end of line
                        std::getline(infile, s);
                    }
                }
            }
        }
        if (!error.empty())
        {
            std::cerr << error << std::endl;
            makeEmpty();                    // reset data (as it is invalid)
            infile.seekg(0, infile.end);    // move input stream to the end
        }
    }

    //---------------------------------------------------------------------------
    // findShortestPath
    // Calculates the shortest path between any two vertices within the Graph
    // by implementing Dijkstra's shortest path algorithm. 
    void GraphM::findShortestPath()
    {
        clearShortestPath();        // Clear previous data (if any)

        // For each node in the graph, assess shortest path to all other vertices
        for (int fromNode = 0; fromNode < size; fromNode++)
        {
            // As all paths are un-optimized, we visit the other nodes one by one
            // and we mark them as "visited". The nodes are visited in increasing
            // order of their distance to current node (i.e. "fromNode").
            for (int pass = size - 1; pass >= 0; pass--)
            {
                // Find vertex within the smallest distance from current node
                int toNode = findNode(fromNode);

                if ((toNode < 0) || (T[fromNode][toNode].dist >= MAX_COST_PATH))
                {
                    // All remaining vertices are inaccessible from current node
                    break;
                }

                T[fromNode][toNode].visited = true;

                // If we found one path, then record the fact that we have at least
                // one path available
                shortestPath = true;

                // Assess short path from current node (i.e. "fromNode") to all
                // (yet to be visited) neighbors of closest node (i.e. "toNode").
                for (int nextNode = 0; nextNode < size; nextNode++)
                {
                    // Iterate over all neighbors of "toNode" yet to be visited
                    if ((nextNode != fromNode) &&
                        (nextNode != toNode) &&
                        !T[fromNode][nextNode].visited &&
                        (C[toNode][nextNode] < MAX_COST_PATH))
                    {
                        int dist = T[fromNode][toNode].dist + C[toNode][nextNode];
                        if (dist < T[fromNode][nextNode].dist)
                        {
                            // Update max. distance and record path
                            int path = T[fromNode][nextNode].path;

                            T[fromNode][nextNode].dist = dist;
                            T[fromNode][nextNode].path =
                                (path >= 0) ? path : toNode;
                        }
                    }
                }
            }
        }
    }

    //---------------------------------------------------------------------------
    // display
    // Displays the shortest path between two vertices within the Graph.
    // It assumes that findShortestPath was previously called and the Graph was
    // not subsequently modified.
    //
    // The display layout is as follows:
    //  1__5_____14____21__________33___
    //     From  To    Distance    Shortest Path
    //  Data 1
    //  Data 2
    //
    // Note: the public interface assumes a 1-based indexing of nodes while
    // the internal implementation uses a 0-based indexing scheme.
    void GraphM::display(int fromNode, int toNode) const
    {
        if ((fromNode >= 1) && (fromNode <= size) &&
            (toNode >= 1) && (toNode <= size) &&
            (toNode != fromNode))
        {
            int start = fromNode - 1;
            int end = toNode - 1;

            displayPathDistance(start, end);
            std::cout << std::endl;
            if (T[start][end].dist < MAX_COST_PATH)
            {
                int current = T[start][end].path;

                std::cout << data[start] << std::endl;
                while (current >= 0)
                {
                    std::cout << data[current] << std::endl;
                    current = T[current][end].path;
                }
                std::cout << data[end] << std::endl;
            }
        }
    }

    //---------------------------------------------------------------------------
    // displayAll
    // Displays the shortest path between all the vertices within the Graph.
    // It assumes that findShortestPath was previously called and the Graph was
    // not modified afterwards.
    //
    // The display layout is as follows:
    //
    //  1________________22_________33_______42__________54___
    //  Description      From node  To node  Dijkstra's  Path
    //
    //  1___________________25________35_____42__________54___
    //  Data                From      To     Distance    Shortest
    //                      Index     Index  (min. cost) Path
    //
    void GraphM::displayAll() const
    {
        std::string info;

        // Display header
        std::cout << std::endl;
        info += "Description";
        padString(info, DESCRIPTION_LENGTH);
        info += "From node  To Node  Dijkstra's  Path";
        std::cout << info << std::endl;

        // Display graph data
        for (int fromNode = 0; fromNode < size; fromNode++)
        {
            std::cout << data[fromNode] << std::endl;

            for (int toNode = 0; toNode < size; toNode++)
            {
                if (toNode != fromNode)
                {
                    for (int i = 0; i < DESCRIPTION_LENGTH; i++)
                    {
                        // pad beginning of the line
                        std::cout << " ";
                    }
                    displayPathDistance(fromNode, toNode);
                    std::cout << std::endl;
                }
            }
        }
        std::cout << std::endl;
    }

    // ---------------------------------------------------------------------------
    // initGraph
    // Helper method for initializing Graph data within constructors
    void GraphM::initGraph()
    {
        size = MAXNODES;
        makeEmpty();
    }

    //---------------------------------------------------------------------------
    // clearShortestPath
    // Helper method used to clear the shortest path data computed by
    // findShortestPath method.
    void GraphM::clearShortestPath()
    {
        shortestPath = false;
        for (int fromNode = 0; fromNode < size; fromNode++)
        {
            for (int toNode = 0; toNode < size; toNode++)
            {
                // If "fromNode == "toNode", then we flag the edge as "visited"
                T[fromNode][toNode].visited = (toNode == fromNode);
                T[fromNode][toNode].dist = C[fromNode][toNode];
                T[fromNode][toNode].path = -1;
            }
        }
    }

    //---------------------------------------------------------------------------
    // findNode
    // Helper method that locates and returns the node within the shortest
    // distance from a reference node and not marked as "visited".
    int GraphM::findNode(int fromNode) const
    {
        int nextNode = -1;

        if ((fromNode >= 0) && (fromNode < size))
        {
            for (int toNode = 0; toNode < size; toNode++)
            {
                if ((toNode != fromNode) && !T[fromNode][toNode].visited)
                {
                    if ((nextNode < 0) ||
                        (T[fromNode][toNode].dist < T[fromNode][nextNode].dist))
                    {
                        nextNode = toNode;
                    }
                }
            }
        }

        return nextNode;
    }

    //---------------------------------------------------------------------------
    // displayPath
    // Helper method for displaying the shortest path between two vertices
    // within the Graph.
    // Note: As a private method it assumes that the arguments are 0-based (as
    // used by the internal indexing scheme).
    void GraphM::displayPath(int fromNode, int toNode) const
    {
        if ((fromNode >= 0) && (fromNode < size) &&
            (toNode >= 0) && (toNode < size) &&
            (toNode != fromNode) && shortestPath &&
            (T[fromNode][toNode].dist < MAX_COST_PATH))
        {
            std::cout << (fromNode + 1) << " ";
            if (T[fromNode][toNode].path >= 0)
            {
                displayPath(T[fromNode][toNode].path, toNode);
            }
            else
            {
                std::cout << (toNode + 1);
            }
        }
    }

    //---------------------------------------------------------------------------
    // displayPath
    // Helper method for displaying the shortest path between two vertices
    // within the Graph including distance information.
    //
    // The display layout is as follows:
    //  __5_____14____21__________33___________
    //    From  To    Distance    Shortest Path
    //
    // Note: As a private method it assumes that the arguments are 0-based (as
    // used by the internal indexing scheme).
    void GraphM::displayPathDistance(int fromNode, int toNode) const
    {
        if ((fromNode >= 0) && (fromNode < size) &&
            (toNode >= 0) && (toNode < size) &&
            (toNode != fromNode))
        {
            std::string info;

            padString(info, FROM_NODE_INDENT);
            addIntToString(info, fromNode + 1);
            padString(info, TO_NODE_INDENT);
            addIntToString(info, toNode + 1);
            padString(info, DISTANCE_INDENT);
            if (shortestPath && (T[fromNode][toNode].dist < MAX_COST_PATH))
            {
                addIntToString(info, T[fromNode][toNode].dist);
                padString(info, PATH_INDENT);
                std::cout << info;
                displayPath(fromNode, toNode);
            }
            else
            {
                std::cout << info << "---";
            }
        }
    }

    //---------------------------------------------------------------------------
    // addIntToString
    // Helper method for converting an integer into a string and appending it to
    // a reference string.
    void GraphM::addIntToString( std::string &info, int value)
    {
        std::stringstream ss;
        ss << value;
        info += ss.str();
    }

    //---------------------------------------------------------------------------
    // padString
    // Helper method for padding as string with spaces until it reaches a
    // required length.
    void GraphM::padString( std::string& info, int length)
    {
        if (length > 0)
        {
            std::stringstream ss;

            for (int i = length - info.length(); i > 0; i--)
            {
                ss << " ";
            }
            info += ss.str();
        }
    }
}
