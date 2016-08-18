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
#include <random>

namespace
{
	using value_type = std::uint64_t;
	const auto ITERATIONS = 1000U;
}

namespace dsa
{
	TEST_CASE( "bubble sort", "sort" )
	{
		std::default_random_engine generator;
		std::array< value_type, ITERATIONS > container;
		std::generate(
			std::begin( container ),
			std::end( container ),
			generator );

		dsa::bubble_sort(
			std::begin( container ),
			std::end( container ) );

		REQUIRE(
			std::is_sorted(
				std::begin( container ),
				std::end( container ) ) );
	}

	TEST_CASE( "insertion sort", "sort" )
	{
		std::default_random_engine generator;
		std::array< value_type, ITERATIONS > container;
		std::generate(
			std::begin( container ),
			std::end( container ),
			generator );

		dsa::insertion_sort(
			std::begin( container ),
			std::end( container ) );

		REQUIRE(
			std::is_sorted(
				std::begin( container ),
				std::end( container ) ) );
	}

	TEST_CASE( "merge sort", "sort" )
	{
		std::default_random_engine generator;
		std::array< value_type, ITERATIONS > container;
		std::generate(
			std::begin( container ),
			std::end( container ),
			generator );

		dsa::merge_sort(
			std::begin( container ),
			std::end( container ) );

		REQUIRE(
			std::is_sorted(
				std::begin( container ),
				std::end( container ) ) );
	}

	TEST_CASE( "quick sort", "sort" )
	{
		// Fix iterator-based dsa::partition
		/*

		dsa::quick_sort(
			std::begin( container ),
			std::end( container ) );

		ASSERT_TRUE(
			std::is_sorted(
				std::begin( container ),
				std::end( container ) ) );

		*/
	}
}
