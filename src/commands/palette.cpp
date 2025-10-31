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

	this->red = colorComponents.at(0);
	this->green = colorComponents.at(1);
	this->blue = colorComponents.at(2);
	this->alpha = colorComponents.at(3);
	return true;
}

bool command::PaletteCommand::exec(context::Context *context) const
{
	context->alpha = this->alpha;
	context->red = this->red;
	context->green = this->green;
	context->blue = this->blue;
	return true;
}

bool command::PaletteCommand::revert(context::Context *context) const
{
	context->alpha = 0.0f;
	context->red = 0.0f;
	context->green = 0.0f;
	context->blue = this->blue;
	return true;
}