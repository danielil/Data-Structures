/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 *
 * Node for the doubly linked list.
 */

#pragma once

#include <memory>

namespace dsa
{
	template < typename T >
	struct doubly_linked_node
	{
		doubly_linked_node() = default;
		doubly_linked_node( T input_item ) :
			item( input_item )
		{
		}
		~doubly_linked_node() = default;

		doubly_linked_node( doubly_linked_node const & ) = default;
		doubly_linked_node( doubly_linked_node && ) noexcept = default;

		doubly_linked_node & operator=( doubly_linked_node const & ) = default;
		doubly_linked_node & operator=( doubly_linked_node && ) noexcept = default;

		bool
		operator==( doubly_linked_node const & rhs ) const
		{
			return ( this->item == rhs.item );
		}

		bool
		operator!=( doubly_linked_node const & rhs ) const
		{
			return !( *this == rhs );
		}

		T item = T();

		std::weak_ptr< doubly_linked_node > previous;
		std::shared_ptr< doubly_linked_node > next = nullptr;
	};
}
