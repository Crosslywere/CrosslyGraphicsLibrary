#include <CrosslyGL/ResourceManager.hpp>

#include <iostream>

namespace Crossly
{
	std::unordered_map<std::string, std::unique_ptr<Shader>> ResourceManager::s_Shaders;
	std::vector<std::string> ResourceManager::s_DeletedShaders;

	ResourceManager& ResourceManager::GetInstance()
	{
		static ResourceManager instance;
		return instance;
	}

	Shader& ResourceManager::CreateShader(const std::string& rname, const std::initializer_list<unsigned int>& shaders)
	{
		if (s_Shaders.find(rname) == s_Shaders.end())
		{
			std::cout << "Shader with attributed name '" << rname << "' already exists!\n";
			return *s_Shaders.at(rname);
		}
		s_Shaders[rname].reset(new Shader(shaders));
		return *s_Shaders.at(rname);
	}

	Shader& ResourceManager::CreateShader(const std::string& rname, const std::initializer_list<ShaderFile>& shaderFiles)
	{
		const auto iter = std::find(s_DeletedShaders.begin(), s_DeletedShaders.end(), rname);
		if (s_Shaders.find(rname) == s_Shaders.end() && iter != s_DeletedShaders.end())
		{
			std::cout << "Shader with attributed name '" << rname << "' already exists!\n";
			s_DeletedShaders.erase(iter);
			return *s_Shaders.at(rname);
		}
		s_Shaders[rname].reset(new Shader(shaderFiles));
		return *s_Shaders.at(rname);
	}

	Shader& ResourceManager::GetShader(const std::string& rname) const
	{
		if (s_Shaders.find(rname) == s_Shaders.end())
			throw std::runtime_error(("Unable to find shader resource with name '" + rname + "'").c_str());

		return *s_Shaders.at(rname);
	}

	void ResourceManager::DestroyShader(const std::string& rname)
	{
		if (s_Shaders.find(rname) == s_Shaders.end())
			return;

		s_Shaders.at(rname).reset();
		s_DeletedShaders.push_back(rname);
	}

}