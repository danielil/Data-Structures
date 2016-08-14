/**
 * Daniel Sebastian Iliescu
 *
 * An implementation of merge sort.
 */

#pragma once

#include "sort.hpp"

namespace
{
	static const std::size_t MERGE_THRESHOLD = 1;
}

namespace dsa
{
	template < typename iterator >
	void
	merge_sort(
		iterator begin,
		iterator end )
	{
		std::vector< std::iterator_traits< iterator >::value_type > mergedItems( std::distance( begin, end ) );

		merge_sort(
			begin,
			end,
			std::begin( mergedItems ) );

		std::copy(
			std::begin( mergedItems ),
			std::end( mergedItems ),
			begin );
	}

	template <
		typename input_iterator,
		typename output_iterator >
	void
	merge_sort(
		input_iterator inputBegin,
		input_iterator inputEnd,
		output_iterator output )
	{
		const auto length = std::distance( inputBegin, inputEnd );

		if ( length > MERGE_THRESHOLD )
		{
			const auto mid = length / 2;
			const auto midIt = std::next( inputBegin, mid );

			merge_sort( inputBegin, midIt, output );
			merge_sort( midIt, inputEnd, output );

			// Merge both sorted regions into sorted output
			dsa::merge(
				inputBegin,
				midIt,
				midIt,
				inputEnd,
				output );

			// Replace first unsorted region with first sorted region
			std::copy(
				output,
				std::next( output, mid ),
				inputBegin );

			// Replace second unsorted region with second sorted region
			std::copy(
				std::next( output, mid ),
				std::next( output, length ),
				midIt );
		}
	}
}
