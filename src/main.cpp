#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <functional>

struct Resource
{
public:
	int id{};

public:
	std::string type{};

public:
	std::string path{};
};

class Context
{
public:
	std::vector<Resource> resources{};
};

const char *COMMAND_SEPARATOR = ":";
const char *ARGUMENT_SEPARATOR = "|";

struct ConsoleCommand
{
	bool valid{false};
	std::string name{""};
	std::vector<std::string> arguments{};

	static ConsoleCommand bind(std::string input)
	{
		auto command = ConsoleCommand{};

		auto separatorIndex = input.find(":");
		if (separatorIndex == SIZE_MAX)
		{
			command.valid = false;
			return command;
		}

		command.name = input.substr(0, separatorIndex);

		unsigned int argumentStartIndex = separatorIndex + 1;
		for (int argumentEndIndex = separatorIndex + 1; argumentEndIndex < input.length(); argumentEndIndex++)
		{
			auto currentChar = input[argumentEndIndex];

			// Weve reach the end, substr is built a bit different
			if (argumentEndIndex == input.length() - 1)
			{
				auto argument = input.substr(argumentStartIndex, argumentEndIndex + 1 - argumentStartIndex);
				command.arguments.push_back(argument);
			}

			if (currentChar == *ARGUMENT_SEPARATOR)
			{
				auto argument = input.substr(argumentStartIndex, argumentEndIndex - argumentStartIndex);
				command.arguments.push_back(argument);
				argumentStartIndex = argumentEndIndex + 1;
			}
		}

		command.valid = true;
		return command;
	}
};

std::ostream &operator<<(std::ostream &os, const ConsoleCommand command)
{
	std::string output = "[COMMAND] name => " + command.name + ", valid => " + (command.valid ? "true" : "false");

	for (int i = 0; i < command.arguments.size(); i++)
	{
		auto argument = command.arguments[i];
		output += ", argument-" + std::to_string(i) + " => " + argument;
	}

	os << output << "\n";
	return os;
}

class Command
{
public:
	virtual bool exec(const Context *context) = 0;

public:
	virtual bool revert(const Context *context) = 0;
};

class QuitCommand : public Command
{
public:
	static Command *build(ConsoleCommand command)
	{
		return new QuitCommand();
	};

public:
	bool exec(const Context *context)
	{
		std::cout << "quit command" << "\n";
		return true;
	}

public:
	bool revert(const Context *context)
	{
		return true;
	}
};

class LoadCommand : public Command
{
public:
	std::string path{};

public:
	static Command *build(ConsoleCommand command)
	{
		auto loadCommand = new LoadCommand();
		// assertions
		if (command.arguments.size() != 1)
		{
			return nullptr;
		}

		loadCommand->path = command.arguments.at(0);
		return loadCommand;
	}

public:
	bool exec(const Context *context) override
	{
		std::ifstream file(path);

		if (file.is_open())
		{
			std::cout << "[LOAD COMMAND] file open \n";
			return false;
		}
		else
		{
			std::cout << "[LOAD COMMAND] file is not open \n";
		}

		file.close();
		return true;
	}

public:
	bool revert(const Context *context) override
	{
		return true;
	}
};

class SnapCommand : public Command
{

public:
	static Command *build(ConsoleCommand command)
	{
		return new SnapCommand();
	}

public:
	bool exec(const Context *context)
	{
		return true;
	}

public:
	bool revert(const Context *context)
	{
		return true;
	}
};

class PaletteCommand : public Command
{
public:
	static Command *build(ConsoleCommand command)
	{
		return new PaletteCommand();
	}

public:
	bool exec(const Context *context)
	{
		return true;
	}

public:
	bool revert(const Context *context)
	{
		return true;
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

	// Avoid this abstraction construction and rather
	// just create a builder function
	std::map<std::string, std::function<Command *(ConsoleCommand)>> commandsBuilder{
			{"quit", QuitCommand::build},
			{"load", LoadCommand::build},
			{"snap", SnapCommand::build},
			{"palette", PaletteCommand::build},
	};

	const Context context{};

	for (;;)
	{
		std::string input = "";
		std::cin >> input;
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
	}

	return 0;
}