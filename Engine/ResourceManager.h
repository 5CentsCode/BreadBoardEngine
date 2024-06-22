#pragma once
#include <map>
#include <memory>
#include "Typedefs.h"
#include "Resource.h"

class Shader;
class Mesh;
class Texture;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

public:
	std::shared_ptr<Shader> LoadShader(std::string name, std::string vertex, std::string fragmentFile);
	std::shared_ptr<Mesh> LoadMesh(std::string filepath);

	std::shared_ptr<Texture> LoadTexture(std::string filepath);
	std::shared_ptr<Texture> CreateColorTexture(glm::u8vec4 color);
	std::shared_ptr<Texture> CreateColorTexture(glm::vec4 color);

	void Clear();

private:
	std::vector<char> ReadFile(std::string& filePath);

	Guid GetGuid(std::string name);

private:
	std::map<Guid, std::shared_ptr<Resource>> m_resources;
};
