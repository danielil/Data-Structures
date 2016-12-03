/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 *
 * A doubly-linked implementation of a list combining both stack (LIFO) and queue (FIFO) operations.
 *
 * All insertions (push_front, push_back) and removals (pop_front, pop_back) are done in constant time
 * since no traversal is done for these operations.
 *
 * STL-style iterators for the list are also implemented. Mutable and const iterators share
 * the same implementation through template logic to determine constness.
 *
 * The previous and next links of the doubly linked list node are held by std::weak_ptr and
 * std::shared_ptr, respectively. Since the previous link is held by a std::weak_ptr, forward
 * iteration may be faster than reverse iteration. This is due to the construction of a new
 * std::shared_ptr from std::weak_ptr links on every node iterated. However, this tradeoff
 * is acceptable in contrast to potential memory leaks from not manually resetting double
 * linkage to a single node. This would occur if the previous node were an std::shared_ptr
 * instead of a std::weak_ptr.
 */

#pragma once

#include "doubly_linked_node.hpp"

namespace dsa
{
	template < typename T >
	class doubly_linked_list
	{
	public:

		// Iterator class for both mutable and const iterators.
		template< bool IsConstIterator >
		class iterator_impl
		{
		public:

			using iterator_category = std::bidirectional_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = typename std::conditional< IsConstIterator, T const * const, T >::type;
			using reference = typename std::conditional< IsConstIterator, T const &, T >::type;

			iterator_impl( const std::shared_ptr< doubly_linked_node< T > > node ) :
				node( node )
			{
			}

			iterator_impl( iterator_impl< false > const & it ) :
				node( it.node )
			{
			}

			/**
			 * Copy construction for const iterators is handled by the default
			 * generated implementation. The copy constructor specialization for
			 * mutable iterators allows for the conversion from mutable to const.
			 */
			iterator_impl& operator=( iterator_impl< false > const & it )
			{
				this->node = it.node;

				return *this;
			}

			void
			swap( iterator_impl& it )
			{
				std::swap( this->node, it.node );
			}

			iterator_impl&
			operator++()
			{
				this->node = this->node->next;

				return *this;
			}

			iterator_impl
			operator++( int )
			{
				const iterator_impl iterator( *this );
				++( *this );

				return iterator;
			}

			iterator_impl&
			operator--()
			{
				this->node = this->node->previous.lock();

				return *this;
			}

			iterator_impl
			operator--( int )
			{
				const iterator_impl iterator ( *this );
				--( *this );

				return iterator;
			}

			reference
			operator*() const
			{
				return this->node->item;
			}

			pointer
			operator->() const
			{
				return this->node;
			}

			bool
			operator==( iterator_impl const & it ) const
			{
				if ( !this->node &&
					 !it.node )
				{
					return true;
				}

				if ( !it.node )
				{
					return false;
				}

				return ( *( this->node ) == *( it.node ) );
			}

			bool
			operator!=( iterator_impl const & it ) const
			{
				return !( *this == it );
			}

		private:
			std::shared_ptr< doubly_linked_node< T > > node;
		};

		// Iterator class for both mutable and const reverse iterators.
		template< bool IsConstIterator >
		class reverse_iterator_impl
		{
		public:

			using iterator_category = std::bidirectional_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = typename std::conditional< IsConstIterator, T const * const, T >::type;
			using reference = typename std::conditional< IsConstIterator, T const &, T >::type;

			reverse_iterator_impl( const std::shared_ptr< doubly_linked_node< T > > node ) :
				node( node )
			{
			}

			reverse_iterator_impl( reverse_iterator_impl< false > const & it ) :
				node( it.node )
			{
			}

			reverse_iterator_impl& operator=( reverse_iterator_impl< false > const & it )
			{
				this->node = it.node;

				return *this;
			}

			void
			swap( reverse_iterator_impl& it )
			{
				std::swap( this->node, it.node );
			}

			reverse_iterator_impl&
			operator++()
			{
				this->node = this->node->previous.lock();

				return *this;
			}

