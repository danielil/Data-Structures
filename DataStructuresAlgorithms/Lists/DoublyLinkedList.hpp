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
    struct DoublyLinkedNode
    {
        T item;

        DoublyLinkedNode< T >* previous;
        DoublyLinkedNode< T >* next;
    };

    template < typename T >
    class DoublyLinkedList
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
            friend class DoublyLinkedList;
            friend class const_iterator;

            inline iterator(DoublyLinkedNode< T >* node = nullptr) :
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
            DoublyLinkedNode<T>* node;
        };

        class const_iterator : public std::iterator<std::bidirectional_iterator_tag, const T>
        {
        public:
            friend class DoublyLinkedList;
            friend class const_iterator;

            inline const_iterator(const DoublyLinkedNode< T >* node = nullptr) :
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
            DoublyLinkedNode<T>* node;
        }

        DoublyLinkedList();
        ~DoublyLinkedList() noexcept;

        DoublyLinkedList( const DoublyLinkedList& other );
        DoublyLinkedList( DoublyLinkedList&& other ) noexcept;

        // Operators
        DoublyLinkedList& operator=( const DoublyLinkedList& rhs );
        DoublyLinkedList& operator=( DoublyLinkedList&& rhs ) noexcept;

        DoublyLinkedList& operator+( const DoublyLinkedList& rhs );
        DoublyLinkedList& operator+=( const DoublyLinkedList& rhs );

        bool operator==( const DoublyLinkedList& rhs ) const;
        bool operator!=( const DoublyLinkedList& rhs ) const;

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
        DoublyLinkedNode< T >* first() const;
        DoublyLinkedNode< T >* last() const;
        DoublyLinkedNode< T >* next( DoublyLinkedNode< T >* current ) const;
        DoublyLinkedNode< T >* previous( DoublyLinkedNode< T >* current ) const;
        DoublyLinkedListIterator< T > begin();
        DoublyLinkedListIterator< T > rbegin();
        DoublyLinkedListIterator< T > end();
        DoublyLinkedListIterator< T > rend();
    private:
        void blank_pop_front();
        void blank_pop_back();

        bool equals( const DoublyLinkedNode< T >* node1, const DoublyLinkedNode< T >* node2 ) const;
        std::string to_string() const;

        DoublyLinkedNode< T >* front;
        DoublyLinkedNode< T >* back;

        std::size_t nodes;
    };

    template < typename T >
    DoublyLinkedList< T >::DoublyLinkedList() :
        front( nullptr ),
        back( nullptr ),
        nodes( 0 )
    {
    }

    template < typename T >
    DoublyLinkedList< T >::~DoublyLinkedList() noexcept
    {
        clear();
    }

    template < typename T >
    DoublyLinkedList< T >::DoublyLinkedList( const DoublyLinkedList& other ) :
        front( nullptr ),
        back( nullptr ),
        nodes( 0 )
    {
        DoublyLinkedNode<T>* node = other.back;

        while(node != nullptr)
        {
            this->push_front(node->item);
            node = node->next;
        }
    }

    template < typename T >
    DoublyLinkedList< T >::DoublyLinkedList( DoublyLinkedList&& other ) noexcept :
        front( other.front ),
        back( other.back ),
        nodes( other.nodes )
    {
        other.front = nullptr;
        other.back = nullptr;
        other.nodes = 0;
    }

    template < typename T >
    DoublyLinkedList< T >& DoublyLinkedList< T >::operator=( const DoublyLinkedList& rhs )
    {
        if ( this != &rhs )
        {
            clear();

            DoublyLinkedList< T > temp( rhs );

            *this = std::move( temp );
        }

        return *this;
    }

    template < typename T >
    DoublyLinkedList< T >& DoublyLinkedList< T >::operator=( DoublyLinkedList&& rhs ) noexcept
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
    DoublyLinkedList< T >& DoublyLinkedList< T >::operator+( const DoublyLinkedList& rhs )
    {
        return *this += rhs;
    }

    template < typename T >
    DoublyLinkedList< T > operator+(const DoublyLinkedList<T>& lhs, const DoublyLinkedList<T>& rhs)
    {
        DoublyLinkedList<T> result(lhs);
        
        return lhs += rhs;
    }

    template < typename T >
    DoublyLinkedList< T >& DoublyLinkedList< T >::operator+=( const DoublyLinkedList& rhs )
    {
        if ( !rhs.empty() )
        {
            DoublyLinkedNode< T >* currentNodeOther = rhs.back;

            while ( currentNodeOther != nullptr )
            {
                this->push_front( currentNodeOther->item );

                currentNodeOther = currentNodeOther->next;
            }
        }

        return *this;
    }

    template < typename T >
    bool DoublyLinkedList< T >::operator==( const DoublyLinkedList& rhs ) const
    {
        return this->equals( this->back, rhs.back );
    }

    template < typename T >
    bool DoublyLinkedList< T >::operator!=( const DoublyLinkedList& rhs ) const
    {
        return !( *this == rhs );
    }

    template < typename T >
    std::ostream& operator<<( std::ostream& os, const DoublyLinkedList< T >& stack )
    {
        return ( os << stack.to_string() );
    }

    template < typename T >
    void DoublyLinkedList< T >::push_front( const T item )
    {
        DoublyLinkedNode< T >* newNode = new DoublyLinkedNode< T >();
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
    void DoublyLinkedList< T >::push_back( const T item )
    {
        DoublyLinkedNode< T >* newNode = new DoublyLinkedNode< T >();
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
    T DoublyLinkedList< T >::pop_front()
    {
        if ( empty() )
        {
            return T();
        }

        T item = this->front->item;
        DoublyLinkedNode< T >* previousNode = this->front->previous;

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
    T DoublyLinkedList< T >::pop_back()
    {
        if ( empty() )
        {
            return T();
        }

        T item = this->back->item;
        DoublyLinkedNode< T >* nextNode = this->back->next;

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
    void DoublyLinkedList< T >::clear()
    {
        while (!empty())
        {
            blank_pop_front();
        }
    }

    template < typename T >
    T DoublyLinkedList< T >::peek_front() const
    {
        if ( empty() )
        {
            return T();
        }

        return this->front->item;
    }

    template < typename T >
    T DoublyLinkedList< T >::peek_back() const
    {
        if ( empty() )
        {
            return T();
        }

        return this->back->item;
    }

    template < typename T >
    std::size_t DoublyLinkedList< T >::size() const
    {
        return this->nodes;
    }

    template < typename T >
    bool DoublyLinkedList< T >::empty() const
    {
        return ( ( this->front == nullptr ) &&
                 ( this->back == nullptr ) &&
                 ( this->nodes == 0 ) );
    }

    template < typename T >
    DoublyLinkedNode< T >* DoublyLinkedList< T >::first() const
    {
        return this->back;
    }

    template < typename T >
    DoublyLinkedNode< T >* DoublyLinkedList< T >::last() const
    {
        return this->front;
    }

    template < typename T >
    DoublyLinkedNode< T >* DoublyLinkedList< T >::next( DoublyLinkedNode< T >* current ) const
    {
        return current->next;
    }

    template < typename T >
    DoublyLinkedNode< T >* DoublyLinkedList< T >::previous( DoublyLinkedNode< T >* current ) const
    {
        return current->previous;
    }

    template < typename T >
    DoublyLinkedListIterator< T > DoublyLinkedList< T >::begin()
    {
        DoublyLinkedListIterator< T > iterator( this );
        iterator.currentNode = first();

        return iterator;
    }

    template < typename T >
    DoublyLinkedListIterator< T > DoublyLinkedList< T >::rbegin()
    {
        DoublyLinkedListIterator< T > iterator( this );
        iterator.currentNode = last();

        return iterator;
    }

    template < typename T >
    DoublyLinkedListIterator< T > DoublyLinkedList< T >::end()
    {
        DoublyLinkedListIterator< T > iterator( this );
        iterator.currentNode = next( last() );

        return iterator;
    }

    template < typename T >
    DoublyLinkedListIterator< T > DoublyLinkedList< T >::rend()
    {
        DoublyLinkedListIterator< T > iterator( this );
        iterator.currentNode = previous( first() );

        return iterator;
    }

    template < typename T >
    void DoublyLinkedList< T >::blank_pop_front()
    {
        if (!empty())
        {
            DoublyLinkedNode< T >* previousNode = this->front->previous;

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
    void DoublyLinkedList< T >::blank_pop_back()
    {
        if (!empty())
        {
            DoublyLinkedNode< T >* nextNode = this->back->next;

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
    bool DoublyLinkedList< T >::equals( const DoublyLinkedNode< T >* node1, const DoublyLinkedNode< T >* node2 ) const
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
    std::string DoublyLinkedList< T >::to_string() const
    {
        DoublyLinkedNode< T >* currentNode = this->front;

        std::stringstream list;
        while ( currentNode != nullptr )
        {
            list << currentNode->data << std::endl;

            currentNode = currentNode->next;
        }

        return list.str();
    }
}
