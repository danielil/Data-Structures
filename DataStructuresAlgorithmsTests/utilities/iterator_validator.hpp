template< typename OutputIterator, typename IteratorRetriever >
bool
is_valid_iterator(
	OutputIterator begin,
	OutputIterator end,
	IteratorRetriever retriever )
{
	const auto iterations = std::distance( begin, end );
	std::array< value_type, iterations > values;

	generator< value_type > generator;
	generator.fill_buffer(
			std::begin( values ),
			std::end( values ) );

	std::copy(
			std::cbegin( values ),
			std::cend( values ),
			begin );

	auto it_standard = retriever( values );
	auto prefix_increment_standard = ++it_standard;
	const auto prefix_value_standard = *prefix_increment_standard;
	auto postfix_increment_standard = prefix_increment_standard++;
	const auto postfix_value_standard = *postfix_increment_standard;

	REQUIRE( prefix_value_standard == postfix_value_standard );

	auto it_custom = begin;
	auto prefix_increment_custom = ++it_custom;
	const auto prefix_value_custom = *prefix_increment_custom;
	auto postfix_increment_custom = prefix_increment_custom++;
	const auto postfix_value_custom = *postfix_increment_custom;

	REQUIRE( prefix_value_custom == postfix_value_custom );

	REQUIRE( prefix_value_standard == prefix_value_custom );
	REQUIRE( postfix_value_standard == postfix_value_custom );
}