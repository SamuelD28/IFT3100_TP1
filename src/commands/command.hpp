#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <vector>
#include <iostream>

namespace command
{
	struct TextCommand
	{
		bool valid{false};
		std::string name{""};
		std::vector<std::string> arguments{};
	};

	TextCommand from(std::string input);

	class Command
	{
	public:
		virtual bool exec(Context *context) = 0;

	public:
		virtual bool revert(Context *context) = 0;
	};
};

#endif