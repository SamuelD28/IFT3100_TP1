#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

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

	static ConsoleCommand build(std::string input)
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
	Command() {}

public:
	virtual bool from(ConsoleCommand command) = 0;

public:
	virtual bool exec(Context context) = 0;

public:
	virtual bool revert(Context context) = 0;
};

class QuitCommand : public Command
{
public:
	bool from(ConsoleCommand command)
	{
	}

public:
	bool exec(Context context)
	{
	}

public:
	bool revert(Context context)
	{
	}
};

class LoadCommand : public Command
{
public:
	std::string path{};

public:
	bool from(ConsoleCommand command)
	{
		// assertions
		if (command.arguments.size() != 1)
		{
			return false;
		}

		path = command.arguments.at(0);
	}

public:
	bool from(std::string path)
	{
		path = path;
	}

public:
	bool exec(Context context)
	{
	}

public:
	bool revert(Context context)
	{
	}
};

class SnapCommand : public Command
{
public:
	bool from(ConsoleCommand command)
	{
	}

public:
	bool exec(Context context)
	{
	}

public:
	bool revert(Context context)
	{
	}
};

class PaletteCommand : public Command
{
public:
	bool from(ConsoleCommand command)
	{
	}

public:
	bool exec(Context context)
	{
	}

public:
	bool revert(Context context)
	{
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

	std::map<std::string, Command> commands{
			{"quit", QuitCommand()},
			{"load", LoadCommand()},
			{"snap", SnapCommand()},
			{"palette", PaletteCommand()},
	};

	for (;;)
	{
		std::string input = "";
		std::cin >> input;
		auto consoleCommand = ConsoleCommand{}.build(input);
		std::cout << consoleCommand;

		if (!consoleCommand.valid)
		{
			std::cout << "[ERROR] Command is invalid, verify input\n";
			continue;
		}

		if (!commands.contains(consoleCommand.name))
		{
			std::cout << "[ERROR] No command of name:" << consoleCommand.name << " found\n";
			continue;
		}
	}

	return 0;
}