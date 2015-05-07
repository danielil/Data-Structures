/**
 * @author Daniel Sebastian Iliescu
 * @file tbst.cpp
 *
 * This file contains the methods associated with the following classes:
 *      ThreadedBinarySearchTree    : class implementing the actual TBST
 *      TreeIterator                : class implementing the TBST iterator
 */

#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>

#include "dataSorter.h"
#include "tbst.h"

// Minimum number of nodes required for compressing the tree
const int COMPRESSION_MIN_NODES = 3;

using namespace std;

// Function prototypes
static bool isTokenChar(char ch);

/**
 * ThreadedBinarySearchTree()
 *
 * Default constructor
 */
ThreadedBinarySearchTree::ThreadedBinarySearchTree()
    : rootNode(NULL),
      treeSize(0),
      treeHeight(0)
{
}

/**
 * ThreadedBinarySearchTree(const ThreadedBinarySearchTree& source)
 *
 * Copy constructor
 * @param source TBST to copy
 */
ThreadedBinarySearchTree::ThreadedBinarySearchTree(
    const ThreadedBinarySearchTree& source)
    : rootNode(NULL),
      treeSize(0),
      treeHeight(0)
{
    Node** nodesList = source.preorderTraverse();

    if (nodesList != NULL)
    {
        // We sort the node by ID to ensure that we insert data in the
        // same order as in the source tree
        DataSorter::quickSort(BY_ID, nodesList, source.getNodesCount());

        for (int i = 0; i < source.getNodesCount(); i++)
        {
            const Node* source = nodesList[i];
            insert(*source);
        }
    }

    delete [] nodesList;
}


/**
 * ThreadedBinarySearchTree()
 *
 * Destructor
 */
ThreadedBinarySearchTree::~ThreadedBinarySearchTree()
{
    destroy(rootNode);
}

/**
 * isEmpty() const
 *
 * Method checking whether the tree is empty or not.
 *
 * @pre None
 * @post Checks whether tree has any node
 * @return True if tree is empty; false otherwise
 */
bool ThreadedBinarySearchTree::isEmpty() const
{
    return treeSize == 0;
}

/**
 * isVine() const
 *
 * Method checking whether the tree was transformed into a Vine.
 * Vine is a degenerate binary tree resembling a linked list, in which
 * each node has at most one child.
 *
 * @pre None
 * @post Checks whether tree has any node
 * @return True if tree is empty; false otherwise
 */
bool ThreadedBinarySearchTree::isVine() const
{
    return (treeSize > 0) && (treeSize == treeHeight);
}

/**
 * getNodesCount() const
 *
 * Method retrieving the tree size (in number of nodes).
 *
 * @pre None
 * @post Returns the current tree size
 * @return tree size
 */
int ThreadedBinarySearchTree::getNodesCount() const
{
    return treeSize;
}

/**
 * getHeigth() const
 *
 * Method retrieving the tree height.
 *
 * @pre None
 * @post Returns the current tree height
 * @return tree height
 */
int ThreadedBinarySearchTree::getHeigth() const
{
    return treeHeight;
}

/**
 * clear()
 *
 * Method destroying all the nodes in the tree and initializing its properties
 *
 * @pre None
 * @post Tree is left empty
 */
void ThreadedBinarySearchTree::clear()
{
    destroy(rootNode);
    rootNode = NULL;
    treeSize = 0;
    treeHeight = 0;
}

/**
 * balance()
 *
 * Method for balancing the tree in two steps:
 * 1. Tree is transformed into a vine (i.e. a linear structure resembling a
 * linked list) by use of rotations. 
 * 2. Vine is transformed back into a balanced tree.
 *
 * @pre Tree is not empty
 * @post Tree is balanced
 */
void ThreadedBinarySearchTree::balance()
{
    treeToVine();
    vineToTree();
}

/**
 * treeToVine()
 *
 * Method for transforming the tree into a vine by use of rotations.
 * Vine is a degenerate binary tree resembling a linked list, in which
 * each node has at most one child.
 *
 * @pre Tree is not empty
 * @post Tree is transformed into a Vine
 */
void ThreadedBinarySearchTree::treeToVine()
{
    if (!isEmpty())
    {
        Node* current = getFirst();
		bool run = (current != NULL);

        while (run)
        {
            Node* next = getNext(current);

            current->rightNodeType = THREAD;
            current->rightNode = next;

            if (next == NULL)
            {
				run = false;
            }
			else
			{
				next->leftNodeType = CHILD;
				next->leftNode = current;
				current = next;
			}
        }

        rootNode = current;

        // Reset the nodes depths and parents
        init(NULL);
    }
}

