#include <fstream>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <vector>

// Puzzle 5:
//

struct Seat
{
	std::bitset<7> row{};
	std::bitset<3> column{};
	uint64_t id{};
};

auto generate_seat( const std::string& string )
{
	Seat seat;
	// First 7 characters we can treat as bits of an integer
	for ( auto bit_index = 0u; bit_index < seat.row.size(); ++bit_index )
	{
		if ( string[bit_index] == 'B' )
		{
			seat.row.set( seat.row.size() - bit_index - 1 );
		}
	}
	
	// Next 3 are also bits of an integer, for the column
	for ( auto column_index = 0u; column_index < seat.column.size(); ++column_index )
	{
		if ( string[column_index + 7] == 'R' ) // magic number bad, I know
		{
			seat.column.set( seat.column.size() - column_index - 1 );
		}
	}

	seat.id = seat.row.to_ulong() * 8 + seat.column.to_ulong();

	return seat;
}

int main()
{
	std::ifstream file( "input.txt" );

	if ( !file )
	{
		std::cout << "Failed to load input file";
		return 1;
	}

	std::string line{};
	uint64_t max_seat_id{};
	std::vector<Seat> seats;
	while ( file >> line )
	{
		seats.emplace_back( generate_seat( line ) );
		
		max_seat_id = std::max( max_seat_id, seats.back().id );
	}

	std::cout << "Max seat ID: " << max_seat_id << std::endl;

	// Now we sort the seats and iterate over until we find the missing ID
	std::sort( seats.begin(), seats.end(), []( Seat& lhs, Seat& rhs )
				{
					return lhs.id < rhs.id;
				} );

	for ( auto seat = seats.begin()+1; seat != seats.end()-1; ++seat )
	{
		// To be our seat, there needs to be a gap either below or above this seat
		if ( (seat - 1)->id == seat->id - 2 )
		{
			std::cout << "My seat is " << seat->id - 1 << std::endl;
			break;
		}
		else if ( (seat + 1)->id == seat->id + 2 )
		{
			std::cout << "My seat is " << seat->id + 1 << std::endl;
			break;
		}
	}

	return 0;
}