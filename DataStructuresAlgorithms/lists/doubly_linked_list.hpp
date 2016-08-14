/**
 * Author: Daniel Sebastian Iliescu
 *
 * A doubly-linked implementation of a list combining both stack (LIFO) and queue (FIFO) operations.
 *
 * All insertions (push_front, push_back) and removal (pop_front, pop_back) are done in O(1) complexity
 * since no traversal is done for these operations.
 *
 * Custom STL-style iterators for the list are also implemented.
 */

#pragma once

#include <memory>

namespace dsa
{
	template < typename T >
	class doubly_linked_list
	{
	public:

		using value_type = T;

		template < typename T >
		struct doubly_linked_node
		{
			doubly_linked_node() = default;

			doubly_linked_node( T item ) :
				item( item )
			{
			}

			~doubly_linked_node() = default;

			doubly_linked_node( const doubly_linked_node& ) = default;
			doubly_linked_node( doubly_linked_node&& ) noexcept = default;
			doubly_linked_node& operator=( const doubly_linked_node& ) = default;
			doubly_linked_node& operator=( doubly_linked_node&& ) noexcept = default;

			bool
				operator==( const doubly_linked_node& rhs ) const
			{
				return ( this->item == rhs.item );
			}

			bool
				operator!=( const doubly_linked_node& rhs ) const
			{
				return !( *this == rhs );
			}

			T item = T();

			std::shared_ptr< doubly_linked_node< T > > previous = nullptr;
			std::shared_ptr< doubly_linked_node< T > > next = nullptr;
		};

		class iterator : public std::iterator< std::bidirectional_iterator_tag, T, std::ptrdiff_t, T*, T& >
		{
		public:
			friend class doubly_linked_list;
			friend class const_iterator;

			iterator( std::weak_ptr< doubly_linked_node< T > > node ) :
				node( node )
			{
			}

			iterator( const iterator& it ) :
				node( it.node )
			{
			}

			iterator&
			operator=( const iterator& it )
			{
				this->node = it.node;

				return *this;
			}

			iterator&
			operator++()
			{
				this->node = this->node.lock()->next;

				return *this;
			}

			iterator
			operator++( int )
			{
				iterator iterator( *this );
				++( *this );

				return iterator;
			}

			iterator&
			operator--()
			{
				this->node = this->node.lock()->previous;

				return *this;
			}

			iterator
			operator--( int )
			{
				iterator iterator( *this );
				--( *this );

				return iterator;
			}

			T
			operator*() const
			{
				return this->node.lock()->item;
			}

			doubly_linked_node< T >*
			operator->() const
			{
				return this->node.lock().get();
			}

			bool
			operator==( const iterator& it )
			{
				if ( this->node.expired() && 
					 it.node.expired() )
				{
					return true;
				}

				if ( it.node.expired() )
				{
					return false;
				}

				return ( *( this->node.lock() ) == *( it.node.lock() ) );
			}

			bool
			operator!=( const iterator& it )
			{
				return !( *this == it );
			}

		private:
			std::weak_ptr< doubly_linked_node< T > > node;
		};

		class const_iterator : public std::iterator< std::bidirectional_iterator_tag, T, T*, T& >
		{
		public:
			friend class doubly_linked_list;
			friend class iterator;

			const_iterator( std::weak_ptr< doubly_linked_node< T > > node ) :
				node( node )
			{
			}

			const_iterator( const const_iterator& it ) :
				node( it.node )
			{
			}

			const_iterator( const iterator& it ) :
				node( it.node )
			{
			}

			const_iterator&
			operator=( const const_iterator& it )
			{
				this->node = it.node;

				return *this;
			}

			const_iterator&
			operator=( const iterator& it )
			{
				this->node = it.node;

				return *this;
			}

			const_iterator& 
			operator++()
			{
				this->node = this->node.lock()->next;

				return *this;
			}

			const_iterator
			operator++( int )
			{
				const_iterator iterator( *this );
				++( *this );

				return iterator;
			}

			const_iterator&
			operator--()
			{
				this->node = this->node.lock()->previous;

				return *this;
			}

