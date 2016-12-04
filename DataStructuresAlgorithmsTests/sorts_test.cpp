/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
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

namespace
{
	const std::string UNIT_NAME = "sort_";
}

namespace dsa
{
	template< typename SortImplementation >
	void sort_tester()
	{
		using value_type = std::int32_t;
		constexpr auto ITERATIONS = 1000U;

		std::array< value_type, ITERATIONS > container;

		generator< value_type > generator;
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

	TEST_CASE( ( UNIT_NAME + "bubble sort" ).c_str() )
	{
		sort_tester< bubble >();
	}

	TEST_CASE( ( UNIT_NAME + "selection sort (std implementation)" ).c_str() )
	{
		sort_tester< selection::std_implementation >();
	}

	TEST_CASE( ( UNIT_NAME + "selection sort (custom implementation)" ).c_str() )
	{
		sort_tester< selection::custom_implementation >();
	}

	TEST_CASE( ( UNIT_NAME + "insertion sort (std implementation)" ).c_str() )
	{
		sort_tester< insertion::std_implementation >();
	}

	TEST_CASE( ( UNIT_NAME + "insertion sort (custom implementation)" ).c_str() )
	{
		sort_tester< insertion::custom_implementation >();
	}

	TEST_CASE( ( UNIT_NAME + "merge sort (std implementation)" ).c_str() )
	{
		sort_tester< merge::std_implementation >();
	}

	TEST_CASE( ( UNIT_NAME + "merge sort (custom implementation)" ).c_str() )
	{
		sort_tester< merge::custom_implementation >();
	}

	TEST_CASE( ( UNIT_NAME + "quick sort" ).c_str() )
	{
		sort_tester< quick::std_implementation >();
	}

	TEST_CASE( ( UNIT_NAME + "quick sort (custom implementation)" ).c_str() )
	{
		sort_tester< quick::custom_implementation >();
	}

}
