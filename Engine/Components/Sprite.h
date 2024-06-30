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
		std::shared_ptr<Material> Material;
	};
}