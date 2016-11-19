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

		bool empty() const
		{
			return this->root;
		}

		std::size_t get_tree_size() const
		{
			return this->get_branch_size( this->root );
		}

		std::size_t get_tree_height() const
		{
			return this->get_branch_height( this->root );
		}

		std::size_t get_depth( const node& data ) const
		{
			return this->find_node( this->root, data, nullptr );
		}

		void clear()
		{
			// Might be defaulted
		}

		bool operator==( const binary_search_tree& other ) const;
		bool operator!=( const binary_search_tree& other ) const;

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

			std::shared_ptr< node > left = nullptr;
			std::shared_ptr< node > right = nullptr;
		};

		std::shared_ptr< node > root;
	};
}
