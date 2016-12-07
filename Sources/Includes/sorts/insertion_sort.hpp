/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 *
 * Implementation of insertion sort.
 */

#pragma once

namespace dsa
{
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
	};
}