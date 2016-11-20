/**
 * Utility class for generating random value from a distribution.
 */

#pragma once

#include <random>

template < typename T >
class generator
{
public:

	generator() = default;
	~generator() noexcept = default;

	generator( const generator& ) = default;
	generator( generator&& ) noexcept = default;

	generator& operator=( const generator& ) = default;
	generator& operator=( generator&& ) noexcept = default;

	T
	operator()()
	{
		return distribution( engine );
	}

	template < typename Iterator >
	void
	fill_buffer(
		Iterator begin,
		Iterator end )
	{
		std::generate(
			begin,
			end,
			[=]()
			{
				return this->operator()();
			} );
	}

private:
	std::random_device entropy;
	std::default_random_engine engine { entropy() };
	std::uniform_int_distribution< T > distribution;
};
