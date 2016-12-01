/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 *
 * A doubly-linked implementation of a list combining both stack (LIFO) and queue (FIFO) operations.
 *
 * All insertions (push_front, push_back) and removals (pop_front, pop_back) are done in O(1) complexity
 * since no traversal is done for these operations.
 *
 * Custom STL-style iterators for the list are also implemented. Mutable and const iterators share 
 * the same implementation through compile-time logic.
 *
 * Two std::shared_ptr are used to keep track of the previous and next nodes. A better candidate for
 * one of these nodes might have been an std::weak_ptr since we don't actually need to keep track of 
 * two strong references to the same node (one strong and one weak reference would work). However,
 * trivial tasks such as forward or backward (depending on which node is the weak reference) 
 * iterations would be slowed down due to the construction of a new std::shared_ptr for every iterated
 * nodes.
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
		template< bool is_const_iterator >
		class iterator_impl
		{
		public:

			using iterator_category = std::bidirectional_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = typename std::conditional< is_const_iterator, T const * const, T >::type;
			using reference = typename std::conditional< is_const_iterator, T const &, T >::type;

			iterator_impl( doubly_linked_node< T >* const node ) :
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
				this->node = this->node->next.get();

				return *this;
			}

			iterator_impl
			operator++( int )
			{
				iterator_impl const iterator( *this );
				++( *this );

				return iterator;
			}

			iterator_impl&
			operator--()
			{
				this->node = this->node->previous.get();

				return *this;
			}

			iterator_impl
			operator--( int )
			{
				iterator_impl const iterator ( *this );
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
				if ( nullptr == this->node &&
					 nullptr == it.node )
				{
					return true;
				}

				if ( nullptr == it.node )
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
			doubly_linked_node< T >* node;
		};

		// Iterator class for both mutable and const reverse iterators.
		template< bool is_const_iterator >
		class reverse_iterator_impl
		{
		public:

			using iterator_category = std::bidirectional_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = typename std::conditional< is_const_iterator, T const * const, T >::type;
			using reference = typename std::conditional< is_const_iterator, T const &, T >::type;

			reverse_iterator_impl( doubly_linked_node< T >* const node ) :
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
				this->node = this->node->previous.get();

				return *this;
			}

			reverse_iterator_impl
			operator++( int )
			{
				reverse_iterator_impl const iterator( *this );
				++( *this );

				return iterator;
			}

			reverse_iterator_impl&
			operator--()
			{
				this->node = this->node->next.get();

				return *this;
			}

			reverse_iterator_impl
			operator--( int )
			{
				reverse_iterator_impl const iterator( *this );
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
				if ( nullptr == this->node &&
					 nullptr == it.node )
				{
					return true;
				}

				if ( nullptr == it.node )
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

			doubly_linked_node< T > * node;
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
			auto node = other.back;

			while ( node )
			{
				this->push_back( node->item );
				node = node->next;
			}
		}

		doubly_linked_list( doubly_linked_list&& other ) noexcept :
			front( std::move( other.front ) ),
			back( std::move( other.back ) ),
			nodes( other.nodes )
		{
			other.nodes = 0;
		}

		doubly_linked_list&
		operator=( doubly_linked_list rhs )
		{
			this->swap( *this, rhs );

			return *this;
		}

		doubly_linked_list&
		operator+( doubly_linked_list const & rhs )
		{
			return *this += rhs;
		}

		doubly_linked_list&
		operator+=( doubly_linked_list const & rhs )
		{
			if ( !rhs.empty() )
			{
				std::shared_ptr< doubly_linked_node< T > > node = rhs.back;

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
			return this->equals( this->back.get(), rhs.back.get() );
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
		push_front( T const item )
		{
			auto newNode = std::make_shared< doubly_linked_node< T > >( item );

			if ( this->empty() )
			{
				this->back = newNode;
				this->front = newNode;
			}
			else
			{
				newNode->next = this->back;

				this->back->previous = newNode;
				this->back = newNode;
			}

			++( this->nodes );
		}

		void
		push_back( T const item )
		{
			auto newNode = std::make_shared< doubly_linked_node< T > >( item );

			if ( this->empty() )
			{
				this->front = newNode;
				this->back = newNode;
			}
			else
			{
				newNode->previous = this->front;

				this->front->next = newNode;
				this->front = newNode;
			}

			++( this->nodes );
		}

		T
		pop_front()
		{
			if ( this->empty() )
			{
				return T();
			}

			T item = this->front->item;
			auto previousNode = std::move( this->front->previous );

			if ( previousNode )
			{
				previousNode->next = nullptr;

				this->front = std::move( previousNode );
			}
			else
			{
				this->front = nullptr;
				this->back = nullptr;
			}

			--( this->nodes );

			return item;
		}

		T
		pop_back()
		{
			if ( this->empty() )
			{
				return T();
			}

			T item = this->back->item;
			auto nextNode = std::move( this->back->next );

			if ( nextNode )
			{
				nextNode->previous = nullptr;

				this->back = std::move( nextNode );
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
			while ( !this->empty() )
			{
				this->blank_pop_front();
			}
		}

		T
		peek_front() const noexcept
		{
			if ( this->empty() )
			{
				return T();
			}

			return this->front->item;
		}

		T
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

		iterator
		begin() noexcept
		{
			return iterator( this->first() );
		}

		iterator
		end() noexcept
		{
			return iterator( this->next( this->last() ) );
		}

		reverse_iterator
		rbegin() noexcept
		{
			return reverse_iterator( this->last() );
		}

		reverse_iterator
		rend() noexcept
		{
			return reverse_iterator( this->previous( this->first() ) );
		}

		const_iterator
		begin() const noexcept
		{
			return const_iterator( this->first() );
		}

		const_iterator
		end() const noexcept
		{
			return const_iterator( this->next( this->last() ) );
		}

		const_reverse_iterator
		rbegin() const noexcept
		{
			return const_reverse_iterator( this->last() );
		}

		const_reverse_iterator
		rend() const noexcept
		{
			return const_reverse_iterator( this->previous( this->first() ) );
		}

		const_iterator
		cbegin() const noexcept
		{
			return this->begin();
		}

		const_iterator
		cend() const noexcept
		{
			return this->end();
		}

		const_reverse_iterator
		crbegin() const noexcept
		{
			return this->rbegin();
		}

		const_reverse_iterator
		crend() const noexcept
		{
			return this->rend();
		}

	private:

		void
		blank_pop_front() noexcept
		{
			if ( !this->empty() )
			{
				auto previousNode = std::move( this->front->previous );

				if ( previousNode )
				{
					previousNode->next = nullptr;

					this->front = std::move( previousNode );
				}
				else
				{
					this->front = nullptr;
					this->back = nullptr;
				}

				--( this->nodes );
			}
		}

		bool
		equals(
			doubly_linked_node< T > const * const node1,
			doubly_linked_node< T > const * const node2 ) const noexcept
		{
			if ( nullptr == node1 &&
				 nullptr == node2 )
			{
				return true;
			}

			if ( nullptr == node1 ||
				 nullptr == node2 )
			{
				return false;
			}

			if ( node1->item == node2->item )
			{
				return this->equals( node1->next.get(), node2->next.get() );
			}

			return false;
		}

		auto
		first() const noexcept
		{
			return this->back.get();
		}

		auto
		last() const noexcept
		{
			return this->front.get();
		}

		auto
		next( doubly_linked_node< T > const * const current ) const noexcept
		{
			return current->next.get();
		}

		auto
		previous( doubly_linked_node< T > const * const current ) const noexcept
		{
			return current->previous.get();
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
