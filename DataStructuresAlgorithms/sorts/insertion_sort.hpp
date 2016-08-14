/**
 * Daniel Sebastian Iliescu
 *
 * An implementation of insertion sort.
 */

#pragma once

namespace dsa
{
	template < typename iterator >
	void insertion_sort(
		iterator begin,
		iterator end )
	{
		for ( auto it = ( begin + 1 ); it != end; ++it )
		{
			const auto currentItem = *it;
			const auto previousItem = *( it - 1 );

			auto insertPosition = it;

			while ( ( insertPosition != begin ) &&
					( currentItem < previousItem ) )
			{
				*insertPosition = previousItem;
				--insertPosition;
			}

			*insertPosition = currentItem;
		}
	}
}
