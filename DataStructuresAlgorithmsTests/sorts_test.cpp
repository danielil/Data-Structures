/**
 * Author: Daniel Sebastian Iliescu
 *
 * Tester for the various sorting algorithms.
 */

#include "sorts/bubble_sort.hpp"
#include "sorts/selection_sort.hpp"
#include "sorts/insertion_sort.hpp"
#include "sorts/merge_sort.hpp"
#include "sorts/quick_sort.hpp"

#include "utilities/generator.hpp"

#include <catch.hpp>

#include <array>
#include <algorithm>
#include <functional>
#include <numeric>

namespace dsa::sorts
{
	template< typename SortImplementation >
	void sort_tester()
	{
		using value_type = std::uint64_t;
		const auto ITERATIONS = 1000U;

		using container_type = std::array< value_type, ITERATIONS >;

		generator< value_type > generator;
		container_type container;

		generator.fill_buffer(
			std::begin( container ),
			std::end( container ) );

		SortImplementation::sort(
			std::begin( container ),
			std::end( container ) );

		REQUIRE(
			std::is_sorted(
				std::cbegin( container ),
				std::cend( container ) ) );
	}

	TEST_CASE( "bubble sort", "sort" )
	{
		sort_tester< bubble >();
	}

	TEST_CASE( "selection sort (std implementation)", "sort" )
	{
		sort_tester< selection >();
	}

	TEST_CASE( "selection sort (custom implementation)", "sort" )
	{
		sort_tester< selection::custom_implementation >();
	}

	TEST_CASE( "insertion sort (std implementation)", "sort" )
	{
		sort_tester< insertion >();
	}

	TEST_CASE( "insertion sort (custom implementation)", "sort" )
	{
		sort_tester< insertion::custom_implementation >();
	}

	TEST_CASE( "merge sort (std implementation)", "sort" )
	{
		sort_tester< merge >();
	}

	TEST_CASE( "merge sort (custom implementation)", "sort" )
	{
		sort_tester< merge::custom_implementation >();
	}

	TEST_CASE( "quick sort", "sort" )
	{
		sort_tester< quick >();
	}

	TEST_CASE( "quick sort (custom implementation)", "sort" )
	{
		sort_tester< quick::custom_implementation >();
	}

}
