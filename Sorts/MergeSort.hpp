/**
 * Daniel Sebastian Iliescu
 *
 * An implementation of merge sort.
 */

#pragma once

#include "Sort.hpp"

#include <memory>

namespace Sorts
{
    template < typename T >
    void mergesort( T* data, const std::size_t size )
    {
        if ( ( data ) &&
             ( size >= 0U ) )
        {
            std::unique_ptr< T > dest( new T[size] );

            mergesort( data, dest.get(), 0, size );
            copy( dest.get(), data, 0, size );
        }
    }

    template < typename T >
    void mergesort( T* data, T* dest, const std::size_t start, const std::size_t end )
    {
        if ( ( start + 1 ) < end )
        {
            const std::size_t mid = static_cast< std::size_t >( ( start + end ) / 2 );

            mergesort( data, dest, start, mid );
            mergesort( data, dest, mid, end );

            merge( data, dest, start, mid, end );
            copy( dest, data, start, end );
        }
    }
}
