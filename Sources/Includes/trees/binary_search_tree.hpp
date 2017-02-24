/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "binary_search_tree_node.hpp"

#include <memory>
#include <functional>

#include <iostream>

namespace dsa
{
	template <
		typename Key,
		typename Value >
	class binary_search_tree
	{

	public:
		using node_type = std::unique_ptr< binary_search_tree_node< Key, Value > >;

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

		void
		insert(
			const Key key,
			const Value value )
		{
			this->insert( this->root, key, value );
		}

		void
		erase( const Key key )
		{
			this->erase( this->root, key );
		}

		bool
		contains( const Key key )
		{
			return this->contains( this->root, key );
		}

		std::size_t
		calculated_size()
		{
			std::size_t calculated_nodes = 0;

			this->preorder( this->root, [&calculated_nodes](const auto&)
			{
				++calculated_nodes;
			});

			return calculated_nodes;
		}

		std::size_t
		height()
		{
			const auto height = this->height( this->root );

			return ( height == 0 ) ? height : height - 1;
		}

		bool
		balanced()
		{
			return this->balanced( this->root );
		}

		bool
		empty() const
		{
			return ( !this->root && !this->nodes );
		}

		auto
		size() const
		{
			return this->nodes;
		}

		void
		preorder( std::function< void( node_type const & ) >&& callback )
		{
			this->preorder( this->root, std::move( callback ) );
		}

		void
		inorder( std::function< void( node_type const & ) >&& callback )
		{
			this->inorder( this->root, std::move( callback ) );
		}

		void
		postorder( std::function< void( node_type const & ) >&& callback )
		{
			this->postorder( this->root, std::move( callback ) );
		}

	private:

		auto
		create_node(
			const Key key,
			const Value value )
		{
			return std::make_unique< binary_search_tree_node< Key, Value > >( key, value );
		}

		void
		insert(
			node_type& current,
			const Key key,
			const Value value )
		{
			if( !current )
			{
				current = this->create_node( key, value );

				++( this->nodes );
			}
			else if ( key > current->key )
			{
				this->insert( current->right, key, value );
			}
			else if ( key < current->key )
			{
				this->insert( current->left, key, value );
			}
		}

		void
		erase(
			node_type& current,
			const Key key )
		{
			if ( current )
			{
				if ( key == current->key )
				{
					if ( !current->left && !current->right )
					{
						current = nullptr;
						--nodes;
					}
					else if ( current->left && !current->right )
					{
						current = std::move( current->left );
						--nodes;
					}
					else if ( current->right && !current->left )
					{
						current = std::move( current->right );
						--nodes;
					}
					else
					{
						const binary_search_tree_node<Key, Value> temp_node = this->find_max( current->left );

						current->key = temp_node.key;
						current->value = temp_node.value;

						this->erase( current->left, current->key );
					}
				}
				else if ( key > current->key )
				{
					this->erase( current->right, key );
				}
				else if ( key < current->key )
				{
					this->erase( current->left, key );
				}
			}
		}

		binary_search_tree_node<Key, Value>
		find_max( node_type& current )
		{
			if ( current )
			{
				auto* node = current.get();

				while ( node->right )
				{
					node = node->right.get();
				}

				return binary_search_tree_node<Key, Value>( node->key, node->value );
			}

			return binary_search_tree_node<Key, Value>();
		}

		bool
		contains(
			node_type& current,
			const Key key )
		{
			if ( current )
			{
				if ( key == current->key )
				{
					return true;
				}
				else if ( key > current->key )
				{
					return this->contains( current->right, key );
				}
				else if ( key < current->key )
				{
					return this->contains( current->left, key );
				}
			}

			return false;
		}

		std::size_t
		height( node_type& current )
		{
			if ( current )
			{
				return 1 + std::max( this->height( current->left ), this->height( current->right ));
			}

			return 0;
		}

		bool
		balanced( node_type& current )
		{
			if ( current )
			{
				if ( this->balanced( current->left ) && this->balanced( current->right ) )
				{
					const auto left_subtree_height = static_cast<int>( this->height( current->left ) );
					const auto right_subtree_height = static_cast<int>( this->height( current->right ) );

					return ( std::abs( left_subtree_height - right_subtree_height ) <= 1 );
				}

				return false;
			}

			return true;
		}

		void
		preorder(
			node_type& current,
			std::function< void( node_type const & ) >&& callback )
		{
			if ( current )
			{
				callback( current );

				this->preorder( current->left, std::move( callback ) );
				this->preorder( current->right, std::move( callback ) );
			}
		}

		void
		inorder(
			node_type& current,
			std::function< void( node_type const & ) >&& callback )
		{
			if ( current )
			{
				this->inorder( current->left, std::move( callback ) );

				callback( current );

				this->inorder( current->right, std::move( callback ) );
			}
		}

		void
		postorder(
			node_type& current,
			std::function< void( node_type const & ) >&& callback )
		{
			if ( current )
			{
				this->preorder( current->left, std::move( callback ) );
				this->preorder( current->right, std::move( callback ) );

				callback( current );
			}
		}

		node_type root;
		std::size_t nodes = 0;
	};
}
