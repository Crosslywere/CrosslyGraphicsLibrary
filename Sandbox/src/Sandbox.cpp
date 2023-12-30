#include <CrosslyGL/Window.hpp>
#include <iostream>

int main(int argc, char** argv)
{
	Crossly::Window::Run(800, 600, "Sandbox Application");
	std::cout << "Press Enter to exit...\n";
	std::cin.get();
	return 0;
}