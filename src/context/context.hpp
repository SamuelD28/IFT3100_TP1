#pragma once
#include <string>
#include <vector>
#include <iostream>

namespace context
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

	std::ostream &operator<<(std::ostream &os, const Context *context);
}
