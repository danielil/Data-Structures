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

	generator( const generator& ) = delete;
	generator( generator&& ) noexcept = delete;

	generator& operator=( const generator& ) = delete;
	generator& operator=( generator&& ) noexcept = delete;

	T
	operator()()
	{
		return this->distribution( this->engine );
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

	template < typename Iterator >
	void
	fill_buffer_n(
		Iterator begin,
		const std::size_t iterations )
	{
		std::generate_n(
			begin,
			iterations,
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