			reverse_iterator_impl
			operator++( int )
			{
				const reverse_iterator_impl iterator( *this );
				++( *this );

				return iterator;
			}

			reverse_iterator_impl&
			operator--()
			{
				this->node = this->node->next;

				return *this;
			}

			reverse_iterator_impl
			operator--( int )
			{
				const reverse_iterator_impl iterator( *this );
				--( *this );

				return iterator;
			}

			reference
			operator*() const
			{
				return this->node->item;
			}

			pointer
			operator->() const
			{
				return this->node;
			}

			bool
			operator==( reverse_iterator_impl const & it )
			{
				if ( !this->node &&
					 !it.node )
				{
					return true;
				}

				if ( !it.node )
				{
					return false;
				}

				return ( *( this->node ) == *( it.node ) );
			}

			bool
			operator!=( reverse_iterator_impl const & it )
			{
				return !( *this == it );
			}

		private:

			std::shared_ptr< doubly_linked_node< T > > node;
		};

		using value_type = T;
		using pointer = T*;
		using const_pointer = T const * const;
		using reference = T&;
		using const_reference = T const &;

		using iterator = iterator_impl< false >;
		using const_iterator = iterator_impl< true >;
		using reverse_iterator = reverse_iterator_impl< false >;
		using const_reverse_iterator = reverse_iterator_impl< true >;

		doubly_linked_list() = default;
		~doubly_linked_list() noexcept = default;

		doubly_linked_list( doubly_linked_list const & other )
		{
			auto node = other.front;

			while ( node )
			{
				this->push_back( node->item );
				node = node->next;
			}
		}

		doubly_linked_list( doubly_linked_list&& other ) noexcept
		{
			auto node = std::move( other.front );

			while ( node )
			{
				this->push_back( node->item );
				node = std::move( node->next );
			}

			// Since a node's previous link is a std::weak_ptr, there is always
			// a single weak reference and a single strong reference to the
			// front node. As a result, the front node doesn't need to be
			// explicitly cleared. The default destructor would work here.
			//
			// On the other hand, since the next link of a node is a std::shared_ptr,
			// there are always two strong references to the back node. That is, the
			// back node itself and its previous link pointing to it. As a result,
			// the back node needs to be explicitly cleared.
			other.back = nullptr;
			other.nodes = 0;
		}

		auto&
		operator=( doubly_linked_list rhs )
		{
			this->swap( *this, rhs );

			return *this;
		}

		auto&
		operator+( doubly_linked_list const & rhs )
		{
			return *this += rhs;
		}

		auto&
		operator+=( doubly_linked_list const & rhs )
		{
			if ( !rhs.empty() )
			{
				auto node = rhs.front;

				while ( node )
				{
					this->push_back( node->item );

					node = node->next;
				}
			}

			return *this;
		}

		bool
		operator==( doubly_linked_list const & rhs ) const noexcept
		{
			return this->equals( this->front, rhs.front );
		}

		bool
		operator!=( doubly_linked_list const & rhs ) const noexcept
		{
			return !( *this == rhs );
		}

		friend void
		swap( doubly_linked_list& first, doubly_linked_list& second ) noexcept
		{
			using std::swap;

			swap( first.front, second.front );
			swap( first.back, second.back );
			swap( first.nodes, second.nodes );
		}

		void
		push_front( const T item )
		{
			const auto new_node = std::make_shared< doubly_linked_node< T > >( item );

			if ( this->empty() )
			{
				this->front = new_node;
				this->back = new_node;
			}
			else
			{
				new_node->next = this->front;

				this->front->previous = new_node;
				this->front = new_node;
			}

			++( this->nodes );
		}

		void
		push_back( const T item )
		{
			const auto new_node = std::make_shared< doubly_linked_node< T > >( item );

			if ( this->empty() )
			{
				this->front = new_node;
				this->back = new_node;
			}
			else
			{
				new_node->previous = this->back;

				this->back->next = new_node;
				this->back = new_node;
			}

			++( this->nodes );
		}

