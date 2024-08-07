#pragma once
#include <memory>
#include "Resource.h"

class Shader;
class Texture;

class Material : public Resource
{
public:
	Material(Guid guid, std::string name);
	~Material();

public:

	void SetShader(std::shared_ptr<Shader> shader);
	void SetColorTint(glm::vec3 colorTint);
	void SetAlbedoTexture(std::shared_ptr<Texture> albedoTexture);
	void SetNormalTexture(std::shared_ptr<Texture> normalTexture);
	void SetRoughnessTexture(std::shared_ptr<Texture> roughnessTexture);
	void SetMetalTexture(std::shared_ptr<Texture> metalTexture);

	std::shared_ptr<Shader> Bind();

public:

	std::shared_ptr<Shader> m_shader;

	glm::vec3 m_colorTint;
	std::shared_ptr<Texture> m_albedoTexture;
	std::shared_ptr<Texture> m_normalTexture;
	std::shared_ptr<Texture> m_roughnessTexture;
	std::shared_ptr<Texture> m_metalTexture;
};
