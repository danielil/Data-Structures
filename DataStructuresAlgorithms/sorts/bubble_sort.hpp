/**
 * Daniel Sebastian Iliescu
 *
 * An implementation of bubble sort.
 */

#pragma once

#include "sort.hpp"

namespace dsa
{
	template < typename iterator >
	void bubble_sort(
		iterator begin,
		iterator end )
	{
		for ( auto it = begin; it != end; ++it )
		{
			for ( auto shiftIt = begin; shiftIt != ( end - 1 ); ++shiftIt )
			{
				auto& currentItem = *shiftIt;
				auto& nextItem = *( shiftIt + 1 );

				if ( currentItem > nextItem )
				{
					std::swap( currentItem, nextItem );
				}
			}
		}
	}
}
