#pragma once
#include <memory>
#include "Typedefs.h"
#include "Material.h"
#include "Texture.h"

namespace Component
{
	struct Sprite
	{
		std::shared_ptr<Texture> Texture;
		glm::vec3 ColorTint = glm::vec3(1.0f);
	};
}