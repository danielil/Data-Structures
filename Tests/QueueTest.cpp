#include "stdafx.h"

#include "CppUnitTest.h"

#include "TestsConsts.hpp"
#include "..\DataStructuresAlgorithms\Lists\Queue.hpp"

#include <random>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ListsTests
{
    TEST_CLASS(QueueTest)
    {
    public:

        TEST_METHOD(ConstructorTest)
        {
            {
                Lists::Queue< unsigned int > queue;

                Assert::AreEqual( true, queue.isEmpty() );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(CopyConstructorTest)
        {
            {
                std::minstd_rand generator;

                Lists::Queue< unsigned int > queue1;
                for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
                {
                    queue1.enqueue( generator() );
                }

                Lists::Queue< unsigned int > queue2( queue1 );

                Assert::AreEqual( true, queue1 == queue2 );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(CopyAssignmentTest)
        {
            {
                std::minstd_rand generator;

                Lists::Queue< unsigned int > queue1;
                for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
                {
                    queue1.enqueue( generator() );
                }

                Lists::Queue< unsigned int > queue2;
                queue2 = queue1;

                Assert::AreEqual( true, queue1 == queue2 );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(EqualityTest)
        {
            {
                std::minstd_rand generator;

                Lists::Queue< unsigned int > queue1;
                Lists::Queue< unsigned int > queue2;

                for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
                {
                    unsigned int value = generator();

                    queue1.enqueue( value );
                    queue2.enqueue( value );
                }

                Assert::AreEqual( true, queue1 == queue2 );

                queue1.clear();
                queue2.clear();

                for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
                {
                    queue1.enqueue( generator() );
                    queue2.enqueue( generator() );
                }

                Assert::AreEqual( true, queue1 != queue2 );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(EmptyDequeueTest)
        {
            {
                Lists::Queue< unsigned int > queue;

                queue.dequeue();

                Assert::AreEqual( true, queue.isEmpty() );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(EnqueueDequeueTest)
        {
            {
                std::minstd_rand generator;

                Lists::Queue< unsigned int > queue;
                unsigned int values[ITERATIONS];

                for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
                {
                    values[idx] = generator();
                    queue.enqueue( values[idx] );

                    Assert::AreEqual( idx + 1, queue.getSize() );
                }

                Assert::AreEqual( ITERATIONS, queue.getSize() );

                for ( auto value : values )
                {
                    Assert::AreEqual( value, queue.dequeue() );
                }

                Assert::AreEqual( true, queue.isEmpty() );
            }

            _CrtDumpMemoryLeaks();
        }
    };
}

