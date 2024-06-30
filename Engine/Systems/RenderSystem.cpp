#include "RenderSystem.h"
#include <Windows.h> // TEMP? WINAPI Entry Redef in glad.h
#include <glad/glad.h>
#include "Components/Camera.h"
#include "Components/MeshRenderer.h"
#include "Components/RectTransform.h"
#include "Components/Sprite.h"
#include "Components/Transform.h"
#include "ResourceManager.h"
#include "Shader.h"

EnttSystem::RenderSystem::RenderSystem(Window* window, Mesh* quadMesh)
{
	m_window = window;
	m_quadMesh = quadMesh;
}

EnttSystem::RenderSystem::~RenderSystem()
{
}

void EnttSystem::RenderSystem::Update(entt::registry& registry, float UNUSED_PARAM(deltaTime))
{
	entt::entity cameraEntity = registry.view<Component::Transform, Component::Camera>().front();
	Component::Transform& cameraTransform = registry.get<Component::Transform>(cameraEntity);
	Component::Camera& cameraComponent = registry.get<Component::Camera>(cameraEntity);
	cameraComponent.SetAspectRatio(m_window->GetAspectRatio());

	glm::mat4 projection = cameraComponent.GetProjectionMatrix();
	glm::mat4 view = cameraTransform.GetLookAtMatrix();

	registry.view<Component::Transform, Component::MeshRenderer>()
		.each([&](const entt::entity UNUSED_PARAM(entity), Component::Transform& transform, Component::MeshRenderer& meshRenderer)
	{
		std::shared_ptr<Material> material = meshRenderer.Material;
		std::shared_ptr<Mesh> mesh = meshRenderer.Mesh;

		std::shared_ptr<Shader> shader = material->Bind();
		shader->SetUniform("Projection", projection);
		shader->SetUniform("View", view);
		shader->SetUniform("Model", transform.GetWorldMatrix());

		mesh->Bind();
		glDrawArrays(GL_TRIANGLES, 0, (int)mesh->GetIndexCount());
	});

	float halfWidth = m_window->GetAspectRatio() * m_window->GetHeight() * 0.5f;
	float halfHeight = m_window->GetHeight() * 0.5f;
	glm::mat4 uiCanvas = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, -10.0f, 10.0f);

	registry.view<Component::RectTransform, Component::Sprite>()
		.each([&](const entt::entity UNUSED_PARAM(entity), Component::RectTransform& transform, Component::Sprite& sprite)
	{
		std::shared_ptr<Material> material = sprite.Material;
		std::shared_ptr<Texture> texture = sprite.Texture;

		std::shared_ptr<Shader> shader = material->Bind();

		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, texture->GetId());
		shader->SetUniform("Sprite", 4);
		shader->SetUniform("Projection", uiCanvas);
		shader->SetUniform("Model", transform.GetWorldMatrix());

		m_quadMesh->Bind();
		glDrawArrays(GL_TRIANGLES, 0, (int)m_quadMesh->GetIndexCount());
	});
}
