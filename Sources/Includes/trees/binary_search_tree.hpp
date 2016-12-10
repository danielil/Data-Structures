/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */
#pragma once

#include "binary_search_tree_node.hpp"

#include <memory>

namespace dsa
{
	template <
		typename Key,
		typename Value >
	class binary_search_tree
	{

	public:
		binary_search_tree() = default;
		~binary_search_tree() noexcept = default;

		binary_search_tree( const binary_search_tree& other ) = default;
		binary_search_tree( binary_search_tree&& other ) noexcept = default;

		binary_search_tree& operator=( const binary_search_tree& rhs ) = default;
		binary_search_tree& operator=( binary_search_tree&& rhs ) noexcept = default;

		bool
		operator==( const binary_search_tree& other ) const
		{
			return ( this != &other && this->are_equal( root, other.root ) );
		}

		bool
		operator!=( const binary_search_tree& other ) const
		{
			return !( *this == other );
		}

		bool
		empty() const
		{
			return this->root;
		}

		std::size_t
		get_tree_size() const
		{
			return this->get_branch_size( this->root );
		}

		std::size_t
		get_tree_height() const
		{
			return this->get_branch_height( this->root );
		}

		std::size_t
		get_depth( binary_search_tree_node* data ) const
		{
			return this->find_node( this->root, data, nullptr );
		}

		void
		clear()
		{
		}

		// Tree operations
		void
		insert(
			const Key key,
			const Value value )
		{
			this->insert( this->root, key, value );
		}

		Value
		at( const Key key ) const
		{
			return this->retrieve_item( this->root, key );
		}

		// Recursive tree traversal
		binary_search_tree_node** preorderTraverse() const
		{
			NodeData** nodesData = createDataArray();

			if ( nodesData != nullptr )
			{
				int index = 0;
				preorderHelper( root, nodesData, index, false );
			}

			return nodesData;
		}

		binary_search_tree_node** inorderTraverse() const
		{
			NodeData** nodesData = createDataArray();

			if ( nodesData != nullptr )
			{
				int index = 0;
				inorderHelper( root, nodesData, index, false );
			}

			return nodesData;
		}

		binary_search_tree_node** postorderTraverse() const
		{
			NodeData** nodesData = createDataArray();

			if ( nodesData != nullptr )
			{
				int index = 0;
				postorderHelper( root, nodesData, index, false );
			}

			return nodesData;
		}

		// Tree-Array conversions
		void bstreeToArray( binary_search_tree_node* nodesData[] )
		{
			if ( !isEmpty() && ( nodesData != nullptr ) )
			{
				int index = 0;
				inorderHelper( root, nodesData, index, true );
			}
			makeEmpty();
		}
		void arrayToBSTree( binary_search_tree_node* nodesData[] )
		{
			makeEmpty();
			if ( nodesData != nullptr )
			{
				int maxPosition = -1;

				// Calculate tree size
				while ( nodesData[maxPosition + 1] != nullptr )
				{
					maxPosition++;
				}
				insertBalanced( nodesData, 0, maxPosition );
			}
		}

		// Display operations
		void displaySideways() const
		{
			sideways( root, 0 );
		}
		void displayTree() const
		{
			int size = getTreeSize();
			std::cout << "[" << size << ", " << getTreeHeight() << "]";
			if ( !isEmpty() )
			{
				NodeData** data = preorderTraverse();

				for ( int i = 0; i < size; i++ )
				{
					std::cout << " " << *data[i];
				}
				delete[] data;
			}
			std::cout << std::endl;
		}

	private:

		// Helper methods 
		binary_search_tree_node** createDataArray() const
		{
			NodeData** nodesData = nullptr;

			if ( !isEmpty() )
			{
				int size = getTreeSize() + 1;
				nodesData = new NodeData*[size];
				for ( int i = 0; i < size; i++ )
				{
					nodesData[i] = nullptr;
				}
			}

			return nodesData;
		}

		// ---------------------------------------------------------------------------
		// destroyNode
		// Helper method for destroying a node and all its children.
		void destroyNode( binary_search_tree_node* node )
		{
			if ( node != nullptr )
			{
				if ( node->data != nullptr )
				{
					delete node->data;
				}
				destroyNode( node->left );
				destroyNode( node->right );
				delete node;
			}
		}

		// ---------------------------------------------------------------------------
		// getBranchSize
		// Helper method for calculating the number of nodes within the branch
		// anchored by a given node.
		int getBranchSize( binary_search_tree_node* node ) const
		{
			int count = 0;

			if ( node != nullptr )
			{
				count = 1 + getBranchSize( node->left ) + getBranchSize( node->right );
			}

			return count;
		}

