#pragma once
#include <memory>
#include "Resource.h"

class Shader;
class Texture;

class Material : public Resource
{
public:

	Material(Guid guid, std::string name)
		: Resource(guid, name)
	{
	}

	~Material()
	{
	}

public:

	std::shared_ptr<Shader> Shader;
};
