/**
 * @author Daniel Sebastian Iliescu
 * @file bintree.cpp
 *
 * This file contains the methods for BinTree class that implements a
 * Search Binary Tree.
 */

#include <algorithm>
#include "bintree.h"

using namespace std;

// Tree traversal types
const int PREORDER = 1;     // Recursive pre-order traversal
const int INORDER = 2;      // Recursive in-order traversal
const int POSTORDER = 3;    // Recursive post-order traversal

// ---------------------------------------------------------------------------
// Default constructor for class BinTree
BinTree::BinTree() : root(NULL)
{
}

// ---------------------------------------------------------------------------
// Copy constructor for class BinTree
BinTree::BinTree(const BinTree &source) : root(NULL)
{
	*this = source;
}

// ---------------------------------------------------------------------------
// Destructor for class BinTree
BinTree::~BinTree()
{
	makeEmpty();
}

// ---------------------------------------------------------------------------
// isEmpty
// Checks whether the tree is empty and returns true if it is.
bool BinTree::isEmpty() const
{
	return (root == NULL);
}

// ---------------------------------------------------------------------------
// getTreeSize
// Returns the number of nodes in the tree.
int BinTree::getTreeSize() const
{
	return getBranchSize(root);
}

// ---------------------------------------------------------------------------
// getTreeHeight
// Returns the length of the longest branch in the tree.
int BinTree::getTreeHeight() const
{
	return getBranchHeight(root);
}

// ---------------------------------------------------------------------------
// makeEmpty
// Clears the tree and deallocates the memory associated with its nodes.
void BinTree::makeEmpty()
{
	destroyNode(root);
	root = NULL;
}

// ---------------------------------------------------------------------------
// getDepth
// Finds the depth of a given value in the tree
int BinTree::getDepth(const NodeData &targetData) const
{
	return findNode(root, targetData, NULL);
}

// ---------------------------------------------------------------------------
// operator= 
// Overloaded assignment operator
BinTree& BinTree::operator=(const BinTree &other)
{
	// Check for self-assignment!
	if (this != &other)
	{
		makeEmpty();
		copyNode(&root, other.root);
	}

	return *this;
}

// --------------------------------------------------------------------------
// operator== 
// Determine if two BinTreenomial are equal.
bool BinTree::operator==(const BinTree &other) const
{
	bool equal = true;

	if (this != &other)
	{
		equal = areEqual(root, other.root);
	}

	return equal;
}

// --------------------------------------------------------------------------
// operator!= 
// Determine if two BinTreenomial are not equal.
bool BinTree::operator!=(const BinTree &other) const
{
	bool equal = (*this == other);
	return !equal;
}

// --------------------------------------------------------------------------
// operator<< 
// Overloaded output operator for class BinTree.
std::ostream& operator<<(std::ostream& os, const BinTree& obj)
{
	if (!obj.isEmpty())
	{
		int size = obj.getTreeSize();
		NodeData** data = obj.inorderTraverse();

		for (int i = 0; i < size; i++)
		{
			os << " " << *data[i];
		}
		delete [] data;
	}
	os << endl;

	return os;
}

// ---------------------------------------------------------------------------
// insert
// Attempts to insert a new (and unique) data into the tree.
// If data is inserted, then it returns true; otherwise it returns false.
bool BinTree::insert(NodeData* data)
{
	bool success = false;

	if (data != NULL)
	{
		if (root == NULL)
		{
			root = createNode(data);
			success = true;
		}
		else
		{
			success = insertHelper(root, data);
		}
	}

	return success;
}

// ---------------------------------------------------------------------------
// retrieve
// Attempts to retrieve the node holding given data.
// If node is found, then it returns true; otherwise it returns false.
bool BinTree::retrieve(const NodeData &refData, NodeData* &data) const
{
	Node* node = NULL;

	if (findNode(root, refData, &node) > 0)
	{
		data = node->data;
		return true;
	}
	else
	{
		data = NULL;
		return false;
	}
}

