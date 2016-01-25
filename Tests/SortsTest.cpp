#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Sorts\BubbleSort.hpp"
#include "..\Sorts\InsertionSort.hpp"
#include "..\Sorts\MergeSort.hpp"
#include "..\Sorts\QuickSort.hpp"
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace
{
    const std::size_t iterations = 10U;
}

namespace SortsTests
{
    TEST_CLASS(SortsTest)
    {
    public:

        TEST_METHOD(BubbleSortTest)
        {
            int values[iterations];

            for ( std::size_t idx = 0U; idx < iterations; ++idx )
            {
                values[idx] = std::rand();
            }

            Sorts::bubblesort( values, iterations );

            Assert::AreEqual( true, std::is_sorted(values, values + iterations));
        }

        TEST_METHOD(InsertionSortTest)
        {
            int values[iterations];

            for ( std::size_t idx = 0U; idx < iterations; ++idx )
            {
                values[idx] = std::rand();
            }

            Sorts::insertionsort( values, iterations );

            Assert::AreEqual(true, std::is_sorted(values, values + iterations));
        }

        TEST_METHOD(MergeSortTest)
        {
            int values[iterations];

            for ( std::size_t idx = 0U; idx < iterations; ++idx )
            {
                values[idx] = std::rand();
            }

            Sorts::mergesort( values, iterations );

            Assert::AreEqual(true, std::is_sorted(values, values + iterations));
        }

        TEST_METHOD(QuickSortTest)
        {
            int values[iterations];

            for ( std::size_t idx = 0U; idx < iterations; ++idx )
            {
                values[idx] = std::rand();
            }

            Sorts::quicksort( values, iterations );

            Assert::AreEqual(true, std::is_sorted(values, values + iterations));
        }
    };
}
