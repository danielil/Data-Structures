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
        QueueNode< T >* next;
    };

    template < typename T >
    class Queue
    {
    public:
        Queue();
        ~Queue();

        void enqueue( T item );
        T dequeue();

        std::size_t getSize() const;
        bool isEmpty() const;

        std::string toString() const;
    private:
        void clear();

        QueueNode< T >* head;
        std::size_t size;
    };

    template < typename T >
    Queue< T >::Queue() :
        head( nullptr ),
        size( 0U )
    {
    }

    template < typename T >
    Queue< T >::~Queue()
    {
        clear();
    }

    template < typename T >
    void Queue< T >::enqueue( T item )
    {
        QueueNode< T >* newNode = new QueueNode< T >();

        newNode->data = item;
        newNode->next = nullptr;

        // List is empty; push head node.
        if ( isEmpty() )
        {
            this->head = newNode;
        }
        // Push attached nodes.
        else
        {
            QueueNode< T >* currentNode = head;

            while ( currentNode->next )
            {
                currentNode = currentNode->next;
            }

            currentNode->next = newNode;
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

        // List contains multiple nodes; need to keep track of current node and 
        // next node for traversal.
        QueueNode< T >* currentNode = this->head;
        QueueNode< T >* nextNode = currentNode->next;

        T item = currentNode->data;

        delete currentNode;
        this->head = nextNode;

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
        QueueNode< T >* currentNode = head;

        std::stringstream list;
        while ( currentNode )
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
                 ( this->size == 0U ) );
    }

    template < typename T >
    void Queue< T >::clear()
    {
        QueueNode< T >* nextNode;

        while ( this->head )
        {
            nextNode = this->head->next;

            delete this->head;

            this->head = nextNode;
        }
    }
}

