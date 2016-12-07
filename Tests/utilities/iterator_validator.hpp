/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 *
 * Validating iterators for generic containers.
 */

#include <iostream>

namespace dsa
{
	template< typename InputIterator >
	bool
	is_valid_iterator(
		InputIterator begin,
		InputIterator end )
	{
		const auto length = std::distance( begin, end );

		// If we cannot perform std::prev( end ) because the end
		// iterator points to null, then we must find another way
		// to get the second-to-last element in the container.
		const auto second_to_last = std::next( begin, length - 1 );

		for ( auto it = begin; it != second_to_last; ++it )
		{
			const auto it_before_increment = it;
			const auto postfix_increment_value = it++;
			const auto postfix_increment_test = ( *it_before_increment == *postfix_increment_value );

			const auto it_before_decrement = it;
			const auto postfix_decrement_value = it--;
			const auto postfix_decrement_test = ( *it_before_decrement == *postfix_decrement_value );

			if ( !postfix_increment_test ||
				 !postfix_decrement_test )
			{
				return false;
			}
		}

		return true;
	}
}