/**
 * vineToTree()
 *
 * Method for transforming a vine into a balanced tree.
 * Vine is a degenerate binary tree resembling a linked list, in which
 * each node has at most one child.
 * The transformation is based on the algorithm defined here:
 * http://adtinfo.org/libavl.html/Transforming-a-Vine-into-a-Balanced-TBST.html
 *
 * @pre Tree was previously transformed into a Vine
 * @post Vine is transformed into a Tree
 */
void ThreadedBinarySearchTree::vineToTree()
{
    if (isVine())
    {
        int leaves = treeSize + 1;  // Nodes in incomplete bottom level (if any)
        int vine = 0;               // nodes in main vine
		bool run = true;

        while (run)
        {
            int next = leaves & (leaves - 1);
            if (next == 0)
            {
				run = false;
            }
			else
			{
				leaves = next;
			}
        }

        leaves = treeSize + 1 - leaves;
        compress(0, leaves);

        vine = treeSize - leaves;

        if (vine > 1)
        {
            int nonLeaves = vine / 2;

            leaves /= 2;
            if (leaves > nonLeaves)
            {
                leaves = nonLeaves;
                nonLeaves = 0;
            }
            else
            {
                nonLeaves -= leaves;
            }

            compress (leaves, nonLeaves);
            vine /= 2;
        }

        while (vine > 1)
        {
            vine /= 2;
            compress (vine, 0);
        }

        // Reset the nodes depths and parents
        init(NULL);
    }
}

/**
 * find(const string& token) const
 *
 * Method searching for the node holding the input token.
 *
 * @param token Data to search for
 * @pre None
 * @post Returns node holding the token
 * @return Node on success; NULL on failure
 */
Node* ThreadedBinarySearchTree::find(const string& token) const
{
    if (!token.empty() && (rootNode != NULL))
    {
        Node* current = rootNode;
		bool run = (current != NULL);

        while (run)
        {
            int result = current->data.compare(token);

            if (result == 0)
            {
                // Match found!
                return current;
            }
            else if (result > 0)
            {
                // Navigate through the left branch
                if (current->leftNodeType == THREAD)
                {
                    // No match found; end search.
					run = false;
                }
				else
				{
					current = current->leftNode;
				}
            }
            else
            {
                // Navigate through the right branch
                if (current->rightNodeType == THREAD)
                {
                    // No match found; end search.
					run = false;
                }
				else
				{
					current = current->rightNode;
				}
            }
        }
    }

    return NULL;
}

/**
 * insert(const string& token)
 *
 * Method inserting a new token into the tree.
 * If the token exists, then it only increments its frequency.
 *
 * @param token Data to insert
 * @pre token is valid (not empty)
 * @post Returns the outcome of the operation
 * @return true on success; false on failure
 */
bool ThreadedBinarySearchTree::insert(const string& token)
{
    bool success = !token.empty();

    if (success)
    {
        Node* newNode = new Node(token);

        // If insertHelper returns false, it means that we found
        // a duplicate whose frequency was incremented.
        // The operation is still a success
        if (!insertHelper(newNode))
        {
            delete newNode;
        }
    }

    return success;
}

/**
 * insert(const string& token)
 *
 * Method inserting a new node into the tree.
 * If the token exists, then it only increments its frequency.
 *
 * @param node Reference node to copy 
 * @pre Reference node is valid
 * @post Returns the outcome of the operation
 * @return true on success; false on failure
 */
bool ThreadedBinarySearchTree::insert(const Node& node)
{
    Node* newNode = new Node(node);
    bool success = newNode->data.isValid();

    if (success)
    {
        // If insertHelper returns false, it means that we found
        // a duplicate whose frequency was incremented.
        // The operation is still a success
        if (!insertHelper(newNode))
        {
            delete newNode;
        }
    }

    return success;
}

/**
 * remove(const string& token)
 *
 * Method removing a token from the tree.
 *
 * @param token Data to remove
 * @pre token is valid (not empty)
 * @post Returns the outcome of the operation
 * @return true on success; false on failure
 */