		auto
		pop_front()
		{
			if ( this->empty() )
			{
				return T();
			}

			const T item = this->front->item;
			auto& next_node = this->front->next;

			if ( next_node )
			{
				this->front = std::move( next_node );
			}
			else
			{
				this->front = nullptr;
				this->back = nullptr;
			}

			--( this->nodes );

			return item;
		}

		auto
		pop_back()
		{
			if ( this->empty() )
			{
				return T();
			}

			const T item = this->back->item;
			auto& previous_node = this->back->previous;

			if ( !previous_node.expired() )
			{
				this->back = std::move( previous_node.lock() );
				this->back->next = nullptr;
			}
			else
			{
				this->front = nullptr;
				this->back = nullptr;
			}

			--( this->nodes );

			return item;
		}

		void
		clear() noexcept
		{
			if ( !this->empty() )
			{
				while ( !this->front )
				{
					auto& next_node = this->front->next;

					if ( next_node )
					{
						this->front = std::move( next_node );
					}
				}

				this->front = nullptr;
				this->back = nullptr;
				this->nodes = 0;
			}
		}

		auto
		peek_front() const noexcept
		{
			if ( this->empty() )
			{
				return T();
			}

			return this->front->item;
		}

		auto
		peek_back() const noexcept
		{
			if ( this->empty() )
			{
				return T();
			}

			return this->back->item;
		}

		auto
		size() const noexcept
		{
			return this->nodes;
		}

		bool
		empty() const noexcept
		{
			return ( ( !this->front ) &&
					 ( !this->back ) &&
					 ( this->nodes == 0 ) );
		}

		auto
		begin() noexcept
		{
			return iterator( this->first() );
		}

		auto
		end() noexcept
		{
			return iterator( this->next( this->last() ) );
		}

		auto
		rbegin() noexcept
		{
			return reverse_iterator( this->last() );
		}

		auto
		rend() noexcept
		{
			return reverse_iterator( this->previous( this->first() ) );
		}

		auto
		begin() const noexcept
		{
			return const_iterator( this->first() );
		}

		auto
		end() const noexcept
		{
			return const_iterator( this->next( this->last() ) );
		}

		auto
		rbegin() const noexcept
		{
			return const_reverse_iterator( this->last() );
		}

		auto
		rend() const noexcept
		{
			return const_reverse_iterator( this->previous( this->first() ) );
		}

		auto
		cbegin() const noexcept
		{
			return const_iterator( this->begin() );
		}

		auto
		cend() const noexcept
		{
			return const_iterator( this->end() );
		}

		auto
		crbegin() const noexcept
		{
			return const_reverse_iterator( this->rbegin() );
		}

		auto
		crend() const noexcept
		{
			return const_reverse_iterator( this->rend() );
		}

	private:

		bool
		equals(
			std::shared_ptr< doubly_linked_node< T > > const & node1,
			std::shared_ptr< doubly_linked_node< T > > const & node2 ) const noexcept
		{
			if ( !node1 && !node2 )
			{
				return true;
			}

			if ( !node1 || !node2 )
			{
				return false;
			}

			if ( node1->item == node2->item )
			{
				return this->equals( node1->next, node2->next );
			}

			return false;
		}

		auto
		first() const noexcept
		{
			return this->front;
		}

		auto
		last() const noexcept
		{
			return this->back;
		}

		auto
		next( std::shared_ptr< doubly_linked_node< T > > const & current ) const noexcept
		{
			return current->next;
		}

		auto
		previous( std::shared_ptr< doubly_linked_node< T > > const & current ) const noexcept
		{
			return current->previous.lock();
		}

		std::shared_ptr< doubly_linked_node< T > > front = nullptr;
		std::shared_ptr< doubly_linked_node< T > > back = nullptr;

		std::size_t nodes = 0;
	};

	template < typename T >
	auto
	operator+( doubly_linked_list< T > const & lhs, doubly_linked_list< T > const & rhs )
	{
		doubly_linked_list< T > result( lhs );

		return result += rhs;
	}
}
