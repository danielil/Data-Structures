#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Sorts\BubbleSort.hpp"
#include "..\Sorts\InsertionSort.hpp"
#include "..\Sorts\MergeSort.hpp"
#include "..\Sorts\QuickSort.hpp"

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

            for ( std::size_t idx = 0U; idx < iterations - 1; ++idx )
            {
                Assert::AreEqual( values[idx] < values[idx + 1], true );
            }
        }

        TEST_METHOD(InsertionSortTest)
        {
            int values[iterations];

            for ( std::size_t idx = 0U; idx < iterations; ++idx )
            {
                values[idx] = std::rand();
            }

            Sorts::insertionsort( values, iterations );

            for ( std::size_t idx = 0U; idx < iterations - 1; ++idx )
            {
                Assert::AreEqual( values[idx] < values[idx + 1], true );
            }
        }

        TEST_METHOD(MergeSortTest)
        {
            int values[iterations];

            for ( std::size_t idx = 0U; idx < iterations; ++idx )
            {
                values[idx] = std::rand();
            }

            Sorts::mergesort( values, iterations );

            for ( std::size_t idx = 0U; idx < iterations - 1; ++idx )
            {
                Assert::AreEqual( values[idx] < values[idx + 1], true );
            }
        }

        TEST_METHOD(QuickSortTest)
        {
            int values[iterations];

            for ( std::size_t idx = 0U; idx < iterations; ++idx )
            {
                values[idx] = std::rand();
            }

            Sorts::quicksort( values, iterations );

            for ( std::size_t idx = 0U; idx < iterations - 1; ++idx )
            {
                Assert::AreEqual( values[idx] < values[idx + 1], true );
            }
        }
    };
}
