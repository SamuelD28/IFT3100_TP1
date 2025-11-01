#include <context/context.hpp>
#include <cstring>

std::ostream &context::operator<<(std::ostream &os, const context::Context *context)
{
	for (auto resource : context->resources)
	{
		std::cout << "[RESOURCE] id => " + std::to_string(resource.id) + " type => " + resource.type + " path => " + resource.path + "\n";
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

	auto test = reinterpret_cast<const char *>(&this->background);
	std::cout << "size of :" << sizeof(this->background) << std::endl;
	for (int i = 0; i < sizeof(this->background); i++)
	{
		auto c = test[i];
		std::cout << "character - " << c << std::endl;
	}

	file.write(reinterpret_cast<const char *>(&this->background), sizeof(this->background));

	// auto size = this->resources.size();
	// file.write((char *)(&size), sizeof(size));

	// if (size == 0)
	// {
	// 	return true;
	// }

	// file.write((char *)(this->resources.data()), size * sizeof(context::Resource{}));

	file.close();
	return true;
}

context::Context context::Context::deserialize()
{
	auto applicationContext = context::Context{};

	// Should add error cheking if the data cannot be parsed into their respective members
	std::ifstream file("./resources/manifest.bin", std::ios::binary);
	if (!file.is_open())
	{
		return applicationContext;
	}

	if (std::filesystem::file_size("./resources/manifest.bin") == 0)
	{
		return applicationContext;
	}

	file.read(reinterpret_cast<char *>(&applicationContext.background), sizeof(applicationContext.background));

	// size_t size;
	// file.read((char *)&size, sizeof(size));

	// std::cout << size << "HERE \n";
	// applicationContext.resources.resize(size);
	// file.read(reinterpret_cast<char *>(applicationContext.resources.data()), applicationContext.resources.size());

	return applicationContext;
}