#include <fstream>
#include <iostream>
#include <unordered_map>
#include <regex>
#include <string>

// Puzzle 3:
//
// Part 1 - We're given some "passport" data separated by new lines, and need to validate that it includes all of the required data except one, the "Country ID"
// Part 2 - validate further:
//    byr( Birth Year ) - four digits; at least 1920 and at most 2002.
//    iyr( Issue Year ) - four digits; at least 2010 and at most 2020.
//    eyr( Expiration Year ) - four digits; at least 2020 and at most 2030.
//    hgt( Height ) - a number followed by either cm or in:
//		- If cm, the number must be at least 150 and at most 193.
//		- If in, the number must be at least 59 and at most 76.
//    hcl( Hair Color ) - a # followed by exactly six characters 0 - 9 or a - f.
//    ecl( Eye Color ) - exactly one of : amb blu brn gry grn hzl oth.
//    pid( Passport ID ) - a nine - digit number, including leading zeroes.
//    cid( Country ID ) - ignored, missing or not.

constexpr auto birth_year = "byr";
constexpr auto issue_year = "iyr";
constexpr auto expiration_year = "eyr";
constexpr auto height = "hgt";
constexpr auto hair_colour = "hcl";
constexpr auto eye_colour = "ecl";
constexpr auto passport_id = "pid";

int main()
{
	std::ifstream file("input.txt");

	if ( !file )
	{
		std::cout << "Failed to load input file";
		return 1;
	}

	
	std::unordered_map<std::string, std::string> passport_fields;
	auto valid_passport_count = 0u;

	auto validate_passport = [&passport_fields, &valid_passport_count]()
	{
		bool valid = true;

		// byr( Birth Year ) - four digits; at least 1920 and at most 2002.
		if ( valid = valid && !passport_fields[birth_year].empty() )
		{
			const auto birth_year_value = std::stoi( passport_fields[birth_year] );
			if ( birth_year_value < 1920 || birth_year_value > 2002 )
			{
				valid = false;
			}
		}

		// iyr( Issue Year ) - four digits; at least 2010 and at most 2020.
		if ( valid = valid && !passport_fields[issue_year].empty() )
		{
			const auto issue_year_value = std::stoi( passport_fields[issue_year] );
			if ( issue_year_value < 2010 || issue_year_value > 2020 )
			{
				valid = false;
			}
		}

		// eyr( Expiration Year ) - four digits; at least 2020 and at most 2030.
		if ( valid = valid && !passport_fields[expiration_year].empty() )
		{
			const auto expiration_year_value = std::stoi( passport_fields[expiration_year] );
			if ( expiration_year_value < 2020 || expiration_year_value > 2030 )
			{
				valid = false;
			}
		}

		// hgt( Height ) - a number followed by either cm or in:
		if ( valid = valid && !passport_fields[height].empty() )
		{
			std::regex height_pattern{ "(\\d+)(cm|in)" };
			std::smatch match;
			if ( !std::regex_match( passport_fields[height], match, height_pattern ) )
			{
				valid = false;
			}
			else
			{
				// If cm, the number must be at least 150 and at most 193.
				// If in, the number must be at least 59 and at most 76.
				const auto value = std::stoi( match[1] );
				if ( match[2] == "cm" )
				{
					if ( value < 150 || value > 193 )
					{
						valid = false;
					}
				}
				else if ( value < 59 || value > 76 )
				{
					valid = false;
				}
			}
		}

		// hcl( Hair Color ) - a # followed by exactly six characters 0 - 9 or a - f.
		if ( valid = valid && !passport_fields[hair_colour].empty() )
		{
			std::regex colour_pattern{ "#([0-9]|[a-f]){6}" };
			if ( !std::regex_match( passport_fields[hair_colour], colour_pattern ) )
			{
				valid = false;
			}
		}

		// ecl( Eye Color ) - exactly one of : amb blu brn gry grn hzl oth.
		if ( valid = valid && !passport_fields[eye_colour].empty() )
		{
			std::regex eye_colour_pattern{ "amb|blu|brn|gry|grn|hzl|oth" };
			if ( !std::regex_match( passport_fields[eye_colour], eye_colour_pattern ) )
			{
				valid = false;
			}
		}

		// pid( Passport ID ) - a nine - digit number, including leading zeroes.
		if ( valid = valid && !passport_fields[passport_id].empty() )
		{
			std::regex id_pattern{ "\\d{9}" };
			if ( !std::regex_match( passport_fields[passport_id], id_pattern ) )
			{
				valid = false;
			}
		}
		
		if ( valid )
		{
			++valid_passport_count;
		}
	};

	std::string field;
	while ( std::getline( file, field ) )
	{
		// Empty line indicates end of the passport details
		if ( !field.length() )
		{
			validate_passport();
			passport_fields = {};
			continue;
		}

		while ( field.length() )
		{
			const auto first_colon = field.find_first_of( ':' );
			auto first_space = field.find_first_of( ' ' );
			if ( first_space == std::string::npos )
			{
				// end of the line...
				first_space = field.length();
			}
			const auto key = field.substr( 0, first_colon );
			const auto value = field.substr( first_colon + 1, first_space - 1 - first_colon);
			passport_fields[key] = value;

			if ( first_space == field.length() )
			{
				break;
			}
			else
			{
				field = field.substr( first_space + 1 );
			}
		}
	}

	// We may not get an empty line at the end, so if we still have passport details at the end then check them
	if ( !passport_fields.empty() )
	{
		validate_passport();
	}

	std::cout << "Total valid passports: " << valid_passport_count << std::endl;

	return 0;
}