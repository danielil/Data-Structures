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

	void sort_tester(
		std::function<
			void(
				container_type::iterator,
				container_type::iterator ) >&& sort )
	{
		std::default_random_engine generator;
		container_type container;

		std::iota(
			std::rbegin( container ),
			std::rend( container ),
			0 );

		if ( false )
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
					bubble::sort( begin, end );
				} );
	}

	TEST_CASE( "insertion sort (std implementation)", "sort" )
	{
		sort_tester(
			[](
				auto begin,
				auto end )
				{
					insertion::sort( begin, end );
				} );
	}

	TEST_CASE( "insertion sort (custom implementation)", "sort" )
	{
		sort_tester(
			[](
				auto begin,
				auto end )
				{
					insertion::sort< insertion::custom_implementation >( begin, end );
				} );
	}

	TEST_CASE( "merge sort (std implementation)", "sort" )
	{
		sort_tester(
			[](
				auto begin,
				auto end )
				{
					merge::sort( begin, end );
				} );
	}

	TEST_CASE( "merge sort (custom implementation)", "sort" )
	{
		sort_tester(
			[](
				auto begin,
				auto end )
				{
					merge::sort< merge::custom_implementation >( begin, end );
				} );
	}

	TEST_CASE( "quick sort", "sort" )
	{
		sort_tester(
			[](
				auto begin,
				auto end )
				{
					quick::sort( begin, end );
				} );
	}

}}
