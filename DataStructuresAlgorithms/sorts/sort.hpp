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
		typename input_iterator,
		typename output_iterator >
	auto
	merge(
		input_iterator inputBegin1,
		input_iterator inputEnd1,
		input_iterator inputBegin2,
		input_iterator inputEnd2,
		output_iterator output )
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

	template < typename iterator >
	auto
	partition(
		iterator begin,
		iterator end,
		iterator pivot )
	{
		auto position = pivot;

		while ( ( begin != end ) &&
				( pivot != end ) )
		{
			const auto pivotValue = *pivot;

			// Move pivot to the rightmost end
			std::swap( *pivot, *end );

			position = end;

			for ( auto it = begin; it != std::prev( end ); ++it )
			{
				if ( *it <= pivotValue )
				{
					std::swap( *it, *position );
					++position;
				}
			}

			// Move pivot to its final position
			std::swap( *position, *end );
		}

		return position;
	}
}
