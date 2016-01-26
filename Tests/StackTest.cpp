#include "stdafx.h"

#include "CppUnitTest.h"

#include "TestsConsts.hpp"
#include "..\Lists\Stack.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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
                for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
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
                for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
                {
                    stack1.push( std::rand() );
                }

                Lists::Stack< int > stack2;
                stack2 = stack1;

                Assert::AreEqual( true, stack1 == stack2 );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(EqualityTest)
        {
            {
                Lists::Stack< int > stack1;
                Lists::Stack< int > stack2;

                for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
                {
                    int value = std::rand();

                    stack1.push( value );
                    stack2.push( value );
                }

                Assert::AreEqual( true, stack1 == stack2 );

                stack1.clear();
                stack2.clear();

                for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
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

                int values[ITERATIONS];

                for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
                {
                    values[idx] = std::rand();
                    stack.push( values[idx] );

                    Assert::AreEqual( idx + 1, stack.getSize() );
                }

                Assert::AreEqual( ITERATIONS, stack.getSize() );

                for ( int idx = ITERATIONS - 1; idx >= 0; --idx )
                {
                    Assert::AreEqual( values[idx], stack.pop() );
                }

                Assert::AreEqual( true, stack.isEmpty() );
            }

            _CrtDumpMemoryLeaks();
        }
    };
}
