#include "RenderSystem.h"
#include <Windows.h> // TEMP? WINAPI Entry Redef in glad.h
#include <glad/glad.h>
#include "Components/Camera.h"
#include "Components/MeshRenderer.h"
#include "Components/Transform.h"
#include "Shader.h"

EntitySystem::RenderSystem::RenderSystem()
{
}

EntitySystem::RenderSystem::~RenderSystem()
{
}

void EntitySystem::RenderSystem::Update(entt::registry& registry, float UNUSED_PARAM(deltaTime))
{
	entt::entity cameraEntity = registry.view<Component::Transform, Component::Camera>().front();
	Component::Transform& cameraTransform = registry.get<Component::Transform>(cameraEntity);
	Component::Camera& cameraComponent = registry.get<Component::Camera>(cameraEntity);

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
}
