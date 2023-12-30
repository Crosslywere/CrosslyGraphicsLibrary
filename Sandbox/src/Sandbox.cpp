#include <CrosslyGL/Window.hpp>
#include <iostream>

int main(int argc, char** argv)
{
	Crossly::Window::Run(800, 600, "Sandbox Application");
	std::cin.get();
	return 0;
}