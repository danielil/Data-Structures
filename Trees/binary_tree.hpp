/**
 * @author Daniel Sebastian Iliescu
 *
 * This file contains the methods for BinTree class that implements a
 * Search Binary Tree.
 */

#pragma once
#include <iostream>

#include "node_data.hpp"

//---------------------------------------------------------------------------
// BinTree class: implementation of a Binary Search Tree (BST) holding data
// packaged as NodeData objects.
// Features:
//  --  allows insertion of retrieval of data
//  --  exposes properties such as tree size, tree height and depth
//  --  allows for assignment/copy of other trees
//  --  allows pre-order, in-order and post-order traversal
//---------------------------------------------------------------------------
class BinTree
{
public: 
    BinTree();                      // constructor 
    BinTree(const BinTree &source); // copy constructor 
    ~BinTree();                     // destructor 

    // Accessors
    bool isEmpty() const;
    int getTreeSize() const;
    int getTreeHeight() const;
    int getDepth(const NodeData &targetData) const;
    void makeEmpty();

    // Operators
    BinTree& operator=(const BinTree &source); 
    bool operator==(const BinTree &other) const; 
    bool operator!=(const BinTree &other) const; 

    // Oputput operator
    friend std::ostream& operator<<(std::ostream& os, const BinTree& obj);

    // Tree operations
    bool insert(NodeData* data);
    bool retrieve(const NodeData &refData, NodeData* &data) const;

    // Recursive tree traversal
    NodeData** preorderTraverse() const;
    NodeData** inorderTraverse() const;
    NodeData** postorderTraverse() const;

    // Tree-Array conversions
    void bstreeToArray(NodeData* nodesData[]);
    void arrayToBSTree(NodeData* nodesData[]);

    // Display operations
    void displaySideways() const;
    void displayTree() const;

private: 
    struct Node
    { 
        NodeData* data;             // pointer to data object 
        Node* left;                 // left subtree pointer 
        Node* right;                // right subtree pointer 
    }; 

    // Helper methods 
    NodeData** createDataArray() const;
    Node* createNode(NodeData* data) const;
    void destroyNode(Node* node);
    int getBranchSize(Node* node) const;
    int getBranchHeight(Node* node) const;
    void copyNode(Node** dst, const Node* source);
    bool areEqual(Node* node1, Node* node2) const;
    int findNode(Node* rootNode, const NodeData &targetData, Node**) const;
    bool insertHelper(Node* current, NodeData* data);
    void insertBalanced(NodeData** data, int low, int high);
    void preorderHelper(
        Node* node, NodeData** nodesData, int &index, bool removeData) const;
    void inorderHelper(
        Node* node, NodeData** nodesData, int &index, bool removeData) const;
    void postorderHelper(
        Node* node, NodeData** nodesData, int &index, bool removeData) const;
    void traverseHelper(
        int traverseType,
        Node* node,
        NodeData** nodesData,
        int &index,
        bool removeData) const;
    void sideways(Node* current, int level) const; 

    // Data members
    Node* root;                     // root of the tree 
};
