/**
 * Author: Daniel Sebastian Iliescu
 * 
 * Tester for the Doubly Linked List.
 */

#include <lists/doubly_linked_list.hpp>

#include <gtest/gtest.h>

#include <array>
#include <random>

namespace
{
	const auto ITERATIONS = 10000U;
	using value_type = std::uint64_t;
}

namespace dsa
{
	TEST( doubly_linked_list, default_constructor )
	{
		doubly_linked_list< value_type > list;

		ASSERT_TRUE( list.empty() );
	}

	TEST( doubly_linked_list, copy_constructor_push_front )
	{
		std::default_random_engine generator;

		doubly_linked_list< value_type > list1;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list1.push_front( generator() );
		}

		auto list2( list1 );

		ASSERT_TRUE( list1 == list2 );
	}

	TEST( doubly_linked_list, copy_constructor_push_back )
	{
		std::default_random_engine generator;

		doubly_linked_list< value_type > list1;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list1.push_back( generator() );
		}

		auto list2( list1 );

		ASSERT_TRUE( list1 == list2 );
	}

	TEST( doubly_linked_list, copy_assignment_push_front )
	{
		std::default_random_engine generator;

		doubly_linked_list< value_type > list1;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list1.push_front( generator() );
		}

		auto list2 = list1;

		ASSERT_TRUE( list1 == list2 );
	}

	TEST( doubly_linked_list, copy_assignment_push_back )
	{
		std::default_random_engine generator;

		doubly_linked_list< value_type > list1;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list1.push_back( generator() );
		}

		auto list2 = list1;

		ASSERT_TRUE( list1 == list2 );
	}

	TEST( doubly_linked_list, addition_operator_push_front )
	{
		std::default_random_engine generator;

		std::array< value_type, ITERATIONS > values;
		std::generate(
			std::begin( values ),
			std::end( values ),
			generator );

		doubly_linked_list< value_type > firstHalf;
		doubly_linked_list< value_type > secondHalf;

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			firstHalf.push_front( values[idx] );
			secondHalf.push_front( values[idx] );
		}

		auto wholeList = firstHalf + secondHalf;

		ASSERT_TRUE(
			std::equal(
				std::begin( wholeList ),
				std::end( firstHalf ),
				std::begin( firstHalf ),
				std::end( firstHalf ) ) );
		ASSERT_TRUE(
			std::equal(
				std::begin( secondHalf ),
				std::end( wholeList ),
				std::begin( secondHalf ),
				std::end( secondHalf ) ) );
	}

	TEST( doubly_linked_list, addition_operator_push_back )
	{
		std::default_random_engine generator;

		std::array< value_type, ITERATIONS > values;
		std::generate(
			std::begin( values ),
			std::end( values ),
			generator );

		doubly_linked_list< value_type > firstHalf;
		doubly_linked_list< value_type > secondHalf;

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			firstHalf.push_back( values[idx] );
			secondHalf.push_back( values[idx] );
		}

		auto wholeList = firstHalf + secondHalf;

		ASSERT_TRUE(
			std::equal(
				std::begin( wholeList ),
				std::end( firstHalf ),
				std::begin( firstHalf ),
				std::end( firstHalf ) ) );
		ASSERT_TRUE(
			std::equal(
				std::begin( secondHalf ),
				std::end( wholeList ),
				std::begin( secondHalf ),
				std::end( secondHalf ) ) );
	}

	TEST( doubly_linked_list, addition_equal_operator_push_front )
	{
		std::default_random_engine generator;

		std::array< value_type, ITERATIONS > values;
		std::generate(
			std::begin( values ),
			std::end( values ),
			generator );

		doubly_linked_list< value_type > list1;
		doubly_linked_list< value_type > list2;

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list1.push_front( values[idx] );
			list2.push_front( values[idx] );
		}

		list2 += list1;

		ASSERT_TRUE(
			std::equal(
				std::begin( list2 ),
				std::end( list1 ),
				std::begin( list2 ),
				std::end( list2 ) ) );
		ASSERT_TRUE(
			std::equal(
				std::begin( list1 ),
				std::end( list2 ),
				std::begin( list1 ),
				std::end( list1 ) ) );
	}

	TEST( doubly_linked_list, addition_equal_operator_push_back )
	{
		std::default_random_engine generator;

		std::array< value_type, ITERATIONS > values;
		std::generate(
			std::begin( values ),
			std::end( values ),
			generator );

		doubly_linked_list< value_type > list1;
		doubly_linked_list< value_type > list2;

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list1.push_back( values[idx] );
			list2.push_back( values[idx] );
		}

		list2 += list1;

		ASSERT_TRUE(
			std::equal(
				std::begin( list2 ),
				std::end( list1 ),
				std::begin( list2 ),
				std::end( list2 ) ) );
		ASSERT_TRUE(
			std::equal(
				std::begin( list1 ),
				std::end( list2 ),
				std::begin( list1 ),
				std::end( list1 ) ) );
	}

	TEST( doubly_linked_list, equality_operator_push_front )
	{
		std::default_random_engine generator;

		doubly_linked_list< value_type > list1;
		doubly_linked_list< value_type > list2;

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			auto value = generator();

			list1.push_front( value );
			list2.push_front( value );
		}

		ASSERT_TRUE( list1 == list2 );

		list1.clear();
		list2.clear();

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list1.push_front( generator() );
			list2.push_front( generator() );
		}

		ASSERT_TRUE( list1 != list2 );
	}

	TEST( doubly_linked_list, equality_operator_push_back )
	{
		std::default_random_engine generator;

		doubly_linked_list< value_type > list1;
		doubly_linked_list< value_type > list2;

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			auto value = generator();

			list1.push_back( value );
			list2.push_back( value );
		}

		ASSERT_TRUE( list1 == list2 );

		list1.clear();
		list2.clear();

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list1.push_back( generator() );
			list2.push_back( generator() );
		}

		ASSERT_TRUE( list1 != list2 );
	}

	TEST( doubly_linked_list, empty_pop_front )
	{
		doubly_linked_list< value_type > list;

		list.pop_front();

		ASSERT_TRUE( list.empty() );
	}

	TEST( doubly_linked_list, empty_pop_back )
	{
		doubly_linked_list< value_type > list;

		list.pop_back();

		ASSERT_TRUE( list.empty() );
	}

	TEST( doubly_linked_list, clear )
	{
		std::default_random_engine generator;

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_back( generator() );
		}

		list.clear();

		ASSERT_TRUE( list.empty() );
	}

	TEST( doubly_linked_list, empty_peek_front )
	{
		std::default_random_engine generator;

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_back( generator() );
		}

		auto size = list.size();
		auto value = list.peek_front();

		ASSERT_EQ( size, list.size() );
		ASSERT_EQ( value, list.pop_front() );
	}

	TEST( doubly_linked_list, empty_peek_back )
	{
		std::default_random_engine generator;

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_back( generator() );
		}

		auto size = list.size();
		auto value = list.peek_back();

		ASSERT_EQ( size, list.size() );
		ASSERT_EQ( value, list.pop_back() );
	}

	TEST( doubly_linked_list, push_front_pop_front )
	{
		std::default_random_engine generator;

		std::array< value_type, ITERATIONS > values;
		std::generate(
			std::begin( values ),
			std::end( values ),
			generator );

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_front( values[idx] );
		}

		ASSERT_EQ( ITERATIONS, list.size() );

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			std::size_t reverseIdx = ITERATIONS - 1 - idx;

			ASSERT_EQ( values[reverseIdx], list.pop_front() );
		}

		ASSERT_TRUE( list.empty() );
	}

	TEST( doubly_linked_list, push_front_pop_back )
	{
		std::default_random_engine generator;

		std::array< value_type, ITERATIONS > values;
		std::generate(
			std::begin( values ),
			std::end( values ),
			generator );

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_front( values[idx] );
		}

		ASSERT_EQ( ITERATIONS, list.size() );

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			ASSERT_EQ( values[idx], list.pop_back() );
		}

		ASSERT_TRUE( list.empty() );
	}

	TEST( doubly_linked_list, push_back_pop_front )
	{
		std::default_random_engine generator;

		std::array< value_type, ITERATIONS > values;
		std::generate(
			std::begin( values ),
			std::end( values ),
			generator );

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_back( values[idx] );
		}

		ASSERT_EQ( ITERATIONS, list.size() );

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			ASSERT_EQ( values[idx], list.pop_front() );
		}

		ASSERT_TRUE( list.empty() );
	}

	TEST( doubly_linked_list, push_back_pop_back )
	{
		std::default_random_engine generator;

		std::array< value_type, ITERATIONS > values;
		std::generate(
			std::begin( values ),
			std::end( values ),
			generator );

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_back( values[idx] );
		}

		ASSERT_EQ( ITERATIONS, list.size() );

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			std::size_t reverseIdx = ITERATIONS - 1 - idx;

			ASSERT_EQ( values[reverseIdx], list.pop_back() );
		}

		ASSERT_TRUE( list.empty() );
	}

	TEST( doubly_linked_list, iterator_push_front_begin_end )
	{
		std::default_random_engine generator;

		std::array< value_type, ITERATIONS > values;
		std::generate(
			std::begin( values ),
			std::end( values ),
			generator );

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_front( values[idx] );
		}

		ASSERT_TRUE(
			std::equal(
				std::begin( values ),
				std::end( values ),
				std::begin( list ),
				std::end( list ) ) );
	}

	TEST( doubly_linked_list, iterator_push_back_begin_end )
	{
		std::default_random_engine generator;

		std::array< value_type, ITERATIONS > values;
		std::generate(
			std::begin( values ),
			std::end( values ),
			generator );

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_back( values[idx] );
		}

		ASSERT_TRUE(
			std::equal(
				std::rbegin( values ),
				std::rend( values ),
				std::begin( list ),
				std::end( list ) ) );
	}

	TEST( doubly_linked_list, iterator_push_front_rbegin_rend )
	{
		std::default_random_engine generator;

		std::array< value_type, ITERATIONS > values;
		std::generate(
			std::begin( values ),
			std::end( values ),
			generator );

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_front( values[idx] );
		}

		ASSERT_TRUE(
			std::equal(
				std::rbegin( values ),
				std::rend( values ),
				std::rbegin( list ),
				std::rend( list ) ) );
	}

	TEST( doubly_linked_list, iterator_push_back_rbegin_rend )
	{
		std::default_random_engine generator;

		std::array< value_type, ITERATIONS > values;
		std::generate(
			std::begin( values ),
			std::end( values ),
			generator );

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_back( values[idx] );
		}

		ASSERT_TRUE(
			std::equal(
				std::begin( values ),
				std::end( values ),
				std::rbegin( list ),
				std::rend( list ) ) );
	}

	TEST( doubly_linked_list, iterator_push_front_cbegin_cend )
	{
		std::default_random_engine generator;

		std::array< value_type, ITERATIONS > values;
		std::generate(
			std::begin( values ),
			std::end( values ),
			generator );

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_front( values[idx] );
		}

		ASSERT_TRUE(
			std::equal(
				std::cbegin( values ),
				std::cend( values ),
				std::cbegin( list ),
				std::cend( list ) ) );
	}

	TEST( doubly_linked_list, iterator_push_back_cbegin_cend )
	{
		std::default_random_engine generator;

		std::array< value_type, ITERATIONS > values;
		std::generate(
			std::begin( values ),
			std::end( values ),
			generator );

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_back( values[idx] );
		}

		ASSERT_TRUE(
			std::equal(
				std::crbegin( values ),
				std::crend( values ),
				std::cbegin( list ),
				std::cend( list ) ) );
	}

	TEST( doubly_linked_list, iterator_push_front_crbegin_crend )
	{
		std::default_random_engine generator;

		std::array< value_type, ITERATIONS > values;
		std::generate(
			std::begin( values ),
			std::end( values ),
			generator );

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_front( values[idx] );
		}

		ASSERT_TRUE(
			std::equal(
				std::crbegin( values ),
				std::crend( values ),
				std::crbegin( list ),
				std::crend( list ) ) );
	}

	TEST( doubly_linked_list, iterator_push_back_crbegin_crend )
	{
		std::default_random_engine generator;

		std::array< value_type, ITERATIONS > values;
		std::generate(
			std::begin( values ),
			std::end( values ),
			generator );

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_back( values[idx] );
		}

		ASSERT_TRUE(
			std::equal(
				std::cbegin( values ),
				std::cend( values ),
				std::crbegin( list ),
				std::crend( list ) ) );
	}
}
