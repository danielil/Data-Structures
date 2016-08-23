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
#include <random>

namespace
{
	using value_type = std::uint64_t;
	const auto ITERATIONS = 1000U;

	using container_type = std::array< value_type, ITERATIONS >;
}

namespace dsa
{
	void sort_tester(
		std::function<
			void(
				container_type::iterator,
				container_type::iterator ) >&& sort )
	{
		std::default_random_engine generator;
		container_type container;

		std::generate(
			std::begin( container ),
			std::end( container ),
			generator );

		sort(
			std::begin( container ),
			std::end( container ) );

		REQUIRE(
			std::is_sorted(
				std::cbegin( container ),
				std::cend( container ) ) );
	}

	TEST_CASE( "bubble sort", "sort" )
	{
		sort_tester(
			[](
				auto begin,
				auto end )
				{
					dsa::bubble_sort( begin, end );
				} );
	}

	TEST_CASE( "insertion sort", "sort" )
	{
		sort_tester(
			[](
				auto begin,
				auto end )
				{
					dsa::insertion_sort( begin, end );
				} );
	}

	TEST_CASE( "merge sort", "sort" )
	{
		sort_tester(
			[](
				auto begin,
				auto end )
				{
					dsa::merge_sort( begin, end );
				} );
	}

	TEST_CASE( "quick sort", "sort" )
	{
		// Fix iterator-based dsa::partition
		/*

		sort_tester(
			[](
				auto begin,
				auto end )
				{
					dsa::quick_sort( begin, end );
				} );

		*/
	}
}
