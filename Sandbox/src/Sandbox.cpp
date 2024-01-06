#include "Sandbox.hpp"
#include <CrosslyGL/ResourceManager.hpp>
#include <CrosslyGL/VertexBufferLayout.hpp>

#include <glad/glad.h>
#include <glm/glm.hpp>

using Crossly::VertexArray;
using Crossly::VertexBuffer;
using Crossly::VertexBufferLayout;

static Crossly::ResourceManager& g_Manager = Crossly::ResourceManager::GetInstance();

Sandbox::Sandbox()
	: Crossly::Application(800, 600, "Sandbox App"), f_TotalTime(0.0f)
{
}

void Sandbox::OnCreate()
{
	float vertices[] =
	{
		0.0f, 0.5f, 0.0f,
		-.5f, -.5f, 0.0f,
		0.5f, -.5f, 0.0f,
	};

	p_VertexArray.reset(new VertexArray());
	p_VertexArray->Bind();
	p_VertexBuffer.reset(new VertexBuffer(vertices, sizeof(vertices) / sizeof(float)));
	p_VertexBuffer->Bind();
	VertexBufferLayout layout = {
		{0, 3, 3 * sizeof(float), 0, true}
	};
	layout.SetAttribs();
	g_Manager.CreateShader("shader", { {"res/shader.vert", GL_VERTEX_SHADER}, {"res/shader.frag", GL_FRAGMENT_SHADER} });
}

void Sandbox::OnUpdate(float dt)
{
	f_TotalTime += dt;
}

void Sandbox::OnRender()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glm::vec3 color1 = { 1.0f, 0.5f, 0.0f };
	glm::vec3 color2 = { 0.5f, 0.0f, 1.0f };
	auto shader = g_Manager.GetShader("shader");
	shader.Use();
	shader.SetFloat("t", f_TotalTime);
	shader.SetVec3("color1", &color1.x);
	shader.SetVec3("color2", &color2.x);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Sandbox::OnDestroy()
{
	g_Manager.DestroyShader("shader");
	p_VertexBuffer.reset();
	p_VertexArray.reset();
}