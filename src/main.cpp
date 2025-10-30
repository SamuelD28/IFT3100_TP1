#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <filesystem>
#include <iostream>
#include <random>
#include <commands/command.hpp>

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

	command::Context context{};

	for (;;)
	{
		std::cin.clear();
		std::string input = "";
		std::getline(std::cin, input);
		auto consoleCommand = command::from(input);
		// std::cout << consoleCommand;

		if (!consoleCommand.valid)
		{
			std::cout << "[ERROR] Command is invalid, verify input\n";
			continue;
		}

		if (!command::commandsBuilder.contains(consoleCommand.name))
		{
			std::cout << "[ERROR] No command of name:" << consoleCommand.name << " found\n";
			continue;
		}

		auto command = command::commandsBuilder[consoleCommand.name](consoleCommand);
		std::cout << &context;
	}

	return 0;
}