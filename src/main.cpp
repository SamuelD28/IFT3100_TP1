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
	virtual Command *clone() = 0;

public:
	virtual bool exec(const Context *context) = 0;

public:
	virtual bool revert(const Context *context) = 0;
};

class QuitCommand : public Command
{
public:
	Command *clone() override
	{
		return new QuitCommand(*this);
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

class LoadCommand : public Command
{
public:
	std::string path{};

public:
	Command *clone() override
	{
		return new LoadCommand(*this);
	}

public:
	bool from(ConsoleCommand command)
	{
		// assertions
		if (command.arguments.size() != 1)
		{
			return false;
		}

		path = command.arguments.at(0);
		return true;
	}

public:
	bool exec(const Context *context) override
	{
		std::ifstream file(path);

		if (file.is_open())
		{
			std::cout << "file open \n";
			return false;
		}
		else
		{
			std::cout << "file is not open \n";
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
	Command *clone() override
	{
		return new SnapCommand(*this);
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
	Command *clone() override
	{
		return new PaletteCommand(*this);
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

	std::map<std::string, Command *> commands{
			{"quit", QuitCommand{}.clone()},
			{"load", LoadCommand{}.clone()},
			// {"snap", SnapCommand()},
			// {"palette", PaletteCommand()},
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

		// auto command = commands[consoleCommand.name];
		// command.exec(&context);
	}

	return 0;
}