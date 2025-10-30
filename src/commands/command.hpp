#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <random>
#include <functional>
#include <map>

namespace command
{
	struct Resource
	{
		int id{};
		std::string type{};
		std::string path{};
	};

	struct Context
	{
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

	struct ICommand
	{
		virtual bool exec(Context *) const = 0;
		virtual bool revert(Context *) const = 0;
		virtual bool bind(TextCommand) = 0;
	};

	ICommand *build(TextCommand);

	struct LoadCommand : public ICommand
	{
		std::string path{};
		bool exec(Context *) const override;
		bool revert(Context *) const override;
		bool bind(TextCommand) override;
	};

	// struct QuitCommand
	// {
	// };

	// struct SnapCommand
	// {
	// };

	// struct PaletteCommand
	// {
	// };

	// const std::map<std::string, > commands{
	// 		{"load", LoadCommand::build},
	// };

};