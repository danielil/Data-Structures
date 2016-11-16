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
		InputIterator1 input_begin1,
		InputIterator1 input_end1,
		InputIterator2 input_begin2,
		InputIterator2 input_end2,
		OutputIterator output )
	{
		while ( ( input_begin1 != input_end1 ) &&
				( input_begin2 != input_end2 ) )
		{
			if ( *input_begin1 <= *input_begin2 )
			{
				*output = *input_begin1;
				++input_begin1;
			}
			else
			{
				*output = *input_begin2;
				++input_begin2;
			}

			++output;
		}

		return ( input_begin1 == input_end1 ) ?
			std::copy( input_begin2, input_end2, output ) :
			std::copy( input_begin1, input_end1, output );
	}

	/**
	 * This partition algorithm attempts to preserve 
	 * the condition that the elements less than the
	 * predicate (pivot) come exactly before it. This
	 * is different than a partition algorithm which 
	 * groups values less than the pivot but forgoes
	 * any guarantees about the relative pivot position.
	 */
	template < typename RandomAccessIterator >
	auto
	partition(
		RandomAccessIterator begin,
		RandomAccessIterator end )
	{
		const auto center = begin + ( end - begin ) / 2;
		const auto container_end = end - 1;

		// Median-of-three pivot calculation
		auto pivot =
			std::max(
				std::min( *begin, *container_end ),
				std::min( std::max( *begin, *container_end ), *center ) );

		auto mid = begin;

		while ( mid != end )
		{
			if ( *mid < pivot )
			{
				std::swap( *begin, *mid );

				++begin;
				++mid;
			}
			else if ( *mid == pivot )
			{
				++mid;
			}
			else
			{
				--end;

				std::swap( *end, *mid );
			}
		}

		return begin;
	}
}
