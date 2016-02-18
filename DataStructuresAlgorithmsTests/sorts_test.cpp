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

namespace SortsTests
{
    TEST_CLASS(SortsTest)
    {
    public:

        TEST_METHOD(BubbleSortTest)
        {
            std::default_random_engine generator;

            unsigned int values[ITERATIONS];
            for (std::size_t idx = 0; idx < ITERATIONS; ++idx)
            {
                values[idx] = generator();
            }

            dsa::bubblesort( values, ITERATIONS );

            Assert::IsTrue( std::is_sorted( values, values + ITERATIONS ) );
        }

        TEST_METHOD(InsertionSortTest)
        {
            std::default_random_engine generator;

            unsigned int values[ITERATIONS];
            for (std::size_t idx = 0; idx < ITERATIONS; ++idx)
            {
                values[idx] = generator();
            }

            dsa::insertionsort( values, ITERATIONS );

            Assert::IsTrue( std::is_sorted( values, values + ITERATIONS ) );
        }

        TEST_METHOD(MergeSortTest)
        {
            std::default_random_engine generator;

            unsigned int values[ITERATIONS];
            for (std::size_t idx = 0; idx < ITERATIONS; ++idx)
            {
                values[idx] = generator();
            }

            dsa::mergesort( values, ITERATIONS );

            Assert::IsTrue( std::is_sorted( values, values + ITERATIONS ) );
        }

        TEST_METHOD(QuickSortTest)
        {
            std::default_random_engine generator;

            unsigned int values[ITERATIONS];
            for (std::size_t idx = 0; idx < ITERATIONS; ++idx)
            {
                values[idx] = generator();
            }

            dsa::quicksort( values, ITERATIONS );

            Assert::IsTrue( std::is_sorted( values, values + ITERATIONS ) );
        }
    };
}
