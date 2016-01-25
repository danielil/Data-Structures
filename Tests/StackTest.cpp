#include "stdafx.h"

#include "CppUnitTest.h"

#include "..\Lists\Stack.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace
{
    const std::size_t iterations = 10;
}

namespace ListsTests
{
    TEST_CLASS(StackTest)
    {
    public:

        TEST_METHOD(ConstructorTest)
        {
            {
                Lists::Stack< int > stack;

                Assert::AreEqual( true, stack.isEmpty() );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(CopyConstructorTest)
        {
            {
                Lists::Stack< int > stack1;
                for ( std::size_t idx = 0; idx < iterations; ++idx )
                {
                    stack1.push( std::rand() );
                }

                Lists::Stack< int > stack2( stack1 );

                Assert::AreEqual( true, stack1 == stack2 );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(CopyAssignmentTest)
        {
            {
                Lists::Stack< int > stack1;
                for ( std::size_t idx = 0; idx < iterations; ++idx )
                {
                    stack1.push( std::rand() );
                }

                Lists::Stack< int > stack2;
                stack2 = stack1;

                Assert::AreEqual( true, stack1 == stack2 );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(EgalityTest)
        {
            {
                Lists::Stack< int > stack1;
                Lists::Stack< int > stack2;

                for ( std::size_t idx = 0; idx < iterations; ++idx )
                {
                    int value = std::rand();

                    stack1.push( value );
                    stack2.push( value );
                }

                Assert::AreEqual( true, stack1 == stack2 );

                stack1.clear();
                stack2.clear();

                for ( std::size_t idx = 0; idx < iterations; ++idx )
                {
                    stack1.push( std::rand() );
                    stack2.push( std::rand() );
                }

                Assert::AreEqual( true, stack1 != stack2 );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(EmptyPopTest)
        {
            {
                Lists::Stack< int > stack;

                stack.pop();

                Assert::AreEqual( true, stack.isEmpty() );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(PushPopTest)
        {
            {
                Lists::Stack< int > stack;

                int values[iterations];

                for ( std::size_t iteration = 0; iteration < iterations; ++iteration )
                {
                    values[iteration] = std::rand();
                    stack.push( values[iteration] );

                    Assert::AreEqual( iteration + 1, stack.getSize() );
                }

                Assert::AreEqual( iterations, stack.getSize() );

                for ( int iteration = iterations - 1; iteration >= 0; --iteration )
                {
                    Assert::AreEqual( values[iteration], stack.pop() );
                }

                Assert::AreEqual( true, stack.isEmpty() );
            }

            _CrtDumpMemoryLeaks();
        }
    };
}
