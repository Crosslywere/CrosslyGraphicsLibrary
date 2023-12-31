#pragma once

#include <vector>
#include <string>
#include <unordered_map>

namespace Crossly
{

	class Shader
	{
	public:
		static unsigned int CompileShaderSource(const char* const source, unsigned int type);
		static void DeleteShader(unsigned int shader);
		static bool ValidateShader(unsigned int shader, unsigned int pname);
		static bool ValidateShaderCompileStatus(unsigned int shader);
		static bool ValidateProgram(unsigned int program, unsigned int pname);
		static bool ValidateProgramLinkStatus(unsigned int program_id);
	public:
		Shader(const std::vector<unsigned int>& shader_ids);
		~Shader();
		void Use() const;
		void SetFloat(const std::string& name, float v0);
	private:
		int GetUniformLocation(const std::string& name);
	private:
		unsigned int m_ProgramID;
		std::unordered_map<std::string, int> m_UniformCache;
	};

}