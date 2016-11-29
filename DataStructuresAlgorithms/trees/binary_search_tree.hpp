/**
 * Daniel Sebastian Iliescu
 */

#pragma once

#include <memory>

namespace dsa
{
	class node;

	template < typename T >
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
		get_depth( const node& data ) const
		{
			return this->find_node( this->root, data, nullptr );
		}

		void clear()
		{
			// Might be defaulted
		}

		bool operator==( const binary_search_tree& other ) const
		{
			bool equal = true;

			if ( this != &other )
			{
				equal = areEqual( root, other.root );
			}

			return equal;
		}

		bool operator!=( const binary_search_tree& other ) const
		{

		}

		// Oputput operator
		friend std::ostream& operator<<( std::ostream& os, const BinTree& obj )
		{
			bool equal = ( *this == other );
			return !equal;
		}

		// Tree operations
		bool insert( NodeData* data )
		{
			bool success = false;

			if ( data != nullptr )
			{
				if ( root == nullptr )
				{
					root = createNode( data );
					success = true;
				}
				else
				{
					success = insertHelper( root, data );
				}
			}

			return success;
		}
		bool retrieve( const NodeData &refData, NodeData* &data ) const
		{
			Node* node = nullptr;

			if ( findNode( root, refData, &node ) > 0 )
			{
				data = node->data;
				return true;
			}
			else
			{
				data = nullptr;
				return false;
			}
		}

		// Recursive tree traversal
		NodeData** preorderTraverse() const
		{
			NodeData** nodesData = createDataArray();

			if ( nodesData != nullptr )
			{
				int index = 0;
				preorderHelper( root, nodesData, index, false );
			}

			return nodesData;
		}

		NodeData** inorderTraverse() const
		{
			NodeData** nodesData = createDataArray();

			if ( nodesData != nullptr )
			{
				int index = 0;
				inorderHelper( root, nodesData, index, false );
			}

			return nodesData;
		}

		NodeData** postorderTraverse() const
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
		void bstreeToArray( NodeData* nodesData[] )
		{
			if ( !isEmpty() && ( nodesData != nullptr ) )
			{
				int index = 0;
				inorderHelper( root, nodesData, index, true );
			}
			makeEmpty();
		}
		void arrayToBSTree( NodeData* nodesData[] )
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
		NodeData** createDataArray() const
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
		Node* createNode( NodeData* data ) const
		{
			Node* node = new Node();
			if ( data != nullptr )
			{
				node->data = data;
			}
			else
			{
				node->data = new NodeData();
			}
			node->left = nullptr;
			node->right = nullptr;

			return node;
		}
		void destroyNode( Node* node )
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
		int getBranchSize( Node* node ) const
		{
			int count = 0;

			if ( node != nullptr )
			{
				count = 1 + getBranchSize( node->left ) + getBranchSize( node->right );
			}

			return count;
		}
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

		struct node
		{
			node() = default;

			node( T item ) :
				item( item )
			{
			}

			~node() = default;

			node( const doubly_linked_node& ) = default;
			node( node&& ) noexcept = default;
			node& operator=( const node& ) = default;
			node& operator=( node&& ) noexcept = default;

			bool
			operator==( const node& rhs ) const
			{
				return ( this->item == rhs.item );
			}

			bool
			operator!=( const node& rhs ) const
			{
				return !( *this == rhs );
			}

			T item = T();

			std::shared_ptr< node > parent = nullptr;
			std::shared_ptr< node > left = nullptr;
			std::shared_ptr< node > right = nullptr;
		};

		std::shared_ptr< node > root;
	};
}
