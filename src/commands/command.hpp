#pragma once

#include <context/context.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <random>
#include <functional>
#include <map>

namespace command
{
	struct TextCommand
	{
		bool valid{false};
		std::string name{""};
		std::vector<std::string> arguments{};
	};

	std::ostream &operator<<(std::ostream &os, const command::TextCommand command);
	TextCommand from(std::string input);

	struct ICommand
	{
		virtual bool exec(context::Context *) const = 0;
		virtual bool revert(context::Context *) const = 0;
		virtual bool bind(TextCommand) = 0;
	};

	ICommand *build(TextCommand);

	struct LoadCommand : public ICommand
	{
		std::string path{};
		bool exec(context::Context *) const override;
		bool revert(context::Context *) const override;
		bool bind(TextCommand) override;
	};

	// Could support multiple color schema (rgba, rgb, hsb)
	struct PaletteCommand : public ICommand
	{
		float red = 0.0f;
		float green = 0.0f;
		float blue = 0.0f;
		float alpha = 0.0f;

		bool exec(context::Context *) const override;
		bool revert(context::Context *) const override;
		bool bind(TextCommand) override;
	};

	// struct QuitCommand
	// {
	// };

	// struct SnapCommand
	// {
	// };

};