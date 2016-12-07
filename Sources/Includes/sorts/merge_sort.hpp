/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 *
 * Implementation of merge sort.
 */

#pragma once

#include "sort.hpp"

namespace
{
	static constexpr std::size_t MERGE_THRESHOLD = 16;
}

namespace dsa
{
	struct merge
	{
		struct std_implementation
		{
			template < typename BidirectionalIterator >
			static void sort(
				BidirectionalIterator begin,
				BidirectionalIterator end )
			{
				const auto size = static_cast< decltype( MERGE_THRESHOLD ) >( std::distance( begin, end ) );

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
					insertion::std_implementation::sort( begin, end );
				}
			}
		};

		/**
		 * The custom_implementation is limited to a forward iterator
		 * but because the std_implementation requires a bidirectional
		 * iterator, the wrapper function also requires it. Even though
		 * this is a stricter constraint, the std_implementation is an
		 * in-place solution.
		 */
		struct custom_implementation
		{
			template < typename Iterator >
			static void sort(
				Iterator begin,
				Iterator end )
			{
				using input_type = typename std::iterator_traits< decltype( begin ) >::value_type;

				std::vector< input_type > merged_items( std::distance( begin, end ) );

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
				typename InputIterator,
				typename OutputIterator >
			static void
			sort(
				InputIterator begin,
				InputIterator end,
				OutputIterator output )
			{
				const auto size = static_cast< decltype( MERGE_THRESHOLD ) >( std::distance( begin, end ) );

				if ( size > MERGE_THRESHOLD )
				{
					const auto center = size / 2;
					const auto mid = std::next( begin, center );

					sort( begin, mid, output );
					sort( mid, end, output );

					// Merge both sorted regions into sorted output
					dsa::merge(
						begin,
						mid,
						mid,
						end,
						output );

					// Replace first unsorted region with first sorted region
					std::copy(
						output,
						std::next( output, center ),
						begin );

					// Replace second unsorted region with second sorted region
					std::copy(
						std::next( output, center ),
						std::next( output, size ),
						mid );
				}
				else
				{
					// Switch to insertion sort if the container size is small enough.
					insertion::std_implementation::sort( begin, end );
				}
			}
		};
	};
}