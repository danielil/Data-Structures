/**
* Author: Daniel Sebastian Iliescu
*
* Tester for the various sorting algorithms.
*/

#include <sorts/bubble_sort.hpp>
#include <sorts/insertion_sort.hpp>
#include <sorts/merge_sort.hpp>
#include <sorts/quick_sort.hpp>

#include <gtest/gtest.h>

#include <array>
#include <algorithm>
#include <random>

namespace dsa
{
	class sort_tester : public testing::Test
	{
	protected:

		using value_type = uint64_t;
		static const auto ITERATIONS = 10000U;

		void SetUp() override
		{
			std::generate(
				std::begin( container ),
				std::end( container ),
				this->generator );
		}

		std::array< value_type, ITERATIONS > container;

	private:

		std::default_random_engine generator;
	};

	TEST_F( sort_tester, bubble_sort )
	{
		dsa::bubble_sort(
			std::begin( container ),
			std::end( container ) );

		ASSERT_TRUE(
			std::is_sorted(
				std::begin( container ),
				std::end( container ) ) );
	}

	TEST_F( sort_tester, insertion_sort )
	{
		dsa::insertion_sort(
			std::begin( container ),
			std::end( container ) );

		ASSERT_TRUE(
			std::is_sorted(
				std::begin( container ),
				std::end( container ) ) );
	}

	TEST_F( sort_tester, merge_sort )
	{
		dsa::merge_sort(
			std::begin( container ),
			std::end( container ) );

		ASSERT_TRUE(
			std::is_sorted(
				std::begin( container ),
				std::end( container ) ) );
	}

	TEST_F( sort_tester, quick_sort )
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
