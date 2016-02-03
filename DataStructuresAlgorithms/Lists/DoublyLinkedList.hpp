/**
 * Daniel Sebastian Iliescu
 *
 * A doubly-linked implementation of a list combining both stack (LIFO) and queue (FIFO) operations.
 *
 * All insertion (push_front, push_back) and removal (pop_front, pop_back) is done in O(1) complexity
 * since no traversal is done for either operations.
 *
 * A custom STL-style iterator for the list is also implemented.
 */

#pragma once

#include <string>
#include <sstream>

namespace Lists
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
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef int difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;

        class iterator : public std::iterator<std::bidirectional_iterator_tag, T>
        {
        public:
            friend class doubly_linked_list;
            friend class const_iterator;

            inline iterator(doubly_linked_node< T >* node = nullptr) :
                node(node)
            {
            }

            inline iterator(const iterator& it) :
                node(it.node)
            {
            }

            inline iterator& operator=(const iterator& it) :
                node(it.node)
            {
                return *this;
            }

            inline iterator& operator++()
            {
                this->currentNode = this->list->next(this->currentNode);

                return *this;
            }

            iterator operator++(int)
            {
                iterator iterator(*this);
                operator++();

                return iterator;
            }

            inline iterator& operator--()
            {
                this->currentNode = this->list->previous(this->currentNode);

                return *this;
            }

            inline iterator operator--(int)
            {
                iterator iterator(*this);
                operator--();

                return iterator;
            }

            inline reference operator*() const
            {
                return this->node->next->item;
            }

            inline pointer operator->() const
            {
                return this->node->next;
            }

            bool operator==(const iterator& it)
            {
                return ( ( this->list == it.list ) &&
                         ( this->currentNode == it.currentNode ) );
            }
            bool operator!=(const iterator& it)
            {
                return ( ( this->list != it.list ) ||
                         ( this->currentNode != it.currentNode ) );
            }
        private:
            doubly_linked_node<T>* node;
        };

        class const_iterator : public std::iterator<std::bidirectional_iterator_tag, const T>
        {
        public:
            friend class doubly_linked_list;
            friend class const_iterator;

            inline const_iterator(const doubly_linked_node< T >* node = nullptr) :
                node(node)
            {
            }

            inline const_iterator(const const_iterator& it) :
                node(it.node)
            {
            }

            inline const_iterator(const iterator& it) : 
                node(it.node)
            {
            }

            inline const_iterator& operator=(const const_iterator& it) :
                node(it.node)
            {
                return *this;
            }
            
            inline const_iterator& operator=(const iterator& it) :
                node(it.node)
            {
                return *this;
            }

            inline const_iterator& operator++()
            {
                this->currentNode = this->list->next(this->currentNode);

                return *this;
            }

            inline const_iterator operator++(int)
            {
                const_iterator iterator(*this);
                operator++();

                return iterator;
            }

            inline reference operator*() const
            {
                return this->node->next->item;
            }

            inline pointer operator->() const
            {
                return this->node->next;
            }

            inline bool operator==(const const_iterator& it) const
            {
                return ( ( this->list == it.list ) &&
                         ( this->currentNode == it.currentNode ) );
            }
            inline bool operator!=(const const_iterator& it) const
            {
                return ( ( this->list != it.list ) ||
                         ( this->currentNode != it.currentNode ) );
            }
        private:
            doubly_linked_node<T>* node;
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
        DoublyLinkedListIterator< T > begin();
        DoublyLinkedListIterator< T > rbegin();
        DoublyLinkedListIterator< T > end();
        DoublyLinkedListIterator< T > rend();
    private:
        void blank_pop_front();
        void blank_pop_back();

        bool equals( const doubly_linked_node< T >* node1, const doubly_linked_node< T >* node2 ) const;
        std::string to_string() const;

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
        clear();
    }

    template < typename T >
    doubly_linked_list< T >::doubly_linked_list( const doubly_linked_list& other ) :
        front( nullptr ),
        back( nullptr ),
        nodes( 0 )
    {
        doubly_linked_node<T>* node = other.back;

        while(node != nullptr)
        {
            this->push_front(node->item);
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
            clear();

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
    doubly_linked_list< T > operator+(const doubly_linked_list<T>& lhs, const doubly_linked_list<T>& rhs)
    {
        doubly_linked_list<T> result(lhs);
        
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
    std::ostream& operator<<( std::ostream& os, const doubly_linked_list< T >& stack )
    {
        return ( os << stack.to_string() );
    }

    template < typename T >
    void doubly_linked_list< T >::push_front( const T item )
    {
        doubly_linked_node< T >* newNode = new doubly_linked_node< T >();
        newNode->item = item;
        newNode->next = nullptr;

        if ( empty() )
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

        if ( empty() )
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
        if ( empty() )
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
        if ( empty() )
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
        while (!empty())
        {
            blank_pop_front();
        }
    }

    template < typename T >
    T doubly_linked_list< T >::peek_front() const
    {
        if ( empty() )
        {
            return T();
        }

        return this->front->item;
    }

    template < typename T >
    T doubly_linked_list< T >::peek_back() const
    {
        if ( empty() )
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
    DoublyLinkedListIterator< T > doubly_linked_list< T >::begin()
    {
        DoublyLinkedListIterator< T > iterator( this );
        iterator.currentNode = first();

        return iterator;
    }

    template < typename T >
    DoublyLinkedListIterator< T > doubly_linked_list< T >::rbegin()
    {
        DoublyLinkedListIterator< T > iterator( this );
        iterator.currentNode = last();

        return iterator;
    }

    template < typename T >
    DoublyLinkedListIterator< T > doubly_linked_list< T >::end()
    {
        DoublyLinkedListIterator< T > iterator( this );
        iterator.currentNode = next( last() );

        return iterator;
    }

    template < typename T >
    DoublyLinkedListIterator< T > doubly_linked_list< T >::rend()
    {
        DoublyLinkedListIterator< T > iterator( this );
        iterator.currentNode = previous( first() );

        return iterator;
    }

    template < typename T >
    void doubly_linked_list< T >::blank_pop_front()
    {
        if (!empty())
        {
            doubly_linked_node< T >* previousNode = this->front->previous;

            delete this->front;

            if (previousNode == nullptr)
            {
                this->front = nullptr;
                this->back = nullptr;
            }
            else
            {
                previousNode->next = nullptr;

                this->front = previousNode;
            }

            --(this->nodes);
        }
    }

    template < typename T >
    void doubly_linked_list< T >::blank_pop_back()
    {
        if (!empty())
        {
            doubly_linked_node< T >* nextNode = this->back->next;

            delete this->back;

            if (nextNode == nullptr)
            {
                this->front = nullptr;
                this->back = nullptr;
            }
            else
            {
                nextNode->previous = nullptr;

                this->back = nextNode;
            }

            --(this->nodes);
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

    template < typename T >
    std::string doubly_linked_list< T >::to_string() const
    {
        doubly_linked_node< T >* currentNode = this->front;

        std::stringstream list;
        while ( currentNode != nullptr )
        {
            list << currentNode->data << std::endl;

            currentNode = currentNode->next;
        }

        return list.str();
    }
}
