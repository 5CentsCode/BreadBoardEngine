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
			shader.SetUniform("Lights.Type", (int32)Type);
			shader.SetUniform("Lights.Position", transform.GetPosition());
			shader.SetUniform("Lights.Direction", transform.GetForward());
			shader.SetUniform("Lights.Color", Color);
			shader.SetUniform("Lights.Range", Range);
			shader.SetUniform("Lights.Angle", Angle);
			shader.SetUniform("Lights.Intensity", Intensity);
			shader.SetUniform("Lights.Attenuation", Attenuation);
		}
	};
}