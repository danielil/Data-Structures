/**
 * Author: Daniel Sebastian Iliescu
 * 
 * Tester for the Doubly Linked List.
 */

#include "lists/doubly_linked_list.hpp"

#include "utilities/generator.hpp"

#include <catch.hpp>

#include <array>

namespace
{
	using value_type = std::uint64_t;

	const auto ITERATIONS = 1000U;
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
		generator< value_type > generator;

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_front( generator() );
		}

		auto list_copy( list );

		REQUIRE( list == list_copy );
	}

	TEST_CASE( "copy_constructor_push_back", "doubly_linked_list" )
	{
		generator< value_type > generator;

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_back( generator() );
		}

		auto list_copy( list );

		REQUIRE( list == list_copy );
	}

	TEST_CASE( "move_constructor_push_front", "doubly_linked_list" )
	{
		generator< value_type > generator;

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_front( generator() );
		}

		auto list_copy( list );
		auto list_move( std::move( list ) );

		REQUIRE( list.empty() );
		REQUIRE( list_move == list_copy );
	}

	TEST_CASE( "move_constructor_push_back", "doubly_linked_list" )
	{
		generator< value_type > generator;

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_back( generator() );
		}

		auto list_copy( list );
		auto list_move( std::move( list ) );

		REQUIRE( list.empty() );
		REQUIRE( list_move == list_copy );
	}

	TEST_CASE( "copy_assignment_push_front", "doubly_linked_list" )
	{
		generator< value_type > generator;

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_front( generator() );
		}

		auto list_copy = list;

		REQUIRE( list == list );
	}

	TEST_CASE( "copy_assignment_push_back", "doubly_linked_list" )
	{
		generator< value_type > generator;

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_back( generator() );
		}

		auto list_copy = list;

		REQUIRE( list == list_copy );
	}

	TEST_CASE( "move_assignment_push_front", "doubly_linked_list" )
	{
		generator< value_type > generator;

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_front( generator() );
		}

		auto list_copy = list;
		auto list_move = std::move( list );

		REQUIRE( list.empty() );
		REQUIRE( list_move == list_copy );
	}

	TEST_CASE( "move_assignment_push_back", "doubly_linked_list" )
	{
		generator< value_type > generator;

		doubly_linked_list< value_type > list;
		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_back( generator() );
		}

		auto list_copy = list;
		auto list_move = std::move( list );

		REQUIRE( list.empty() );
		REQUIRE( list_move == list_copy );
	}

	TEST_CASE( "addition_operator_push_front", "doubly_linked_list" )
	{
		generator< value_type > generator;
		std::array< value_type, ITERATIONS > values;

		generator.fill_buffer(
			std::begin( values ),
			std::end( values ) );

		doubly_linked_list< value_type > first_half;
		doubly_linked_list< value_type > second_half;

		for ( auto&& value : values )
		{
			first_half.push_front( value );
			second_half.push_front( value );
		}

		auto whole_list = first_half + second_half;

		REQUIRE(
			std::equal(
				std::cbegin( whole_list ),
				std::cend( first_half ),
				std::cbegin( first_half ),
				std::cend( first_half ) ) );
		REQUIRE(
			std::equal(
				std::cbegin( second_half ),
				std::cend( whole_list ),
				std::cbegin( second_half ),
				std::cend( second_half ) ) );
	}

	TEST_CASE( "addition_operator_push_back", "doubly_linked_list" )
	{
		generator< value_type > generator;
		std::array< value_type, ITERATIONS > values;

		generator.fill_buffer(
			std::begin( values ),
			std::end( values ) );

		doubly_linked_list< value_type > first_half;
		doubly_linked_list< value_type > second_half;

		for ( auto&& value : values )
		{
			first_half.push_back( value );
			second_half.push_back( value );
		}

		auto whole_list = first_half + second_half;

		REQUIRE(
			std::equal(
				std::cbegin( whole_list ),
				std::cend( first_half ),
				std::cbegin( first_half ),
				std::cend( first_half ) ) );
		REQUIRE(
			std::equal(
				std::cbegin( second_half ),
				std::cend( whole_list ),
				std::cbegin( second_half ),
				std::cend( second_half ) ) );
	}

	TEST_CASE( "addition_equal_operator_push_front", "doubly_linked_list" )
	{
		generator< value_type > generator;
		std::array< value_type, ITERATIONS > values;

		generator.fill_buffer(
			std::begin( values ),
			std::end( values ) );

		doubly_linked_list< value_type > list;
		doubly_linked_list< value_type > list_appended;

		for ( auto&& value : values )
		{
			list.push_front( value );
			list_appended.push_front( value );
		}

		list_appended += list;

		REQUIRE(
			std::equal(
				std::cbegin( list_appended ),
				std::cend( list ),
				std::cbegin( list_appended ),
				std::cend( list_appended ) ) );
		REQUIRE(
			std::equal(
				std::cbegin( list ),
				std::cend( list_appended ),
				std::cbegin( list ),
				std::cend( list ) ) );
	}

	TEST_CASE( "addition_equal_operator_push_back", "doubly_linked_list" )
	{
		generator< value_type > generator;
		std::array< value_type, ITERATIONS > values;

		generator.fill_buffer(
			std::begin( values ),
			std::end( values ) );

		doubly_linked_list< value_type > list;
		doubly_linked_list< value_type > list_appended;

		for ( auto&& value : values )
		{
			list.push_back( value );
			list_appended.push_back( value );
		}

		list_appended += list;

		REQUIRE(
			std::equal(
				std::cbegin( list_appended ),
				std::cend( list ),
				std::cbegin( list_appended ),
				std::cend( list_appended ) ) );
		REQUIRE(
			std::equal(
				std::cbegin( list ),
				std::cend( list_appended ),
				std::cbegin( list ),
				std::cend( list ) ) );
	}

	TEST_CASE( "equality_operator_push_front", "doubly_linked_list" )
	{
		generator< value_type > generator;

		doubly_linked_list< value_type > list;
		doubly_linked_list< value_type > list_copy;

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			auto value = generator();

			list.push_front( value );
			list_copy.push_front( value );
		}

		REQUIRE( list == list_copy );

		list.clear();
		list_copy.clear();

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_front( generator() );
			list_copy.push_front( generator() );
		}

		REQUIRE( list != list_copy );
	}

	TEST_CASE( "equality_operator_push_back", "doubly_linked_list" )
	{
		generator< value_type > generator;

		doubly_linked_list< value_type > list;
		doubly_linked_list< value_type > list_copy;

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			auto value = generator();

			list.push_back( value );
			list_copy.push_back( value );
		}

		REQUIRE( list == list_copy );

		list.clear();
		list_copy.clear();

		for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
		{
			list.push_back( generator() );
			list_copy.push_back( generator() );
		}

		REQUIRE( list != list_copy );
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
		generator< value_type > generator;

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
		generator< value_type > generator;

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
		generator< value_type > generator;

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
		generator< value_type > generator;
		std::array< value_type, ITERATIONS > values;

		generator.fill_buffer(
			std::begin( values ),
			std::end( values ) );

		doubly_linked_list< value_type > list;
		for ( auto&& value : values )
		{
			list.push_front( value );
		}

		REQUIRE( ITERATIONS == list.size() );

		for ( auto it = std::rbegin( values ); it != std::rend( values ); ++it )
		{
			REQUIRE( *it == list.pop_front() );
		}

		REQUIRE( list.empty() );
	}

	TEST_CASE( "push_front_pop_back", "doubly_linked_list" )
	{
		generator< value_type > generator;
		std::array< value_type, ITERATIONS > values;

		generator.fill_buffer(
			std::begin( values ),
			std::end( values ) );

		doubly_linked_list< value_type > list;
		for ( auto&& value : values )
		{
			list.push_front( value );
		}

		REQUIRE( ITERATIONS == list.size() );

		for ( auto&& value : values )
		{
			REQUIRE( value == list.pop_back() );
		}

		REQUIRE( list.empty() );
	}

	TEST_CASE( "push_back_pop_front", "doubly_linked_list" )
	{
		generator< value_type > generator;
		std::array< value_type, ITERATIONS > values;

		generator.fill_buffer(
			std::begin( values ),
			std::end( values ) );

		doubly_linked_list< value_type > list;
		for ( auto&& value : values )
		{
			list.push_back( value );
		}

		REQUIRE( ITERATIONS == list.size() );

		for ( auto&& value : values )
		{
			REQUIRE( value == list.pop_front() );
		}

		REQUIRE( list.empty() );
	}

	TEST_CASE( "push_back_pop_back", "doubly_linked_list" )
	{
		generator< value_type > generator;
		std::array< value_type, ITERATIONS > values;

		generator.fill_buffer(
			std::begin( values ),
			std::end( values ) );

		doubly_linked_list< value_type > list;
		for ( auto&& value : values )
		{
			list.push_back( value );
		}

		REQUIRE( ITERATIONS == list.size() );

		for ( auto it = std::rbegin( values ); it != std::rend( values ); ++it )
		{
			REQUIRE( *it == list.pop_back() );
		}

		REQUIRE( list.empty() );
	}

	TEST_CASE( "iterator_push_front_begin_end", "doubly_linked_list" )
	{
		generator< value_type > generator;
		std::array< value_type, ITERATIONS > values;

		generator.fill_buffer(
			std::begin( values ),
			std::end( values ) );

		doubly_linked_list< value_type > list;
		for ( auto&& value : values )
		{
			list.push_front( value );
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
		generator< value_type > generator;
		std::array< value_type, ITERATIONS > values;

		generator.fill_buffer(
			std::begin( values ),
			std::end( values ) );

		doubly_linked_list< value_type > list;
		for ( auto&& value : values )
		{
			list.push_back( value );
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
		generator< value_type > generator;
		std::array< value_type, ITERATIONS > values;

		generator.fill_buffer(
			std::begin( values ),
			std::end( values ) );

		doubly_linked_list< value_type > list;
		for ( auto&& value : values )
		{
			list.push_front( value );
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
		generator< value_type > generator;
		std::array< value_type, ITERATIONS > values;

		generator.fill_buffer(
			std::begin( values ),
			std::end( values ) );

		doubly_linked_list< value_type > list;
		for ( auto&& value : values )
		{
			list.push_back( value );
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
		generator< value_type > generator;
		std::array< value_type, ITERATIONS > values;

		generator.fill_buffer(
			std::begin( values ),
			std::end( values ) );

		doubly_linked_list< value_type > list;
		for ( auto&& value : values )
		{
			list.push_front( value );
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
		generator< value_type > generator;
		std::array< value_type, ITERATIONS > values;

		generator.fill_buffer(
			std::begin( values ),
			std::end( values ) );

		doubly_linked_list< value_type > list;
		for ( auto&& value : values )
		{
			list.push_back( value );
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
		generator< value_type > generator;
		std::array< value_type, ITERATIONS > values;

		generator.fill_buffer(
			std::begin( values ),
			std::end( values ) );

		doubly_linked_list< value_type > list;
		for ( auto&& value : values )
		{
			list.push_front( value );
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
		generator< value_type > generator;
		std::array< value_type, ITERATIONS > values;

		generator.fill_buffer(
			std::begin( values ),
			std::end( values ) );

		doubly_linked_list< value_type > list;
		for ( auto&& value : values )
		{
			list.push_back( value );
		}

		REQUIRE(
			std::equal(
				std::cbegin( values ),
				std::cend( values ),
				std::crbegin( list ),
				std::crend( list ) ) );
	}
}
