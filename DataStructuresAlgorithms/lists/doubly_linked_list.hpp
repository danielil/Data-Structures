/**
 * Daniel Sebastian Iliescu
 *
 * A doubly-linked implementation of a list combining both stack (LIFO) and queue (FIFO) operations.
 *
 * All insertion (push_front, push_back) and removal (pop_front, pop_back) is done in O(1) complexity
 * since no traversal is done for either operations.
 *
 * Custom STL-style iterators for the list are also implemented.
 */

#pragma once

#include <memory>

namespace dsa
{
    template < typename T >
    struct doubly_linked_node
    {
        T item;

        std::shared_ptr< doubly_linked_node< T > > previous;
        std::shared_ptr< doubly_linked_node< T > > next;
    };

    template < typename T >
    class doubly_linked_list
    {
    public:
        class iterator : public std::iterator< std::bidirectional_iterator_tag, T, std::ptrdiff_t, T*, T& >
        {
        public:
            friend class doubly_linked_list;
            friend class const_iterator;

            inline iterator( std::weak_ptr< doubly_linked_node< T > > node ) :
                node( node )
            {
            }

            inline iterator( const iterator& it ) :
                node( it.node )
            {
            }

            inline iterator& operator=( const iterator& it )
            {
                this->node = it.node;

                return *this;
            }

            inline iterator& operator++()
            {
                this->node = this->node.lock()->next;

                return *this;
            }

            iterator operator++( int )
            {
                iterator iterator( *this );
                ++iterator;

                return iterator;
            }

            inline iterator& operator--()
            {
                this->node = this->node.lock()->previous;

                return *this;
            }

            inline iterator operator--( int )
            {
                iterator iterator( *this );
                --iterator;

                return iterator;
            }

            inline typename std::iterator_traits< iterator >::reference operator*() const
            {
                return this->node.lock()->item;
            }

            inline typename std::iterator_traits< iterator >::pointer operator->() const
            {
                return this->node.lock().get();
            }

            bool operator==( const iterator& it )
            {
                return ( this->node.lock() == it.node.lock() );
            }

            bool operator!=( const iterator& it )
            {
                return ( this->node.lock() != it.node.lock() );
            }

        private:
            std::weak_ptr< doubly_linked_node< T > > node;
        };

        class const_iterator : public std::iterator< std::bidirectional_iterator_tag, T, T*, T& >
        {
        public:
            friend class doubly_linked_list;
            friend class iterator;

            inline const_iterator( std::weak_ptr< doubly_linked_node< T > > node ) :
                node( node )
            {
            }

            inline const_iterator( const const_iterator& it ) :
                node( it.node )
            {
            }

            inline const_iterator( const iterator& it ) :
                node( it.node )
            {
            }

            inline const_iterator& operator=( const const_iterator& it )
            {
                this->node = it.node;

                return *this;
            }

            inline const_iterator& operator=( const iterator& it )
            {
                this->node = it.node;

                return *this;
            }

            inline const_iterator& operator++()
            {
                this->node = this->node.lock()->next;

                return *this;
            }

            inline const_iterator operator++( int )
            {
                const_iterator iterator( *this );
                ++iterator;

                return iterator;
            }

            inline const_iterator& operator--()
            {
                this->node = this->node.lock()->previous;

                return *this;
            }

            inline const_iterator operator--( int )
            {
                const_iterator iterator( *this );
                --iterator;

                return iterator;
            }

            inline typename std::iterator_traits< const_iterator >::reference operator*() const
            {
                return this->node.lock()->item;
            }

            inline typename std::iterator_traits< const_iterator >::pointer operator->() const
            {
                return this->node.lock().get();
            }

            inline bool operator==( const const_iterator& it ) const
            {
                return ( this->node.lock() == it.node.lock() );
            }

            inline bool operator!=( const const_iterator& it ) const
            {
                return ( this->node.lock() != it.node.lock() );
            }

        private:
            std::weak_ptr< doubly_linked_node< T > > node;
        };

        class reverse_iterator : public std::iterator< std::bidirectional_iterator_tag, T, T*, T& >
        {
        public:
            friend class doubly_linked_list;
            friend class const_reverse_iterator;

            inline reverse_iterator( std::weak_ptr< doubly_linked_node< T > > node ) :
                node( node )
            {
            }

