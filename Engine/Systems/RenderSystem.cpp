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

EnttSystem::RenderSystem::RenderSystem(std::shared_ptr<Window> window)
{
	m_window = window;
}

EnttSystem::RenderSystem::~RenderSystem()
{
}

void EnttSystem::RenderSystem::Update(entt::registry& UNUSED_PARAM(registry), float UNUSED_PARAM(deltaTime))
{
	/*
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
		glDrawArrays(GL_TRIANGLES, 0, mesh->GetIndexCount());
	});
	*/

	/*
	float halfWidth = m_window->GetAspectRatio() * m_window->GetHeight() * 0.5f;
	float halfHeight = m_window->GetHeight() * 0.5f;
	glm::mat4 uiCanvas = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, -10.0f, 10.0f);
	std::shared_ptr<Mesh> quadMesh = ResourceManager::LoadMesh(std::string(PROJECT_ASSET_PATH) + "Models/quad.obj");
	std::shared_ptr<Shader> spriteShader = ResourceManager::LoadShader("SpriteShader", std::string(PROJECT_ASSET_PATH) + "Sprite.vert", std::string(PROJECT_ASSET_PATH) + "Sprite.frag");
	spriteShader->Bind();

	// TODO: Find a better place to store the QuadMesh than using a MeshRenderer for rendering Sprites
	registry.view<Component::RectTransform, Component::Sprite>()
		.each([&](const entt::entity UNUSED_PARAM(entity), Component::RectTransform& transform, Component::Sprite& sprite)
	{
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, sprite.Texture->GetId());
		spriteShader->SetUniform("Sprite", 4);
		spriteShader->SetUniform("Projection", uiCanvas);
		spriteShader->SetUniform("Model", transform.GetWorldMatrix());
		spriteShader->SetUniform("ColorTint", sprite.ColorTint);

		quadMesh->Bind();
		glDrawArrays(GL_TRIANGLES, 0, quadMesh->GetIndexCount());
	});
	*/
}
