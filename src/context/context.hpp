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

		float red = 0.0f;
		float green = 0.0f;
		float blue = 0.0f;
		float alpha = 0.0f;
	};

	std::ostream &operator<<(std::ostream &os, const Context *context);
}
