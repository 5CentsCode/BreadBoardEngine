#pragma once
#include "Typedefs.h"

#include "Shader.h" // TEMP
#include "Components/Transform.h" // TEMP

enum LightType : uint8
{
	Ambient,
	Directional,
	Point,
	Spotlight
};

namespace Component
{
	struct Light
	{
		LightType Type;
		glm::vec3 Color;

		float Range;
		float Intensity;
		float SpotFalloff;
	};
}