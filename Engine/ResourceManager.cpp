#include "ResourceManager.h"
#include <filesystem>
#include <fstream>

#include "Shader.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

std::shared_ptr<Shader> ResourceManager::LoadShader(std::string name, std::string vertex, std::string fragmentFile)
{
	Guid guid = GetGuid(name);
	assert(m_resources.find(guid) == m_resources.end());

	std::vector<char> vertexSource = ReadFile(vertex);
	std::vector<char> fragmentSource = ReadFile(fragmentFile);

	std::shared_ptr<Shader> newShader = std::make_shared<Shader>(guid, name, vertexSource, fragmentSource);
	m_resources.emplace(guid, newShader);

	return newShader;
}

void ResourceManager::Clear()
{
	m_resources.clear();
}

std::vector<char> ResourceManager::ReadFile(std::string& filePath)
{
	std::vector<char> buffer;
	bool fileExists = std::filesystem::exists(filePath);
	if (fileExists)
	{
		std::ifstream file(filePath);
		buffer.resize((uint64)std::filesystem::file_size(filePath));
		file.read(buffer.data(), buffer.size());
		file.close();
	}

	return buffer;
}

Guid ResourceManager::GetGuid(std::string name)
{
	std::string lowercaseString = name;
	std::transform(name.begin(), name.end(), lowercaseString.begin(), [](char ch)
	{
		return (char)std::tolower((int32)ch); 
	});
	Guid guid = std::hash<std::string>{}(lowercaseString);
	return guid;
}