bool ThreadedBinarySearchTree::remove(const string& token)
{
    bool rightLink = false; // navigation direction: false/true => left/right
    Node* current = NULL;   // node to remove
    Node* parent = NULL;    // parent of node to remove
    bool success = false;

    // Find node to remove
    if (!token.empty() && (rootNode != NULL))
    {
        current = rootNode;
		bool run = (current != NULL);

		while (run)
        {
            int result = current->data.compare(token);

            if (result == 0)
            {
                // Match found!
                success = true;
				run = false;
            }
            else if (result > 0)
            {
                // Navigate through the left branch
                rightLink = false;
                if (current->leftNodeType == THREAD)
                {
                    // No match found; end search.
					run = false;
                }
				else
				{
					parent = current;
					current = current->leftNode;
				}
            }
            else
            {
                // Navigate through the right branch
                rightLink = true;
                if (current->rightNodeType == THREAD)
                {
                    // No match found; end search.
					run = false;
				}
				else
				{
					parent = current;
					current = current->rightNode;
				}
            }
        }
    }

    if (success)
    {
        // Assess the links of node to remove
        if (treeSize == 1)
        {
            // We are about to remove the last node in the tree
            clear();
        }
        else if (current->rightNodeType == THREAD)
        {
            if (current->leftNodeType == THREAD)
            {
                // Both links are of THREAD type (that is, node to remove
                // is not the root node; otherwise, the treeSize should
                // have been 1) 
                if (parent != NULL)
                {
                    if (rightLink)
                    {
                        parent->rightNode = current->rightNode;
                        parent->rightNodeType = THREAD;
                    }
                    else
                    {
                        parent->leftNode = current->leftNode;
                        parent->leftNodeType = THREAD;
                    }
                }
            }
            else
            {
                // One link (the left one) is a CHILD
                Node* child = current->leftNode;

                // Locate the next node (in order) for that child
                while (child->rightNodeType == CHILD)
                {
                    child = child->rightNode;
                }

                // Reset the links of the child and parent nodes
                child->rightNode = current->rightNode;
                if (parent != NULL)
                {
                    if (rightLink)
                    {
                        parent->rightNode = current->leftNode;
                    }
                    else
                    {
                        parent->leftNode = current->leftNode;
                    }
                }
                else if (current == rootNode)
                {
					rootNode = current->leftNode;
                }
            }
        }
        else
        {
            // Right node is CHILD
            Node* child = current->rightNode;

            if (child->leftNodeType == THREAD)
            {
                // Only the right node is a CHILD
                child->leftNode = current->leftNode;
                child->leftNodeType = current->leftNodeType;
                if (child->leftNodeType == CHILD)
                {
                    Node* childLink = child->leftNode;
                    while (childLink->rightNodeType == CHILD)
                    {
                        childLink = childLink->rightNode;
                    }
                    childLink->rightNode = child;
                }

                // Reset the links of the parent node
                if (parent != NULL)
                {
                    if (rightLink)
                    {
                        parent->rightNode = child;
                    }
                    else
                    {
                        parent->leftNode = child;
                    }
                }
                else if (current == rootNode)
                {
                    rootNode = child;
                }
            }
            else
            {
                // Both links are of CHILD type
                Node* childLink = child->leftNode;

                // Get the lowest node on left branch
                while (childLink->leftNodeType == CHILD)
                {
                    child = childLink;
                    childLink = child->leftNode;
                }

                // Reset the links of the child and grandchild nodes
                if (childLink->rightNodeType == CHILD)
                {
                    child->leftNode = childLink->rightNode;
                }
                else
                {
                    child->leftNode = childLink;
                    child->leftNodeType = THREAD;
                }

                childLink->leftNode = current->leftNode;
                if (current->leftNodeType == CHILD)
                {
                    Node* prevLink = current->leftNode;
                    while (prevLink->rightNodeType == CHILD)
                    {
                        prevLink = prevLink->rightNode;
                    }
                    prevLink->rightNode = childLink;
                    childLink->leftNodeType = CHILD;
                }

                childLink->rightNode = current->rightNode;
                childLink->rightNodeType = CHILD;

                // Reset the links of the parent node
                if (parent != NULL)
                {
                    if (rightLink)
                    {
                        parent->rightNode = childLink;
                    }
                    else
                    {
                        parent->leftNode = childLink;
                    }
                }
                else if (current == rootNode)
                {
                    rootNode = childLink;
                }
            }
        }

        if (treeSize > 0)
        {
            // Delete node to remove, decrement size and reset parent links
            treeSize--;
            if (current->leftNodeType == CHILD)
            {
                current->leftNode->parentNode = NULL;
            }
            if (current->rightNodeType == CHILD)
            {
                current->rightNode->parentNode = NULL;
            }

            delete current;

            // Reset the nodes depths and parents
            init(NULL);
        }
    }

    return success;
}

