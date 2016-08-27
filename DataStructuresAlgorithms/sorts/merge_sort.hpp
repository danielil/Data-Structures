/**
 * Daniel Sebastian Iliescu
 *
 * Implementation of merge sort.
 */

#pragma once

#include "sort.hpp"

namespace
{
	static const std::size_t MERGE_THRESHOLD = 1;
}

namespace dsa {
namespace sorts {

struct merge
{
	/**
	 * The custom_implementation can work using only a forward iterator
	 * but because the std_implementation requires a bidirectional
	 * iterator, the wrapper function also requires it. Even though
	 * this is a stricter constraint, the std_implementation is an 
	 * in-place solution.
	 */
	template <
		typename Implementation = std_implementation,
		typename ForwardIterator >
	static void
	sort(
		ForwardIterator begin,
		ForwardIterator end )
	{
		Implementation::sort( begin, end );
	}

	struct std_implementation
	{
		template < typename BidirectionalIterator >
		static void sort(
			BidirectionalIterator begin,
			BidirectionalIterator end )
		{
			const auto length = std::distance( begin, end );

			if ( length > MERGE_THRESHOLD )
			{
				const auto mid = length / 2;
				const auto mid_it = std::next( begin, mid );

				sort( begin, mid_it );
				sort( mid_it, end );

				std::inplace_merge( begin, mid_it, end );
			}
		}
	};

	struct custom_implementation
	{
		template < typename ForwardIterator >
		static void sort(
			ForwardIterator begin,
			ForwardIterator end )
		{
			std::vector< 
				std::iterator_traits< decltype( begin ) >::value_type > merged_items(
					std::distance( begin, end ) );

			sort(
				begin,
				end,
				std::begin( merged_items ) );

			std::copy(
				std::begin( merged_items ),
				std::end( merged_items ),
				begin );
		}

		template <
			typename ForwardIterator,
			typename OutputIterator >
		static void
		sort(
			ForwardIterator input_begin,
			ForwardIterator input_end,
			OutputIterator output )
		{
			const auto length = std::distance( input_begin, input_end );

			if ( length > MERGE_THRESHOLD )
			{
				const auto mid = length / 2;
				const auto mid_it = std::next( input_begin, mid );

				sort( input_begin, mid_it, output );
				sort( mid_it, input_end, output );

				// Merge both sorted regions into sorted output
				dsa::merge(
					input_begin,
					mid_it,
					mid_it,
					input_end,
					output );

				// Replace first unsorted region with first sorted region
				std::copy(
					output,
					std::next( output, mid ),
					input_begin );

				// Replace second unsorted region with second sorted region
				std::copy(
					std::next( output, mid ),
					std::next( output, length ),
					mid_it );
			}
		}
	};
};

}}
