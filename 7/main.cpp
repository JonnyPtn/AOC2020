#include <fstream>
#include <iostream>
#include <unordered_map>
#include <regex>
#include <string>

// Puzzle 3:
//
// Part 1 - We're given a bunch of rules about which coloured bags can contain which other coloured bags, and we have to count the number of colours that can somehow contain a specific colour...
// Part 2 - calculate how many bags a certain coloured bag should contain in total

int main()
{
	std::ifstream file( "input.txt" );

	if ( !file )
	{
		std::cout << "Failed to load input file";
		return 1;
	}

	struct Bag
	{
		std::string colour;

		struct BagCount { Bag& bag; int32_t count; };
		std::vector<BagCount> contained_bag_limits;
	};

	std::unordered_map<std::string, Bag> bag_map;

	std::string line;
	while ( std::getline( file, line ) )
	{
		using namespace std::string_literals;

		// Up to first "bags" is this bag colour, so read and crop it
		const auto bags_string = "bags"s;
		const auto first_bags = line.find( bags_string );
		const auto bag_colour = line.substr( 0, first_bags );
		
		bag_map[bag_colour].colour = bag_colour;

		// We also know the next part will be " contain " in all cases, so also crop that
		line.erase( 0, bag_colour.length() + bags_string.length() + " contain "s.length() );

		while ( line.length() )
		{
			// Now we check for the special case of "no other bags." which we just ignore
			if ( line == "no other bags." )
			{
				break;
			}

			// Otherwise, it will follow the pattern of "X <colour> <bags,|bag.>
			// So first, read the number
			const auto first_space = line.find_first_of( ' ' );
			const auto X = std::stoi( line.substr( 0, first_space ) );
			line.erase( 0, first_space + 1 ); // + 1 to remove the space also

			// Then the colour
			const auto next_bag = line.find( "bag" );
			const auto colour = line.substr( 0, next_bag );
			line.erase( 0, colour.length() );

			// Make sure the colour being contained already exists, then keep a reference to it in our
			bag_map[colour].colour = colour;
			bag_map[bag_colour].contained_bag_limits.push_back( { bag_map[colour], X } );

			// Trim the remaining string so it's ready for next iteration (if present)
			if ( X == 1 )
			{
				line.erase( 0, "bag. "s.length() );
			}
			else
			{
				line.erase( 0, "bags. "s.length() );
			}
		}
	}
	// Now iterate over all the bags, and see how many of them could eventually contain a "shiny gold" bag
	auto bags_containing_colour = 0u;
	for ( const auto& bag : bag_map )
	{
		auto can_contain_colour = [&bag_map]( const Bag& bag_to_check, const std::string& colour ) -> bool
		{
			auto recurse_check = []( const Bag& bag_to_check, const std::string& colour, const auto& recurse_method )
			{
				for ( const auto& bag_count : bag_to_check.contained_bag_limits )
				{
					// See if this bag can directly contain it
					if ( bag_count.bag.colour == colour )
					{
						return true;
					}
					// If not, see if the bags this contains could contain it
					else if ( recurse_method( bag_count.bag, colour, recurse_method ) )
					{
						return true;
					}
				}
				return false;
			};

			return recurse_check( bag_to_check, colour, recurse_check );
		};

		if ( can_contain_colour( bag.second, "shiny gold " ) )
		{
			++bags_containing_colour;
		}
	}

	std::cout << "Total bags that can contain shiny gold bags: " << bags_containing_colour << std::endl;

	// Find the total number of bags contained in a shiny gold one
	const auto& shiny_gold_bag = bag_map["shiny gold "];
	auto count_total_contained_bags = [&]( const Bag& bag )
	{
		auto recursive_count = [&]( const Bag& bag, const auto& recurse_method ) -> uint64_t
		{
			// For each bag colour this can contain, check how many bags that can contain and then
			// multiply by the number of this bag we can hold
			uint64_t this_contains_count = 0u;
			for ( auto& contained_bag : bag.contained_bag_limits )
			{
				const auto contained_count = recurse_method( contained_bag.bag, recurse_method );
				this_contains_count += contained_bag.count + contained_count * contained_bag.count;
			}
			return this_contains_count;
		};
		return recursive_count( shiny_gold_bag, recursive_count );
	};

	const auto result = count_total_contained_bags( shiny_gold_bag );
	std::cout << "Shiny gold bag can contain a total of " << result << " other bags";
	return 0;
}