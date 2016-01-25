#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Lists\Queue.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ListsTests
{
    TEST_CLASS(QueueTest)
    {
    public:

        TEST_METHOD(ConstructorTest)
        {
            Lists::Queue<int> queue;

            Assert::AreEqual(queue.isEmpty(), true);
        }

        TEST_METHOD(PushPopTest)
        {
            Lists::Queue<int> queue;

            const std::size_t iterations = 3U;
            int values[iterations];

            for (std::size_t iteration = 0U; iteration < iterations; ++iteration)
            {
                values[iteration] = std::rand();
                queue.enqueue(values[iteration]);

                Assert::AreEqual(iteration + 1U, queue.getSize());
            }

            Assert::AreEqual(queue.getSize(), iterations);

            for (std::size_t iteration = 0U; iteration < iterations; ++iteration)
            {
                Assert::AreEqual(values[iteration], queue.dequeue());
            }

            Assert::AreEqual(queue.isEmpty(), true);
        }

    };
}
