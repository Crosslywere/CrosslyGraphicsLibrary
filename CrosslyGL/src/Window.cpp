#include <CrosslyGL/Window.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace Crossly
{

	GLFWwindow* window;

	void Window::Run(Application* app)
	{
		if (app == nullptr)
		{
			throw std::runtime_error("Null pointer passed in as argument to Window::Run()");
		}
		glfwInit();
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		window = glfwCreateWindow(app->GetWidth(), app->GetHeight(), app->GetTitle(), nullptr, nullptr);
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
		std::cout << "Running '" << app->GetTitle() << "'\n";
		app->OnCreate();
		float past = 0.0f;
		while (!glfwWindowShouldClose(window))
		{
			float now = glfwGetTime();
			float delta = now - past;
			past = now;
			app->OnUpdate(delta);
			app->OnRender();
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		app->OnDestroy();
		glfwDestroyWindow(window);
		glfwTerminate();
		std::cout << "Application terminated!\n";
	}

}