			const_iterator
			operator--( int )
			{
				const_iterator iterator( *this );
				--( *this );

				return iterator;
			}

			const T
			operator*() const
			{
				return this->node.lock()->item;
			}

			const doubly_linked_node< T >*
			operator->() const
			{
				return this->node.lock().get();
			}

			bool
			operator==( const const_iterator& it ) const
			{
				if ( this->node.expired() && 
					 it.node.expired() )
				{
					return true;
				}

				if ( it.node.expired() )
				{
					return false;
				}

				return ( *( this->node.lock() ) == *( it.node.lock() ) );
			}

			bool
			operator!=( const const_iterator& it ) const
			{
				return !( *this == it );
			}

		private:
			std::weak_ptr< doubly_linked_node< T > > node;
		};

		class reverse_iterator : public std::iterator< std::bidirectional_iterator_tag, T, T*, T& >
		{
		public:
			friend class doubly_linked_list;
			friend class const_reverse_iterator;

			reverse_iterator( std::weak_ptr< doubly_linked_node< T > > node ) :
				node( node )
			{
			}

			reverse_iterator( const reverse_iterator& it ) :
				node( it.node )
			{
			}

			reverse_iterator&
			operator=( const reverse_iterator& it )
			{
				this->node = it.node;

				return *this;
			}

			reverse_iterator&
			operator++()
			{
				this->node = this->node.lock()->previous;

				return *this;
			}

			reverse_iterator
			operator++( int )
			{
				reverse_iterator iterator( *this );
				++( *this );

				return iterator;
			}

			reverse_iterator&
			operator--()
			{
				this->node = this->node.lock()->next;

				return *this;
			}

			reverse_iterator
			operator--( int )
			{
				iterator iterator( *this );
				--( *this );

				return iterator;
			}

			T
			operator*() const
			{
				return this->node.lock()->item;
			}

			doubly_linked_node< T >*
			operator->() const
			{
				return this->node.lock().get();
			}

			bool
			operator==( const reverse_iterator& it )
			{
				if ( this->node.expired() && 
					 it.node.expired() )
				{
					return true;
				}

				if ( it.node.expired() )
				{
					return false;
				}

				return ( *( this->node.lock() ) == *( it.node.lock() ) );
			}

			bool
			operator!=( const reverse_iterator& it )
			{
				return !( *this == it );
			}

		private:
			std::weak_ptr< doubly_linked_node< T > > node;
		};

		class const_reverse_iterator : public std::iterator< std::bidirectional_iterator_tag, T, T*, T& >
		{
		public:
			friend class doubly_linked_list;
			friend class iterator;

			const_reverse_iterator( std::weak_ptr< doubly_linked_node< T > > node ) :
				node( node )
			{
			}

			const_reverse_iterator( const const_reverse_iterator& it ) :
				node( it.node )
			{
			}

			const_reverse_iterator( const reverse_iterator& it ) :
				node( it.node )
			{
			}

			const_reverse_iterator&
			operator=( const const_reverse_iterator& it )
			{
				this->node = it.node;

				return *this;
			}

			const_reverse_iterator&
			operator=( const reverse_iterator& it )
			{
				this->node = it.node;

				return *this;
			}

			const_reverse_iterator&
			operator++()
			{
				this->node = this->node.lock()->previous;

				return *this;
			}

			const_reverse_iterator
			operator++( int )
			{
				const_reverse_iterator iterator( *this );
				++( *this );

				return iterator;
			}

			const_reverse_iterator&
			operator--()
			{
				this->node = this->node.lock()->next;

				return *this;
			}

			const_reverse_iterator
			operator--( int )
			{
				const_reverse_iterator iterator( *this );
				--( *this );

				return iterator;
			}

			const T
			operator*() const
			{
				return this->node.lock()->item;
			}

			const doubly_linked_node< T >*
			operator->() const
			{
				return this->node.lock().get();
			}

			bool
			operator==( const const_reverse_iterator& it ) const
			{
				if ( this->node.expired() && 
					 it.node.expired() )
				{
					return true;
				}

				if ( it.node.expired() )
				{
					return false;
				}

				return ( *( this->node.lock() ) == *( it.node.lock() ) );
			}

