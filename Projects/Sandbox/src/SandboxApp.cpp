#include <Components/Camera.h>
#include <Components/MeshRenderer.h>
#include <Components/Transform.h>
#include <glm/glm.hpp>
#include <imgui.h>
#include <Input.h>
#include <Shader.h>
#include <Typedefs.h>
#include "SandboxApp.h"

#include <StaticRenderer.h>
#include <Components/Light.h>

SandboxApp::SandboxApp()
	: Application()
{
}

SandboxApp::~SandboxApp()
{
}

void SandboxApp::Initialize(void)
{
	std::shared_ptr<Shader> whiteShader = ResourceManager::LoadShader("WhiteShader", std::string(PROJECT_ASSET_PATH) + "Shaders/White.vert", std::string(PROJECT_ASSET_PATH) + "Shaders/White.frag");
	std::shared_ptr<Material> whiteMaterial = std::make_shared<Material>((Guid)0, "");
	whiteMaterial->Shader = whiteShader;

	std::vector<std::shared_ptr<Mesh>> meshes
	{
		ResourceManager::LoadMesh(std::string(PROJECT_ASSET_PATH) + "Models/cube.obj"),
		ResourceManager::LoadMesh(std::string(PROJECT_ASSET_PATH) + "Models/Cylinder.obj"),
		ResourceManager::LoadMesh(std::string(PROJECT_ASSET_PATH) + "Models/Helix.obj"),
		ResourceManager::LoadMesh(std::string(PROJECT_ASSET_PATH) + "Models/Sphere.obj"),
		ResourceManager::LoadMesh(std::string(PROJECT_ASSET_PATH) + "Models/Torus.obj"),
		ResourceManager::LoadMesh(std::string(PROJECT_ASSET_PATH) + "Models/Quad.obj"),
		ResourceManager::LoadMesh(std::string(PROJECT_ASSET_PATH) + "Models/Quad_Double_Sided.obj")
	};

	for (int32 i = 0; i < meshes.size(); i++)
	{
		entt::entity meshEntity = m_registry.create();
		Component::Transform& transform = m_registry.emplace<Component::Transform>(meshEntity);
		Component::MeshRenderer& meshRenderer = m_registry.emplace<Component::MeshRenderer>(meshEntity);

		glm::vec3 position = glm::vec3(-9.0f + (3.0f * i), 0.0f, 0.0f);

		transform.SetPosition(position);
		meshRenderer.Mesh = meshes[i];
		meshRenderer.Material = whiteMaterial;
	}

	{
		entt::entity lightEntity = m_registry.create();
		Component::Light& light = m_registry.emplace<Component::Light>(lightEntity);
		Component::Transform& transform = m_registry.emplace<Component::Transform>(lightEntity);
		light.Color = glm::vec3(1.0f, 0.0f, 0.0f);
		light.Type = LightType::Directional;
		light.Intensity = 1.0f;
		transform.SetForward(glm::vec3(1.0f, 0.0f, 0.0f));
	}

	{
		entt::entity lightEntity = m_registry.create();
		Component::Light& light = m_registry.emplace<Component::Light>(lightEntity);
		Component::Transform& transform = m_registry.emplace<Component::Transform>(lightEntity);
		light.Color = glm::vec3(0.0f, 1.0f, 0.0f);
		light.Type = LightType::Directional;
		light.Intensity = 1.0f;
		transform.SetForward(glm::vec3(0.0f, -1.0f, 0.0f));
	}

	{
		entt::entity lightEntity = m_registry.create();
		Component::Light& light = m_registry.emplace<Component::Light>(lightEntity);
		Component::Transform& transform = m_registry.emplace<Component::Transform>(lightEntity);
		light.Color = glm::vec3(0.0f, 0.0f, 1.0f);
		light.Type = LightType::Directional;
		light.Intensity = 1.0f;
		transform.SetForward(glm::vec3(-1.0f, 1.0f, -0.5f));
	}

	{
		entt::entity lightEntity = m_registry.create();
		Component::Light& light = m_registry.emplace<Component::Light>(lightEntity);
		Component::Transform& transform = m_registry.emplace<Component::Transform>(lightEntity);
		light.Color = glm::vec3(1.0f);
		light.Type = LightType::Point;
		light.Intensity = 1.0f;
		light.Range = 10.0f;
		transform.SetPosition(glm::vec3(-1.5f, 0.0f, 0.0f));
	}

	{
		entt::entity lightEntity = m_registry.create();
		Component::Light& light = m_registry.emplace<Component::Light>(lightEntity);
		Component::Transform& transform = m_registry.emplace<Component::Transform>(lightEntity);
		light.Color = glm::vec3(1.0f);
		light.Type = LightType::Point;
		light.Intensity = 0.5f;
		light.Range = 10.0f;
		transform.SetForward(glm::vec3(1.5f, 0.0f, 0.0f));
	}

	Component::Transform& cameraTransform = m_editorCamera.GetTransform();
	cameraTransform.SetPosition(glm::vec3(0.0f, 0.0f, 15.0f));
	Component::Camera& camera = m_editorCamera.GetCamera();
	camera.SetFieldOfView(45.0f);

	StaticRenderer::SetCamera(&camera, &cameraTransform);
}

std::string textInput;

void SandboxApp::Update(float deltaTime)
{
	m_editorCamera.Update(deltaTime);
	m_editorCamera.GetCamera().SetAspectRatio(m_window->GetAspectRatio());

	float offset = glm::pi<float>() / 10.0f;
	m_registry.view<Component::Transform, Component::MeshRenderer>()
		.each([&](const entt::entity UNUSED_PARAM(entity), Component::Transform& transform, Component::MeshRenderer& meshRenderer)
		{
			StaticRenderer::RenderMesh(transform, meshRenderer);

			glm::vec3 position = transform.GetPosition();
			float y = glm::sin(((m_totalTime * 2.0f) + ((position.x / 3.0f) * offset))) * 2.0f;

			if (position.x <= -8.9f)
			{
				float scale = (glm::sin(m_totalTime * 5.0f) * 0.5f) + 1.0f;
				transform.SetScale(glm::vec3(scale));
				transform.Rotate(glm::vec3(0.0f, 0.0f, m_deltaTime));
			}

			transform.SetPosition(glm::vec3(position.x, y, position.z));
			transform.Rotate(glm::vec3(0.0f, -deltaTime, 0.0f));
		});

	// StaticRenderer::RenderLine(glm::vec3(0.0f), glm::vec3(5.0f, 5.0f, 5.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}

void SandboxApp::Shutdown(void)
{
}
