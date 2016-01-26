/**
 * Daniel Sebastian Iliescu
 *
 * A collection of helper functions for sorting.
 */

#pragma once

namespace Sorts
{
    template < typename T >
    void copy( T* source, T* dest, const std::size_t start, const std::size_t end )
    {
        if ( ( dest != nullptr ) &&
             ( source != nullptr ) &&
             ( start < end ) )
        {
            for ( std::size_t idx = start; idx < end; ++idx )
            {
                dest[idx] = source[idx];
            }
        }
    }

    template < typename T >
    void swap( T* data, const std::size_t index1, const std::size_t index2 )
    {
        if ( ( data != nullptr ) &&
             ( index1 != index2 ) )
        {
            T temp = data[index1];
            data[index1] = data[index2];
            data[index2] = temp;
        }
    }

    template < typename T >
    void merge( T* source, T* dest, const std::size_t start, const std::size_t middle, const std::size_t end )
    {
        if ( ( source != nullptr ) &&
             ( dest != nullptr ) &&
             ( start < middle ) &&
             ( middle < end ) )
        {
            std::size_t j1 = start;
            std::size_t j2 = middle;

            for ( std::size_t idx = start; idx < end; ++idx )
            {
                if ( ( j1 < middle ) &&
                     ( ( j2 >= end ) ||
                       ( source[j1] <= source[j2] ) ) )
                {
                    dest[idx] = source[j1];
                    ++j1;
                }
                else
                {
                    dest[idx] = source[j2];
                    ++j2;
                }
            }
        }
    }

    template < typename T >
    std::size_t partition( T* data, const std::size_t start, const std::size_t end, const std::size_t pivot )
    {
        std::size_t position = pivot;

        if ( ( data != nullptr ) &&
             ( start < end ) &&
             ( pivot >= start ) &&
             ( pivot <= end ) )
        {
            const T pivotValue = data[pivot];

            // Move pivot to the rightmost end
            swap( data, pivot, end );
            position = start;

            for ( std::size_t idx = start; idx <= ( end - 1 ); idx++ )
            {
                if ( data[idx] <= pivotValue )
                {
                    swap( data, idx, position );
                    ++position;
                }
            }

            // Move pivot to its final position
            swap( data, position, end );
        }

        return position;
    }
}
