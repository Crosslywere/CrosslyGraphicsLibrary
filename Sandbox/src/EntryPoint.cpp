#include <CrosslyGL/Window.hpp>

#include <exception>
#include <iostream>

#include "Sandbox.hpp"

int main(int argc, char** argv)
{
	Sandbox app;
	try
	{
		Crossly::Window::Run(&app);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "Press Enter to exit...\n";
	std::cin.get();
	return 0;
}