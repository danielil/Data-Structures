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
        Stack( const Stack& other );
        Stack( Stack&& other ) noexcept;

        Stack& operator=( const Stack& other );
        Stack& operator=( Stack&& other ) noexcept;

        ~Stack() noexcept;

        void push( const T item );
        T pop();

        std::size_t getSize() const;
        bool isEmpty() const;

        std::string toString() const;
    private:
        void clear();

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
    Stack< T >::Stack( const Stack& other ) :
        head( other.head ),
        tail( other.tail ),
        size( other.size )
    {
        clear();

        StackNode< T >* currentNodeOther = other.head;

        while ( currentNodeOther )
        {
            push( currentNodeOther->data );

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
    Stack< T >& Stack< T >::operator=( const Stack& other )
    {
        if ( this != &other )
        {
            Stack< T > stack( other );

            *this = std::move( stack );
        }

        return *this;
    }

    template < typename T >
    Stack< T >& Stack< T >::operator=( Stack&& other ) noexcept
    {
        clear();

        this->head = other.head;
        this->tail = other.tail;
        this->size = other.size;

        other.head = nullptr;
        other.tail = nullptr;
        other.size = nullptr;

        return *this;
    }

    template < typename T >
    Stack< T >::~Stack() noexcept
    {
        clear();
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
        // Push should be of O(1) complexity, since we are
        // adding to the head, and not traversing from the tail.
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

        // List contains only head; no need to keep track of 
        // previous and next node.
        if ( this->size == 1 )
        {
            delete this->head;

            this->head = nullptr;
            this->tail = nullptr;
        }
        // Pop should be of O(1) complexity, since we are
        // removing the head, and not traversing from the tail.
        else
        {
            StackNode< T >* previousNode = this->head->previous;
            previousNode->next = nullptr;

            delete this->head;

            this->head = previousNode;
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
        StackNode< T >* currentNode = head;

        std::stringstream list;
        while ( currentNode )
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
}
