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
		LightType Type = LightType::Ambient;

		glm::vec3 Color = glm::vec3(1.0f);

		float Intensity = 1.0f;
		float Angle = 60.0f;
		float Attenuation = .5f;
		float Range = 5.0f;

		// TEMP
		void AddToShader(Transform& transform, Shader& shader)
		{
			shader.SetUniform("Light.Type", (int32)Type);
			shader.SetUniform("Light.Position", transform.GetPosition());
			shader.SetUniform("Light.Direction", transform.GetForward());
			shader.SetUniform("Light.Color", Color);
			shader.SetUniform("Light.Range", Range);
			shader.SetUniform("Light.Angle", Angle);
			shader.SetUniform("Light.Intensity", Intensity);
			shader.SetUniform("Light.Attenuation", Attenuation);
		}
	};
}