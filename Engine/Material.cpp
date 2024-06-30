#include "Material.h"
#include <glad/glad.h>
#include "Shader.h"
#include "Texture.h"

Material::Material(Guid guid, std::string name)
	: Resource(guid, name)
{
}

Material::~Material()
{
}

void Material::SetShader(std::shared_ptr<Shader> shader)
{
	m_shader = shader;
}

void Material::SetAlbedoTexture(std::shared_ptr<Texture> albedoTexture)
{
	m_albedoTexture = albedoTexture;
}

void Material::SetNormalTexture(std::shared_ptr<Texture> normalTexture)
{
	m_normalTexture = normalTexture;
}

void Material::SetRoughnessTexture(std::shared_ptr<Texture> roughnessTexture)
{
	m_roughnessTexture = roughnessTexture;
}

void Material::SetMetalTexture(std::shared_ptr<Texture> metalTexture)
{
	m_metalTexture = metalTexture;
}

std::shared_ptr<Shader> Material::Bind()
{
	m_shader->Bind();

	if (m_albedoTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_albedoTexture->GetId());
		m_shader->SetUniform("Material.Albedo", 0);
	}

	if (m_normalTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_normalTexture->GetId());
		m_shader->SetUniform("Material.Normal", 1);
	}

	if (m_roughnessTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, m_roughnessTexture->GetId());
		m_shader->SetUniform("Material.Roughness", 2);
	}

	if (m_metalTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, m_metalTexture->GetId());
		m_shader->SetUniform("Material.Metal", 3);
	}

	return m_shader;
}
