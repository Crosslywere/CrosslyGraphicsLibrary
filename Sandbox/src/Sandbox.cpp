#include <CrosslyGL/Window.hpp>
#include <CrosslyGL/ResourceManager.hpp>
// TODO: Remove need for glad.h and glfw3.h
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

Crossly::ResourceManager& ResMan = Crossly::ResourceManager::GetInstance();


class SandboxApp : public Crossly::Application
{
public:
	SandboxApp()
		: Crossly::Application(800, 600, "SandboxApp"), VAO(0), VBO(0)
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

		ResMan.CreateShader("shader", { { "res/shader.vert", GL_VERTEX_SHADER }, { "res/shader.frag", GL_FRAGMENT_SHADER } });
	}

	virtual void OnUpdate(float dt) override
	{
	}

	virtual void OnRender() override
	{
		auto& shader = ResMan.GetShader("shader");
		shader.Use();
		shader.SetFloat("t", static_cast<float>(glfwGetTime()));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	virtual void OnDestroy() override
	{
		ResMan.DestroyShader("shader");
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
	}
private:
	GLuint VAO, VBO;
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