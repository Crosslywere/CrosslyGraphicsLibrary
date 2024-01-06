#pragma once

#include <CrosslyGL/Application.hpp>
#include <CrosslyGL/VertexArray.hpp>
#include <CrosslyGL/VertexBuffer.hpp>

#include <memory>

class Sandbox : public Crossly::Application
{
public:
	Sandbox();
	virtual void OnCreate() override;
	virtual void OnUpdate(float dt) override;
	virtual void OnRender() override;
	virtual void OnDestroy() override;
private:
	float f_TotalTime;
	std::unique_ptr<Crossly::VertexArray> p_VertexArray;
	std::unique_ptr<Crossly::VertexBuffer> p_VertexBuffer;
};