#include <fstream>
#include <iostream>
#include <vector>

// Puzzle 1:
//
// Part 1 - Find the two entries that sum to 2020 and then multiply those two numbers together.
// Part 2 - Also do the same but looking for 3 entries
int main()
{
	// Read input
	std::vector<uint16_t> numbers;
	std::ifstream file("input.txt");

	if ( file )
	{
		uint16_t value;
		while ( file >> value )
		{
			numbers.push_back( value );
		}
	}

	constexpr auto target_number = 2020;

	// Loop through, stopping when we find two numbers which sum up to 2020
	auto found = false;
	for ( auto lhs = numbers.begin(); lhs != numbers.end() && !found; lhs++ )
	{
		for ( auto rhs = lhs + 1; rhs != numbers.end() && !found; rhs++ )
		{
			if (*lhs + *rhs == target_number)
			{
				const auto result = *rhs * *lhs; // all the stars because it's christmas
				std::cout << "Part one's answer is " << result << std::endl;
				found = true;
			}
		}
	}

	// Now the same but for 3 numbers. There is likely a smarter way
	found = false;
	for ( auto lhs = numbers.begin(); lhs != numbers.end() && !found; lhs++ )
	{
		// mhs = middle hand side?
		for ( auto mhs = lhs + 1; mhs != numbers.end() && !found; mhs++ )
		{
			for ( auto rhs = mhs + 1; rhs != numbers.end() && !found; rhs++ )
			{
				if (*lhs + *mhs + *rhs == target_number)
				{
					const auto result = *rhs * *mhs * *lhs; // all the stars because it's still christmas
					std::cout << "Part two's answer is " << result;
					found = true;
				}
			}
		}
	}
	return 0;
}