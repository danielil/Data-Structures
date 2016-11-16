/**
 * Author: Daniel Sebastian Iliescu
 * 
 * Tester for the Doubly Linked List.
 */

#include <lists/doubly_linked_list.hpp>

#include <catch.hpp>

#include <array>
#include <random>

namespace
{
	const auto ITERATIONS = 1000U;
	using value_type = std::uint64_t;
}

namespace dsa
{
	TEST_CASE( "default_constructor", "doubly_linked_list" )
	{
		doubly_linked_list< value_type > list;

		REQUIRE( list.empty() );
	}

	TEST_CASE( "copy_constructor_push_front", "doubly_linked_list" )
	{
		std::default_random_engine generator;

		doubly_linked_list< value_type > list1;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list1.push_front( generator() );
		}

		auto list2( list1 );

		REQUIRE( list1 == list2 );
	}

	TEST_CASE( "copy_constructor_push_back", "doubly_linked_list" )
	{
		std::default_random_engine generator;

		doubly_linked_list< value_type > list1;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list1.push_back( generator() );
		}

		auto list2( list1 );

		REQUIRE( list1 == list2 );
	}

	TEST_CASE( "copy_assignment_push_front", "doubly_linked_list" )
	{
		std::default_random_engine generator;

		doubly_linked_list< value_type > list1;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list1.push_front( generator() );
		}

		auto list2 = list1;

		REQUIRE( list1 == list2 );
	}

	TEST_CASE( "copy_assignment_push_back", "doubly_linked_list" )
	{
		std::default_random_engine generator;

		doubly_linked_list< value_type > list1;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list1.push_back( generator() );
		}

		auto list2 = list1;

		REQUIRE( list1 == list2 );
	}

	TEST_CASE( "addition_operator_push_front", "doubly_linked_list" )
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

		REQUIRE(
			std::equal(
				std::cbegin( wholeList ),
				std::cend( firstHalf ),
				std::cbegin( firstHalf ),
				std::cend( firstHalf ) ) );
		REQUIRE(
			std::equal(
				std::cbegin( secondHalf ),
				std::cend( wholeList ),
				std::cbegin( secondHalf ),
				std::cend( secondHalf ) ) );
	}

	TEST_CASE( "addition_operator_push_back", "doubly_linked_list" )
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

		REQUIRE(
			std::equal(
				std::cbegin( wholeList ),
				std::cend( firstHalf ),
				std::cbegin( firstHalf ),
				std::cend( firstHalf ) ) );
		REQUIRE(
			std::equal(
				std::cbegin( secondHalf ),
				std::cend( wholeList ),
				std::cbegin( secondHalf ),
				std::cend( secondHalf ) ) );
	}

	TEST_CASE( "addition_equal_operator_push_front", "doubly_linked_list" )
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

		REQUIRE(
			std::equal(
				std::cbegin( list2 ),
				std::cend( list1 ),
				std::cbegin( list2 ),
				std::cend( list2 ) ) );
		REQUIRE(
			std::equal(
				std::cbegin( list1 ),
				std::cend( list2 ),
				std::cbegin( list1 ),
				std::cend( list1 ) ) );
	}

	TEST_CASE( "addition_equal_operator_push_back", "doubly_linked_list" )
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

		REQUIRE(
			std::equal(
				std::cbegin( list2 ),
				std::cend( list1 ),
				std::cbegin( list2 ),
				std::cend( list2 ) ) );
		REQUIRE(
			std::equal(
				std::cbegin( list1 ),
				std::cend( list2 ),
				std::cbegin( list1 ),
				std::cend( list1 ) ) );
	}

	TEST_CASE( "equality_operator_push_front", "doubly_linked_list" )
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

		REQUIRE( list1 == list2 );

		list1.clear();
		list2.clear();

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list1.push_front( generator() );
			list2.push_front( generator() );
		}

		REQUIRE( list1 != list2 );
	}

	TEST_CASE( "equality_operator_push_back", "doubly_linked_list" )
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

		REQUIRE( list1 == list2 );

		list1.clear();
		list2.clear();

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list1.push_back( generator() );
			list2.push_back( generator() );
		}

		REQUIRE( list1 != list2 );
	}

	TEST_CASE( "empty_pop_front", "doubly_linked_list" )
	{
		doubly_linked_list< value_type > list;

		list.pop_front();

		REQUIRE( list.empty() );
	}

	TEST_CASE( "empty_pop_back", "doubly_linked_list" )
	{
		doubly_linked_list< value_type > list;

		list.pop_back();

		REQUIRE( list.empty() );
	}

	TEST_CASE( "clear", "doubly_linked_list" )
	{
		std::default_random_engine generator;

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_back( generator() );
		}

		list.clear();

		REQUIRE( list.empty() );
	}

	TEST_CASE( "empty_peek_front", "doubly_linked_list" )
	{
		std::default_random_engine generator;

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_back( generator() );
		}

		auto size = list.size();
		auto value = list.peek_front();

		REQUIRE( size == list.size() );
		REQUIRE( value == list.pop_front() );
	}

	TEST_CASE( "empty_peek_back", "doubly_linked_list" )
	{
		std::default_random_engine generator;

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_back( generator() );
		}

		auto size = list.size();
		auto value = list.peek_back();

		REQUIRE( size == list.size() );
		REQUIRE( value == list.pop_back() );
	}

	TEST_CASE( "push_front_pop_front", "doubly_linked_list" )
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

		REQUIRE( ITERATIONS == list.size() );

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			std::size_t reverseIdx = ITERATIONS - 1 - idx;

			REQUIRE( values[reverseIdx] == list.pop_front() );
		}

		REQUIRE( list.empty() );
	}

	TEST_CASE( "push_front_pop_back", "doubly_linked_list" )
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

		REQUIRE( ITERATIONS == list.size() );

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			REQUIRE( values[idx] == list.pop_back() );
		}

		REQUIRE( list.empty() );
	}

	TEST_CASE( "push_back_pop_front", "doubly_linked_list" )
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

		REQUIRE( ITERATIONS == list.size() );

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			REQUIRE( values[idx] == list.pop_front() );
		}

		REQUIRE( list.empty() );
	}

	TEST_CASE( "push_back_pop_back", "doubly_linked_list" )
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

		REQUIRE( ITERATIONS == list.size() );

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			std::size_t reverseIdx = ITERATIONS - 1 - idx;

			REQUIRE( values[reverseIdx] == list.pop_back() );
		}

		REQUIRE( list.empty() );
	}

	TEST_CASE( "iterator_push_front_begin_end", "doubly_linked_list" )
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

		REQUIRE(
			std::equal(
				std::cbegin( values ),
				std::cend( values ),
				std::cbegin( list ),
				std::cend( list ) ) );
	}

	TEST_CASE( "iterator_push_back_begin_end", "doubly_linked_list" )
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

		REQUIRE(
			std::equal(
				std::crbegin( values ),
				std::crend( values ),
				std::cbegin( list ),
				std::cend( list ) ) );
	}

	TEST_CASE( "iterator_push_front_rbegin_rend", "doubly_linked_list" )
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

		REQUIRE(
			std::equal(
				std::crbegin( values ),
				std::crend( values ),
				std::crbegin( list ),
				std::crend( list ) ) );
	}

	TEST_CASE( "iterator_push_back_rbegin_rend", "doubly_linked_list" )
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

		REQUIRE(
			std::equal(
				std::cbegin( values ),
				std::cend( values ),
				std::crbegin( list ),
				std::crend( list ) ) );
	}

	TEST_CASE( "iterator_push_front_cbegin_cend", "doubly_linked_list" )
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

		REQUIRE(
			std::equal(
				std::cbegin( values ),
				std::cend( values ),
				std::cbegin( list ),
				std::cend( list ) ) );
	}

	TEST_CASE( "iterator_push_back_cbegin_cend", "doubly_linked_list" )
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

		REQUIRE(
			std::equal(
				std::crbegin( values ),
				std::crend( values ),
				std::cbegin( list ),
				std::cend( list ) ) );
	}

	TEST_CASE( "iterator_push_front_crbegin_crend", "doubly_linked_list" )
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

		REQUIRE(
			std::equal(
				std::crbegin( values ),
				std::crend( values ),
				std::crbegin( list ),
				std::crend( list ) ) );
	}

	TEST_CASE( "iterator_push_back_crbegin_crend", "doubly_linked_list" )
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

		REQUIRE(
			std::equal(
				std::cbegin( values ),
				std::cend( values ),
				std::crbegin( list ),
				std::crend( list ) ) );
	}
}
