#pragma once
#include <map>
#include <memory>
#include "Typedefs.h"
#include "Resource.h"

class Shader;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

public:
	std::shared_ptr<Shader> LoadShader(std::string name, std::string vertex, std::string fragmentFile);

	void Clear();

private:
	std::vector<char> ReadFile(std::string& filePath);

	Guid GetGuid(std::string name);

private:
	std::map<Guid, std::shared_ptr<Resource>> m_resources;
};
