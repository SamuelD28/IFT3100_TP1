#include <commands/command.hpp>
#include <ranges>

bool command::PaletteCommand::bind(TextCommand textCommand)
{

	if (textCommand.arguments.size() != 1)
	{
		return false;
	}

	auto colorComponents = std::vector<float>();
	auto position = textCommand.arguments[0].find(',');

	while (position != std::string::npos)
	{
		auto rawComponent = textCommand.arguments[0].substr(0, position);
		auto component = std::stof(rawComponent);
		colorComponents.push_back(component);

		textCommand.arguments[0].erase(0, position + 1);
		position = textCommand.arguments[0].find(',');

		if (position == std::string::npos)
		{
			auto rawComponent = textCommand.arguments[0].substr(0, position);
			auto component = std::stof(rawComponent);
			colorComponents.push_back(component);
		}
	}

	if (colorComponents.size() != 4)
	{
		return false;
	}

	this->color.red = colorComponents.at(0);
	this->color.green = colorComponents.at(1);
	this->color.blue = colorComponents.at(2);
	this->color.alpha = colorComponents.at(3);
	return true;
}

bool command::PaletteCommand::exec(context::Context *context) const
{
	context->background = this->color;
	return true;
}

bool command::PaletteCommand::revert(context::Context *context) const
{
	context->background = color::RGBA{};
	return true;
}