/**
 * getFirst() const
 *
 * Method retrieving the node holding the first token (in order).
 *
 * @pre None
 * @post Returns node holding the first token
 * @return Node on success; NULL on failure
 */
Node* ThreadedBinarySearchTree::getFirst() const
{
    Node* first = rootNode;

    while ((first != NULL) && (first->leftNodeType == CHILD))
    {
        first = first->leftNode;
    }

    return first;
}

/**
 * getLast() const
 *
 * Method retrieving the node holding the last token (in order).
 *
 * @pre None
 * @post Returns node holding the last token
 * @return Node on success; NULL on failure
 */
Node* ThreadedBinarySearchTree::getLast() const
{
    Node* last = rootNode;

    while ((last != NULL) && (last->rightNodeType == CHILD))
    {
        last = last->rightNode;
    }

    return last;
}

/**
 * getNext() const
 *
 * Method retrieving the node holding the next token.
 *
 * @param current Reference node
 * @pre None
 * @post Returns node holding the next token
 * @return Node on success; NULL on failure
 */
Node* ThreadedBinarySearchTree::getNext(Node* current) const
{
    Node* next = NULL;

    if (current == NULL)
    {
        next = getFirst();
    }
    else if (current->rightNodeType == THREAD)
    {
        next = current->rightNode;
    }
    else
    {
        next = current->rightNode;
        while (next->leftNodeType == CHILD)
        {
            next = next->leftNode;
        }
    }

    return next;
}

/**
 * getNext() const
 *
 * Method retrieving the node holding the previous token.
 *
 * @param current Reference node
 * @pre None
 * @post Returns node holding the previous token
 * @return Node on success; NULL on failure
 */
Node* ThreadedBinarySearchTree::getPrevious(Node* current) const
{
    Node* previous = NULL;

    if (current == NULL)
    {
        previous = getLast();
    }
    else if (current->leftNodeType == THREAD)
    {
        previous = current->leftNode;
    }
    else
    {
        previous = current->leftNode;
        while (previous->rightNodeType == CHILD)
        {
            previous = previous->rightNode;
        }
    }

    return previous;
}

/**
 * begin()
 *
 * Method returning a tree iterator initialized for incremental navigation.
 *
 * @pre Tree is not empty
 * @post Constructs and initialize iterator for forward navigation.
 * @return Initialized iterator
 */
TreeIterator ThreadedBinarySearchTree::begin()
{
    TreeIterator iter(this);
    iter.currentNode = getFirst();
    return iter;
}

/**
 * rbegin()
 *
 * Method returning a tree iterator initialized for decremental navigation.
 *
 * @pre Tree is not empty
 * @post Constructs and initialize iterator for backward navigation.
 * @return Initialized iterator
 */
TreeIterator ThreadedBinarySearchTree::rbegin()
{
    TreeIterator iter(this);
    iter.currentNode = getLast();
    return iter;
}

/**
 * end()
 *
 * Method returning a tree iterator initialized for incremental navigation
 * and having the position moved beyond the last node.
 *
 * @pre Tree is not empty
 * @post Constructs and initialize iterator.
 * @return Initialized iterator
 */
TreeIterator ThreadedBinarySearchTree::end()
{
    TreeIterator iter(this);
    iter.currentNode = getNext(getLast());
    return iter;
}

/**
 * rend()
 *
 * Method returning a tree iterator initialized for decremental navigation
 * and having the position moved beyond the first node.
 *
 * @pre Tree is not empty
 * @post Constructs and initialize iterator.
 * @return Initialized iterator
 */
TreeIterator ThreadedBinarySearchTree::rend()
{
    TreeIterator iter(this);
    iter.currentNode = getPrevious(getFirst());
    return iter;
}

/**
 * inorderIterativeTraverse() const
 *
 * Method returning the in-order traversal list of nodes.
 * It employs an iterative approach.
 *
 * @pre None
 * @post Returns list of in-order traversal nodes
 * @return List of nodes on success; NULL on failure
 */
