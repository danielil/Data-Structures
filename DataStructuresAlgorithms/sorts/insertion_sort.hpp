/**
 * Daniel Sebastian Iliescu
 *
 * Implementation of insertion sort.
 */

#pragma once

namespace dsa {
namespace sorts {

struct insertion
{
	struct std_implementation
	{
		template < typename Iterator >
		static void
		sort(
				Iterator begin,
				Iterator end )
		{
			for ( auto it = begin; it != end; ++it )
			{
				std::rotate(
						std::upper_bound(
								begin,
								it,
								*it ),
						it,
						std::next( it ) );
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
			for ( auto it = std::next( begin ); it != end; ++it )
			{
				const auto previousItem = std::prev( it );
				auto insertPosition = it;

				while ( ( insertPosition != begin ) &&
						( *it < *previousItem ) )
				{
					*insertPosition = *previousItem;
					--insertPosition;
				}

				*insertPosition = *it;
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
