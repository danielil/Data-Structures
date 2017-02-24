/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 *
 * Tester for the Binary Search Tree.
 */

#include "trees/binary_search_tree.hpp"

#include "utilities/generator.hpp"

#include <catch.hpp>

#include <array>

namespace
{
	const std::string UNIT_NAME = "binary_search_tree_";

	using key_type = std::int32_t;
	using value_type = std::int32_t;
	constexpr std::size_t ITERATIONS = 10000;
}

namespace dsa
{
	TEST_CASE( ( UNIT_NAME + "empty" ).c_str() )
	{
		binary_search_tree< key_type, value_type > bst;

		REQUIRE( bst.empty() );
	}

	TEST_CASE( ( UNIT_NAME + "insert" ).c_str() )
	{
		std::vector< key_type > keys;
		generator< value_type >().fill_buffer_n( std::back_inserter( keys ), ITERATIONS );

		binary_search_tree< key_type, value_type > bst;
		for ( auto key : keys )
		{
			bst.insert( key, static_cast< value_type >( key ) );
		}

		std::sort( std::begin( keys ), std::end( keys ) );
		keys.erase( std::unique( std::begin( keys ), std::end( keys ) ), std::end( keys ) );

		std::vector< key_type > extracted_keys;
		bst.inorder([&extracted_keys]( auto const & node )
		{
			extracted_keys.emplace_back( node->key );
		} );

		REQUIRE(
			std::equal(
				std::cbegin( keys ),
				std::cend( keys ),
				std::cbegin( extracted_keys ),
				std::cend( extracted_keys ) ) );
	}

	TEST_CASE( ( UNIT_NAME + "insert_duplicate" ).c_str() )
	{
		binary_search_tree< key_type, value_type > bst;
		for ( std::size_t iteration = 0; iteration < ITERATIONS; ++iteration )
		{
			bst.insert( key_type(), iteration );
		}

		REQUIRE( bst.size() == 1 );
	}

	TEST_CASE( ( UNIT_NAME + "contains" ).c_str() )
	{
		std::vector< key_type > keys;
		generator< value_type >().fill_buffer_n( std::back_inserter( keys ), ITERATIONS );

		binary_search_tree< key_type, value_type > bst;
		for ( auto key : keys )
		{
			bst.insert( key, static_cast< value_type >( key ) );

			REQUIRE( bst.contains( key ) );
		}
	}

	TEST_CASE( ( UNIT_NAME + "erase_none" ).c_str() )
	{
		std::vector< key_type > keys;
		generator< value_type >().fill_buffer_n( std::back_inserter( keys ), ITERATIONS );

		binary_search_tree< key_type, value_type > bst;
		bst.insert( 0, value_type() );
		bst.insert( -2, value_type() );
		bst.insert( -1, value_type() );
		bst.insert( 4, value_type() );
		bst.insert( 3, value_type() );
		bst.insert( 7, value_type() );

		bst.erase( 5 );

		REQUIRE( bst.size() == 6 );
	}

	TEST_CASE( ( UNIT_NAME + "erase_case_one_no_children" ).c_str() )
	{
		std::vector< key_type > keys;
		generator< value_type >().fill_buffer_n( std::back_inserter( keys ), ITERATIONS );

		binary_search_tree< key_type, value_type > bst;
		bst.insert( 0, value_type() );
		bst.insert( -2, value_type() );
		bst.insert( -1, value_type() );
		bst.insert( 4, value_type() );
		bst.insert( 3, value_type() );
		bst.insert( 7, value_type() );

		bst.erase( -1 );

		REQUIRE( !bst.contains( -1 ) );
	}