Node** ThreadedBinarySearchTree::inorderIterativeTraverse() const
{
    Node** nodesList = createNodesList();

    if (nodesList != NULL)
    {
        Node* current = getNext(NULL);
        int count = 0;

        while (current != NULL)
        {
            nodesList[count++] = current;
            current = getNext(current);
        }
    }

    return nodesList;
}

/**
 * preorderTraverse() const
 *
 * Method returning the pre-order traversal list of nodes.
 * It employs an recursive approach.
 *
 * @pre None
 * @post Returns list of pre-order traversal nodes
 * @return List of nodes on success; NULL on failure
 */
Node** ThreadedBinarySearchTree::preorderTraverse() const
{
    Node** nodesList = createNodesList();

    if (nodesList != NULL)
    {
        int count = 0;
        traverseHelper(PREORDER, rootNode, nodesList, count);
    }

    return nodesList;
}

/**
 * inorderTraverse() const
 *
 * Method returning the in-order traversal list of nodes.
 * It employs an recursive approach.
 *
 * @pre None
 * @post Returns list of in-order traversal nodes
 * @return List of nodes on success; NULL on failure
 */
Node** ThreadedBinarySearchTree::inorderTraverse() const
{
    Node** nodesList = createNodesList();

    if (nodesList != NULL)
    {
        int count = 0;
        traverseHelper(INORDER, rootNode, nodesList, count);
    }

    return nodesList;
}

/**
 * postorderTraverse() const
 *
 * Method returning the post-order traversal list of nodes.
 * It employs an recursive approach.h.
 *
 * @pre None
 * @post Returns list of post-order traversal nodes
 * @return List of nodes on success; NULL on failure
 */
Node** ThreadedBinarySearchTree::postorderTraverse() const
{
    Node** nodesList = createNodesList();

    if (nodesList != NULL)
    {
        int count = 0;
        traverseHelper(POSTORDER, rootNode, nodesList, count);
    }

    return nodesList;
}

/**
 * operator>>(istream& is, ThreadedBinarySearchTree& tbst)
 *
 * Overloaded operator for populating the tree from an input stream.
 *
 * @param is Input stream sourcing the data
 * @param tbst Tree to populate
 * @pre None
 * @post Tree is filled up with data supplied by input stream.
 * @return Reference to input stream
 */
istream& operator>>(istream& is, ThreadedBinarySearchTree& tbst)
{
    bool error = false;
    string data;

    while (!error && is.good())
    {
        char ch = is.get();

        if (isTokenChar(ch))
        {
            // alphanumeric - build the token
            data.push_back(ch);
        }
        else
        {
            // We reached a word boundary; insert the token built so far.
            if (!data.empty())
            {
                // Insert the current token (if any)
                if (tbst.insert(data))
                {
                    data.clear();
                }
                else
                {
                    error = true;
                }
            }

            if (!error &&
                (isprint(ch) != 0) &&
                (isspace(ch) == 0) &&
                (isgraph(ch) == 0))
            {
                // Non white-space delimiter - inserted as a single char
                data.push_back(ch);
                if (tbst.insert(data))
                {
                    data.clear();
                }
                else
                {
                    error = true;
                }
            }

            if (error)
            {
                cerr << "Failed to insert ";
                cerr << data.c_str() << "\r\n";
            }
        }
    }
    is.clear();

    return is;
}

/**
 * show(std::ostream& output,  bool details) const
 *
 * Helper method for pushing the tree information into an output stream.
 *
 * @param output Output stream
 * @param details Whether to display extended info
 * @pre None
 * @post data is pushed into the stream.
 */
void ThreadedBinarySearchTree::show(std::ostream& output,  bool details) const
{
    output << "Threaded Binary Search Tree: ";
    output << "size = " << treeSize;
    output << ", height = " << treeHeight;
    output << "\r\n";

    if (details)
    {
		Node* current = getNext(NULL);

        while (current != NULL)
        {
            current->show(output, true);
            current = getNext(current);
        }
        output << "\r\n";
    }
}

/**
 * show(std::ostream& output, Node** nodesList, bool details) const
 *
 * Helper method for pushing the nodes information into an output stream.
 *
 * @param output Output stream
 * @param nodesList List of nodes to display
 * @param details Whether to display extended info
 * @pre List is not NULL or empty
 * @post data is pushed into the stream.
 */
