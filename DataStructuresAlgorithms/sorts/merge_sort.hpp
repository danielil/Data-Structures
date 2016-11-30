/**
 * Daniel Sebastian Iliescu
 *
 * Implementation of merge sort.
 */

#pragma once

#include "sort.hpp"

namespace
{
	static const std::size_t MERGE_THRESHOLD = 16;
}

namespace dsa {
namespace sorts {

struct merge
{
	struct std_implementation
	{
		template < typename Iterator >
		static void sort(
				Iterator begin,
				Iterator end )
		{
			const auto size = std::distance( begin, end );

			if ( size > MERGE_THRESHOLD )
			{
				const auto center = size / 2;
				const auto mid = std::next( begin, center );

				sort( begin, mid );
				sort( mid, end );

				std::inplace_merge( begin, mid, end );
			}
			else
			{
				// Switch to insertion sort if the container size is small enough.
				insertion::sort( begin, end );
			}
		}
	};

	struct custom_implementation
	{
		template < typename Iterator >
		static void sort(
				Iterator begin,
				Iterator end )
		{
			using input_type = typename std::iterator_traits< decltype( begin ) >::value_type;

			std::vector< input_type > merged_items(
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
				typename Iterator,
				typename OutputIterator >
		static void
		sort(
				Iterator input_begin,
				Iterator input_end,
				OutputIterator output )
		{
			const auto size = std::distance( input_begin, input_end );

			if ( size > MERGE_THRESHOLD )
			{
				const auto center = size / 2;
				const auto mid = std::next( input_begin, center );

				sort( input_begin, mid, output );
				sort( mid, input_end, output );

				// Merge both sorted regions into sorted output
				dsa::merge(
						input_begin,
						mid,
						mid,
						input_end,
						output );

				// Replace first unsorted region with first sorted region
				std::copy(
						output,
						std::next( output, center ),
						input_begin );

				// Replace second unsorted region with second sorted region
				std::copy(
						std::next( output, center ),
						std::next( output, size ),
						mid );
			}
			else
			{
				// Switch to insertion sort if the container size is small enough.
				insertion::sort( input_begin, input_end );
			}
		}
	};

	/**
	 * The custom_implementation can work using only a forward iterator
	 * but because the std_implementation requires a bidirectional
	 * iterator, the wrapper function also requires it. Even though
	 * this is a stricter constraint, the std_implementation is an 
	 * in-place solution.
	 */
	template <
		typename Implementation = std_implementation,
		typename Iterator >
	static void
	sort(
		Iterator begin,
		Iterator end )
	{
		Implementation::sort( begin, end );
	}
};

}}
