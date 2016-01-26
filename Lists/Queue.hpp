/**
 * Daniel Sebastian Iliescu
 *
 * An implementation of the Queue (FIFO) data structure.
 */

#pragma once

#include <string>
#include <sstream>

namespace Lists
{
    template < typename T >
    struct QueueNode
    {
        T data;

        QueueNode< T >* previous;
        QueueNode< T >* next;
    };

    template < typename T >
    class Queue
    {
    public:
        Queue();
        ~Queue() noexcept;

        Queue( const Queue& other );
        Queue( Queue&& other ) noexcept;

        Queue& operator=( const Queue& rhs );
        Queue& operator=( Queue&& rhs ) noexcept;

        bool operator==( const Queue& rhs ) const;
        bool operator!=( const Queue& rhs ) const;

        friend std::ostream& operator<<( std::ostream& os, const Queue& stack )
        {
            os << stack.toString();

            return os;
        }

        void enqueue( const T item );
        T dequeue();

        void clear();

        std::size_t getSize() const;
        bool isEmpty() const;

        std::string toString() const;
    private:
        bool equals( const QueueNode< T >& node1, const QueueNode< T >& node2 ) const;

        QueueNode< T >* head;
        QueueNode< T >* tail;

        std::size_t size;
    };

    template < typename T >
    Queue< T >::Queue() :
        head( nullptr ),
        tail( nullptr ),
        size( 0 )
    {
    }

    template < typename T >
    Queue< T >::~Queue() noexcept
    {
        clear();
    }

    template < typename T >
    Queue< T >::Queue( const Queue& other ) :
        head( nullptr ),
        tail( nullptr ),
        size( 0 )
    {
        QueueNode< T >* currentNodeOther = other.head;

        while ( currentNodeOther != nullptr )
        {
            this->enqueue( currentNodeOther->data );

            currentNodeOther = currentNodeOther->previous;
        }
    }

    template < typename T >
    Queue< T >::Queue( Queue&& other ) noexcept :
        head( other.head ),
        tail( other.tail ),
        size( other.size )
    {
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    template < typename T >
    Queue< T >& Queue< T >::operator=( const Queue& rhs )
    {
        if ( this != &rhs )
        {
            clear();

            Queue< T > temp( rhs );

            *this = std::move( temp );
        }

        return *this;
    }

    template < typename T >
    Queue< T >& Queue< T >::operator=( Queue&& rhs ) noexcept
    {
        if ( this != &rhs )
        {
            clear();

            this->head = rhs.head;
            this->tail = rhs.tail;
            this->size = rhs.size;

            rhs.head = nullptr;
            rhs.tail = nullptr;
            rhs.size = 0;
        }

        return *this;
    }

    template < typename T >
    bool Queue< T >::operator==( const Queue& rhs ) const
    {
        return this->equals( *( this->head ), *( rhs.head) );
    }

    template < typename T >
    bool Queue< T >::operator!=( const Queue& rhs ) const
    {
        return !( this->equals( *( this->head), *( rhs.head) ) );
    }

    template < typename T >
    void Queue< T >::enqueue( const T item )
    {
        QueueNode< T >* newNode = new QueueNode< T >();
        newNode->data = item;
        newNode->previous = nullptr;

        // List is empty; head and tail node are identical.
        if ( isEmpty() )
        {
            newNode->next = nullptr;

            this->tail = newNode;
            this->head = this->tail;
        }
        // Enqueue is of O(1) complexity, since we are adding 
        // at the head.
        else
        {
            newNode->next = this->tail;

            this->tail->previous = newNode;
            this->tail = newNode;
        }

        ++( this->size );
    }

    template < typename T >
    T Queue< T >::dequeue()
    {
        // List is empty; return the default value for the type.
        if ( isEmpty() )
        {
            return T();
        }

        T item = this->head->data;
        QueueNode< T >* previousNode = this->head->previous;

        delete this->head;

        // Dequeue is of O(1) complexity, since we are removing 
        // the head, and not traversing from the tail.
        if ( previousNode != nullptr )
        {
            previousNode->next = nullptr;

            this->head = previousNode;
        }
        // List contains only one node; no need to keep track of 
        // previous and next node.
        else
        {
            this->head = nullptr;
            this->tail = nullptr;
        }

        --( this->size );

        return item;
    }

    template < typename T >
    std::size_t Queue< T >::getSize() const
    {
        return this->size;
    }

    template < typename T >
    std::string Queue< T >::toString() const
    {
        QueueNode< T >* currentNode = this->head;

        std::stringstream list;
        while ( currentNode != nullptr )
        {
            list << currentNode->data << std::endl;

            currentNode = currentNode->next;
        }

        return list.str();
    }

    template < typename T >
    bool Queue< T >::isEmpty() const
    {
        return ( ( this->head == nullptr ) &&
                 ( this->tail == nullptr ) &&
                 ( this->size == 0 ) );
    }

    template < typename T >
    void Queue< T >::clear()
    {
        while ( !isEmpty() )
        {
            dequeue();
        }
    }

    template < typename T >
    bool Queue< T >::equals( const QueueNode< T >& node1, const QueueNode< T >& node2 ) const
    {
        // Both nodes are either nullptr or identical.
        if ( &node1 == &node2 )
        {
            return true;
        }

        if ( ( &node1 != nullptr ) &&
             ( &node2 != nullptr ) &&
             ( node1.data == node2.data ) )
        {
            if ( this->equals( *( node1.next ), *( node2.next ) ) )
            {
                return true;
            }
        }

        return false;
    }
}