void ThreadedBinarySearchTree::show(
    std::ostream& output,
    Node** nodesList,
    bool details) const
{
    if ((treeSize > 0) && (nodesList != NULL))
    {
        for (int i = 0; i < treeSize; i++)
        {
			if (details)
			{
				nodesList[i]->show(output, true);
			}
			else
			{
				if ((i % NODES_PER_LINE) == 0)
				{
					if (i > 0)
					{
						output << "\r\n";
					}
					output << "\t";
				}
				nodesList[i]->show(output, false);
				output << " ";
			}
        }
    }
}

/**
 * showPartial(std::ostream& output, Node** nodesList, bool top) const
 *
 * Helper method for pushing the nodes information into an output stream.
 * Only top of the list is displayed.
 * @param output Output stream
 * @param nodesList List of nodes to display
 * @param top Whether to show the bottom of the top of the list
 * @pre List is not NULL or empty
 * @post data is pushed into the stream.
 */
void ThreadedBinarySearchTree::showPartial(
    std::ostream& output,
    Node** nodesList,
    bool top) const
{
    if ((treeSize > 0) && (nodesList != NULL))
    {
        if (treeSize <= NODES_DISPLAYED)
        {
            ThreadedBinarySearchTree::show(
                output, nodesList, 0, treeSize - 1);
        }
        else if (top)
        {
            ThreadedBinarySearchTree::show(
                output, nodesList, treeSize - NODES_DISPLAYED, treeSize - 1);
        }
        else
        {
            ThreadedBinarySearchTree::show(
                output, nodesList, 0, NODES_DISPLAYED - 1);
        }
    }
}

/**
 * show(std::ostream& output, Node** nodesList, int first, int last) const
 *
 * Helper method for pushing the nodes information into an output stream.
 *
 * @param output Output stream
 * @param nodesList List of nodes to display
 * @param first Index of of first node to display
 * @param last Index of of last node to display
 * @pre List is not NULL or empty; first & last parameters are valid.
 * @post data is pushed into the stream.
 */
void ThreadedBinarySearchTree::show(
    std::ostream& output,
    Node** nodesList,
    int first,
    int last)
{
    if ((nodesList != NULL) && (first >= 0) && (first <= last))
    {
        output << "\t";
        for (int i = first, nodes = 0; i <= last; i++, nodes++)
        {
            if ((nodes > 0) && ((nodes % NODES_PER_LINE) == 0))
            {
                output << "\r\n";
                output << "\t";
            }
            nodesList[i]->show(output, false);
            output << " ";
        }
        output << "\r\n";
    }
}

/**
 * createNodesList() const
 *
 * Helper method for creating a array to hold all the nodes in the tree.
 * The array will be further filled with traversal nodes.
 *
 * @pre The tree is not empty
 * @post Returns array that can hold all the nodes
 * @return Array of Node pointers
 */
Node** ThreadedBinarySearchTree::createNodesList() const
{
    Node** nodesList = NULL;

    if (treeSize > 0)
    {
        nodesList = new Node*[treeSize];
        for (int i = 0; i < treeSize; i++)
        {
            nodesList[i] = NULL;
        }
    }

    return nodesList;
}

/**
 * init(Node* node)
 *
 * Helper method for re-setting the depth and parent for each node
 * (starting from a reference node)
 *
 * @param Node Initial node to start with
 * @pre None
 * @post Depth and parent are set for each node
 */
void ThreadedBinarySearchTree::init(Node* node)
{
    if (node == NULL)
    {
        if (rootNode != NULL)
        {
            rootNode->depth = 0;
            rootNode->parentNode = NULL;
            treeHeight = 0;
            init(rootNode);
        }
    }
    else
    {
        treeHeight = std::max(treeHeight, node->depth + 1);

        if (node->leftNodeType == CHILD)
        {
            node->leftNode->depth = node->depth + 1;
            node->leftNode->parentNode = node;
            init(node->leftNode);
        }

        if (node->rightNodeType == CHILD)
        {
            node->rightNode->depth = node->depth + 1;
            node->rightNode->parentNode = node;
            init(node->rightNode);
        }
    }
}

/**
 * insertHelper(Node* newNode)
 *
 * Helpert method for inserting a new node into the tree.
 *
 * @param node Node to insert
 * @pre Node is valid
 * @post Returns the outcome of the operation
 * @return true on success; false on failure
 */
