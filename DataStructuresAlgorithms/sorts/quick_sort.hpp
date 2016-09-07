/**
 * Daniel Sebastian Iliescu
 *
 * An implementation of quick sort.
 */

#pragma once

#include "sort.hpp"

namespace
{
	static const std::size_t PARTITION_THRESHOLD = 1;
}

namespace dsa {
namespace sorts {

struct quick
{
	template <
		typename Implementation = std_implementation,
		typename BidirectionalIterator >
	static void
	sort(
		BidirectionalIterator begin,
		BidirectionalIterator end )
	{
		Implementation::sort( begin, end );
	}

	struct std_implementation
	{
		template < typename ForwardIterator >
		static void
		sort(
			ForwardIterator begin,
			ForwardIterator end )
		{
			if ( begin != end )
			{
				const auto size = std::distance( begin, end );

				if ( size > PARTITION_THRESHOLD )
				{
					const auto mid = size / 2;
					const auto pivot = *std::next( begin, mid );

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
			}
		}
	};

	struct custom_implementation
	{
		template < typename BidirectionalIterator >
		static void
		sort(
			BidirectionalIterator begin,
			BidirectionalIterator end )
		{
			if ( begin != end )
			{
				const auto size = std::distance( begin, end );

				if ( size > PARTITION_THRESHOLD )
				{
					const auto mid = size / 2;
					const auto pivot = std::next( begin, mid );

					const auto partition = dsa::partition( begin, pivot, end );

					sort( begin, partition );
					sort( std::next( partition ), end );
				}
			}
		}
	};
};

}}