            inline reverse_iterator( const reverse_iterator& it ) :
                node( it.node )
            {
            }

            inline reverse_iterator& operator=( const reverse_iterator& it )
            {
                this->node = it.node;

                return *this;
            }

            inline reverse_iterator& operator++()
            {
                this->node = this->node.lock()->previous;

                return *this;
            }

            reverse_iterator operator++( int )
            {
                reverse_iterator iterator( *this );
                ++iterator;

                return iterator;
            }

            inline reverse_iterator& operator--()
            {
                this->node = this->node.lock()->next;

                return *this;
            }

            inline reverse_iterator operator--( int )
            {
                iterator iterator( *this );
                --iterator;

                return iterator;
            }

            inline typename std::iterator_traits< reverse_iterator >::reference operator*() const
            {
                return this->node.lock()->item;
            }

            inline typename std::iterator_traits< reverse_iterator >::pointer operator->() const
            {
                return this->node.lock().get();
            }

            bool operator==( const reverse_iterator& it )
            {
                return ( this->node.lock() == it.node.lock() );
            }

            bool operator!=( const reverse_iterator& it )
            {
                return ( this->node.lock() != it.node.lock() );
            }

        private:
            std::weak_ptr< doubly_linked_node< T > > node;
        };

        class const_reverse_iterator : public std::iterator< std::bidirectional_iterator_tag, T, T*, T& >
        {
        public:
            friend class doubly_linked_list;
            friend class iterator;

            inline const_reverse_iterator( std::weak_ptr< doubly_linked_node< T > > node ) :
                node( node )
            {
            }

            inline const_reverse_iterator( const const_reverse_iterator& it ) :
                node( it.node )
            {
            }

            inline const_reverse_iterator( const reverse_iterator& it ) :
                node( it.node )
            {
            }

            inline const_reverse_iterator& operator=( const const_reverse_iterator& it )
            {
                this->node = it.node;

                return *this;
            }

            inline const_reverse_iterator& operator=( const reverse_iterator& it )
            {
                this->node = it.node;

                return *this;
            }

            inline const_reverse_iterator& operator++()
            {
                this->node = this->node.lock()->previous;

                return *this;
            }

            inline const_reverse_iterator operator++( int )
            {
                const_reverse_iterator iterator( *this );
                ++iterator;

                return iterator;
            }

            inline const_reverse_iterator& operator--()
            {
                this->node = this->node.lock()->next;

                return *this;
            }

            inline const_reverse_iterator operator--( int )
            {
                const_reverse_iterator iterator( *this );
                --iterator;

                return iterator;
            }

            inline typename std::iterator_traits< const_reverse_iterator >::reference operator*() const
            {
                return this->node.lock()->item;
            }

            inline typename std::iterator_traits< const_reverse_iterator >::reference operator->() const
            {
                return this->node.lock().get();
            }

            inline bool operator==( const const_reverse_iterator& it ) const
            {
                return ( this->node.lock() == it.node.lock() );
            }

            inline bool operator!=( const const_reverse_iterator& it ) const
            {
                return ( this->node.lock() != it.node.lock() );
            }

        private:
            std::weak_ptr< doubly_linked_node< T > > node;
        };

        doubly_linked_list();
        ~doubly_linked_list() noexcept;

        doubly_linked_list( const doubly_linked_list& other );
        doubly_linked_list( doubly_linked_list&& other ) noexcept;

        // Operators
        doubly_linked_list& operator=( const doubly_linked_list& rhs );
        doubly_linked_list& operator=( doubly_linked_list&& rhs ) noexcept;

        doubly_linked_list& operator+( const doubly_linked_list& rhs );
        doubly_linked_list& operator+=( const doubly_linked_list& rhs );

        bool operator==( const doubly_linked_list& rhs ) const;
        bool operator!=( const doubly_linked_list& rhs ) const;

        // Operations
        void push_front( const T item );
        void push_back( const T item );
        T pop_front();
        T pop_back();
        void clear();

        // Accessors
        T peek_front() const;
        T peek_back() const;
        std::size_t size() const;
        bool empty() const;

        // Iterator operations
        iterator begin();
        iterator end();
        reverse_iterator rbegin();
        reverse_iterator rend();
        const_iterator begin() const;
        const_iterator end() const;
        const_reverse_iterator rbegin() const;
        const_reverse_iterator rend() const;
    private:
        void blank_pop_front();