bool ThreadedBinarySearchTree::insertHelper(Node* newNode)
{
    Node* current = rootNode;       // current reference node
    bool success = false;

    if ((newNode != NULL) && newNode->data.isValid())
    {
        if (rootNode == NULL)
        {
            rootNode = newNode;
            success = true;
        }
        else
        {
            // Search for the insertion position
			int result = -1;

			while (!success && (result != 0))
            {
                result = current->data.compare(newNode->data.getToken());

                if (result == 0)
                {
                    // duplicate found
                    current->data.increaseFrequency();
                }
                else if (result > 0)
                {
                    // Navigate the left branch
                    if (current->leftNodeType == CHILD)
                    {
                        current = current->leftNode;
                    }
                    else
                    {
                        // Insertion point found on left branch
                        newNode->leftNode = current->leftNode;
                        newNode->rightNode = current;
                        current->leftNode = newNode;
                        current->leftNodeType = CHILD;
                        success = true;
                    }
                }
                else
                {
                    // Navigate the right branch
                    if (current->rightNodeType == CHILD)
                    {
                        current = current->rightNode;
                    }
                    else
                    {
                        // Insertion point found on right branch
                        newNode->leftNode = current;
                        newNode->rightNode = current->rightNode;
                        current->rightNode = newNode;
                        current->rightNodeType = CHILD;
                        success = true;
                    }
                }
            }
        }
    }

    if (success)
    {
        treeSize++;
        newNode->id = treeSize;
        newNode->parentNode = current;
        newNode->depth = (current == NULL) ? 0 : (current->depth + 1);
        treeHeight = std::max(treeHeight, newNode->depth + 1);
    }

    return success;
}

/**
 * compress(int nonThreadCount, int threadCount)
 *
 * Helper method for compressing a tree:
 * 1. Performs a non-threaded compression operation nonThreadCount times.
 * 2. Performs a threaded compression operation threadCount times.
 * Reference:
 * http://adtinfo.org/libavl.html/Transforming-a-Vine-into-a-Balanced-TBST.html
 *
 * @pre Tree has at least 3 nodes
 * @post Tree is compressed
 */
void ThreadedBinarySearchTree::compress(int nonThreadCount, int threadCount)
{
    if (treeSize >= COMPRESSION_MIN_NODES)
    {
        Node* root = rootNode;

        while ((root != NULL) && (nonThreadCount-- > 0))
        {
            Node* red = root->leftNode;
            Node* black = red->leftNode;

            root->leftNode = black;
            red->leftNode = black->rightNode;
            black->rightNode = red;
            root = black;
        }

        while ((root != NULL) && (threadCount-- > 0))
        {
            Node* red = root->leftNode;
            Node* black = red->leftNode;

            root->leftNode = black;
            red->leftNode = black;
            red->leftNodeType = THREAD;
            black->rightNodeType = CHILD;
            root = black;
        }
    }
}

/**
 * destroy(Node* node)
 *
 * Helper method destroying all the nodes (starting from a reference node)
 *
 * @param Node Initial node to start with
 * @pre None
 * @post All nodes (including the reference) are deleted
 */
void ThreadedBinarySearchTree::destroy(Node* node)
{
    if (node != NULL)
    {
        if (node->leftNodeType == CHILD)
        {
            destroy(node->leftNode);
        }

        if (node->rightNodeType == CHILD)
        {
            destroy(node->rightNode);
        }

        delete node;
    }
}

/**
 * traverseHelper(int traverseType, Node* node, Node** nodesList,
 *                int& currentPosition);
 *
 * Helpert method for recursive traversal starting from a reference node.
 *
 * @param traverseType Type of traversal (PREORDER, INORDER, POSTORDER)
 * @param node Reference node to start with
 * @param nodesList Traversal list
 * @param currentPosition Current position within traversal list
 * @pre Reference node and traversal list are not NULL
 */
