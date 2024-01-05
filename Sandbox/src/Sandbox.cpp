#include <CrosslyGL/Window.hpp>
#include <CrosslyGL/ResourceManager.hpp>
#include <CrosslyGL/VertexArray.hpp>
#include <CrosslyGL/VertexBuffer.hpp>
#include <CrosslyGL/VertexBufferLayout.hpp>
// TODO: Remove need for glfw3.h
#include <glad/glad.h>
#include <iostream>
#include <memory>

Crossly::ResourceManager& g_Manager = Crossly::ResourceManager::GetInstance();

class SandboxApp : public Crossly::Application
{
public:
	SandboxApp()
		: Crossly::Application(800, 600, "SandboxApp"), f_TotalTime(0.0f), p_VertexArray(nullptr), p_VertexBuffer(nullptr)
	{
	}

	virtual void OnCreate() override
	{
		p_VertexArray.reset(new Crossly::VertexArray());
		float vertices[] =
		{
			0.0f, 0.5f, 0.0f,
			-.5f, -.5f, 0.0f,
			0.5f, -.5f, 0.0f,
		};

		p_VertexArray->Bind();
		p_VertexBuffer.reset(new Crossly::VertexBuffer(vertices, sizeof(vertices) / sizeof(float)));
		Crossly::VertexBufferLayout layout = { { 0, 3, sizeof(float) * 3, 0, true } };
		layout.SetAttribs();
		Crossly::VertexArray::Unbind();

		g_Manager.CreateShader("shader", { { "res/shader.vert", GL_VERTEX_SHADER }, { "res/shader.frag", GL_FRAGMENT_SHADER } });
	}

	virtual void OnUpdate(float dt) override
	{
		f_TotalTime += dt;
	}

	virtual void OnRender() override
	{
		glClear(GL_COLOR_BUFFER_BIT);
		auto& shader = g_Manager.GetShader("shader");
		shader.Use();
		shader.SetFloat("t", f_TotalTime);

		p_VertexArray->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	virtual void OnDestroy() override
	{
		g_Manager.DestroyShader("shader");
		p_VertexBuffer.reset();
		p_VertexArray.reset();
	}
private:
	float f_TotalTime;
	std::unique_ptr<Crossly::VertexArray> p_VertexArray;
	std::unique_ptr<Crossly::VertexBuffer> p_VertexBuffer;
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