#include <CrosslyGL/Window.hpp>

#include <GLFW/glfw3.h>

#include <iostream>

namespace Crossly
{

	GLFWwindow* window;

	void Window::Run(int width, int height, const char* title)
	{
		glfwInit();
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		if (window == nullptr)
		{
			glfwTerminate();
			throw std::runtime_error("glfwCreateWindow failed!");
		}
		glfwMakeContextCurrent(window);

		std::cout << "Running Application!...\n";
		glfwSwapInterval(1);
		while (!glfwWindowShouldClose(window))
		{
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glfwTerminate();
	}

}