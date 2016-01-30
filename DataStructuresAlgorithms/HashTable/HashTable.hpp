/**
 * Daniel Sebastian Iliescu
 *
 * An implementation of the Queue (FIFO) data structure.
 */

#pragma once

namespace Hash
{
    template < typename T >
    class HashTable
    {
    public:
        HashTable();
        ~HashTable();

    private:
        void hashFunction();
    };
}