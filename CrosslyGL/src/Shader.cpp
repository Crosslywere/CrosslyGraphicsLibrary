#include <CrosslyGL/Shader.hpp>

#include <glad/glad.h>

#include <iostream>

namespace Crossly
{

	unsigned int Shader::CompileShaderSource(const char* source, unsigned int type)
	{
		unsigned int shader = glCreateShader(type);
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);
		return shader;
	}

	void Shader::DeleteShader(unsigned int shader)
	{
		glDeleteShader(shader);
	}

	bool Shader::ValidateShader(unsigned int shader, unsigned int pname)
	{
		int success{};
		glGetShaderiv(shader, pname, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			std::cout << infoLog << std::endl;
			return false;
		}
		return true;
	}

	bool Shader::ValidateShaderCompileStatus(unsigned int shader)
	{
		return ValidateShader(shader, GL_COMPILE_STATUS);
	}

	bool Shader::ValidateProgram(unsigned int program, unsigned int pname)
	{
		int success{};
		glGetProgramiv(program, pname, &success);
		if (!success)
		{
			char infoLog[512];
			glGetProgramInfoLog(program, 512, nullptr, infoLog);
			std::cout << infoLog << std::endl;
			return false;
		}
		return true;
	}

	bool Shader::ValidateProgramLinkStatus(unsigned int program)
	{
		return ValidateProgram(program, GL_LINK_STATUS);
	}

	Shader::Shader(const std::vector<unsigned int>& shader_ids)
	{
		m_ProgramID = glCreateProgram();
		for (unsigned int shader_id : shader_ids)
		{
			glAttachShader(m_ProgramID, shader_id);
		}
		glLinkProgram(m_ProgramID);
		ValidateProgramLinkStatus(m_ProgramID);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ProgramID);
	}

	void Shader::Use() const
	{
		glUseProgram(m_ProgramID);
	}

	void Shader::SetFloat(const std::string& name, float v0)
	{
		glUniform1f(GetUniformLocation(name), v0);
	}

	int Shader::GetUniformLocation(const std::string& name)
	{
		if (m_UniformCache.find(name) != m_UniformCache.end())
		{
			return m_UniformCache.at(name);
		}
		int location = glGetUniformLocation(m_ProgramID, name.c_str());
		if (location < 0) std::cout << "Uniform isn't located on compiled shader '" << name << "'\n";
		return m_UniformCache[name] = location;
	}

}