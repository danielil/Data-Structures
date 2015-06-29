/**
 * @author Daniel Sebastian Iliescu
 */

#pragma once

#include "tbst_node_data.hpp"

// Node link types
const bool THREAD = false;  // Thread link
const bool CHILD = true;    // Child link 

/**
 * Node
 *
 * Struct implementing the node of the Threaded Binary Search Tree.
 */
struct Node
{
    Node();
    Node(const Node& source);
    Node(const std::string& token);

    // Operators
    bool operator==(const Node& target) const;
    bool operator!=(const Node& target) const;

    // Display/Log methods
    void show(std::ostream& output, bool details) const;

    // Node data
    int id;                     // Node ID (indicating insertion order)
    int depth;                  // Node depth
    nodeData data;              // Node data
    struct Node* parentNode;    // Parent node (used only for debugging)
    struct Node* leftNode;      // Left child/thread
    struct Node* rightNode;     // Right child/thread
    bool leftNodeType;          // Left node type: Thread vs. Child
    bool rightNodeType;         // Right node type: Thread vs. Child
};
