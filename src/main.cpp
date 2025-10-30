#include <commands/command.hpp>
#include <context/context.hpp>
#include <application.hpp>
#include <thread>

context::Context applicationContext{};

void process(std::string input)
{
	auto textCommand = command::from(input);
	std::cout << textCommand;

	if (!textCommand.valid)
	{
		std::cout << "[ERROR] Text command is invalid, verify input\n";
	}

	auto command = command::build(textCommand);
	if (command == nullptr)
	{
		std::cout << "[ERROR] Command is invalid, verify input\n";
	}

	if (!command->exec(&applicationContext))
	{
		std::cout << "[ERROR] Could not execute command, verify input\n";
	}
	std::cout << &applicationContext;
}

void processCinAsync()
{
	for (;;)
	{
		std::cin.clear();
		std::string input = "";
		std::getline(std::cin, input);
		std::cout << input;
		std::cout.flush();
	}
}

/**
 * Console process to parse commands
 *
 * Commands
 * quit : exit the current process
 *
 * Image part ---
 * load : load a file at a given path, extract and save metadata
 * Snap : Export current framebuffer for a given period
 * palette : create a color palette that can be reused
 *
 */
int main(int argc, char *argv[])
{

	// Start console process in background

	// Listen for input
	// On input, parse and apply command
	// Notify window of change
	// Update

	auto cin = std::thread(processCinAsync);
	cin.detach();

	auto window = application::setup("Labo 4", 800, 800);
	if (window == nullptr)
	{
		std::cout << "There was an error initializing the window";
		std::cout.flush();
		return -1;
	}

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	std::cout << "Runned \n";
	return 0;
}