        bool equals( const std::weak_ptr< doubly_linked_node< T > > node1, const std::weak_ptr< doubly_linked_node< T > > node2 ) const;

        std::weak_ptr< doubly_linked_node< T > > first() const;
        std::weak_ptr< doubly_linked_node< T > > last() const;
        std::weak_ptr< doubly_linked_node< T > > next( const std::weak_ptr< doubly_linked_node< T > > current ) const;
        std::weak_ptr< doubly_linked_node< T > > previous( const std::weak_ptr< doubly_linked_node< T > > current ) const;

        std::shared_ptr< doubly_linked_node< T > > front;
        std::shared_ptr< doubly_linked_node< T > > back;

        std::size_t nodes;
    };

    template < typename T >
    doubly_linked_list< T >::doubly_linked_list() :
        front(),
        back(),
        nodes( 0 )
    {
    }

    template < typename T >
    doubly_linked_list< T >::~doubly_linked_list() noexcept
    {
        this->clear();
    }

    template < typename T >
    doubly_linked_list< T >::doubly_linked_list( const doubly_linked_list& other ) :
        front(),
        back(),
        nodes( 0 )
    {
        std::shared_ptr< doubly_linked_node< T > > node = other.back;

        while ( node )
        {
            this->push_front( node->item );
            node = node->next;
        }
    }

    template < typename T >
    doubly_linked_list< T >::doubly_linked_list( doubly_linked_list&& other ) noexcept :
        front( std::move( other.front ) ),
        back( std::move( other.back ) ),
        nodes( other.nodes )
    {
        other.nodes = 0;
    }

    template < typename T >
    doubly_linked_list< T >& doubly_linked_list< T >::operator=( const doubly_linked_list& rhs )
    {
        if ( this != &rhs )
        {
            this->clear();

            doubly_linked_list< T > temp( rhs );

            *this = std::move( temp );
        }

        return *this;
    }

    template < typename T >
    doubly_linked_list< T >& doubly_linked_list< T >::operator=( doubly_linked_list&& rhs ) noexcept
    {
        if ( this != &rhs )
        {
            this->clear();

            this->front = std::move( rhs.front );
            this->back = std::move( rhs.back );
            this->nodes = rhs.nodes;

            rhs.nodes = 0;
        }

        return *this;
    }

    template < typename T >
    doubly_linked_list< T >& doubly_linked_list< T >::operator+( const doubly_linked_list& rhs )
    {
        return *this += rhs;
    }

    template < typename T >
    doubly_linked_list< T > operator+( const doubly_linked_list< T >& lhs, const doubly_linked_list< T >& rhs )
    {
        doubly_linked_list< T > result( lhs );

        return result += rhs;
    }

    template < typename T >
    doubly_linked_list< T >& doubly_linked_list< T >::operator+=( const doubly_linked_list& rhs )
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

    template < typename T >
    bool doubly_linked_list< T >::operator==( const doubly_linked_list& rhs ) const
    {
        return this->equals( this->back, rhs.back );
    }

    template < typename T >
    bool doubly_linked_list< T >::operator!=( const doubly_linked_list& rhs ) const
    {
        return !( *this == rhs );
    }

