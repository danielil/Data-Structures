/**
 * @author Daniel Sebastian Iliescu
 * @file tbst.h
 */

#pragma once

#include "node.h"

// Tree traversal types
const int ITERATIVE     = 0;    // Iterative in-order
const int PREORDER      = 1;    // Recursive pre-order
const int INORDER       = 2;    // Recursive in-order
const int POSTORDER     = 3;    // Recursive post-order

// Display constants
const int NODES_PER_LINE = 7;   // nodes per line
const int NODES_DISPLAYED = 21; // nodes to be displayed in a group

// Forward declaration of classes
class ThreadedBinarySearchTree;
class TreeIterator;

/**
 * ThreadedBinarySearchTree
 *
 * Class implementing a Threaded Binary Search Tree (TBST).
 */
class ThreadedBinarySearchTree
{
public:
    ThreadedBinarySearchTree();
    ThreadedBinarySearchTree(const ThreadedBinarySearchTree& source);
    ~ThreadedBinarySearchTree();

    // Properties
    bool isEmpty() const;
    bool isVine() const;
    int getNodesCount() const;
    int getHeigth() const;

    // Operations
    void clear();
    void balance();
    void treeToVine();
    void vineToTree();

    Node* find(const std::string& token) const;
    bool insert(const std::string& token);
    bool insert(const Node& node);
    bool remove(const std::string& token);

    // Iterator operations
    Node* getFirst() const;
    Node* getLast() const;
    Node* getNext(Node* current) const;
    Node* getPrevious(Node* current) const;
    TreeIterator begin();
    TreeIterator rbegin();
    TreeIterator end();
    TreeIterator rend();

    // Non-recursive traversal
    Node** inorderIterativeTraverse() const;

    // Recursive traversal
    Node** preorderTraverse() const;
    Node** inorderTraverse() const;
    Node** postorderTraverse() const;

    // Operators
    friend std::istream& operator>>(
        std::istream& is,
        ThreadedBinarySearchTree& tbst);

    // Display/Log methods
    void show(std::ostream& output, bool details) const;
    void show(std::ostream& output, Node** nodesList, bool details) const;
    void showPartial(std::ostream& output, Node** nodesList, bool top) const;

    // Traversal helpers
    Node** createNodesList() const;

private:
    // Helper methods
    void init(Node* node);
    bool insertHelper(Node* newNode);
    void compress(int nonThreadCount, int threadCount);
    static void destroy(Node* node);
    static void traverseHelper(
        int traverseType,
        Node* node,
        Node** nodesList,
        int& currentPosition);
    static void show(
        std::ostream& output, Node** nodesList, int first, int last);

    // Tree data
    Node* rootNode;         // root node
    int treeSize;           // total number of nodes
    int treeHeight;         // tree height (i.e. number of layers)
};

/**
 * TreeIterator
 *
 * Class implementing an iterator for the Threaded Binary Search Tree (TBST).
 */
class TreeIterator
{
public:
    TreeIterator(ThreadedBinarySearchTree* tbst);
    TreeIterator(const TreeIterator& treeIter);

    // Operators
    Node*& operator*();
    TreeIterator& operator++();     // prefix
    TreeIterator& operator--(); 
    TreeIterator operator++(int);   // postfix
    TreeIterator operator--(int);
    bool operator==(const TreeIterator& treeIter);
    bool operator!=(const TreeIterator& treeIter);

private:
    friend class ThreadedBinarySearchTree;

    ThreadedBinarySearchTree* tbsTree;
    Node* currentNode;
};