//---------------------------------------------------------------------------
// preorderTraverse
// Retrieves the pre-order traversal of the binary tree.
NodeData** BinTree::preorderTraverse() const
{
	NodeData** nodesData = createDataArray();

	if (nodesData != NULL)
	{
		int index = 0;
		preorderHelper(root, nodesData, index, false);
	}

	return nodesData;
}

//---------------------------------------------------------------------------
// inorderTraverse
// Retrieves the in-order traversal of the binary tree.
NodeData** BinTree::inorderTraverse() const
{
	NodeData** nodesData = createDataArray();

	if (nodesData != NULL)
	{
		int index = 0;
		inorderHelper(root, nodesData, index, false);
	}

	return nodesData;
}

//---------------------------------------------------------------------------
// postorderTraverse
// Retrieves the post-order traversal of the binary tree.
NodeData** BinTree::postorderTraverse() const
{
	NodeData** nodesData = createDataArray();

	if (nodesData != NULL)
	{
		int index = 0;
		postorderHelper(root, nodesData, index, false);
	}

	return nodesData;
}

//---------------------------------------------------------------------------
// bstreeToArray
// Converts the binary tree to an in-order array of NodeData. 
// After the conversion, all the nodes in the tree are removed.
void BinTree:: bstreeToArray(NodeData* nodesData[])
{
	if (!isEmpty() && (nodesData != NULL))
	{
		int index = 0;
		inorderHelper(root, nodesData, index, true);
	}
	makeEmpty();
}

//---------------------------------------------------------------------------
// bstreeToArray
// Converts an ordered array of NodeData to a binary search tree.
// The tree is populated recursively with the array data such selected that
// the tree will end up balanced.
void BinTree:: arrayToBSTree(NodeData* nodesData[])
{
	makeEmpty();
	if (nodesData != NULL)
	{
		int maxPosition = -1;

		// Calculate tree size
		while (nodesData[maxPosition + 1] != NULL)
		{
			maxPosition++;
		}
		insertBalanced(nodesData, 0, maxPosition);
	}
}

//---------------------------------------------------------------------------
// displaySideways 
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
void BinTree::displaySideways() const
{
	sideways(root, 0);
}

//---------------------------------------------------------------------------
// displayTree 
// Displays the binary tree info; data is displayed in pre-order format.
// This method is used for debugging purposes.
void BinTree::displayTree() const
{
	int size = getTreeSize();
	cout << "[" << size << ", " << getTreeHeight() << "]";
	if (!isEmpty())
	{
		NodeData** data = preorderTraverse();

		for (int i = 0; i < size; i++)
		{
			cout << " " << *data[i];
		}
		delete [] data;
	}
	cout << endl;
}

// ---------------------------------------------------------------------------
// createDataArray()
// Helper method for creating an array large enough for holding all the data
// in the binary search tree. The array size is set to the tree size + 1, so
// that the last cell is always NULL, thus indicating the end of data.
NodeData** BinTree::createDataArray() const
{
	NodeData** nodesData = NULL;

	if (!isEmpty())
	{
		int size = getTreeSize() + 1;
		nodesData = new NodeData*[size];
		for (int i = 0; i < size; i++)
		{
			nodesData[i] = NULL;
		}
	}

	return nodesData;
}

// ---------------------------------------------------------------------------
// createNode
// Helper method for creating and initializing a new node.
BinTree::Node* BinTree::createNode(NodeData* data) const
{
	Node* node = new Node();
	if (data != NULL)
	{
		node->data = data;
	}
	else
	{
		node->data = new NodeData();
	}
	node->left = NULL;
	node->right = NULL;

	return node;
}

// ---------------------------------------------------------------------------
// destroyNode
// Helper method for destroying a node and all its children.
void BinTree::destroyNode(Node* node)
{
	if (node != NULL)
	{
		if (node->data != NULL)
		{
			delete node->data;
		}
		destroyNode(node->left);
		destroyNode(node->right);
		delete node;
	}
}

