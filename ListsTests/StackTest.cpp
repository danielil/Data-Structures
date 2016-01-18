#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Lists\Stack.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ListsTests
{		
	TEST_CLASS(StackTest)
	{
	public:
		
		TEST_METHOD(ConstructorTest)
		{
		    Lists::Stack<int> stack;

            Assert::AreEqual(stack.isEmpty(), true);
		}

        TEST_METHOD(PushPopTest)
        {
            Lists::Stack<int> stack;

            const std::size_t iterations = 3U;
            int values[iterations];

            for (std::size_t iteration = 0U; iteration < iterations; ++iteration)
            {
                values[iteration] = std::rand();
                stack.push(values[iteration]);

                Assert::AreEqual(iteration + 1U, stack.getSize());
            }

            Assert::AreEqual(stack.getSize(), iterations);

            for (int iteration = iterations - 1; iteration >= 0; --iteration)
            {
                Assert::AreEqual(values[iteration], stack.pop());
            }

            Assert::AreEqual(stack.isEmpty(), true);
        }

	};
}