		// ---------------------------------------------------------------------------
		// getBranchHeight
		// Helper method for calculating the height of a branch anchored by a node.
		int getBranchHeight( binary_search_tree_node* node) const
		{
			int height = 0;

			if ( node != nullptr )
			{
				height = 1 +
					std::max( getBranchHeight( node->left ), getBranchHeight( node->right ) );
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
		void copyNode( binary_search_tree_node** dst, const binary_search_tree_node* source)
		{
			if ( ( dst != nullptr ) && ( source != nullptr ) )
			{
				NodeData* data = new NodeData( *( source->data ) );
				Node* node = createNode( data );
				*dst = node;
				copyNode( &node->left, source->left );
				copyNode( &node->right, source->right );
			}
		}

		// ---------------------------------------------------------------------------
		// areEqual
		// Helper method for checking recursively whether two tree branches are
		// equal. It compares all the nodes in the two branches and returns true
		// if, and only if, the equivalent nodes have matching data.
		bool areEqual( binary_search_tree_node* node1, binary_search_tree_node* node2) const
		{
			bool equal = false;

			if ( node1 == node2 )
			{
				// We end up here when both nodes are NULL or identical
				equal = true;
			}
			else if ( ( node1 != nullptr ) && ( node2 != nullptr ) &&
				( *( node1->data ) == *( node2->data ) ) )
			{
				// If nodes data match, we check their respective children
				if ( areEqual( node1->left, node2->left ) &&
					areEqual( node1->right, node2->right ) )
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
		T retrieve_item( binary_search_tree_node* rootNode, const binary_search_tree_node &targetData, binary_search_tree_node**) const
		{
			int depth = 0;

			if ( ( rootNode != nullptr ) && ( rootNode->data != nullptr ) )
			{
				if ( *( rootNode->data ) == targetData )
				{
					// We found our match
					depth++;
					if ( targetNode != nullptr )
					{
						*targetNode = rootNode;
					}
				}
				else
				{
					// Search left branch first and if unsuccessful
					// look into the right branch
					depth = findNode( rootNode->left, targetData, targetNode );
					if ( depth == 0 )
					{
						depth = findNode( rootNode->right, targetData, targetNode );
					}

					if ( depth != 0 )
					{
						// account for starting node
						depth++;
					}
				}
			}

			return depth;
		}

		void
		insert(
			std::unique_ptr< binary_search_tree_node > const & current,
			const Key key,
			const Value value )
		{
			if( !current )
			{
				current = std::make_unique< binary_search_tree_node >( key, value );
			}
			else if ( value > current->value )
			{
				this->insert( current->right, value );
			}
			else if ( value < current->value )
			{
				this->insert( current->left, value );
			}
		}

		//---------------------------------------------------------------------------
		// insertBalanced
		// Helper method for converting an ordered list of data into the current tree
		// such that the tree is as balanced as possible. The currently inserted node
		// (i.e. the local root) is recursively at mid = (low + high)/2 where low is
		// the lowest subscript of the array range and high is the highest.
		void insertBalanced( binary_search_tree_node** data, int low, int high)
		{
			if ( ( data != nullptr ) && ( low >= 0 ) && ( low <= high ) )
			{
				int mid = ( low + high ) / 2;

				if ( data[mid] != nullptr )
				{
					if ( !insert( data[mid] ) )
					{
						delete data[mid];
					}
					data[mid] = nullptr;
					insertBalanced( data, low, mid - 1 );
					insertBalanced( data, mid + 1, high );
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
		void preorderHelper(
			binary_search_tree_node* node, binary_search_tree_node** nodesData, int &index, bool removeData) const
		{
			traverseHelper( PREORDER, node, nodesData, index, removeData );
		}

		//---------------------------------------------------------------------------
		// inorderHelper
		// Helper method for recursive in-order traversal starting from a
		// reference node. Parameters:
		//  node            Reference node to start with
		//  nodesData       Traversal list
		//  index           Current position within the traversal list
		//  removeData      Whether to remove that data from tree while traversing
		void inorderHelper(
			binary_search_tree_node* node, binary_search_tree_node** nodesData, int &index, bool removeData) const
		{
			traverseHelper( INORDER, node, nodesData, index, removeData );
		}

		//---------------------------------------------------------------------------
		// postorderHelper
		// Helper method for recursive post-order traversal starting from a
		// reference node. Parameters:
		//  node            Reference node to start with
		//  nodesData       Traversal list
		//  index           Current position within the traversal list
		//  removeData      Whether to remove that data from tree while traversing
		void postorderHelper(
			binary_search_tree_node* node, binary_search_tree_node** nodesData, int &index, bool removeData) const
		{
			traverseHelper( POSTORDER, node, nodesData, index, removeData );
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
		void traverseHelper(
			int traverseType,
			binary_search_tree_node* node,
			binary_search_tree_node** nodesData,
			int &index,
			bool removeData) const
		{
			if ( ( node != nullptr ) && ( nodesData != nullptr ) && ( index >= 0 ) )
			{
				if ( traverseType == PREORDER )
				{
					nodesData[index++] = node->data;
				}

				if ( node->left != nullptr )
				{
					traverseHelper(
						traverseType, node->left, nodesData, index, removeData );
				}

				if ( traverseType == INORDER )
				{
					nodesData[index++] = node->data;
				}

				if ( node->right != nullptr )
				{
					traverseHelper(
						traverseType, node->right, nodesData, index, removeData );
				}

				if ( traverseType == POSTORDER )
				{
					nodesData[index++] = node->data;
				}

				if ( removeData )
				{
					node->data = nullptr;
				}
			}
		}

		std::unique_ptr< binary_search_tree_node > root;
	};
}
