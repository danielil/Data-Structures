/**
 * Daniel Sebastian Iliescu
 *
 * A collection of helper functions for sorting.
 */

#pragma once

#include <iterator>
#include <vector>

namespace dsa
{
	template<
		typename InputIterator1,
		typename InputIterator2,
		typename OutputIterator >
	auto
	merge(
		InputIterator1 inputBegin1,
		InputIterator1 inputEnd1,
		InputIterator2 inputBegin2,
		InputIterator2 inputEnd2,
		OutputIterator output )
	{
		while ( ( inputBegin1 != inputEnd1 ) &&
				( inputBegin2 != inputEnd2 ) )
		{
			if ( *inputBegin1 <= *inputBegin2 )
			{
				*output = *inputBegin1;
				++inputBegin1;
			}
			else
			{
				*output = *inputBegin2;
				++inputBegin2;
			}

			++output;
		}

		return ( inputBegin1 == inputEnd1 ) ? 
			std::copy( inputBegin2, inputEnd2, output ) : 
			std::copy( inputBegin1, inputEnd1, output );
	}

	/**
	 * This partition algorithm attempts to preserve 
	 * the condition that the elements less than the
	 * predicate (pivot) come exactly before it. This
	 * is different than a partition algorithm which 
	 * groups values less than the pivot but forgoes
	 * any guarantees about the relative pivot position.
	 */
	template < typename BidirectionalIterator >
	auto
	partition(
		BidirectionalIterator begin,
		BidirectionalIterator pivot,
		BidirectionalIterator end )
	{
		if ( begin != end )
		{
			// Move pivot to the far most right.
			std::swap( *pivot, *std::prev( end ) );

			for ( auto&& it = std::next( begin ); it != end; ++it )
			{
				if ( *it <= *pivot )
				{
					std::swap( *it, *begin );
					++begin;
				}
			}

			// Move back pivot to the index where the predicate
			// has failed to enforce proximity.
			std::swap( *begin, *std::prev( end ) );
		}

		return begin;
	}
}
