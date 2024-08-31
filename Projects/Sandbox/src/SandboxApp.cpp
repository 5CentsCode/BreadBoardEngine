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

std::shared_ptr<Component::Camera> camera;
std::shared_ptr<Component::Transform> cameraTransform;

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

	camera = std::make_shared<Component::Camera>();
	cameraTransform = std::make_shared<Component::Transform>();

	camera->SetFieldOfView(45.0f);
	camera->SetAspectRatio(m_window->GetAspectRatio());
	cameraTransform->SetPosition(glm::vec3(0.0f, 0.0f, -10.0f));

	StaticRenderer::SetCamera(camera, cameraTransform);
}

std::string textInput;

void SandboxApp::Update(float deltaTime)
{
	camera->SetAspectRatio(m_window->GetAspectRatio());

	std::shared_ptr<Shader> spriteShader = ResourceManager::LoadShader("WhiteShader", "", "");

	glm::vec3 cameraMovement = glm::vec3(0.0f);
	if (Input::IsKeyDown(KeyCode::A))
	{
		cameraMovement.x -= 1;
	}
	if (Input::IsKeyDown(KeyCode::D))
	{
		cameraMovement.x += 1;
	}
	if (Input::IsKeyDown(KeyCode::Z))
	{
		cameraMovement.y -= 1;
	}
	if (Input::IsKeyDown(KeyCode::X))
	{
		cameraMovement.y += 1;
	}
	if (Input::IsKeyDown(KeyCode::W))
	{
		cameraMovement.z += 1;
	}
	if (Input::IsKeyDown(KeyCode::S))
	{
		cameraMovement.z -= 1;
	}
	cameraMovement *= deltaTime * 5.0f;
	cameraTransform->SetPosition(cameraTransform->GetPosition() + cameraMovement * 0.5f);

	ImGui::Begin("Camera Info");
	glm::vec3 position = cameraTransform->GetPosition();
	if (ImGui::InputFloat3("Position", (float*)&position))
	{
		cameraTransform->SetPosition(position);
	}
	ImGui::End();

	m_registry.view<Component::Transform, Component::MeshRenderer>()
		.each([&](const entt::entity UNUSED_PARAM(entity), Component::Transform& transform, Component::MeshRenderer& meshRenderer)
		{
			StaticRenderer::RenderMesh(transform, meshRenderer);
		});

	StaticRenderer::RenderLine(glm::vec3(0.0f), glm::vec3(5.0f, 5.0f, 5.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	ImGui::ShowDemoWindow();

	ImGui::Begin("GPU Info");
	ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_FirstUseEver);

	m_minFrameTime = glm::min(m_minFrameTime, 1000.0f / deltaTime);
	m_maxFrameTime = glm::max(m_maxFrameTime, 1000.0f / deltaTime);

	std::rotate(m_frameTimeGraph.begin(), m_frameTimeGraph.begin() + 1, m_frameTimeGraph.end());
	m_frameTimeGraph.back() = 1000.0f / deltaTime;

	ImGui::Text("FPS: %f", 1000.0f / deltaTime);
	ImGui::Text("Min FPS: %f", m_minFrameTime);
	ImGui::Text("Max FPS: %f", m_maxFrameTime);

	ImGui::PlotLines("FPS", &m_frameTimeGraph[0], (int32)m_frameTimeGraph.size(), 0, "", m_minFrameTime, m_maxFrameTime, ImVec2(0, 80));
	ImGui::End();
}

void SandboxApp::Shutdown(void)
{
}
