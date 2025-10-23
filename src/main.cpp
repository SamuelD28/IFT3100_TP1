#include <iostream>
#include <iostream>
#include <string>
#include <vector>

const char *COMMAND_SEPARATOR = ":";
const char *ARGUMENT_SEPARATOR = ",";

struct ConsoleCommand
{
	bool valid{};
	std::string name{};
	std::vector<std::string> arguments{};

	void parse(std::string input)
	{
		auto separatorIndex = input.find(":");

		if (separatorIndex == 0)
		{
			valid = false;
		}

		auto test = input.substr(0, separatorIndex - 1);
		auto argumentsInput = input.substr(separatorIndex + 1, input.length());

		std::cout << test << "\n";
		std::cout << argumentsInput << "\n";

		valid = true;
	}
};

/**
 * Console process to parse commands
 *
 * Commands
 * quit : exit the current process
 *
 * Image part ---
 * load : load a file at a given path, extract and save metadata
 * Snap : Export current framebuffer for a given period
 * palette : create a color palette that can be reused
 *
 */
int main(int argc, char *argv[])
{
	// auto window = application::setup("Labo 4", 800, 800);
	// if (window == nullptr)
	// {
	// 	std::cout << "There was an error initializing the window";
	// 	std::cout.flush();
	// 	return -1;
	// }

	auto command = ConsoleCommand{};

	while (!command.valid)
	{
		std::string input = "";
		std::cin >> input;
		command.parse(input);
	}

	return 0;
}