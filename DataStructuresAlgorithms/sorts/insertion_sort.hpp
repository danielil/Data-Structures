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
	/**
	 * The std_implementation can work using only a forward iterator
	 * but because the custom_implementation requires a bidirectional
	 * iterator, the wrapper function also requires it.
	 */
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
		template < typename BidirectionalIterator >
		static void
		sort(
			BidirectionalIterator begin,
			BidirectionalIterator end )
		{
			for ( auto it = std::next( begin ); it != end; ++it )
			{
				const auto currentItem = *it;
				const auto previousItem = *std::prev( it );

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
	};
};

}}
