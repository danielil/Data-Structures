#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\DataStructuresAlgorithms\sorts\bubble_sort.hpp"
#include "..\DataStructuresAlgorithms\sorts\insertion_sort.hpp"
#include "..\DataStructuresAlgorithms\sorts\merge_sort.hpp"
#include "..\DataStructuresAlgorithms\sorts\quick_sort.hpp"

#include <algorithm>
#include <random>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace
{
    const std::size_t ITERATIONS = 10;
}

namespace dsa
{
    TEST_CLASS(sorts_test)
    {
    public:

        TEST_METHOD(bubble_sort_test)
        {
            std::default_random_engine generator;

            unsigned int values[ITERATIONS];
            for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
            {
                values[idx] = generator();
            }

            dsa::bubblesort( values, ITERATIONS );

            Assert::IsTrue( std::is_sorted( std::begin( values ), std::end( values ) ) );
        }

        TEST_METHOD(insertion_sort_test)
        {
            std::default_random_engine generator;

            unsigned int values[ITERATIONS];
            for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
            {
                values[idx] = generator();
            }

            dsa::insertionsort( values, ITERATIONS );

            Assert::IsTrue( std::is_sorted( std::begin( values ), std::end( values ) ) );
        }

        TEST_METHOD(merge_sort_test)
        {
            std::default_random_engine generator;

            unsigned int values[ITERATIONS];
            for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
            {
                values[idx] = generator();
            }

            dsa::mergesort( values, ITERATIONS );

            Assert::IsTrue( std::is_sorted( std::begin( values ), std::end( values ) ) );
        }

        TEST_METHOD(quick_sort_test)
        {
            std::default_random_engine generator;

            unsigned int values[ITERATIONS];
            for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
            {
                values[idx] = generator();
            }

            dsa::quicksort( values, ITERATIONS );

            Assert::IsTrue( std::is_sorted( std::begin( values ), std::end( values ) ) );
        }
    };
}
