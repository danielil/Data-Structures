/**
 * Daniel Sebastian Iliescu
 *
 * Implementation of selection sort.
 */

#pragma once

#include <algorithm>
#include <utility>

namespace dsa {
namespace sorts {

struct selection
{
	struct std_implementation
	{
		template < typename Iterator >
		static void
		sort(
				Iterator begin,
				Iterator end )
		{
			using std::swap;

			for ( auto current_it = begin; current_it != end; ++current_it )
			{
				auto current_minimum = std::min_element( current_it, end );

				swap( *current_minimum, *current_it );
			}
		}
	};

	struct custom_implementation
	{
		template < typename Iterator >
		static void
		sort(
				Iterator begin,
				Iterator end )
		{
			using std::swap;

			for ( auto current_it = begin; current_it != std::prev( end ); ++current_it )
			{
				auto current_minimum = current_it;

				for ( auto search_minimum_it = std::next( current_it ); search_minimum_it != end; ++search_minimum_it )
				{
					if ( *search_minimum_it < *current_minimum )
					{
						current_minimum = search_minimum_it;
					}
				}

				if ( *current_it != *current_minimum )
				{
					swap( *current_it, *current_minimum );
				}
			}
		}
	};

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
