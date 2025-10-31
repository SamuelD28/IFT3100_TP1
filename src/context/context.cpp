#include <context/context.hpp>

std::ostream &context::operator<<(std::ostream &os, const context::Context *context)
{
	for (auto resource : context->resources)
	{
		std::cout << "[RESOURCE] id => " + std::to_string(resource.id) + " type => " + resource.type + "\n";
	}

	os << "[COLOR] red => " << context->background.red << " green => " << context->background.green << " blue => " << context->background.blue << " alpha => " << context->background.alpha << "\n";
	return os;
}

bool context::Context::serialize() const
{

	std::ofstream file("./resources/manifest.bin", std::ios::binary);
	if (!file.is_open())
	{
		return false;
	}
	file.write(reinterpret_cast<const char *>(this), sizeof(*this));
	file.close();
	return true;
}

context::Context context::Context::deserialize()
{
	context::Context applicationContext{};
	std::ifstream file("./resources/manifest.bin", std::ios::binary);
	if (!file.is_open())
	{
		return applicationContext;
	}
	file.read(reinterpret_cast<char *>(&applicationContext), sizeof(applicationContext));
	file.close();
	return applicationContext;
}