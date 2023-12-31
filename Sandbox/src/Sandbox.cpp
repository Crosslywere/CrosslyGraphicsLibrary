#include <CrosslyGL/Window.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class SandboxApp : public Crossly::Application
{
public:
	SandboxApp()
		: Crossly::Application(800, 600, "SandboxApp"), VAO(0), VBO(0), Program(0)
	{
	}

	virtual void OnCreate() override
	{
		glfwSwapInterval(1);
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		float vertices[] =
		{
			0.0f, 0.5f, 0.0f,
			-.5f, -.5f, 0.0f,
			0.5f, -.5f, 0.0f,
		};

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);

		const char* vertShader = 
R"(#version 410 core
layout (location = 0) in vec3 aPos;
void main()
{
	gl_Position = vec4(aPos, 1.0);
})";
		GLuint vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &vertShader, 0);
		glCompileShader(vs);
		const char* fragShader =
R"(#version 410 core
layout (location = 0) out vec4 oColor;
void main()
{
	oColor = vec4(0.5, 0.8, 0.1, 1.0);
})";
		GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, &fragShader, 0);
		glCompileShader(fs);
		Program = glCreateProgram();
		glAttachShader(Program, vs);
		glAttachShader(Program, fs);
		glLinkProgram(Program);
	}

	virtual void OnUpdate(float dt) override
	{
	}

	virtual void OnRender() override
	{
		glBindVertexArray(VAO);
		glUseProgram(Program);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	virtual void OnDestroy() override
	{
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
	}
private:
	GLuint VAO, VBO, Program;
};

int main(int argc, char** argv)
{
	SandboxApp app;
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