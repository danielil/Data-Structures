#include "stdafx.h"

#include "CppUnitTest.h"

#include "..\DataStructuresAlgorithms\lists\doubly_linked_list.hpp"

#include <random>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace
{
    const std::size_t ITERATIONS = 10;
}

namespace dsa
{
    TEST_CLASS(doubly_linked_list_test)
    {
    public:

        TEST_METHOD(constructor_test)
        {
            dsa::doubly_linked_list< unsigned int > list;

            Assert::IsTrue( list.empty() );
        }

        TEST_METHOD(copy_constructor_push_front_test)
        {
            std::default_random_engine generator;

            dsa::doubly_linked_list< unsigned int > list1;
            for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
            {
                list1.push_front( generator() );
            }

            auto list2( list1 );

            Assert::IsTrue( list1 == list2 );
        }

        TEST_METHOD(copy_constructor_push_back_test)
        {
            std::default_random_engine generator;

            dsa::doubly_linked_list< unsigned int > list1;
            for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
            {
                list1.push_back( generator() );
            }

            auto list2( list1 );

            Assert::IsTrue( list1 == list2 );
        }

        TEST_METHOD(copy_assignment_push_front_test)
        {
            std::default_random_engine generator;

            dsa::doubly_linked_list< unsigned int > list1;
            for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
            {
                list1.push_front( generator() );
            }

            auto list2 = list1;

            Assert::IsTrue( list1 == list2 );
        }

        TEST_METHOD(copy_assignment_push_back_test)
        {
            std::default_random_engine generator;

            dsa::doubly_linked_list< unsigned int > list1;
            for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
            {
                list1.push_back( generator() );
            }

            auto list2 = list1;

            Assert::IsTrue( list1 == list2 );
        }

        TEST_METHOD(equality_push_front_test)
        {
            std::default_random_engine generator;

            dsa::doubly_linked_list< unsigned int > list1;
            dsa::doubly_linked_list< unsigned int > list2;

            for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
            {
                auto value = generator();

                list1.push_front( value );
                list2.push_front( value );
            }

            Assert::IsTrue( list1 == list2 );

            list1.clear();
            list2.clear();

            for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
            {
                list1.push_front( generator() );
                list2.push_front( generator() );
            }

            Assert::IsTrue( list1 != list2 );
        }

        TEST_METHOD(equality_push_back_test)
        {
            std::default_random_engine generator;

            dsa::doubly_linked_list< unsigned int > list1;
            dsa::doubly_linked_list< unsigned int > list2;

            for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
            {
                auto value = generator();

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

        TEST_METHOD(empty_pop_front_test)
        {
            dsa::doubly_linked_list< unsigned int > list;

            list.pop_front();

            Assert::IsTrue( list.empty() );
        }

        TEST_METHOD(empty_pop_back_test)
        {
            dsa::doubly_linked_list< unsigned int > list;

            list.pop_back();

            Assert::IsTrue( list.empty() );
        }

        TEST_METHOD(push_front_pop_front_test)
        {
            std::default_random_engine generator;

            dsa::doubly_linked_list< unsigned int > list;
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

        TEST_METHOD(push_front_pop_back_test)
        {
            std::default_random_engine generator;

            dsa::doubly_linked_list< unsigned int > list;
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
                Assert::AreEqual( values[idx], list.pop_back() );
            }

            Assert::IsTrue( list.empty() );
        }

        TEST_METHOD(push_back_pop_front_test)
        {
            std::default_random_engine generator;

            dsa::doubly_linked_list< unsigned int > list;
            unsigned int values[ITERATIONS];

            for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
            {
                values[idx] = generator();
                list.push_back( values[idx] );

                Assert::AreEqual( idx + 1, list.size() );
            }

            Assert::AreEqual( ITERATIONS, list.size() );

            for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
            {
                Assert::AreEqual( values[idx], list.pop_front() );
            }

            Assert::IsTrue( list.empty() );
        }

        TEST_METHOD(push_back_pop_back_test)
        {
            std::default_random_engine generator;

            dsa::doubly_linked_list< unsigned int > list;
            unsigned int values[ITERATIONS];

            for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
            {
                values[idx] = generator();
                list.push_back( values[idx] );

                Assert::AreEqual( idx + 1, list.size() );
            }

            Assert::AreEqual( ITERATIONS, list.size() );

            for ( std::size_t idx = 0; idx < ITERATIONS; ++idx )
            {
                std::size_t reverseIdx = ITERATIONS - 1 - idx;

                Assert::AreEqual( values[reverseIdx], list.pop_back() );
            }

            Assert::IsTrue( list.empty() );
        }

        TEST_METHOD(iterator_push_front_begin_end_test)
        {
            std::default_random_engine generator;

            dsa::doubly_linked_list< unsigned int > list;
            unsigned int values[ITERATIONS];

            for (std::size_t idx = 0; idx < ITERATIONS; ++idx)
            {
                values[idx] = generator();
                list.push_front(values[idx]);
            }

            Assert::IsTrue(std::equal( std::begin(values), std::end(values), std::begin(list), std::end(list) ));
        }

        TEST_METHOD(iterator_push_back_begin_end_test)
        {
            std::default_random_engine generator;

            dsa::doubly_linked_list< unsigned int > list;
            unsigned int values[ITERATIONS];

            for (std::size_t idx = 0; idx < ITERATIONS; ++idx)
            {
                values[idx] = generator();
                list.push_back(values[idx]);
            }

            Assert::IsTrue(std::equal(std::rbegin(values), std::rend(values), std::begin(list), std::end(list)));
        }

        TEST_METHOD(iterator_push_front_rbegin_rend_test)
        {
            std::default_random_engine generator;

            dsa::doubly_linked_list< unsigned int > list;
            unsigned int values[ITERATIONS];

            for (std::size_t idx = 0; idx < ITERATIONS; ++idx)
            {
                values[idx] = generator();
                list.push_front(values[idx]);
            }

            Assert::IsTrue(std::equal(std::rbegin(values), std::rend(values), std::rbegin(list), std::rend(list)));
        }

        TEST_METHOD(iterator_push_back_rbegin_rend_test)
        {
            std::default_random_engine generator;

            dsa::doubly_linked_list< unsigned int > list;
            unsigned int values[ITERATIONS];

            for (std::size_t idx = 0; idx < ITERATIONS; ++idx)
            {
                values[idx] = generator();
                list.push_back(values[idx]);
            }

            Assert::IsTrue(std::equal(std::begin(values), std::end(values), std::rbegin(list), std::rend(list)));
        }
    };
}
