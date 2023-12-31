#include <CrosslyGL/Window.hpp>
#include <CrosslyGL/Shader.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

class SandboxApp : public Crossly::Application
{
public:
	SandboxApp()
		: Crossly::Application(800, 600, "SandboxApp"), VAO(0), VBO(0), Shader(nullptr)
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
		GLuint vs = Crossly::Shader::CompileShaderSource(vertShader, GL_VERTEX_SHADER);
		Crossly::Shader::ValidateShaderCompileStatus(vs);
		const char* fragShader =
R"(#version 410 core
layout (location = 0) out vec4 oColor;
uniform float t;
void main()
{
	float a = cos(t) / 2.0;
	a += 0.5;
	oColor = vec4(0.5, 0.8, a, 1.0);
})";
		GLuint fs = Crossly::Shader::CompileShaderSource(fragShader, GL_FRAGMENT_SHADER);
		Crossly::Shader::ValidateShaderCompileStatus(fs);
		Shader.reset(new Crossly::Shader({ vs, fs }));
		Crossly::Shader::DeleteShader(vs);
		Crossly::Shader::DeleteShader(fs);
	}

	virtual void OnUpdate(float dt) override
	{
	}

	virtual void OnRender() override
	{
		Shader->Use();
		Shader->SetFloat("t", glfwGetTime());
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	virtual void OnDestroy() override
	{
		Shader.reset();
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
	}
private:
	GLuint VAO, VBO;
	std::unique_ptr<Crossly::Shader> Shader;
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