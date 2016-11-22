/**
 * Author: Daniel Sebastian Iliescu
 * 
 * Tester for the Binary Search Tree.
 */

//#include "trees/binary_search_tree.hpp"

#include "utilities/generator.hpp"

#include <catch.hpp>

namespace
{
	const std::string UNIT_NAME = "binary_search_tree";

	using value_type = std::int32_t;
	const auto ITERATIONS = 1000U;
}

namespace dsa
{
	TEST_CASE( ( UNIT_NAME + "default_constructor" ).c_str() )
	{
		//binary_search_tree< value_type > list;

		//REQUIRE( list.empty() );
	}
}