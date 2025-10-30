#include <context/context.hpp>

std::ostream &context::operator<<(std::ostream &os, const context::Context *context)
{
	std::string output = "";

	for (auto resource : context->resources)
	{
		output += "[RESOURCE] id => " + std::to_string(resource.id) + " type => " + resource.type + "\n";
	}

	os << output << "\n";
	return os;
}