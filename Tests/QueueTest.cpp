#include "stdafx.h"

#include "CppUnitTest.h"

#include "..\Lists\Queue.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace
{
    const std::size_t iterations = 10;
}

namespace ListsTests
{
    TEST_CLASS(QueueTest)
    {
    public:

        TEST_METHOD(ConstructorTest)
        {
            {
                Lists::Queue< int > queue;

                Assert::AreEqual( true, queue.isEmpty() );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(CopyConstructorTest)
        {
            {
                Lists::Queue< int > queue1;
                for ( std::size_t idx = 0; idx < iterations; ++idx )
                {
                    queue1.enqueue( std::rand() );
                }

                Lists::Queue< int > queue2( queue1 );

                Assert::AreEqual( true, queue1 == queue2 );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(CopyAssignmentTest)
        {
            {
                Lists::Queue< int > queue1;
                for ( std::size_t idx = 0; idx < iterations; ++idx )
                {
                    queue1.enqueue( std::rand() );
                }

                Lists::Queue< int > queue2;
                queue2 = queue1;

                Assert::AreEqual( true, queue1 == queue2 );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(EqualityTest)
        {
            {
                Lists::Queue< int > queue1;
                Lists::Queue< int > queue2;

                for ( std::size_t idx = 0; idx < iterations; ++idx )
                {
                    int value = std::rand();

                    queue1.enqueue( value );
                    queue2.enqueue( value );
                }

                Assert::AreEqual( true, queue1 == queue2 );

                queue1.clear();
                queue2.clear();

                for ( std::size_t idx = 0; idx < iterations; ++idx )
                {
                    queue1.enqueue( std::rand() );
                    queue2.enqueue( std::rand() );
                }

                Assert::AreEqual( true, queue1 != queue2 );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(EmptyDequeueTest)
        {
            {
                Lists::Queue< int > queue;

                queue.dequeue();

                Assert::AreEqual( true, queue.isEmpty() );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(EnqueueDequeueTest)
        {
            {
                Lists::Queue< int > queue;

                int values[iterations];

                for ( std::size_t idx = 0; idx < iterations; ++idx )
                {
                    values[idx] = std::rand();
                    queue.enqueue( values[idx] );

                    Assert::AreEqual( idx + 1, queue.getSize() );
                }

                Assert::AreEqual( iterations, queue.getSize() );

                for ( int idx = 0; idx < iterations; ++idx )
                {
                    Assert::AreEqual( values[idx], queue.dequeue() );
                }

                Assert::AreEqual( true, queue.isEmpty() );
            }

            _CrtDumpMemoryLeaks();
        }
    };
}
