/**
 * @author Daniel Sebastian Iliescu
 */

#pragma once

#include <memory>

namespace dsa
{
	template <
		typename Key,
		typename Value >
	struct binary_search_tree_node
	{
		binary_search_tree_node() = default;

		binary_search_tree_node(
			Key input_key,
			Value input_value ) :
			key( input_key ),
			value( input_value )
		{
		}

		~binary_search_tree_node() = default;

		binary_search_tree_node( const binary_search_tree_node& ) = default;
		binary_search_tree_node( binary_search_tree_node&& ) noexcept = default;

		binary_search_tree_node& operator=( const binary_search_tree_node& ) = default;
		binary_search_tree_node& operator=( binary_search_tree_node&& ) noexcept = default;

		bool
		operator==( const binary_search_tree_node& rhs ) const
		{
			return ( this->value == rhs.value );
		}

		bool
		operator!=( const binary_search_tree_node& rhs ) const
		{
			return !( *this == rhs );
		}

		Key key = T();
		Value value = T();

		std::unique_ptr< binary_search_tree_node > left;
		std::unique_ptr< binary_search_tree_node > right;
	};
}
