#include <commands/command.hpp>

const char *COMMAND_SEPARATOR = ":";
const char *ARGUMENT_SEPARATOR = "|";

command::TextCommand command::from(std::string input)
{
	auto command = command::TextCommand{};

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

std::ostream &operator<<(std::ostream &os, const command::TextCommand command)
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
