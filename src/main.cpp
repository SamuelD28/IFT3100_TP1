#include <iostream>
#include <iostream>
#include <string>
#include <vector>

const char *COMMAND_SEPARATOR = ":";
const char *ARGUMENT_SEPARATOR = "|";

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
			return;
		}

		name = input.substr(0, separatorIndex);

		unsigned int argumentStartIndex = separatorIndex + 1;
		for (int argumentEndIndex = separatorIndex + 1; argumentEndIndex < input.length(); argumentEndIndex++)
		{
			auto currentChar = input[argumentEndIndex];

			// Weve reach the end, substr is built a bit different
			if (argumentEndIndex == input.length() - 1)
			{
				auto argument = input.substr(argumentStartIndex, argumentEndIndex + 1 - argumentStartIndex);
				arguments.push_back(argument);
			}

			if (currentChar == *ARGUMENT_SEPARATOR)
			{
				auto argument = input.substr(argumentStartIndex, argumentEndIndex - argumentStartIndex);
				arguments.push_back(argument);
				argumentStartIndex = argumentEndIndex + 1;
			}
		}

		valid = true;
	}
};

std::ostream &operator<<(std::ostream &os, const ConsoleCommand command)
{
	std::string output = "name => " + command.name + ", valid => " + (command.valid ? "true" : "false");

	for (int i = 0; i < command.arguments.size(); i++)
	{
		auto argument = command.arguments[i];
		output += ", argument-" + std::to_string(i) + " => " + argument;
	}

	os << output << "\n";
	return os;
}

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
		std::cout << command << "\n";
	}

	return 0;
}