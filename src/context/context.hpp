#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
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
		bool serialize() const;
		static Context deserialize();
	};

	std::ostream &operator<<(std::ostream &os, const Context *context);

}
