#include "sorts/bubble_sort.hpp"
#include "sorts/insertion_sort.hpp"
#include "sorts/merge_sort.hpp"
#include "sorts/quick_sort.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <random>

namespace
{
	const std::size_t ITERATIONS = 10;
}

namespace dsa
{
	TEST(sort, bubble_sort)
	{
		std::default_random_engine generator;

		unsigned int values[ITERATIONS];
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			values[idx] = generator();
		}

		dsa::bubblesort( values, ITERATIONS );

		ASSERT_TRUE( std::is_sorted( std::begin( values ), std::end( values ) ) );
	}

	TEST(sort, insertion_sort)
	{
		std::default_random_engine generator;

		unsigned int values[ITERATIONS];
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			values[idx] = generator();
		}

		dsa::insertionsort( values, ITERATIONS );

		ASSERT_TRUE( std::is_sorted( std::begin( values ), std::end( values ) ) );
	}

	TEST(sort, merge_sort)
	{
		std::default_random_engine generator;

		unsigned int values[ITERATIONS];
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			values[idx] = generator();
		}

		dsa::mergesort( values, ITERATIONS );

		ASSERT_TRUE( std::is_sorted( std::begin( values ), std::end( values ) ) );
	}

	TEST(sort, quick_sort)
	{
		std::default_random_engine generator;

		unsigned int values[ITERATIONS];
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			values[idx] = generator();
		}

		dsa::quicksort( values, ITERATIONS );

		ASSERT_TRUE( std::is_sorted( std::begin( values ), std::end( values ) ) );
	}
}