    template < typename T >
    void doubly_linked_list< T >::push_front( const T item )
    {
        std::shared_ptr< doubly_linked_node< T > > newNode = std::make_shared< doubly_linked_node< T > >();
        newNode->item = item;

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

    template < typename T >
    void doubly_linked_list< T >::push_back( const T item )
    {
        std::shared_ptr< doubly_linked_node< T > > newNode = std::make_shared< doubly_linked_node< T > >();
        newNode->item = item;

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

    template < typename T >
    T doubly_linked_list< T >::pop_front()
    {
        if ( this->empty() )
        {
            return T();
        }

        T item = this->front->item;
        std::shared_ptr< doubly_linked_node< T > > previousNode = std::move( this->front->previous );

        if ( previousNode )
        {
            previousNode->next.reset();

            this->front = std::move( previousNode );
        }
        else
        {
            this->front.reset();
            this->back.reset();
        }

        --( this->nodes );

        return item;
    }

    template < typename T >
    T doubly_linked_list< T >::pop_back()
    {
        if ( this->empty() )
        {
            return T();
        }

        T item = this->back->item;
        std::shared_ptr< doubly_linked_node< T > > nextNode = std::move( this->back->next );

        if ( nextNode )
        {
            nextNode->previous.reset();

            this->back = std::move( nextNode );
        }
        else
        {
            this->front.reset();
            this->back.reset();
        }

        --( this->nodes );

        return item;
    }

    template < typename T >
    void doubly_linked_list< T >::clear()
    {
        while ( !this->empty() )
        {
            this->blank_pop_front();
        }
    }

    template < typename T >
    T doubly_linked_list< T >::peek_front() const
    {
        if ( this->empty() )
        {
            return T();
        }

        return this->front->item;
    }

    template < typename T >
    T doubly_linked_list< T >::peek_back() const
    {
        if ( this->empty() )
        {
            return T();
        }

        return this->back->item;
    }

    template < typename T >
    std::size_t doubly_linked_list< T >::size() const
    {
        return this->nodes;
    }

    template < typename T >
    bool doubly_linked_list< T >::empty() const
    {
        return ( ( !this->front ) &&
                 ( !this->back ) &&
                 ( this->nodes == 0 ) );
    }

    template < typename T >
    typename doubly_linked_list< T >::iterator doubly_linked_list< T >::begin()
    {
        return iterator( this->first() );
    }

    template < typename T >
    typename doubly_linked_list< T >::iterator doubly_linked_list< T >::end()
    {
        return iterator( this->next( this->last() ) );
    }

    template < typename T >
    typename doubly_linked_list< T >::reverse_iterator doubly_linked_list< T >::rbegin()
    {
        return reverse_iterator( this->last() );
    }

    template < typename T >
    typename doubly_linked_list< T >::reverse_iterator doubly_linked_list< T >::rend()
    {
        return reverse_iterator( this->previous( this->first() ) );
    }

    template < typename T >
    typename doubly_linked_list< T >::const_iterator doubly_linked_list< T >::begin() const
    {
        return const_iterator( this->first() );
    }

    template < typename T >
    typename doubly_linked_list< T >::const_iterator doubly_linked_list< T >::end() const
    {
        return const_iterator( this->next( this->last() ) );
    }

    template < typename T >
    typename doubly_linked_list< T >::const_reverse_iterator doubly_linked_list< T >::rbegin() const
    {
        return const_reverse_iterator( this->last() );
    }

    template < typename T >
    typename doubly_linked_list< T >::const_reverse_iterator doubly_linked_list< T >::rend() const
    {
        return const_reverse_iterator( this->previous( this->first() ) );
    }

    template < typename T >
    void doubly_linked_list< T >::blank_pop_front()
    {
        if ( !this->empty() )
        {
            std::shared_ptr< doubly_linked_node< T > > previousNode = std::move( this->front->previous );

            if ( previousNode )
            {
                previousNode->next.reset();

                this->front = std::move( previousNode );
            }
            else
            {
                this->front.reset();
                this->back.reset();
            }

            --( this->nodes );
        }
    }

    template < typename T >
    bool doubly_linked_list< T >::equals( const std::weak_ptr< doubly_linked_node< T > > node1, const std::weak_ptr< doubly_linked_node< T > > node2 ) const
    {
        if ( node1.lock() == node2.lock() )
        {
            return true;
        }

        if ( ( node1.lock() ) &&
             ( node2.lock() ) &&
             ( node1.lock()->item == node2.lock()->item ) )
        {
            return this->equals( node1.lock()->next, node2.lock()->next );
        }

        return false;
    }

    template < typename T >
    std::weak_ptr< doubly_linked_node< T > > doubly_linked_list< T >::first() const
    {
        return this->back;
    }

    template < typename T >
    std::weak_ptr< doubly_linked_node< T > > doubly_linked_list< T >::last() const
    {
        return this->front;
    }

    template < typename T >
    std::weak_ptr< doubly_linked_node< T > > doubly_linked_list< T >::next( const std::weak_ptr< doubly_linked_node< T > > current ) const
    {
        return current.lock()->next;
    }

    template < typename T >
    std::weak_ptr< doubly_linked_node< T > > doubly_linked_list< T >::previous( const std::weak_ptr< doubly_linked_node< T > > current ) const
    {
        return current.lock()->previous;
    }
}
