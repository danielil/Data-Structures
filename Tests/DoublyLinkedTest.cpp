#include "stdafx.h"

#include "CppUnitTest.h"

#include "TestsConsts.hpp"
#include "..\DataStructuresAlgorithms\Lists\DoublyLinkedList.hpp"

#include <random>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ListsTests
{
    TEST_CLASS(DoublyLinkedListTest)
    {
    public:

        TEST_METHOD(ConstructorTest)
        {
            {
                Lists::doubly_linked_list< unsigned int > list;

                Assert::IsTrue( list.empty() );

                list.push_back(1);
                list.push_back(1);
                list.push_back(1);
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(CopyConstructorTest)
        {
            {
                std::default_random_engine generator;

                Lists::doubly_linked_list< unsigned int > list1;
                for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
                {
                    list1.push_front( generator() );
                }

                Lists::doubly_linked_list< unsigned int > list2( list1 );

                Assert::IsTrue( list1 == list2 );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(CopyAssignmentTest)
        {
            {
                std::default_random_engine generator;

                Lists::doubly_linked_list< unsigned int > list1;
                for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
                {
                    list1.push_front( generator() );
                }

                Lists::doubly_linked_list< unsigned int > list2;
                list2 = list1;

                Assert::IsTrue( list1 == list2 );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(EqualityTest)
        {
            {
                std::default_random_engine generator;

                Lists::doubly_linked_list< unsigned int > list1;
                Lists::doubly_linked_list< unsigned int > list2;

                for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
                {
                    unsigned int value = generator();

                    list1.push_back( value );
                    list2.push_back( value );
                }

                Assert::IsTrue( list1 == list2 );

                list1.clear();
                list2.clear();

                for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
                {
                    list1.push_back( generator() );
                    list2.push_back( generator() );
                }

                Assert::IsTrue( list1 != list2 );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(IteratorTest)
        {
            std::default_random_engine generator;

            Lists::doubly_linked_list< unsigned int > list1;
            for (std::size_t idx = 0; idx < ITERATIONS; ++idx)
            {
                list1.push_front(generator());
            }

            //for (Lists::doubly_linked_list<unsigned int>::iterator it = list1.rbegin(); it != list1.rend(); it--)
            //{
                //Assert::IsTrue(  )
            //}
            //std::transform()
        }

        TEST_METHOD(EmptyPopTest)
        {
            {
                Lists::doubly_linked_list< unsigned int > list;

                list.pop_front();

                Assert::IsTrue( list.empty() );
            }

            _CrtDumpMemoryLeaks();
        }

        TEST_METHOD(PushPopTest)
        {
            {
                std::default_random_engine generator;

                Lists::doubly_linked_list< unsigned int > list;
                unsigned int values[ITERATIONS];

                for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
                {
                    values[idx] = generator();
                    list.push_front( values[idx] );

                    Assert::AreEqual( idx + 1, list.size() );
                }

                Assert::AreEqual( ITERATIONS, list.size() );

                for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
                {
                    std::size_t reverseIdx = ITERATIONS - 1 - idx;

                    Assert::AreEqual( values[reverseIdx], list.pop_front() );
                }

                Assert::IsTrue( list.empty() );
            }

            _CrtDumpMemoryLeaks();
        }
    };
}

