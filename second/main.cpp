#include <fstream>
#include <iostream>
#include <regex>

// Puzzle 2:
//
// Part 1 - File contains lines like "X-Y <char>: <string>" and we need to verify if each <string> contains X < n < Y instances of <char>
// Part 2 - same format as part 1, except X and Y represent specific positions (1-indexed!) in the password, and we need exactly (and only) one of them to match
int main()
{

	// Read input into one big string - we're going to regex this bad boy
	std::vector<uint16_t> numbers;
	std::ifstream file("input.txt");

	if ( !file )
	{
		std::cout << "Failed to load input file";
		return 1;
	}

	std::string str((std::istreambuf_iterator<char>(file)),
                 std::istreambuf_iterator<char>());

	std::regex pattern("(\\d+)-(\\d+) (\\w): (\\w+)");

	const auto first_match = std::sregex_iterator( str.begin(), str.end(), pattern );
	const auto last_match = std::sregex_iterator();

	auto valid_part_1_passwords = 0;
	auto valid_part_2_passwords = 0;

	for ( auto match = first_match; match != last_match; match++ )
	{
		// Match will be the whole pattern, so we get the vars from the submatches
		std::smatch string_match = *match;
		const auto min = std::stoi(string_match[1].str());
		const auto max = std::stoi(string_match[2].str());
		const auto character = string_match[3].str()[0];
		const auto password = string_match[4].str();

		// Part 1 - does the password contain the character as many times as it should
		const auto character_count = std::count( password.begin(), password.end(), character );
		if ( character_count >= min && character_count <= max )
		{
			++valid_part_1_passwords;
		}

		// Part 2 - does one and only one of the given positions match the character
		const auto first_match = password[min - 1] == character;
		const auto second_match = password[max - 1] == character;
		if (first_match ^ second_match)
		{
			++valid_part_2_passwords;
		}
	}
	
	std::cout << "There were " << valid_part_1_passwords << " valid passwords based on count" << std::endl;
	std::cout << "There were " << valid_part_2_passwords << " valid passwords based on specific indices" << std::endl;


	return 0;
}