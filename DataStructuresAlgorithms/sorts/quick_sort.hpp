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
		typename ForwardIt >
	static void
	sort(
		ForwardIt begin,
		ForwardIt end )
	{
		Implementation::sort( begin, end );
	}

	struct std_implementation
	{
		template < typename ForwardIt >
		static void
		sort(
			ForwardIt begin,
			ForwardIt end )
		{
			if ( begin != end )
			{
				const auto size = std::distance( begin, end );

				if ( size > PARTITION_THRESHOLD )
				{
					const auto mid = size / 2;
					const auto pivot = *std::next( begin, mid );

					const std::pair< ForwardIt, ForwardIt > partitions =
					{
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
								return !( pivot < element );
							} )
					};

					sort( begin, partitions.first );
					sort( partitions.second, end );
				}
			}
		}
	};
};

}}
