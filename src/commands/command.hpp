#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <random>
#include <functional>

namespace command
{
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

	std::ostream &operator<<(std::ostream &os, const Context *context)
	{
		std::string output = "";

		for (auto resource : context->resources)
		{
			output += "[RESOURCE] id => " + std::to_string(resource.id) + " type => " + resource.type + "\n";
		}

		os << output << "\n";
		return os;
	}

	struct TextCommand
	{
		bool valid{false};
		std::string name{""};
		std::vector<std::string> arguments{};
	};

	TextCommand from(std::string input);

	typedef Command *build(TextCommand);

	class Command
	{
	public:
		virtual bool exec(Context *context) = 0;

	public:
		virtual bool revert(Context *context) = 0;
	};

	class QuitCommand : public Command
	{
		static Command *build(command::TextCommand command);
	};

	class SnapCommand : public Command
	{
		static Command *build(command::TextCommand command);
	};

	class PaletteCommand : public Command
	{
		static Command *build(command::TextCommand command);
	};

	class LoadCommand : public Command
	{
	public:
		std::string path{};

		static Command *build(command::TextCommand command);
	};
};