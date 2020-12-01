#include <fstream>
#include <iostream>
#include <vector>

// Puzzle 1:
//
// find the two entries that sum to 2020 and then multiply those two numbers together.
int main()
{
	// Read input
	std::vector<uint16_t> numbers;
	std::ifstream file("first_input.txt");

	if ( file )
	{
		uint16_t value;
		while ( file >> value )
		{
			numbers.push_back( value );
		}
	}

	// Loop through, stopping when we find two numbers which sum up to 2020
	for ( auto lhs = numbers.begin(); lhs != numbers.end(); lhs++ )
	{
		for ( auto rhs = lhs + 1; rhs != numbers.end(); rhs++ )
		{
			if (*rhs + *lhs == 2020)
			{
				const auto result = *rhs * *lhs; // all the stars because it's christmas
				std::cout << "The answer is " << result;
			}
		}
	}

	return 0;
}