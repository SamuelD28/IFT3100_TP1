#include <context/context.hpp>

std::ostream &context::operator<<(std::ostream &os, const context::Context *context)
{
	for (auto resource : context->resources)
	{
		std::cout << "[RESOURCE] id => " + std::to_string(resource.id) + " type => " + resource.type + "\n";
	}

	os << "[COLOR] red => " << context->red << " green => " << context->green << " blue => " << context->blue << " alpha => " << context->alpha << "\n";
	return os;
}