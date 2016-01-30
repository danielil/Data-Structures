#include "stdafx.h"

#include "CppUnitTest.h"

#include "TestsConsts.hpp"
#include "..\DataStructuresAlgorithms\Lists\Stack.hpp"

#include <random>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ListsTests
{
    TEST_CLASS(StackTest)
    {
    public:

        TEST_METHOD(ConstructorTest)
        {
            {
                Lists::Stack< unsigned int > stack;

                Assert::AreEqual( true, stack.isEmpty() );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(CopyConstructorTest)
        {
            {
                std::minstd_rand generator;

                Lists::Stack< unsigned int > stack1;
                for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
                {
                    stack1.push( generator() );
                }

                Lists::Stack< unsigned int > stack2( stack1 );

                Assert::AreEqual( true, stack1 == stack2 );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(CopyAssignmentTest)
        {
            {
                std::minstd_rand generator;

                Lists::Stack< unsigned int > stack1;
                for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
                {
                    stack1.push( generator() );
                }

                Lists::Stack< unsigned int > stack2;
                stack2 = stack1;

                Assert::AreEqual( true, stack1 == stack2 );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(EqualityTest)
        {
            {
                std::minstd_rand generator;

                Lists::Stack< unsigned int > stack1;
                Lists::Stack< unsigned int > stack2;

                for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
                {
                    unsigned int value = generator();

                    stack1.push( value );
                    stack2.push( value );
                }

                Assert::AreEqual( true, stack1 == stack2 );

                stack1.clear();
                stack2.clear();

                for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
                {
                    stack1.push( generator() );
                    stack2.push( generator() );
                }

                Assert::AreEqual( true, stack1 != stack2 );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(EmptyPopTest)
        {
            {
                Lists::Stack< unsigned int > stack;

                stack.pop();

                Assert::AreEqual( true, stack.isEmpty() );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(PushPopTest)
        {
            {
                std::minstd_rand generator;

                Lists::Stack< unsigned int > stack;
                unsigned int values[ITERATIONS];

                for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
                {
                    values[idx] = generator();
                    stack.push( values[idx] );

                    Assert::AreEqual( idx + 1, stack.getSize() );
                }

                Assert::AreEqual( ITERATIONS, stack.getSize() );

                for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
                {
                    std::size_t reverseIdx = ITERATIONS - 1 - idx;

                    Assert::AreEqual( values[reverseIdx], stack.pop() );
                }

                Assert::AreEqual( true, stack.isEmpty() );
            }

            _CrtDumpMemoryLeaks();
        }
    };
}
