/**
* Author: Daniel Sebastian Iliescu
*
* Tester for the various sorting algorithms.
*/

#include <sorts/bubble_sort.hpp>
#include <sorts/insertion_sort.hpp>
#include <sorts/merge_sort.hpp>
#include <sorts/quick_sort.hpp>

#include <catch.hpp>

#include <array>
#include <algorithm>
#include <functional>
#include <numeric>
#include <random>

namespace
{
	using value_type = std::uint64_t;
	const auto ITERATIONS = 1000U;

	using container_type = std::array< value_type, ITERATIONS >;
}

namespace dsa {
namespace sorts {

	template< typename sort_implementation >
	void sort_tester()
	{
		std::default_random_engine generator;
		container_type container;

		std::generate(
			std::begin( container ),
			std::end( container ),
			generator );

		sort_implementation::sort(
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

}}
