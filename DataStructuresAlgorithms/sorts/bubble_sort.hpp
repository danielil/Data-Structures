/**
 * Daniel Sebastian Iliescu
 *
 * Implementation of bubble sort.
 * 
 * Worst case performance: O(n^2)
 * Best case performance: O(n)
 * Average case performance: O(n^2)
 * Worst case space complexity: O(1)
 */

#pragma once

namespace dsa {
namespace sorts {

struct bubble
{
	template < typename Iterator >
	static void
	sort(
		Iterator begin,
		Iterator end )
	{
		using std::swap;

		for ( auto it = begin; it != end; ++it )
		{
			bool swapped = false;

			for ( auto shift_it = begin; shift_it != std::prev( end ); ++shift_it )
			{
				auto current_item = shift_it;
				auto next_item = std::next( shift_it );

				if ( *current_item > *next_item )
				{
					swap( *current_item, *next_item );

					swapped = true;
				}
			}

			if ( !swapped )
			{
				break;
			}
		}
	}
};

}}