			bool
			operator!=( const const_reverse_iterator& it ) const
			{
				return !( *this == it );
			}

		private:
			std::weak_ptr< doubly_linked_node< T > > node;
		};

		doubly_linked_list() = default;
		~doubly_linked_list() noexcept = default;

		doubly_linked_list( const doubly_linked_list& other )
		{
			std::shared_ptr< doubly_linked_node< T > > node = other.back;

			while ( node )
			{
				this->push_front( node->item );
				node = node->next;
			}
		}

		doubly_linked_list( doubly_linked_list&& other ) noexcept :
			front( std::move_if_noexcept( other.front ) ),
			back( std::move_if_noexcept( other.back ) ),
			nodes( other.nodes )
		{
			other.nodes = 0;
		}

		doubly_linked_list&
		operator=( const doubly_linked_list& rhs )
		{
			if ( this != &rhs )
			{
				this->clear();

				*this = std::move( doubly_linked_list< T >( rhs ) );
			}

			return *this;
		}

		doubly_linked_list&
		operator=( doubly_linked_list&& rhs ) noexcept
		{
			if ( this != &rhs )
			{
				this->clear();

				this->front = std::move_if_noexcept( rhs.front );
				this->back = std::move_if_noexcept( rhs.back );
				this->nodes = rhs.nodes;

				rhs.nodes = 0;
			}

			return *this;
		}

		doubly_linked_list&
		operator+( const doubly_linked_list& rhs )
		{
			return *this += rhs;
		}

		doubly_linked_list&
		operator+=( const doubly_linked_list& rhs )
		{
			if ( !rhs.empty() )
			{
				std::shared_ptr< doubly_linked_node< T > > node = rhs.back;

				while ( node )
				{
					this->push_front( node->item );

					node = node->next;
				}
			}

			return *this;
		}

		bool
		operator==( const doubly_linked_list& rhs ) const noexcept
		{
			return this->equals( this->back, rhs.back );
		}

		bool
		operator!=( const doubly_linked_list& rhs ) const noexcept
		{
			return !( *this == rhs );
		}

		void
		push_front( const T item )
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

		void
		push_back( const T item )
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
				auto previousNode = std::move_if_noexcept( this->front->previous );

				if ( previousNode )
				{
					previousNode->next = nullptr;

					this->front = std::move_if_noexcept( previousNode );
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
			const std::weak_ptr< doubly_linked_node< T > > node1,
			const std::weak_ptr< doubly_linked_node< T > > node2 ) const noexcept
		{
			if ( node1.expired() &&
				 node2.expired() )
			{
				return true;
			}

			if ( node1.expired() ||
				 node2.expired() )
			{
				return false;
			}

			const auto lockedNode1 = node1.lock();
			const auto lockedNode2 = node2.lock();

			if ( lockedNode1->item == lockedNode2->item )
			{
				return this->equals( lockedNode1->next, lockedNode2->next );
			}

			return false;
		}

		std::weak_ptr< doubly_linked_node< T > >
		first() const noexcept
		{
			return this->back;
		}

		std::weak_ptr< doubly_linked_node< T > >
		last() const noexcept
		{
			return this->front;
		}

		std::weak_ptr< doubly_linked_node< T > >
		next( const std::weak_ptr< doubly_linked_node< T > > current ) const noexcept
		{
			return current.lock()->next;
		}

		std::weak_ptr< doubly_linked_node< T > >
		previous( const std::weak_ptr< doubly_linked_node< T > > current ) const noexcept
		{
			return current.lock()->previous;
		}

		std::shared_ptr< doubly_linked_node< T > > front = nullptr;
		std::shared_ptr< doubly_linked_node< T > > back = nullptr;

		std::size_t nodes = 0;
	};

	template < typename T >
	auto
	operator+( const doubly_linked_list< T >& lhs, const doubly_linked_list< T >& rhs )
	{
		doubly_linked_list< T > result( lhs );

		return result += rhs;
	}
}
