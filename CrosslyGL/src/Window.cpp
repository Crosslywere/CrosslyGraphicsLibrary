#include <CrosslyGL/Window.hpp>

#include <glad/glad.h>
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

		if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0)
		{
			glfwDestroyWindow(window);
			glfwTerminate();
			throw std::runtime_error("gladLoadGLLoader failed!");
		}

		std::cout << "Running Application!...\n";
		glfwSwapInterval(1);

		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		
		glfwDestroyWindow(window);
		glfwTerminate();
	}

}