#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

#include <CrosslyGL/Shader.hpp>

namespace Crossly
{

	class ResourceManager
	{
	public:
		static ResourceManager& GetInstance();
		Shader& CreateShader(const std::string& rname, const std::initializer_list<unsigned int>& shaders);
		Shader& CreateShader(const std::string& rname, const std::initializer_list<ShaderFile>& shaderFiles);
		Shader& GetShader(const std::string& rname) const;
		void DestroyShader(const std::string& rname);
	private:
		inline ResourceManager() {};
		ResourceManager(const ResourceManager&) = delete;
	private:
		static std::unordered_map<std::string, std::unique_ptr<Shader>> s_Shaders;
		static std::vector<std::string> s_DeletedShaders;
	};

}