#pragma once
#include <Memory>
#include "Material.h"
#include "Mesh.h"

namespace Component
{
	struct MeshRenderer
	{
		std::shared_ptr<Material> Material;
		std::shared_ptr<Mesh> Mesh;
	};
}