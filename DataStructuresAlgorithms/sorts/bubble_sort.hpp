/**
 * Daniel Sebastian Iliescu
 *
 * Implementation of bubble sort.
 */

#pragma once

namespace dsa {
namespace sorts {

struct bubble
{
	template < typename ForwardIterator >
	static void
	sort(
		ForwardIterator begin,
		ForwardIterator end )
	{
		for ( auto it = begin; it != end; ++it )
		{
			for ( auto shift_it = begin; shift_it != std::prev( end ); ++shift_it )
			{
				auto& current_item = *shift_it;
				auto& next_item = *std::next( shift_it );

				if ( current_item > next_item )
				{
					std::swap( current_item, next_item );
				}
			}
		}
	}
};

}}
