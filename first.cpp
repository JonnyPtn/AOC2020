#include <string>
#include <fstream>
#include <streambuf>

int main()
{
	// Read input
	std::ifstream t("first_input.txt");
	std::string str((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());
	return 0;
}