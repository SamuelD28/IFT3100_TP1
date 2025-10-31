#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <color.hpp>

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
		color::RGBA background{};
	};

	std::ostream &operator<<(std::ostream &os, const Context *context);
}