	TEST_CASE( ( UNIT_NAME + "erase_case_one_right_child" ).c_str() )
	{
		std::vector< key_type > keys;
		generator< value_type >().fill_buffer_n( std::back_inserter( keys ), ITERATIONS );

		binary_search_tree< key_type, value_type > bst;
		bst.insert( 0, value_type() );
		bst.insert( -2, value_type() );
		bst.insert( -1, value_type() );
		bst.insert( 4, value_type() );
		bst.insert( 3, value_type() );
		bst.insert( 7, value_type() );

		bst.erase( -2 );

		REQUIRE( !bst.contains( -2 ) );
		REQUIRE( bst.contains( -1 ) );
		REQUIRE( bst.size() == 5 );
	}

	TEST_CASE( ( UNIT_NAME + "erase_case_one_left_child" ).c_str() )
	{
		std::vector< key_type > keys;
		generator< value_type >().fill_buffer_n( std::back_inserter( keys ), ITERATIONS );

		binary_search_tree< key_type, value_type > bst;
		bst.insert( 0, value_type() );
		bst.insert( -2, value_type() );
		bst.insert( -3, value_type() );
		bst.insert( 4, value_type() );
		bst.insert( 3, value_type() );
		bst.insert( 7, value_type() );

		bst.erase( -2 );

		REQUIRE( !bst.contains( -2 ) );
		REQUIRE( bst.contains( -3 ) );
		REQUIRE( bst.size() == 5 );
	}

	TEST_CASE( ( UNIT_NAME + "erase_case_both_children" ).c_str() )
	{
		std::vector< key_type > keys;
		generator< value_type >().fill_buffer_n( std::back_inserter( keys ), ITERATIONS );

		binary_search_tree< key_type, value_type > bst;
		bst.insert( 0, value_type() );
		bst.insert( -2, value_type() );
		bst.insert( -1, value_type() );
		bst.insert( 4, value_type() );
		bst.insert( 3, value_type() );
		bst.insert( 7, value_type() );
		bst.insert( 6, value_type() );
		bst.insert( 8, value_type() );

		bst.erase( 4 );

		REQUIRE( !bst.contains( 4 ) );
		REQUIRE( bst.contains( 3 ) );
		REQUIRE( bst.contains( 7 ) );
		REQUIRE( bst.size() == 7 );
	}

	TEST_CASE( ( UNIT_NAME + "number_of_calculated_nodes" ).c_str() )
	{
		std::vector< key_type > keys;
		generator< value_type >().fill_buffer_n( std::back_inserter( keys ), ITERATIONS );

		binary_search_tree< key_type, value_type > bst;
		for ( auto key : keys )
		{
			bst.insert( key, static_cast< value_type >( key ) );
		}

		REQUIRE(bst.size() == bst.calculated_size());
	}

	TEST_CASE( ( UNIT_NAME + "height" ).c_str() )
	{
		std::vector< key_type > keys;
		generator< value_type >().fill_buffer_n( std::back_inserter( keys ), ITERATIONS );

		binary_search_tree< key_type, value_type > bst;
		bst.insert( 0, value_type() );
		bst.insert( -2, value_type() );
		bst.insert( -1, value_type() );
		bst.insert( 4, value_type() );
		bst.insert( 3, value_type() );
		bst.insert( 7, value_type() );
		bst.insert( 8, value_type() );

		REQUIRE( bst.height() == 3 );
	}

	TEST_CASE( ( UNIT_NAME + "balanced" ).c_str() )
	{
		std::vector< key_type > keys;
		generator< value_type >().fill_buffer_n( std::back_inserter( keys ), ITERATIONS );

		binary_search_tree< key_type, value_type > bst;
		bst.insert( 0, value_type() );
		bst.insert( -3, value_type() );
		bst.insert( -2, value_type() );
		bst.insert( 4, value_type() );
		bst.insert( 3, value_type() );
		bst.insert( 7, value_type() );
		bst.insert( 8, value_type() );

		REQUIRE( bst.balanced() );

		bst.insert( 9, value_type() );
		bst.insert( -1, value_type() );

		REQUIRE( !bst.balanced() );
	}
}