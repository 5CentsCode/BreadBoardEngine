#pragma once
#include "Typedefs.h"
#include "Mesh.h"
#include "Material.h"

struct Model
{
    std::vector<Mesh> Meshes;
    std::vector<Material> Materials;
};

Model LoadModel(const char* fileName);