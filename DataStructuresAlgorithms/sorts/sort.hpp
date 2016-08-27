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

	template <
		typename ForwardIt,
		typename UnaryPredicate >
	auto
	partition(
		ForwardIt begin,
		ForwardIt end,
		UnaryPredicate predicate )
	{
		begin = std::find_if_not( begin, end, predicate );

		if ( begin != end )
		{
			for ( auto&& it = std::next( begin ); it != end; ++it )
			{
				if ( predicate( *it ) )
				{
					std::swap( *it, *begin );
					++begin;
				}
			}
		}

		return begin;
	}
}
