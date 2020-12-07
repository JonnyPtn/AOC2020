#include <fstream>
#include <iostream>
#include <regex>

// Puzzle 3:
//
// Part 1 - We have a 2d array representing trees on the slope: "." is empty and "#" is a tree. If we start in the top left and go across 3 and down 1 until we reach the end, how many trees to we hit?
// Part 2 - as above, but for 1,3,5,7 across / 1 down, and 1 across / 2 down, then multiply all the results together

constexpr auto tree = '#';

int main()
{
	std::ifstream file("input.txt");

	if ( !file )
	{
		std::cout << "Failed to load input file";
		return 1;
	}

	std::vector<std::string> lines;
	std::string line;
	while ( file >> line )
	{
		lines.emplace_back( line );
	}

	auto count_trees = [&lines]( auto x_distance, auto y_distance )
	{
		uint64_t x{};
		uint64_t y{};
		uint64_t tree_count{};
		while ( y < lines.size() )
		{
			if ( lines[y][x % lines[y].length()] == tree )
			{
				++tree_count;
			}
			x += x_distance;
			y += y_distance;
		}
		return tree_count;
	};
	
	const auto part_1_answer = count_trees( 3, 1 );

	std::cout << "Part 1: " << part_1_answer << std::endl;

	const auto one_by_one = count_trees( 1, 1 );
	const auto three_by_one = part_1_answer; // no need to recalculate
	const auto five_by_one = count_trees( 5, 1 );
	const auto seven_by_one = count_trees( 7, 1 );
	const auto one_by_two = count_trees( 1, 2 );

	const auto part_2_answer = one_by_one * three_by_one * five_by_one * seven_by_one * one_by_two;

	std::cout << "Part 2: " << part_2_answer << std::endl;

	return 0;
}