// ---------------------------------------------------------------------------
// getBranchSize
// Helper method for calculating the number of nodes within the branch
// anchored by a given node.
int BinTree::getBranchSize(Node* node) const
{
	int count = 0;

	if (node != NULL)
	{
		count = 1 + getBranchSize(node->left) + getBranchSize(node->right);
	}

	return count;
}

// ---------------------------------------------------------------------------
// getBranchHeight
// Helper method for calculating the height of a branch anchored by a node.
int BinTree::getBranchHeight(Node* node) const
{
	int height = 0;

	if (node != NULL)
	{
		height = 1 +
			max(getBranchHeight(node->left), getBranchHeight(node->right));
	}

	return height;
}

// ---------------------------------------------------------------------------
// copyNode
// Helper method for copying a whole tree branch anchored on a given node.
// It copies recursively the reference node data (and all its children data)
// into the current binary search tree.
// For efficiency reason, this method does not call "insert" as it copies
// the data as it occurs in the source tree (without any additional checking).
// Parameters:
//  dst             Location of the new node in the current tree
//  source          Reference node to copy
void BinTree::copyNode(Node** dst, const Node* source)
{
	if ((dst != NULL) && (source != NULL)) 
	{
		NodeData* data = new NodeData(*(source->data));
		Node* node = createNode(data);
		*dst = node;
		copyNode(&node->left, source->left);
		copyNode(&node->right, source->right);
	}
}

// ---------------------------------------------------------------------------
// areEqual
// Helper method for checking recursively whether two tree branches are
// equal. It compares all the nodes in the two branches and returns true
// if, and only if, the equivalent nodes have matching data.
bool BinTree::areEqual(Node* node1, Node* node2) const
{
	bool equal = false;

	if (node1 == node2)
	{
		// We end up here when both nodes are NULL or identical
		equal = true;
	}
	else if ((node1 != NULL) && (node2 != NULL) &&
			 (*(node1->data) == *(node2->data)))
	{
		// If nodes data match, we check their respective children
		if (areEqual(node1->left, node2->left) &&
			areEqual(node1->right, node2->right))
		{
			equal = true;
		}
	}

	return equal;
}

// ---------------------------------------------------------------------------
// findNode
// Helper method for finding the node holding a given data within the tree
// branch anchored by a given node. The search proceeds according to a
// depth-first algorithm and it does not assume that the tree is of BST type.
// If successful, the method returns the node depth; otherwise it returns 0.
int BinTree::findNode(
	Node* rootNode,
	const NodeData &targetData,
	Node** targetNode) const
{
	int depth = 0;

	if ((rootNode != NULL) && (rootNode->data != NULL))
	{
		if (*(rootNode->data) == targetData)
		{
			// We found our match
			depth++;
			if (targetNode != NULL)
			{
				*targetNode = rootNode;
			}
		}
		else
		{
			// Search left branch first and if unsuccessful
			// look into the right branch
			depth = findNode(rootNode->left, targetData, targetNode);
			if (depth == 0)
			{
				depth = findNode(rootNode->right, targetData, targetNode);
			}

			if (depth != 0)
			{
				// account for starting node
				depth++;
			}
		}
	}

	return depth;
}

// ---------------------------------------------------------------------------
// insertHelper
// Helper method for inserting a new data into the binary search tree after
// locating the insertion position. If the data is already in the tree, then
// it is not inserted (as duplicates are not allowed).
// If data is inserted, the method returns true; otherwise it returns false.
bool BinTree::insertHelper(Node* current, NodeData* data)
{
	bool success = false;

	if ((current != NULL) && (current->data != NULL) && (*(current->data) != *data))
	{
		if (*(current->data) > *data)
		{
			// navigate left branch
			if (current->left == NULL)
			{
				current->left = createNode(data);
				success = true;
			}
			else
			{
				success = insertHelper(current->left, data);
			}
		}
		else
		{
			// navigate right branch;
			if (current->right == NULL)
			{
				current->right = createNode(data);
				success = true;
			}
			else
			{
				success = insertHelper(current->right, data);
			}
		}
	}

	return success;
}

