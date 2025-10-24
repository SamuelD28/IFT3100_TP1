#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <filesystem>
#include <iostream>
#include <random>

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

	// Avoid this abstraction construction and rather
	// just create a builder function
	std::map<std::string, std::function<Command *(ConsoleCommand)>> commandsBuilder{
			{"quit", QuitCommand::build},
			{"load", LoadCommand::build},
			{"snap", SnapCommand::build},
			{"palette", PaletteCommand::build},
	};

	Context context{};

	for (;;)
	{
		std::cin.clear();
		std::string input = "";
		std::getline(std::cin, input);
		auto consoleCommand = ConsoleCommand::bind(input);
		std::cout << consoleCommand;

		if (!consoleCommand.valid)
		{
			std::cout << "[ERROR] Command is invalid, verify input\n";
			continue;
		}

		if (!commandsBuilder.contains(consoleCommand.name))
		{
			std::cout << "[ERROR] No command of name:" << consoleCommand.name << " found\n";
			continue;
		}

		auto command = commandsBuilder[consoleCommand.name](consoleCommand);
		command->exec(&context);
		std::cout << &context;
	}

	return 0;
}