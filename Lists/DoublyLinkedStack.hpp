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
        ~Stack();

        void push(T item);
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
        head(nullptr),
        tail(nullptr),
        size(0U)
    {
    }

    template < typename T >
    Stack< T >::~Stack()
    {
        clear();
    }

    template < typename T >
    void Stack< T >::push(T item)
    {
        StackNode< T >* newNode = new StackNode< T >();

        newNode->data = item;
        newNode->next = nullptr;

        // List is empty; push head node.
        if (isEmpty())
        {
            newNode->previous = nullptr;

            this->head = newNode;
            this->tail = head;
        }
        // Push attached nodes.
        else
        {
            newNode->previous = this->tail;

            this->tail->next = newNode;
            this->tail = newNode;
        }

        ++(this->size);
    }

    template < typename T >
    T Stack< T >::pop()
    {
        // List is empty; return the default value for the type.
        if (isEmpty())
        {
            return T();
        }

        T item;

        // List contains only head; need to only keep track of the current node, 
        // not previous node.
        if (this->size == 1U)
        {
            item = this->head->data;

            delete this->head;

            this->head = nullptr;
            this->tail = nullptr;
        }
        // List contains multiple nodes; need to keep track of current node and 
        // previous node for traversal.
        else
        {
            item = this->tail->data;

            StackNode<T>* previous = this->tail->previous;
            previous->next = nullptr;

            delete this->tail;
            this->tail = previous;
        }

        --(this->size);

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
        while (currentNode)
        {
            list << currentNode->data << std::endl;

            currentNode = currentNode->next;
        }

        return list.str();
    }

    template < typename T >
    bool Stack< T >::isEmpty() const
    {
        return ((this->head == nullptr) &&
            (this->size == 0U));
    }

    template < typename T >
    void Stack< T >::clear()
    {
        StackNode< T >* nextNode;

        while (this->head)
        {
            nextNode = this->head->next;

            delete this->head;

            this->head = nextNode;
        }

        this->size = 0;
    }
}
