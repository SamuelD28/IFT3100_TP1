#include <string>
#include <vector>
#include <iostream>

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