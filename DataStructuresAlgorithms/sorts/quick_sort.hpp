/**
 * Daniel Sebastian Iliescu
 *
 * An implementation of quick sort.
 */

#pragma once

#include "sort.hpp"

namespace dsa
{
	template < typename iterator >
	void
	quick_sort(
		iterator begin,
		iterator end )
	{
		if ( begin < end )
		{
			const auto mid = std::distance( begin, end ) / 2;
			auto pivot = dsa::partition( begin, end, std::next( begin, mid ) );

			quick_sort( begin, pivot );
			quick_sort( std::next( pivot ), end );
		}
	}
}
