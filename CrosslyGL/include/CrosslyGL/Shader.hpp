#pragma once

#include <initializer_list>
#include <string>
#include <unordered_map>

namespace Crossly
{

	struct ShaderFile
	{
		const char* URL;
		unsigned int Type;
	};

	class Shader
	{
	public:
		static unsigned int CompileShaderSource(const char* const source, unsigned int type);
		static unsigned int CompileShaderFile(const char* url, unsigned int type);
		static void DeleteShader(unsigned int shader);
		static bool ValidateShader(unsigned int shader, unsigned int pname);
		static bool ValidateShaderCompileStatus(unsigned int shader);
		static bool ValidateProgram(unsigned int program, unsigned int pname);
		static bool ValidateProgramLinkStatus(unsigned int program_id);
	public:
		Shader(const std::initializer_list<unsigned int>& shader_ids);
		Shader(const std::initializer_list<ShaderFile>& files);
		~Shader();
		void Use() const;
		void SetFloat(const std::string& name, float v0);
		void SetVec2(const std::string& name, float* v);
		void SetVec3(const std::string& name, float* v);
		void SetVec4(const std::string& name, float* v);
	private:
		int GetUniformLocation(const std::string& name);
	private:
		unsigned int m_ProgramID;
		std::unordered_map<std::string, int> m_UniformCache;
	};

}