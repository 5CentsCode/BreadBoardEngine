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
		transform.SetPosition(glm::vec3(((float)i - (meshes.size() * 0.5f)) * 3.0f, 0.0f, 0.0f));
		Component::MeshRenderer& meshRenderer = m_registry.emplace<Component::MeshRenderer>(meshEntity);
		meshRenderer.Mesh = meshes[i];
		meshRenderer.Material = whiteMaterial;
	}

	Component::Transform& cameraTransform = m_editorCamera.GetTransform();
	cameraTransform.SetPosition(glm::vec3(0.0f, 0.0f, 10.0f));
	Component::Camera& camera = m_editorCamera.GetCamera();
	camera.SetAspectRatio(m_window->GetAspectRatio());

	StaticRenderer::SetCamera(&camera, &cameraTransform);
}

std::string textInput;

void SandboxApp::Update(float deltaTime)
{
	m_editorCamera.Update(deltaTime);
	m_editorCamera.GetCamera().SetAspectRatio(m_window->GetAspectRatio());
	m_registry.view<Component::Transform, Component::MeshRenderer>()
		.each([&](const entt::entity UNUSED_PARAM(entity), Component::Transform& transform, Component::MeshRenderer& meshRenderer)
		{
			StaticRenderer::RenderMesh(transform, meshRenderer);
		});

	StaticRenderer::RenderLine(glm::vec3(0.0f), glm::vec3(5.0f, 5.0f, 5.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	std::shared_ptr<Texture> numbersTexture = ResourceManager::LoadTexture(std::string(PROJECT_ASSET_PATH) + "Sprites/Numbers.png");

	ImGui::Begin("GPU Info");
	ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_FirstUseEver);

	ImGui::Text("FPS: %f", 1000.0f / deltaTime);
	ImGui::End();
}

void SandboxApp::Shutdown(void)
{
}
