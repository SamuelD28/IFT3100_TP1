#include <application.hpp>

namespace application
{
	// void glfwErrorCallback(int errorCode, const char *description)
	// {
	// 	std::cout << "\nAn error occured. errorCode =" << errorCode << " description: " << *description << std::endl;
	// }

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

	bool start()
	{
		return true;
	}

	GLFWwindow *setup(std::string name, unsigned int width, unsigned int height)
	{
		if (!glfwInit())
		{
			return nullptr;
		}

		// glfwSetErrorCallback(glfwErrorCallback);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow *window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
		if (window == NULL)
		{
			return nullptr;
		}

		glfwMakeContextCurrent(window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			return nullptr;
		}

		glEnable(GL_PROGRAM_POINT_SIZE);
		return window;
	}

	bool exit()
	{
		glfwTerminate();
		return true;
	}
}