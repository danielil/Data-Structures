#include "lists/doubly_linked_list.hpp"

#include <gtest/gtest.h>

#include <array>
#include <random>

namespace
{
	const std::size_t ITERATIONS = 10;

    using ListValueType = unsigned int;
}

namespace dsa
{
	TEST(constructor_test)
	{
		doubly_linked_list< ListValueType > list;

		ASSERT_TRUE( list.empty() );
	}

	TEST(copy_constructor_push_front_test)
	{
		std::default_random_engine generator;

		doubly_linked_list< ListValueType > list1;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list1.push_front( generator() );
		}

		auto list2( list1 );

		ASSERT_TRUE( list1 == list2 );
	}

	TEST(copy_constructor_push_back_test)
	{
		std::default_random_engine generator;

		doubly_linked_list< ListValueType > list1;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list1.push_back( generator() );
		}

		auto list2( list1 );

		ASSERT_TRUE( list1 == list2 );
	}

	TEST(copy_assignment_push_front_test)
	{
		std::default_random_engine generator;

		doubly_linked_list< ListValueType > list1;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list1.push_front( generator() );
		}

		auto list2 = list1;

		ASSERT_TRUE( list1 == list2 );
	}

	TEST(copy_assignment_push_back_test)
	{
		std::default_random_engine generator;

		doubly_linked_list< ListValueType > list1;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list1.push_back( generator() );
		}

		auto list2 = list1;

		ASSERT_TRUE( list1 == list2 );
	}

	TEST(addition_operator_push_front_test)
	{
		std::default_random_engine generator;

		doubly_linked_list< ListValueType > list1;
		doubly_linked_list< ListValueType > list2;
		std::array< ListValueType, ITERATIONS > values;

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			values[idx] = generator();

			list1.push_front( values[idx] );
			list2.push_front( values[idx] );
		}

		auto list3 = list1 + list2;

		ASSERT_TRUE( std::equal( std::begin( list3 ), std::end( list1 ), std::begin( list1 ), std::end( list1 ) ) );
		ASSERT_TRUE( std::equal( std::begin( list2 ), std::end( list3 ), std::begin( list2 ), std::end( list2 ) ) );
	}

	TEST(addition_operator_push_back_test)
	{
		std::default_random_engine generator;

		doubly_linked_list< ListValueType > list1;
		doubly_linked_list< ListValueType > list2;
		std::array< ListValueType, ITERATIONS > values;

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			values[idx] = generator();

			list1.push_back( values[idx] );
			list2.push_back( values[idx] );
		}

		auto list3 = list1 + list2;

		ASSERT_TRUE( std::equal( std::begin( list3 ), std::end( list1 ), std::begin( list1 ), std::end( list1 ) ) );
		ASSERT_TRUE( std::equal( std::begin( list2 ), std::end( list3 ), std::begin( list2 ), std::end( list2 ) ) );
	}

	TEST(addition_equal_operator_push_front_test)
	{
		std::default_random_engine generator;

		doubly_linked_list< ListValueType > list1;
		doubly_linked_list< ListValueType > list2;
		std::array< ListValueType, ITERATIONS > values;

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			values[idx] = generator();

			list1.push_front( values[idx] );
			list2.push_front( values[idx] );
		}

		list2 += list1;

		ASSERT_TRUE( std::equal( std::begin( list2 ), std::end( list1 ), std::begin( list2 ), std::end( list2 ) ) );
		ASSERT_TRUE( std::equal( std::begin( list1 ), std::end( list2 ), std::begin( list1 ), std::end( list1 ) ) );
	}

	TEST(addition_equal_operator_push_back_test)
	{
		std::default_random_engine generator;

		doubly_linked_list< ListValueType > list1;
		doubly_linked_list< ListValueType > list2;
		std::array< ListValueType, ITERATIONS > values;

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			values[idx] = generator();

			list1.push_back( values[idx] );
			list2.push_back( values[idx] );
		}

		list2 += list1;

		ASSERT_TRUE( std::equal( std::begin( list2 ), std::end( list1 ), std::begin( list2 ), std::end( list2 ) ) );
		ASSERT_TRUE( std::equal( std::begin( list1 ), std::end( list2 ), std::begin( list1 ), std::end( list1 ) ) );
	}

	TEST(equality_push_front_test)
	{
		std::default_random_engine generator;

		doubly_linked_list< ListValueType > list1;
		doubly_linked_list< ListValueType > list2;

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

	TEST(equality_push_back_test)
	{
		std::default_random_engine generator;

		doubly_linked_list< ListValueType > list1;
		doubly_linked_list< ListValueType > list2;

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

	TEST(empty_pop_front_test)
	{
		doubly_linked_list< ListValueType > list;

		list.pop_front();

		ASSERT_TRUE( list.empty() );
	}

	TEST(empty_pop_back_test)
	{
		doubly_linked_list< ListValueType > list;

		list.pop_back();

		ASSERT_TRUE( list.empty() );
	}

	TEST(clear_test)
	{
		std::default_random_engine generator;

		doubly_linked_list< ListValueType > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_back( generator() );
		}

		list.clear();

		ASSERT_TRUE( list.empty() );
	}

	TEST(empty_peek_front_test)
	{
		std::default_random_engine generator;

		doubly_linked_list< ListValueType > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_back( generator() );
		}

		auto size = list.size();
		auto value = list.peek_front();

		ASSERT_EQ( size, list.size() );
		ASSERT_EQ( value, list.pop_front() );
	}

	TEST(empty_peek_back_test)
	{
		std::default_random_engine generator;

		doubly_linked_list< ListValueType > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_back( generator() );
		}

		auto size = list.size();
		auto value = list.peek_back();

		ASSERT_EQ( size, list.size() );
		ASSERT_EQ( value, list.pop_back() );
	}

	TEST(push_front_pop_front_test)
	{
		std::default_random_engine generator;

		doubly_linked_list< ListValueType > list;
		std::array< ListValueType, ITERATIONS > values;

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			values[idx] = generator();
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

	TEST(push_front_pop_back_test)
	{
		std::default_random_engine generator;

		doubly_linked_list< ListValueType > list;
		std::array< ListValueType, ITERATIONS > values;

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			values[idx] = generator();
			list.push_front( values[idx] );
		}

		ASSERT_EQ( ITERATIONS, list.size() );

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			ASSERT_EQ( values[idx], list.pop_back() );
		}

		ASSERT_TRUE( list.empty() );
	}

	TEST(push_back_pop_front_test)
	{
		std::default_random_engine generator;

		doubly_linked_list< ListValueType > list;
		std::array< ListValueType, ITERATIONS > values;

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			values[idx] = generator();
			list.push_back( values[idx] );
		}

		ASSERT_EQ( ITERATIONS, list.size() );

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			ASSERT_EQ( values[idx], list.pop_front() );
		}

		ASSERT_TRUE( list.empty() );
	}

	TEST(push_back_pop_back_test)
	{
		std::default_random_engine generator;

		doubly_linked_list< ListValueType > list;
		std::array< ListValueType, ITERATIONS > values;

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			values[idx] = generator();
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

	TEST(iterator_push_front_begin_end_test)
	{
		std::default_random_engine generator;

		doubly_linked_list< ListValueType > list;
		std::array< ListValueType, ITERATIONS > values;

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			values[idx] = generator();
			list.push_front( values[idx] );
		}

		ASSERT_TRUE( std::equal( std::begin( values ), std::end( values ), std::begin( list ), std::end( list ) ) );
	}

	TEST(iterator_push_back_begin_end_test)
	{
		std::default_random_engine generator;

		doubly_linked_list< ListValueType > list;
		std::array< ListValueType, ITERATIONS > values;

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			values[idx] = generator();
			list.push_back( values[idx] );
		}

		ASSERT_TRUE( std::equal( std::rbegin( values ), std::rend( values ), std::begin( list ), std::end( list ) ) );
	}

	TEST(iterator_push_front_rbegin_rend_test)
	{
		std::default_random_engine generator;

		doubly_linked_list< ListValueType > list;
		std::array< ListValueType, ITERATIONS > values;

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			values[idx] = generator();
			list.push_front( values[idx] );
		}

		ASSERT_TRUE( std::equal( std::rbegin( values ), std::rend( values ), std::rbegin( list ), std::rend( list ) ) );
	}

	TEST(iterator_push_back_rbegin_rend_test)
	{
		std::default_random_engine generator;

		doubly_linked_list< ListValueType > list;
		std::array< ListValueType, ITERATIONS > values;

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			values[idx] = generator();
			list.push_back( values[idx] );
		}

		ASSERT_TRUE( std::equal( std::begin( values ), std::end( values ), std::rbegin( list ), std::rend( list ) ) );
	}
}
