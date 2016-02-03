#include "stdafx.h"
#include "CppUnitTest.h"

#include "TestsConsts.hpp"

#include "..\DataStructuresAlgorithms\Sorts\BubbleSort.hpp"
#include "..\DataStructuresAlgorithms\Sorts\InsertionSort.hpp"
#include "..\DataStructuresAlgorithms\Sorts\MergeSort.hpp"
#include "..\DataStructuresAlgorithms\Sorts\QuickSort.hpp"

#include <algorithm>
#include <random>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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

            Sorts::bubblesort( values, ITERATIONS );

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

            Sorts::insertionsort( values, ITERATIONS );

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

            Sorts::mergesort( values, ITERATIONS );

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

            Sorts::quicksort( values, ITERATIONS );

            Assert::IsTrue( std::is_sorted( values, values + ITERATIONS ) );
        }
    };
}