//---------------------------------------------------------------------------
// insertBalanced
// Helper method for converting an ordered list of data into the current tree
// such that the tree is as balanced as possible. The currently inserted node
// (i.e. the local root) is recursively at mid = (low + high)/2 where low is
// the lowest subscript of the array range and high is the highest.
void BinTree::insertBalanced(NodeData** data, int low, int high)
{
	if ((data != NULL) && (low >= 0) && (low <= high))
	{
		int mid = (low + high) / 2;

		if (data[mid] != NULL)
		{
			if (!insert(data[mid]))
			{
				delete data[mid];
			}
			data[mid] = NULL;
			insertBalanced(data, low, mid - 1);
			insertBalanced(data, mid + 1, high);
		}
	}
}

//---------------------------------------------------------------------------
// preorderHelper
// Helper method for recursive pre-order traversal starting from a
// reference node. Parameters:
//  node            Reference node to start with
//  nodesData       Traversal list
//  index           Current position within the traversal list
//  removeData      Whether to remove that data from tree while traversing
void BinTree::preorderHelper(
	Node* node,
	NodeData** nodesData,
	int &index,
	bool removeData) const
{
	traverseHelper(PREORDER, node, nodesData, index, removeData);
}

//---------------------------------------------------------------------------
// inorderHelper
// Helper method for recursive in-order traversal starting from a
// reference node. Parameters:
//  node            Reference node to start with
//  nodesData       Traversal list
//  index           Current position within the traversal list
//  removeData      Whether to remove that data from tree while traversing
void BinTree::inorderHelper(
	Node* node,
	NodeData** nodesData,
	int &index,
	bool removeData) const
{
	traverseHelper(INORDER, node, nodesData, index, removeData);
}

//---------------------------------------------------------------------------
// postorderHelper
// Helper method for recursive post-order traversal starting from a
// reference node. Parameters:
//  node            Reference node to start with
//  nodesData       Traversal list
//  index           Current position within the traversal list
//  removeData      Whether to remove that data from tree while traversing
void BinTree::postorderHelper(
	Node* node,
	NodeData** nodesData,
	int &index,
	bool removeData) const
{
	traverseHelper(POSTORDER, node, nodesData, index, removeData);
}

//---------------------------------------------------------------------------
// traverseHelper
// Helper method for recursive traversal starting from a reference node.
// Parameters:
//  traverseType    Traverse mode: pre-order, in-order, post-order
//  node            Reference node to start with
//  nodesData       Traversal list
//  index           Current position within the traversal list
//  removeData      Whether to remove that data from tree while traversing
void BinTree::traverseHelper(
	int traverseType,
	Node* node,
	NodeData** nodesData,
	int &index,
	bool removeData) const
{
	if ((node != NULL) && (nodesData != NULL) && (index >= 0))
	{
		if (traverseType == PREORDER)
		{
			nodesData[index++] = node->data;
		}

		if (node->left != NULL)
		{
			traverseHelper(
				traverseType, node->left, nodesData, index, removeData);
		}

		if (traverseType == INORDER)
		{
			nodesData[index++] = node->data;
		}

		if (node->right != NULL)
		{
			traverseHelper(
				traverseType, node->right, nodesData, index, removeData);
		}

		if (traverseType == POSTORDER)
		{
			nodesData[index++] = node->data;
		}

		if (removeData)
		{
			node->data = NULL;
		}
	}
}

//---------------------------------------------------------------------------
// sideways 
// Helper method for displaying a binary tree branch (anchored on a reference
// node) as though you are viewing it from the side; hard coded displaying
// to standard output.
void BinTree::sideways(Node* current, int level) const
{
	if (current != NULL)
	{
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--)
		{
			cout << "    ";
		}

		cout << *current->data << endl; // display information of object
		sideways(current->left, level);
	}
}