void ThreadedBinarySearchTree::traverseHelper(
    int traverseType,
    Node* node,
    Node** nodesList,
    int& currentPosition)
{
    if ((node != NULL) && (nodesList != NULL) && (currentPosition >= 0))
    {
        switch (traverseType)
        {
            case PREORDER:
                nodesList[currentPosition++] = node;
                if (node->leftNodeType == CHILD)
                {
                    traverseHelper(
                        traverseType,
                        node->leftNode,
                        nodesList,
                        currentPosition);
                }
                if (node->rightNodeType == CHILD)
                {
                    traverseHelper(
                        traverseType,
                        node->rightNode,
                        nodesList,
                        currentPosition);
                }
                break;

            case INORDER:
                if (node->leftNodeType == CHILD)
                {
                    traverseHelper(
                        traverseType,
                        node->leftNode,
                        nodesList,
                        currentPosition);
                }
                nodesList[currentPosition++] = node;
                if (node->rightNodeType == CHILD)
                {
                    traverseHelper(
                        traverseType,
                        node->rightNode,
                        nodesList,
                        currentPosition);
                }
                break;

            case POSTORDER:
                if (node->leftNodeType == CHILD)
                {
                    traverseHelper(
                        traverseType,
                        node->leftNode,
                        nodesList,
                        currentPosition);
                }
                if (node->rightNodeType == CHILD)
                {
                    traverseHelper(
                        traverseType,
                        node->rightNode,
                        nodesList,
                        currentPosition);
                }
                nodesList[currentPosition++] = node;
                break;
        }
    }
}


/**
 * TreeIterator(ThreadedBinarySearchTree* tbst)
 *
 * Constructor
 * @param tbst TBS tree to iterate over
 */
TreeIterator::TreeIterator(ThreadedBinarySearchTree* tbst)
    : tbsTree(tbst),
      currentNode(NULL)
{
}

/**
 * TreeIterator(ThreadedBinarySearchTree* tbst)
 *
 * Copy constructor
 * @param treeIter Source iterator
 */
TreeIterator::TreeIterator(const TreeIterator& treeIter)
    : tbsTree(treeIter.tbsTree),
      currentNode(treeIter.currentNode)
{
}

/**
 * operator*()
 *
 * De-reference operator
 *
 * @pre None
 * @post Retrieves the current iteration node
 * @return current node
 */
Node*& TreeIterator::operator*()
{
    return currentNode;
}

/**
 * operator++()
 *
 * Increment operator - prefix form
 *
 * @pre None
 * @post The iterator is advanced forward.
 * @return A reference to current iterator
 */
TreeIterator& TreeIterator::operator++()
{
    currentNode = tbsTree->getNext(currentNode);
    return *this;
}

/**
 * operator++()
 *
 * Increment operator - postfix form
 *
 * @pre None
 * @post The iterator is advanced forward.
 * @return A reference to current iterator
 */
TreeIterator TreeIterator::operator++(int)
{
    TreeIterator iter(*this);
    operator++();
    return iter;
}

/**
 * operator--()
 *
 * Decrement operator - prefix form
 *
 * @pre None
 * @post The iterator is advanced backward.
 * @return A reference to current iterator
 */
TreeIterator& TreeIterator::operator--()
{
    currentNode = tbsTree->getPrevious(currentNode);
    return *this;
}

/**
 * operator--()
 *
 * Decrement operator - postfix form
 *
 * @pre None
 * @post The iterator is advanced backward.
 * @return A reference to current iterator
 */
TreeIterator TreeIterator::operator--(int)
{
    TreeIterator iter(*this);
    operator--();
    return iter;
}

/**
 * operator==(const TreeIterator& treeIter)
 *
 * Equality operator
 *
 * @param treeIter The iterator used as comparison target.
 * @pre None
 * @post The local data is compared against the target data.
 * @return True if the data are matching; false otherwise.
 */
bool TreeIterator::operator==(const TreeIterator& treeIter)
{
    return (tbsTree == treeIter.tbsTree) &&
           (currentNode == treeIter.currentNode);
}

/**
 * operator!=(const TreeIterator& treeIter)
 *
 * Equality operator
 *
 * @param treeIter The iterator used as comparison target.
 * @pre None
 * @post The local data is compared against the target data.
 * @return True if the data are matching; false otherwise.
 */
bool TreeIterator::operator!=(const TreeIterator& treeIter)
{
    return (tbsTree != treeIter.tbsTree) ||
           (currentNode != treeIter.currentNode);
}

/**
 * isTokenChar(char ch)
 *
 * Function checking whether input character is part of word token.
 *
 * @param ch Character to check.
 * @pre None
 * @post Character is compared against our definition of token data.
 * @return True of char belongs to a token; false otherwise.
 */
bool isTokenChar(char ch)
{
    switch (ch)
    {
        case '\'':
        case '\"':
        case '-':
        case '_':
            return true;

        default:
            break;
    }

    return (isalnum(ch) != 0);
}
