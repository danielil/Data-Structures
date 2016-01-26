/**
 * Daniel Sebastian Iliescu
 *
 * An implementation of the Stack (LIFO) data structure.
 */

#pragma once

#include <string>
#include <sstream>

namespace Lists
{
    template < typename T >
    struct StackNode
    {
        T data;

        StackNode< T >* previous;
        StackNode< T >* next;
    };

    template < typename T >
    class Stack
    {
    public:
        Stack();
        ~Stack() noexcept;

        Stack( const Stack& other );
        Stack( Stack&& other ) noexcept;

        Stack& operator=( const Stack& rhs );
        Stack& operator=( Stack&& rhs ) noexcept;

        bool operator==( const Stack& rhs ) const;
        bool operator!=( const Stack& rhs ) const;

        friend std::ostream& operator<<( std::ostream& os, const Stack& stack )
        {
            os << stack.toString();

            return os;
        }

        void push( const T item );
        T pop();

        void clear();

        std::size_t getSize() const;
        bool isEmpty() const;

        std::string toString() const;
    private:
        bool equals( const StackNode< T >& node1, const StackNode< T >& node2 ) const;

        StackNode< T >* head;
        StackNode< T >* tail;

        std::size_t size;
    };

    template < typename T >
    Stack< T >::Stack() :
        head( nullptr ),
        tail( nullptr ),
        size( 0 )
    {
    }

    template < typename T >
    Stack< T >::~Stack() noexcept
    {
        clear();
    }

    template < typename T >
    Stack< T >::Stack( const Stack& other ) :
        head( nullptr ),
        tail( nullptr ),
        size( 0 )
    {
        StackNode< T >* currentNodeOther = other.tail;

        while ( currentNodeOther != nullptr )
        {
            this->push( currentNodeOther->data );

            currentNodeOther = currentNodeOther->next;
        }
    }

    template < typename T >
    Stack< T >::Stack( Stack&& other ) noexcept :
        head( other.head ),
        tail( other.tail ),
        size( other.size )
    {
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    template < typename T >
    Stack< T >& Stack< T >::operator=( const Stack& rhs )
    {
        if ( this != &rhs )
        {
            clear();

            Stack< T > temp( rhs );

            *this = std::move( temp );
        }

        return *this;
    }

    template < typename T >
    Stack< T >& Stack< T >::operator=( Stack&& rhs ) noexcept
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
    bool Stack< T >::operator==( const Stack& rhs ) const
    {
        return this->equals( *( this->tail ), *( rhs.tail ) );
    }

    template < typename T >
    bool Stack< T >::operator!=( const Stack& rhs ) const
    {
        return !( this->equals( *( this->tail ), *( rhs.tail ) ) );
    }

    template < typename T >
    void Stack< T >::push( const T item )
    {
        StackNode< T >* newNode = new StackNode< T >();
        newNode->data = item;
        newNode->next = nullptr;

        // List is empty; head and tail node are identical.
        if ( isEmpty() )
        {
            newNode->previous = nullptr;

            this->head = newNode;
            this->tail = this->head;
        }
        // Push is of O(1) complexity, since we are adding 
        // to the head, and not traversing from the tail.
        else
        {
            newNode->previous = this->head;

            this->head->next = newNode;
            this->head = newNode;
        }

        ++( this->size );
    }

    template < typename T >
    T Stack< T >::pop()
    {
        // List is empty; return the default value for the type.
        if ( isEmpty() )
        {
            return T();
        }

        T item = this->head->data;
        StackNode< T >* previousNode = this->head->previous;

        delete this->head;

        // Pop is of O(1) complexity, since we are removing 
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
    std::size_t Stack< T >::getSize() const
    {
        return this->size;
    }

    template < typename T >
    std::string Stack< T >::toString() const
    {
        StackNode< T >* currentNode = this->head;

        std::stringstream list;
        while ( currentNode != nullptr )
        {
            list << currentNode->data << std::endl;

            currentNode = currentNode->next;
        }

        return list.str();
    }

    template < typename T >
    bool Stack< T >::isEmpty() const
    {
        return ( ( this->head == nullptr ) &&
                 ( this->tail == nullptr ) &&
                 ( this->size == 0 ) );
    }

    template < typename T >
    void Stack< T >::clear()
    {
        while ( !isEmpty() )
        {
            pop();
        }
    }

    template < typename T >
    bool Stack< T >::equals( const StackNode< T >& node1, const StackNode< T >& node2 ) const
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
