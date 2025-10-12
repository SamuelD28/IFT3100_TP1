#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace application
{
	GLFWwindow *setup(std::string name, unsigned int width, unsigned int height);
	bool start();
	bool exit();
}

#endif