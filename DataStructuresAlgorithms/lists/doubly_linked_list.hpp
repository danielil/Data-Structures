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

namespace dsa
{
    template < typename T >
    struct doubly_linked_node
    {
        T item;

        doubly_linked_node< T >* previous;
        doubly_linked_node< T >* next;
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

            inline iterator( doubly_linked_node< T >* node = nullptr ) :
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
                this->node = this->node->next;

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
                this->node = this->node->previous;

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
                return this->node->item;
            }

            inline typename std::iterator_traits< iterator >::pointer operator->() const
            {
                return this->node;
            }

            bool operator==( const iterator& it )
            {
                return ( this->node == it.node );
            }

            bool operator!=( const iterator& it )
            {
                return ( this->node != it.node );
            }

        private:
            doubly_linked_node< T >* node;
        };

        class const_iterator : public std::iterator< std::bidirectional_iterator_tag, T, T*, T& >
        {
        public:
            friend class doubly_linked_list;
            friend class iterator;

            inline const_iterator( const doubly_linked_node< T >* node = nullptr ) :
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
                this->node = this->node->next;

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
                this->node = this->node->previous;

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
                return *( this->node );
            }

            inline typename std::iterator_traits< const_iterator >::pointer operator->() const
            {
                return this->node;
            }

            inline bool operator==( const const_iterator& it ) const
            {
                return ( this->node == it.node );
            }

            inline bool operator!=( const const_iterator& it ) const
            {
                return ( this->node != it.node );
            }

        private:
            doubly_linked_node< T >* node;
        };

        class reverse_iterator : public std::iterator< std::bidirectional_iterator_tag, T, T*, T& >
        {
        public:
            friend class doubly_linked_list;
            friend class const_reverse_iterator;

            inline reverse_iterator( doubly_linked_node< T >* node = nullptr ) :
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
                this->node = this->node->previous;

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
                this->node = this->node->next;

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
                return this->node->item;
            }

            inline typename std::iterator_traits< reverse_iterator >::pointer operator->() const
            {
                return this->node;
            }

            bool operator==( const reverse_iterator& it )
            {
                return ( this->node == it.node );
            }

            bool operator!=( const reverse_iterator& it )
            {
                return ( this->node != it.node );
            }

        private:
            doubly_linked_node< T >* node;
        };

        class const_reverse_iterator : public std::iterator< std::bidirectional_iterator_tag, T, T*, T& >
        {
        public:
            friend class doubly_linked_list;
            friend class iterator;

            inline const_reverse_iterator( const doubly_linked_node< T >* node = nullptr ) :
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
                this->node = this->node->previous;

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
                this->node = this->node->next;

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
                return *( this->node );
            }

            inline typename std::iterator_traits< const_reverse_iterator >::reference operator->() const
            {
                return this->node;
            }

            inline bool operator==( const const_reverse_iterator& it ) const
            {
                return ( this->node == it.node );
            }

            inline bool operator!=( const const_reverse_iterator& it ) const
            {
                return ( this->node != it.node );
            }

        private:
            doubly_linked_node< T >* node;
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
        doubly_linked_node< T >* first() const;
        doubly_linked_node< T >* last() const;
        doubly_linked_node< T >* next( doubly_linked_node< T >* current ) const;
        doubly_linked_node< T >* previous( doubly_linked_node< T >* current ) const;
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

        bool equals( const doubly_linked_node< T >* node1, const doubly_linked_node< T >* node2 ) const;

        doubly_linked_node< T >* front;
        doubly_linked_node< T >* back;

        std::size_t nodes;
    };

    template < typename T >
    doubly_linked_list< T >::doubly_linked_list() :
        front( nullptr ),
        back( nullptr ),
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
        front( nullptr ),
        back( nullptr ),
        nodes( 0 )
    {
        doubly_linked_node< T >* node = other.back;

        while ( node != nullptr )
        {
            this->push_front( node->item );
            node = node->next;
        }
    }

    template < typename T >
    doubly_linked_list< T >::doubly_linked_list( doubly_linked_list&& other ) noexcept :
        front( other.front ),
        back( other.back ),
        nodes( other.nodes )
    {
        other.front = nullptr;
        other.back = nullptr;
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
            clear();

            this->front = rhs.front;
            this->back = rhs.back;
            this->nodes = rhs.nodes;

            rhs.front = nullptr;
            rhs.back = nullptr;
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

        return lhs += rhs;
    }

    template < typename T >
    doubly_linked_list< T >& doubly_linked_list< T >::operator+=( const doubly_linked_list& rhs )
    {
        if ( !rhs.empty() )
        {
            doubly_linked_node< T >* currentNodeOther = rhs.back;

            while ( currentNodeOther != nullptr )
            {
                this->push_front( currentNodeOther->item );

                currentNodeOther = currentNodeOther->next;
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
        doubly_linked_node< T >* newNode = new doubly_linked_node< T >();
        newNode->item = item;
        newNode->next = nullptr;

        if ( this->empty() )
        {
            newNode->previous = nullptr;

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
        doubly_linked_node< T >* newNode = new doubly_linked_node< T >();
        newNode->item = item;
        newNode->previous = nullptr;

        if ( this->empty() )
        {
            newNode->next = nullptr;

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
        doubly_linked_node< T >* previousNode = this->front->previous;

        delete this->front;

        if ( previousNode == nullptr )
        {
            this->front = nullptr;
            this->back = nullptr;
        }
        else
        {
            previousNode->next = nullptr;

            this->front = previousNode;
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
        doubly_linked_node< T >* nextNode = this->back->next;

        delete this->back;

        if ( nextNode == nullptr )
        {
            this->front = nullptr;
            this->back = nullptr;
        }
        else
        {
            nextNode->previous = nullptr;

            this->back = nextNode;
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
        return ( ( this->front == nullptr ) &&
                 ( this->back == nullptr ) &&
                 ( this->nodes == 0 ) );
    }

    template < typename T >
    doubly_linked_node< T >* doubly_linked_list< T >::first() const
    {
        return this->back;
    }

    template < typename T >
    doubly_linked_node< T >* doubly_linked_list< T >::last() const
    {
        return this->front;
    }

    template < typename T >
    doubly_linked_node< T >* doubly_linked_list< T >::next( doubly_linked_node< T >* current ) const
    {
        return current->next;
    }

    template < typename T >
    doubly_linked_node< T >* doubly_linked_list< T >::previous( doubly_linked_node< T >* current ) const
    {
        return current->previous;
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
            doubly_linked_node< T >* previousNode = this->front->previous;

            delete this->front;

            if ( previousNode == nullptr )
            {
                this->front = nullptr;
                this->back = nullptr;
            }
            else
            {
                previousNode->next = nullptr;

                this->front = previousNode;
            }

            --( this->nodes );
        }
    }

    template < typename T >
    bool doubly_linked_list< T >::equals( const doubly_linked_node< T >* node1, const doubly_linked_node< T >* node2 ) const
    {
        if ( node1 == node2 )
        {
            return true;
        }

        if ( ( node1 != nullptr ) &&
             ( node2 != nullptr ) &&
             ( node1->item == node2->item ) )
        {
            return this->equals( node1->next, node2->next );
        }

        return false;
    }
}
