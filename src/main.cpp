#include <commands/command.hpp>
#include <context/context.hpp>

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

	context::Context context{};

	for (;;)
	{
		std::cin.clear();
		std::string input = "";
		std::getline(std::cin, input);
		auto textCommand = command::from(input);
		std::cout << textCommand;

		if (!textCommand.valid)
		{
			std::cout << "[ERROR] Text command is invalid, verify input\n";
			continue;
		}

		auto command = command::build(textCommand);
		if (command == nullptr)
		{
			std::cout << "[ERROR] Command is invalid, verify input\n";
			continue;
		}

		if (!command->exec(&context))
		{
			std::cout << "[ERROR] Could not execute command, verify input\n";
			continue;
		}
		std::cout << &context;
	}

	return 0;
}