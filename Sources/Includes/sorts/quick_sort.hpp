/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 *
 * Implementation of quick sort.
 */

#pragma once

#include "sort.hpp"

namespace
{
	static constexpr std::size_t PARTITION_THRESHOLD = 16;
}

namespace dsa
{
	struct quick
	{
		struct std_implementation
		{
			template < typename Iterator >
			static void
			sort(
				Iterator begin,
				Iterator end )
			{
				if ( begin != end )
				{
					const auto size = static_cast< decltype( MERGE_THRESHOLD ) >( std::distance( begin, end ) );

					if ( size > PARTITION_THRESHOLD )
					{
						const auto center = std::next( begin, size / 2 );
						const auto container_end = std::prev( end );

						// Median-of-three pivot calculation
						auto pivot =
							std::max(
								std::min( *begin, *container_end ),
								std::min( std::max( *begin, *container_end ), *center ) );

						/**
						 * Two partitions are required if using the standard
						 * partion implementation since the returned
						 * iterator doesn't guarantee that the pivot itself
						 * will be in the neighbouring area where the predicate
						 * has failed.
						 */
						const auto partitions =
							std::make_pair(
								std::partition(
									begin,
									end,
									[pivot]( const auto& element )
									{
										return ( element < pivot );
									} ),
								std::partition(
									begin,
									end,
									[pivot]( const auto& element )
									{
										return ( element <= pivot );
									} ) );

						sort( begin, partitions.first );
						sort( partitions.second, end );
					}
					else
					{
						// Switch to insertion sort if the container size is small enough.
						insertion::std_implementation::sort( begin, end );
					}
				}
			}
		};

		struct custom_implementation
		{
			template < typename RandomAccessIterator >
			static void
			sort(
				RandomAccessIterator begin,
				RandomAccessIterator end )
			{
				if ( begin != end )
				{
					const auto size = static_cast< decltype( MERGE_THRESHOLD ) >( begin - end );

					if ( size > PARTITION_THRESHOLD )
					{
						const auto partition = dsa::partition( begin, end );

						sort( begin, partition );
						sort( partition + 1, end );
					}
					else
					{
						// Switch to insertion sort if the container size is small enough.
						insertion::std_implementation::sort( begin, end );
					}
				}
			}
		};
	};
}