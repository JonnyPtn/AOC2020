#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <numeric>
#include <unordered_map>

// Puzzle 6:
//
// Part 1: groups have answered questions a-z either yes or no - input shows who answered yes to what, so add up the totals for questions that any person in a group answered yes to then sum them
// Part 2: the same, but only count questions where ALL people in a group answered yes

int main()
{
	std::ifstream file( "input.txt" );

	if ( !file )
	{
		std::cout << "Failed to load input file";
		return 1;
	}

	std::vector<uint64_t> group_counts;
	std::unordered_map<char, uint64_t> current_group_answers;

	std::string line;
	uint64_t current_group_member_count{};
	while ( std::getline( file, line ) )
	{
		if ( line.empty() )
		{
			// New line, end of group, so put the total in our storage
			uint64_t total_count{};
			for ( auto& answer : current_group_answers )
			{
				if ( answer.second == current_group_member_count )
				{
					++total_count;
				}
			}
			group_counts.push_back( total_count );
			current_group_answers = {};
			current_group_member_count = {};
			continue;
		}
		else
		{
			++current_group_member_count;
			for ( const auto& answer : line )
			{
				++current_group_answers[answer];
			}
		}
	}

	// In case we don't get a final blank line
	if ( !current_group_answers.empty() )
	{
		uint64_t total_count{};
		for ( auto& answer : current_group_answers )
		{
			if ( answer.second == current_group_member_count )
			{
				++total_count;
			}
		}
		group_counts.push_back( total_count );
	}

	const auto sum_total = std::accumulate( group_counts.begin(), group_counts.end(), 0 );
	std::cout << "Part 2 answer: " << sum_total << std::endl;

	return 0;
}